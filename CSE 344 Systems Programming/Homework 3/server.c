#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <dirent.h>

typedef struct Task{
    void (*task_func)(void*);
    void * request;
}Task;

void task_func(void *);

void add(Task);

void * start();

void errExit(char *);

void SIGINTHandler(int);

int server_fifo, server_pid, curClients = 0, number_of_tasks = 0;
Task taskQue[256]; 
pthread_mutex_t mutex;
pthread_cond_t cond;


int main(int argc, char * argv[]){

    char FIFO[1024], buffer[10240], fifoKeyServer[100], fifoKeyClient[100];;

    if(argc < 4)
        errExit("Insufficient argc");

    char * dirname = argv[1];

    int number_of_clients = atoi(argv[2]), number_of_threads = atoi(argv[3]),  current = 0, *clients = (int *) malloc(number_of_clients * sizeof(int));

    server_pid = getpid();

    sprintf(fifoKeyServer, "/tmp/%d", getpid());

    printf(">>Server started with PID %d\n>>Waiting for clients...\n", getpid());

    if(mkfifo(fifoKeyServer, 0666) > 0){ /* Create fifo for server. */
        errExit("mkfifo");
    }

    server_fifo = open(fifoKeyServer, O_RDONLY); /* Open the fifo in read mode. */
    if(server_fifo < 0)
        errExit("open");

    signal(SIGINT, SIGINTHandler);

    while(1){
        memset(FIFO, 0, sizeof(FIFO));

        if(read(server_fifo, FIFO, sizeof(FIFO)) > 0){ /* Read the server fifo. */

            int client_pid = atoi(strtok(FIFO, " "));

            char * connect = strtok(NULL, " ");
        
            for(int i = 0;; i++){ /* Find available spot for the client. */
                int position = i % number_of_clients;
                if(kill(clients[position], 0) != 0)
                    clients[position] = 0;

                if(clients[position] == 0){
                    clients[position] = client_pid;
                    current = position;
                    curClients++;
                    break;
                }

                if(i == number_of_clients - 1){
                    printf(">>Client PID %d cannot be connected to server. Que is FULL!\n", client_pid);
                    fflush(stdout);
                    if(strncmp(connect, "connect", 7) != 0){
                        kill(client_pid, SIGTERM);
                        break;
                    }
                }

                if(position == number_of_clients)
                    sleep(1);
            }

            if(clients[current] != client_pid) /* Check whether client can connected to the server. */
                continue;

            printf(">>Client PID %d is connected to server as client%d.\n", client_pid, curClients);

            sprintf(fifoKeyClient, "/tmp/%d", client_pid);

            int client_fifo = open(fifoKeyClient, O_RDONLY);

            int child = fork();
            if(child < 0)
                errExit("fork");
            else if(child == 0){
                pthread_t threadPool[number_of_threads];
                pthread_mutex_init(&mutex, NULL);
                for(int i = 0; i < number_of_threads; i++){
                    if(pthread_create(&threadPool[i], NULL, &start, buffer) != 0){
                        errExit("phread_create");
                    }
                }
                
                while(1){
                    memset(buffer, 0, sizeof(buffer));

                    if(read(client_fifo, buffer, sizeof(buffer)) > 0){
                        Task task = {.task_func = &task_func};
                        task.request = (char *) malloc(sizeof(buffer));
                        strcpy(task.request, buffer);
                        add(task);
                    }
                }
                pthread_mutex_destroy(&mutex);
            }else{
            }
            
        }
    }

    close(server_fifo);

    return 0;
}

void task_func(void * request){
    char response[256];

    char fifoKeyClient[100];

    sprintf(fifoKeyClient, "/tmp/%d%s", server_pid, strtok(request, " "));

    char * command = strtok(NULL, "\n");

    int client_fifo = open(fifoKeyClient, O_WRONLY);
    if(client_fifo < 0)
        errExit("open");

    if(strncmp(command, "readF", 5) == 0){
        strtok(command, " ");

        char * filename = strtok(NULL, " ");

        char * lineNumberStr = strtok(NULL, "\n");

        FILE * file = fopen(filename, "r");
        if(file == NULL)
            errExit("fopen");

        if(lineNumberStr == NULL){
            fseek(file, 0, SEEK_END);
            int file_length = ftell(file);
            rewind(file);

            char * fileContent = (char *) malloc((file_length + 1) * sizeof(char));
            
            fread(fileContent, file_length, 1, file);

            fileContent[file_length] = '\0';

            write(client_fifo, fileContent, strlen(fileContent));

            free(fileContent);
        }else{
            char line[256];
            int lineNumber = atoi(lineNumberStr);
            int counter = 0;

            while(fgets(line, sizeof(line), file) != NULL){
                if(counter == lineNumber){
                    write(client_fifo, line, strlen(line));
                    break;
                }
                counter++;
            }
        }

        fclose(file);
    }
    else if(strncmp(command, "writeT", 6) == 0){
        strtok(command, " ");

        char * filename = strtok(NULL, " ");

        char * lineNumberStr = strtok(NULL, " ");

        char * string = strtok(NULL, "\n");

        int lineNumber = atoi(lineNumberStr);

        if(lineNumber == 0 && strcmp(lineNumberStr, "0") != 0){
            FILE * file = fopen(filename, "a+");
            if(file == NULL)
                errExit("fopen");

            fprintf(file, "%s %s", lineNumberStr, string);
            fclose(file);
        }else{
            char line[256];
            int current = 0, position = 0;

            FILE * file = fopen(filename, "r");
            if(file == NULL)
                errExit("fopen");

            FILE * tmp = fopen("temp.txt", "w");
            if(tmp == NULL)
                errExit("tmpfile");

            while(fgets(line, sizeof(line), file) != NULL){
                if(current != lineNumber){
                    fputs(line, tmp);                    
                }
                else{
                    fprintf(tmp, "%s\n", string);
                }
                current++;
            }
            fclose(file);
            fclose(tmp);

            remove(filename);
            rename("temp.txt", filename);

        }

        strcpy(response, "Task is Completed!\n");
        
        write(client_fifo, response, sizeof(response));
    }
    else if(strncmp(command, "help", 4) == 0){
        strtok(command, " ");
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
        }
        else{
            strcpy(response, "Command not written properly.\n");
        }
        write(client_fifo, response, sizeof(response));
    }
    else if(strncmp(command, "upload", 4) == 0){
        strtok(command, " ");

        char * filename = strtok(NULL, " ");

        char * path = strtok(NULL, "\n");

        char exactPath[124], line[256];

        sprintf(exactPath, "%s/%s", path, filename);

        FILE * fileOriginal = fopen(exactPath, "r");
        if(fileOriginal == NULL)
            errExit("fopen");

        FILE * fileNew = fopen(filename, "w");
        if(fileNew == NULL)
            errExit("fopen");

        while(fgets(line, sizeof(line), fileOriginal) != NULL){
            fputs(line, fileNew);
        }
        
        fclose(fileOriginal);

        fclose(fileNew);

        strcpy(response, "Task is Completed!\n");
        
        write(client_fifo, response, sizeof(response));

    }else if(strncmp(command, "download", 8) == 0){
        strtok(command, " ");

        char * filename = strtok(NULL, " ");

        char * path = strtok(NULL, "\n");

        char exactPath[124], line[256];

        sprintf(exactPath, "%s/%s", path, filename);

        FILE * fileOriginal = fopen(filename, "r");
        if(fileOriginal == NULL)
            errExit("fopen");

        FILE * fileNew = fopen(exactPath, "w");
        if(fileNew == NULL)
            errExit("fopen");

        while(fgets(line, sizeof(line), fileOriginal) != NULL){
        perror(line); 
            fputs(line, fileNew);
        }
        
        fclose(fileOriginal);

        fclose(fileNew);

        strcpy(response, "Task is Completed!\n");
        
        write(client_fifo, response, sizeof(response));

    }else if(strncmp(command, "quit", 4) == 0){
        strcpy(response, "Sending write request to server log file.\nWaiting for log file\nLog file write request granted\nbye...\n");

        write(client_fifo, response, sizeof(response));

        printf(">>client%d disconnected...\n", curClients);

        kill(getpid(), SIGKILL);
    }else if(strncmp(command, "killServer", 10) == 0){
        printf(">>Kill signal from client%d...Terminating...\n>>Bye...\n", curClients);
        kill(0, SIGKILL);
    }
    else if(strncmp(command, "list", 4) == 0){
        DIR * direct = opendir(".");
        struct dirent * entry;
        char files[1024];
        if(direct == NULL)
            errExit("opendir");

        while((entry = readdir(direct)) != NULL){
            strcat(files, entry->d_name);
            strcat(files, "\n");
        }
        write(client_fifo, files, sizeof(files));

        closedir(direct);
    }else{
        strcpy(response, "Command not written properly.\n");
        
        write(client_fifo, response, sizeof(response));
    }
}

void add(Task task){
    pthread_mutex_lock(&mutex);
    taskQue[number_of_tasks] = task;
    number_of_tasks++;
    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&cond);
}

void * start(){
    while(1){
        pthread_mutex_lock(&mutex);

        while(number_of_tasks == 0){
            pthread_cond_wait(&cond, &mutex);
        }

        Task task = taskQue[0];

        for(int i = 0; i < number_of_tasks - 1; i++){
            taskQue[i] = taskQue[i + 1];
        }
        number_of_tasks -= 1;

        pthread_mutex_unlock(&mutex);

        task.task_func(task.request);
    }
}

void errExit(char * message){
    perror(message);
    exit(0);
}

void SIGINTHandler(int signal){
    close(server_fifo);
    exit(0);
}