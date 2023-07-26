#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <dirent.h>
#include <netinet/in.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

void errExit(char * message){
    perror(message);
    exit(-1);
}

typedef struct{
    int isChecked;
    int isDirectory;
    char filename[512];
    struct stat fileStat;
}FileInfo;

char * directory;
int threadPoolSize, * clients, * clientfds, serverfd, number_of_clients = 0, number_of_files = 0;
pthread_t * threadPool, server;
pthread_mutex_t mutex;
pthread_cond_t condition;
sem_t ** semaphores;
FileInfo * files;

void * handleClient();
void * handleServer();
void send_folder(int clientfd, char * foldername, sem_t * semaphore);
void send_file(int clientfd, char * filename, sem_t * semaphore);
void readSocket(int clientfd, sem_t * semaphore);
void removeDir(char * dirname);
void current_files(char * foldername);
void check_files(char * foldername);
void removeFileFromFiles(int index);
void addFileToFiles(char currentFile[512], struct stat filestatus, int isDirectory);

int main(int argc, char * argv[]){
    if(argc < 4){
        printf("Insufficient number of arguments...\n");
        return -1;
    }

    directory = argv[1];

    threadPoolSize = atoi(argv[2]);

    int portNumber = atoi(argv[3]);

    clientfds = malloc(threadPoolSize * sizeof(int));

    current_files(directory);

    semaphores = malloc(threadPoolSize * sizeof(sem_t*));    

    for(int i = 0; i < threadPoolSize; i++){
        clientfds[i] = 0;
        semaphores[i] = NULL;
    }

    pthread_mutex_init(&mutex, NULL);

    pthread_cond_init(&condition, NULL);

    pthread_create(&server, NULL, handleServer, NULL);

    threadPool = malloc(threadPoolSize * sizeof(pthread_t));

    for(int i = 0; i < threadPoolSize; i++){
        if(pthread_create(&threadPool[i], NULL, handleClient, NULL)){
            errExit("pthread_create");
        }
    }

    struct sockaddr_in serverAddress;

    serverfd = socket(AF_INET, SOCK_STREAM, 0);
    if(serverfd == -1){
        errExit("socket");
    }

    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(portNumber);

    if(bind(serverfd, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1){
        errExit("bind");
    }

    if(listen(serverfd, threadPoolSize) == -1){
        errExit("listen");
    }

    while(1){
        struct sockaddr_in clientAddress;
        socklen_t clientAddressSize = sizeof(clientAddress);
        int clientfd = accept(serverfd, (struct sockaddr*) &clientAddress, &clientAddressSize);
        if(clientfd == -1){
            errExit("connect");
        }

        printf("A CLIENT IS CONNECTED TO THE SERVER!\n");

        pthread_mutex_lock(&mutex);

        int * temp = malloc((number_of_clients + 1) * sizeof(int));

        for(int i = 0; i < number_of_clients; i++){
            temp[i] = clients[i];
        }
        temp[number_of_clients] = clientfd;

        free(clients);

        clients = temp;

        number_of_clients++;

        pthread_mutex_unlock(&mutex);

        pthread_cond_signal(&condition);
    }

    for(int i = 0; i < threadPoolSize; i++){
        pthread_join(threadPool[i], NULL);
    }

    pthread_join(server, NULL);

    pthread_cond_destroy(&condition);

    pthread_mutex_destroy(&mutex);

    close(serverfd);

    free(threadPool);

    return 0;
}

void * handleClient(){
    while(1){
        pthread_mutex_lock(&mutex);
        while(number_of_clients == 0){
            pthread_cond_wait(&condition, &mutex);
        }

        int clientfd = clients[0];
        int * temp = malloc((number_of_clients - 1) * sizeof(int));
        for(int i = 0; i < number_of_clients - 1; i++){
            temp[i] = clients[i+1];
        }

        number_of_clients--;
        free(clients);
        clients = temp;

        char sem_name[100];

        read(clientfd, sem_name, sizeof(sem_name));

        sem_t * semaphore = sem_open(sem_name, O_CREAT, 0);

        for(int i = 0; i < threadPoolSize; i++){
            if(clientfds[i] == 0){
                clientfds[i] = clientfd;
                semaphores[i] = semaphore;
                break;
            }
        }

        pthread_mutex_unlock(&mutex);

        send_folder(clientfd, directory, semaphore);

        write(clientfd, "ALLFILESCOPIED", 14);

        sem_wait(semaphore);

        readSocket(clientfd, semaphore);
    }

    pthread_exit(NULL);
}

void * handleServer(){
    while(1){
        sleep(2);
        check_files(directory);
        for(int i = 0; i < number_of_files; i++){
            if(files[i].isChecked == 0){
                printf("%s is deleted.\n", files[i].filename);

                char message[1024];
                if(files[i].isDirectory){
                    sprintf(message, "DELETEDIR#0000%s", &files[i].filename[strlen(directory) + 1]);
                }else
                    sprintf(message, "DELETEFILE#0000%s", &files[i].filename[strlen(directory) + 1]);

                for(int i = 0; i < threadPoolSize; i++){
                    if(clientfds[i] != 0){
                        write(clientfds[i], message, strlen(message));

                        sem_wait(semaphores[i]);
                    }
                }

                removeFileFromFiles(i);
            }
            else
                files[i].isChecked = 0;
        }
        sleep(2);
    }
    pthread_exit(NULL);
}

void send_folder(int clientfd, char * folder, sem_t * semaphore){
    DIR * dir = opendir(folder);
    if(dir == NULL){
        errExit("opendir");
    }

    char message[512], path[512];

    memset(message, 0, sizeof(message));

    sprintf(message, "DIRECTORY#0000%s", &folder[strlen(directory)]);

    write(clientfd, message, sizeof(message));

    sem_wait(semaphore);

    struct dirent * entry;

    while((entry = readdir(dir)) != NULL){
        if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0){
            continue;
        }
        sprintf(path, "%s/%s", folder, entry->d_name);
        
        if(entry->d_type == DT_DIR){
            send_folder(clientfd, path, semaphore);
        }else{
            send_file(clientfd, path, semaphore);
        }
    }

    closedir(dir);
}

void send_file(int clientfd, char * filename, sem_t * semaphore){
    FILE * file = fopen(filename, "r");
    if(file == NULL){
        errExit("fopen");
    }
    char message[10240], buffer[9600];
    
    int bytesRead;

    sprintf(message, "FILE#0000%s", &filename[strlen(directory) + 1]);

    write(clientfd, message, sizeof(message));

    memset(message, 0, sizeof(message));

    sem_wait(semaphore);

    while((bytesRead = fread(buffer, sizeof(char), sizeof(buffer), file)) > 0){
        sprintf(message, "FILE#0000%s %.*s", &filename[strlen(directory) + 1], bytesRead, buffer);

        write(clientfd, message, strlen(message));

        memset(message, 0, sizeof(message));

        sem_wait(semaphore);
    }

    sprintf(message, "FILE#9999");

    write(clientfd, message, sizeof(message));

    sem_wait(semaphore);

    fclose(file);
}

void readSocket(int clientfd, sem_t * semaphore){
    int bytesRead;

    char buffer[10240];

    char prevPath[512] = "", currentPath[512] = "";

    FILE * file = NULL;

    while((bytesRead = read(clientfd, buffer, sizeof(buffer))) > 0){
        if(strncmp(buffer, "DELETEFILE#0000", 15) == 0){
            char filename[512];

            sprintf(filename, "%s/%.*s", directory, 496, &buffer[15]);

            remove(filename);

        }else if(strncmp(buffer, "DELETEDIR#0000", 14) == 0){
            printf("REMOVING FOLDERS ARE NOT CURRENTLY SUPPORTED!\n");
        }else if(strncmp(buffer, "DIRECTORY#0000", 14) == 0 && strcmp(&buffer[14], "") != 0){
            char path[512];
            sprintf(path, "%s/%.*s", directory, 350, &buffer[14]);
            mkdir(path, 0777);
        }else if(strncmp(buffer, "FILE#0000", 9) == 0){
            int length = 0;
            for(int i = 0; i < 10240; i++){
                if(buffer[i] == ' '){
                    length = i;
                    break;
                }
            }

            sprintf(currentPath, "%s/%.*s", directory, length - 9, &buffer[9]);
            
            if(strcmp(prevPath, currentPath) != 0){
                file = fopen(currentPath, "w");
                if(file == NULL){
                    errExit("fopen");
                }

                strcpy(prevPath, currentPath);
            }

            fwrite(&buffer[length + 1], sizeof(char), strlen(buffer) - length - 1, file);

            fflush(file);
            
        }else if(strncmp(buffer, "FILE#9999", 9) == 0){
            fclose(file);

            memset(prevPath, 0, sizeof(prevPath));

        }

        memset(buffer, 0, sizeof(buffer));

        sem_post(semaphore);
    }  

}

void current_files(char * foldername){
    DIR * dir = opendir(foldername);
    if(dir == NULL){
        errExit("opendir");
    }

    struct dirent * entry;

    while((entry = readdir(dir)) != NULL){
        if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0){
            continue;
        }

        char filename[512];

        struct stat filestatus;

        int isDirectory = (entry->d_type == DT_DIR) ? 1: 0;

        sprintf(filename, "%s/%s", foldername, entry->d_name);

        stat(filename, &filestatus);

        addFileToFiles(filename, filestatus, isDirectory);

        if(entry->d_type == DT_DIR){
            char path[512];

            sprintf(path, "%s/%s", foldername, entry->d_name);

            current_files(path);

        }
    }

    closedir(dir);
}

void check_files(char * foldername){
    DIR * dir = opendir(foldername);
    if(dir == NULL){
        errExit("opendir");
    }

    struct dirent * entry;

    while((entry = readdir(dir)) != NULL){
        if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0){
            continue;
        }
        char currentFile[512];

        int isNew = 1;

        struct stat filestatus;

        sprintf(currentFile, "%s/%s", foldername, entry->d_name);

        stat(currentFile, &filestatus);

        for(int i = 0; i < number_of_files; i++){
            if(strcmp(files[i].filename, currentFile) == 0){
                if(entry->d_type != DT_DIR){
                    int difference = files[i].fileStat.st_mtime - filestatus.st_mtime;
                    if(difference > 5 || difference < -5){
                        printf("%s is updated.\n", currentFile);
                        for(int i = 0; i < threadPoolSize; i++){
                            if(clientfds[i] != 0){
                                send_file(clientfds[i], currentFile, semaphores[i]);
                            }
                        }
                        files[i].fileStat = filestatus;
                    }
                }
                files[i].isChecked = 1;
                isNew = 0;
                break;
            }
        }
        if(isNew){
            if(entry->d_type == DT_DIR){
                addFileToFiles(currentFile, filestatus, 1);

            }else{
                addFileToFiles(currentFile, filestatus, 0);
            }
            printf("%s is added.\n", currentFile);
            for(int i = 0; i < threadPoolSize; i++){
                if(clientfds[i] != 0){
                    if(entry->d_type == DT_DIR){
                        send_folder(clientfds[i], currentFile, semaphores[i]);
                    }else{
                        send_file(clientfds[i], currentFile, semaphores[i]);
                    }
                }
            }
        }

        if(entry->d_type == DT_DIR){
            char path[512];

            sprintf(path, "%s/%s", foldername, entry->d_name);

            check_files(path);

        }
    }

    closedir(dir);
}

void removeFileFromFiles(int index){
    FileInfo * temp = malloc((number_of_files - 1) * sizeof(FileInfo));
    for(int j = 0; j < number_of_files - 1; j++){
        if(j < index){
            sprintf(temp[j].filename, "%s", files[j].filename);
            temp[j].fileStat = files[j].fileStat;
            temp[j].isChecked = files[j].isChecked;
            temp[j].isDirectory = files[j].isDirectory;
        }
        else{
            sprintf(temp[j].filename, "%s", files[j+1].filename);
            temp[j].fileStat = files[j+1].fileStat;
            temp[j].isChecked = files[j+1].isChecked;
            temp[j].isDirectory = files[j+1].isDirectory;
        }
    }
    free(files);
    files = temp;
    number_of_files--;
}

void addFileToFiles(char currentFile[512], struct stat filestatus, int isDirectory){
    FileInfo * temp = malloc((number_of_files + 1) * sizeof(FileInfo));
    for(int j = 0; j < number_of_files; j++){
        temp[j] = files[j];
    }

    strcpy(temp[number_of_files].filename, currentFile);
    temp[number_of_files].fileStat = filestatus;
    temp[number_of_files].isChecked = 1;
    temp[number_of_files].isDirectory = isDirectory;

    free(files);
    files = temp;
    number_of_files++;
}
