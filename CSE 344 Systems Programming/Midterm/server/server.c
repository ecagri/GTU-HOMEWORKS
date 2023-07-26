#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <wait.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/sem.h>

#define SERVER_FIFO "/tmp/seqnum_sv"
#define KEY 1901042629
#define KEY2 344

union semun{
    int val;
    struct semid_ds *buf;
    unsigned short * array;
};

void errExit(char * errMessage){
    perror(errMessage);
    exit(EXIT_FAILURE);
}

int main(int argc, char * argv[]){
    if(argc < 3)
        errExit("Unsufficient argc");

    int numberOfClients = atoi(argv[2]);

    char * dirName = argv[1];

    char logFile[100];

    char buffer[1024];

    char secondBuffer[1024];

    char pid[2048];

    int fds[2];

    int child;

    int pidArray[3];

    int current = 0;

    char server_fifo[100];

    struct sembuf sembuf_wait = {0, -1, 0};
    struct sembuf sembuf_signal = {0, 1, 0};

    mkdir(dirName, 0777);

    sprintf(server_fifo, "/tmp/%d", getpid());
    
    mkfifo(server_fifo, 0666);

    int fd = open(server_fifo, 0666);

    printf("Server started pid %d\n", getpid());

    printf("Server waiting for clients\n");

    while(1){
        memset(buffer, 0, sizeof(buffer));
        if(read(fd, buffer, sizeof(buffer))> 0){

            sprintf(pid, "%s", buffer);
            strtok(pid, " ");
        
            int ppid = atoi(strtok(strcpy(buffer, &buffer[5]), " "));

            char * connect = strtok(NULL, " ");

            for(int i = 0;; i++){
                if(i == numberOfClients){
                    if(strncmp(connect, "connect", 7) == 0){
                        i = 0;
                    }
                    else{
                        printf("Connection request pid %d... Que FULL\n", ppid);
                        
                        break;

                    }
                    sleep(1);
                }

                if(kill(pidArray[i], 0) != 0){
                    pidArray[i] = 0;
                }
                if(pidArray[i] == 0){
                    pidArray[i] = ppid;
                    current = i;
                    break;
                }
            }        

            child = fork();
            
            if(child == 0){

                int semid = semget(ppid, 1, 0666);
                if(semid < 0)
                    errExit("semget");
                int semid2 = semget(ppid + 1, 1, 0666);
                if(semid2 < 0)
                    errExit("semget");  

                int client_fd;

                if(pidArray[current] == ppid){
                    if(mkfifo(pid, 0666) == -1)
                        errExit("mkfifo");
                    client_fd = open(pid, 0666);
                    if(client_fd < 0){
                        errExit("open");
                    }
                }                 
                
                if(semop(semid, &sembuf_signal, 1) < 0)
                    errExit("semop");

                if(pidArray[current] != ppid){
                    continue;
                }

                sprintf(logFile, "%s/%d", dirName, ppid);

                int fd = open(logFile, O_WRONLY | O_CREAT | O_APPEND, 0644);

                printf("Client pid %d connected as client%d\n", ppid, current + 1);

                while(1){  
                    if(semop(semid2, &sembuf_wait, 1) == -1)
                        errExit("semop");
                    memset(secondBuffer, 0, sizeof(secondBuffer));
                    if(read(client_fd, secondBuffer, sizeof(secondBuffer)) > 0){

                        char log[100];

                        write(fd, secondBuffer, strlen(secondBuffer));

                        write(fd, "\n", 1);

                        pipe(fds);

                        int new_child = fork();

                        if(new_child == 0){

                            dup2(fds[1], STDOUT_FILENO);

                            if(strncmp(secondBuffer, "list", 4) == 0){
                                char * args[] = {"ls", NULL};
                        
                                execv("/bin/ls", args);
                            }

                            else if(strncmp(secondBuffer, "readF", 5) == 0){

                                char * args[] = {"sed", "-n", "", "", NULL};

                                strtok(secondBuffer, " ");

                                args[3] = strtok(NULL, " ");

                                char * lineNumberStr = strtok(NULL, "\n");

                                int lineNumber = 0;

                                if(lineNumberStr != NULL){
                                    lineNumberStr[strlen(lineNumberStr) - 1] = 'p';
                                    args[2] = lineNumberStr;
                                }
                                else{
                                    args[2] = "p";
                                }

                                execv("/bin/sed", args);

                            }

                            else if(strncmp(secondBuffer, "writeT", 6) == 0){
                                char * args[] = {"sed", "-i", "", "", NULL};

                                strtok(secondBuffer, " ");

                                args[3] = strtok(NULL, " ");

                                char * lastArg = strtok(NULL, "\n");

                                char * copy = strdup(lastArg);

                                char * numberstr = strtok(lastArg, " ");

                                int number = atoi(numberstr);

                                if(number == 0 && numberstr != "0"){
                                    args[2] = malloc((4 + strlen(copy)) * sizeof(char));
                                    sprintf(args[2], "$ a\\%s", copy);
                                }
                                else{
                                    args[2] = malloc((strlen(numberstr) + strlen(copy)) * sizeof(char));
                                    copy[0] = 'c';
                                    copy[1] = '\\';
                                    sprintf(args[2], "%s%s", numberstr, copy);
                                }

                                execv("/bin/sed", args);
                            }

                            else if(strncmp(secondBuffer, "download", 8) == 0){
                                char * args[] = {"cp", "", "", NULL};

                                strtok(secondBuffer, " ");
                            
                                args[1] = strtok(NULL, " ");

                                args[2] = strtok(NULL, " ");

                                execv("/bin/cp", args);
                            }

                            else if(strncmp(secondBuffer, "upload", 6) == 0){

                                char * args[] = {"cp", "", ".", NULL};

                                args[1] = malloc(256 * sizeof(char));

                                strtok(secondBuffer, " ");

                                strcpy(args[1], strcat(strtok(NULL, " "), strtok(NULL, " ")));

                                execv("/bin/cp", args);
                            }

                            exit(1);    
                        
                        }
                        else{

                            waitpid(new_child, NULL, 0);

                            char response[10240];

                            memset(response, 0, sizeof(response));
                            
                            if(strncmp(secondBuffer, "writeT", 6) == 0 || strncmp(secondBuffer, "download", 8) == 0 || strncmp(secondBuffer, "upload", 6) == 0){
                                strcpy(response, "Mission accomplished.\n");
                            }else if(strncmp(secondBuffer, "killServer", 10) == 0){
                                printf(">>kill signal from client%d... terminating...\n", current + 1);
                                printf(">>bye\n");
                                fflush(stdout);
                                for(int i = 0; i < 3; i++){
                                    kill(pidArray[i], SIGTERM);
                                }
                            }else if(strncmp(secondBuffer, "quit", 4) == 0){
                                strcpy(response, "Sending write request to server log file\nwaiting for log file...\n");
                            }else if(strncmp(secondBuffer, "help", 4) == 0){
                                strtok(secondBuffer, " ");
                                char * helpAbout = strtok(NULL, "\n");
                                if(helpAbout == NULL){
                                    strcpy(response, "Available commands are:\nhelp, list, readF, writeT, upload, download, quit, killServer\n");
                                }else if(strncmp(helpAbout, "readF", 5) == 0){
                                    strcpy(response, "readF <file> <line #>\n\tdisplay the #th line of the <file>, returns with an error if <file> does not exist\n");
                                }else if(strncmp(helpAbout, "writeT", 6) == 0){
                                    strcpy(response, "writeT <file> <line #> <string>\n\trequest to write the content of “string” to the #th line the <file>, if the line # is not given writes to the end of file. If the file does not exists in Servers directory creates and edits the file at the same time\n");
                                }else if(strncmp(helpAbout, "download", 8) == 0){
                                    strcpy(response, "download <file>\n\trequest to receive <file> from servers directory to client side\n");
                                }else if(strncmp(helpAbout, "upload", 6) == 0){
                                    strcpy(response, "upload <file>\n\tupload the file from the current working directory of client to the servers directory\n");
                                }else if(strncmp(helpAbout, "list", 4) == 0){
                                    strcpy(response, "list\n\tdisplay the list of files in servers directory\n");
                                }else if(strncmp(helpAbout, "quit", 4) == 0){
                                    strcpy(response, "quit\n\tquit\n");
                                }else if(strncmp(helpAbout, "killServer", 10) == 0){
                                    strcpy(response, "killServer\n\tkill the server\n");
                                }else{
                                    strcpy(response, "NO RESPONSE\n");
                                }
                                
                            }else{
                                read(fds[0], response, sizeof(response));
                            }

                            write(client_fd, response, sizeof(response));
                            if(semop(semid2, &sembuf_signal, 1) < 0)
                                errExit("semop");
                        
                        }
                    }
                }
            }
        }
    }

    return 0;
}