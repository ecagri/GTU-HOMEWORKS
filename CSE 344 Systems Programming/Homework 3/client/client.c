#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>

void errExit(char *);

void SIGINTHandler(int);

int clientRead, clientWrite;

int main(int argc, char * argv[]){

    char buffer[256], response[102400], task[1024], KeyServer[100] ,KeyClientRead[100], KeyClientWrite[100];

    if(argc < 3)
        errExit("Insufficient argc");

    char * connect = argv[1];

    char * server_pid = argv[2];

    sprintf(KeyServer, "/tmp/%s", server_pid); /* Fifo name for server. */

    sprintf(KeyClientWrite, "/tmp/%d", getpid()); /* Fifo name for client to write. */

    sprintf(KeyClientRead, "/tmp/%s%d", server_pid, getpid()); /* Fifo name for client to read. */

    signal(SIGINT, SIGINTHandler);

    int serverWrite = open(KeyServer, O_WRONLY); /* Connect to server fifo. */
    if(serverWrite < 0)
        errExit("open");
    
    if(mkfifo(KeyClientWrite, 0666) < 0) /* Create fifo for client. */
        errExit("mkfifo");

    clientWrite = open(KeyClientWrite, O_RDWR); /* Open the fifo to write to server. */
    if(clientWrite < 0)
        errExit("open");
    
    if(mkfifo(KeyClientRead, 0666) < 0) /* Create fifo for client. */
        errExit("mkfifo");

    clientRead = open(KeyClientRead, O_RDWR); /* Open the fifo to write to server. */
    if(clientRead < 0)
        errExit("open");

    sprintf(buffer, "%d %s", getpid(), connect);

    write(serverWrite, buffer, sizeof(buffer)); /* Send PID of the client to the server fifo. */

    while(strncmp(buffer, "quit", 4) != 0){

        printf(">>");

        fgets(buffer, sizeof(buffer), stdin);

        if(strncmp(buffer, "upload", 6) == 0 || strncmp(buffer, "download", 8) == 0){
            char cwd[256];
            getcwd(cwd, sizeof(cwd));
            buffer[strlen(buffer) - 1] = '\0';
            sprintf(task, "%d %s %s", getpid(), buffer, cwd);
        }else
            sprintf(task, "%d %s", getpid(), buffer);

        write(clientWrite, task, sizeof(task));

        memset(response, 0, sizeof(response));
 
        read(clientRead, response, sizeof(response));   

        printf("%s", response);
    };

    close(clientWrite);

    close(clientWrite);

    return 0;
}

void errExit(char * message){
    perror(message);
    exit(0);
}

void SIGINTHandler(int signal){
    char buffer[100];
    sprintf(buffer, "%d quit", getpid());
    write(clientWrite, buffer, sizeof(buffer));
    sleep(1);
    close(clientWrite);
    close(clientRead);
    exit(0);
}