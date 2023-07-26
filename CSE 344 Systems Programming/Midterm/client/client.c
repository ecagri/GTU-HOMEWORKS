#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
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

    int serverPid = atoi(argv[2]);

    char * option = argv[1];

    char buffer[10240];

    char line[512];

    char pid[100];

    char cwd[100];

    char server_fifo[100];

    struct sembuf sembuf_wait = {0, -1, 0};
    struct sembuf sembuf_signal = {0, 1, 0};

    union semun semun_val;
    union semun semun_val2;

    sprintf(server_fifo, "/tmp/%d", serverPid);

    int semid = semget(getpid(), 1, IPC_CREAT | 0666);
    if(semid < 0)
        errExit("semget");

    semun_val.val = 0;
    if(semctl(semid, 0, SETVAL, semun_val) < 0)
        errExit("semctl");

    int semid2 = semget(getpid()+1, 1, IPC_CREAT | 0666);
    if(semid2 < 0)
        errExit("semget");

    semun_val2.val = 0;
    if(semctl(semid2, 0, SETVAL, semun_val2) < 0)
        errExit("semctl");

    printf("Waiting for Que...\n");

    sprintf(pid, "/tmp/%d %s", getpid(), option);

    int fd = open(server_fifo, 0666);
    if(fd < 0)
        errExit("open");

    write(fd, pid, strlen(pid));

    strcpy(pid, strtok(pid, " "));

    if(semop(semid, &sembuf_wait, 1) == -1)
            errExit("semop");

    int client_fd = open(pid, 0666);
    if(client_fd < 0)
        exit(0);

    printf("Connection established!\n");

    memset(buffer, 0, strlen(buffer));

    while(strncmp(line, "quit", 4) != 0){

        printf(">>");

        memset(line, 0, strlen(line));

        fgets(line, sizeof(line), stdin);

        line[strlen(line) - 1] = ' ';

        if(strncmp(line, "upload", 6) == 0 || strncmp(line, "download", 8) == 0){
            getcwd(cwd, sizeof(cwd));
            sprintf(buffer, "%s%s/", line, cwd);
        }else{
            sprintf(buffer, "%s", line);
        }

        write(client_fd, buffer, strlen(buffer));

        if(semop(semid2, &sembuf_signal, 1) < 0)
            errExit("semop");

        if(semop(semid2, &sembuf_wait, 1) == -1)
            errExit("semop");
        
        memset(buffer, 0, sizeof(buffer));

        read(client_fd, buffer, sizeof(buffer));

        printf("%s", buffer);
    }

    return 0;
}