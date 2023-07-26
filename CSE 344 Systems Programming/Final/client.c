#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <dirent.h>
#include <netinet/in.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>

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

char * dirname;
int clientfd, number_of_files = 0;
sem_t * semaphore;
FileInfo * files;
pthread_t client;

void readSocket(int clientfd);
void current_files(char * foldername);
void check_files(char * filename);
void send_file(int clientfd, char * folder, sem_t * semaphore);
void send_folder(int clientfd, char * folder, sem_t * semaphore);
void * handleClient();
void removeFileFromFiles(int index);
void addFileToFiles(char currentFile[512], struct stat filestatus, int isDirectory);

int main(int argc, char * argv[]){
    if(argc < 3){
        printf("Insufficient number of arguments...\n");
        return -1;
    }

    dirname = argv[1];

    char sem_name[256];

    sprintf(sem_name, "/%s", dirname);

    semaphore = sem_open(sem_name, O_CREAT, S_IRWXU | S_IRWXO | S_IRWXG, 0);

    int portNumber = atoi(argv[2]);

    struct sockaddr_in serverAddress;

    clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if(clientfd == -1){
        errExit("socket");
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(portNumber);
    if(inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr) == -1){
        errExit("inet_pton");
    }

    if(connect(clientfd, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1){
        errExit("connect");
    }

    printf("THE CLIENT IS CONNECTED TO THE SERVER!\n");

    printf("PLEASE WAIT...\n");

    mkdir(dirname, 0777);

    write(clientfd, sem_name, strlen(sem_name));

    readSocket(clientfd);

    printf("FILES ARE SYNCHRONIZED!\n");

    pthread_create(&client, NULL, handleClient, NULL);

    current_files(dirname);


    while(1){
        sleep(2);

        check_files(dirname);

        for(int i = 0; i < number_of_files; i++){
            if(files[i].isChecked == 0){
                printf("%s is deleted.\n", files[i].filename);

                char message[1024];
                if(files[i].isDirectory){
                    sprintf(message, "DELETEDIR#0000%s", &files[i].filename[strlen(dirname) + 1]);
                }else
                    sprintf(message, "DELETEFILE#0000%s", &files[i].filename[strlen(dirname) + 1]);

                write(clientfd, message, strlen(message));

                sem_wait(semaphore);

                removeFileFromFiles(i);
            }
            else
                files[i].isChecked = 0;
        }
    }

    sem_post(semaphore);

    pthread_join(client, NULL);

    close(clientfd);

    return 0;
}

void readSocket(int clientfd){
    int bytesRead;

    char buffer[10240];

    char prevPath[512] = "", currentPath[512] = "";

    FILE * file = NULL;

    while((bytesRead = read(clientfd, buffer, sizeof(buffer)) > 0)){
        if(strncmp(buffer, "ALLFILESCOPIED", 14) == 0){
            sem_post(semaphore);
            break;
        }
        if(strncmp(buffer, "DIRECTORY#0000", 14) == 0 && strcmp(&buffer[14], "") != 0){
            char path[512];
            sprintf(path, "%s/%.*s", dirname, 350, &buffer[14]);
            mkdir(path, 0777);
        }else if(strncmp(buffer, "FILE#0000", 9) == 0){
            int length = 0;
            for(int i = 0; i < 10240; i++){
                if(buffer[i] == ' '){
                    length = i;
                    break;
                }
            }

            sprintf(currentPath, "%s/%.*s", dirname, length - 9, &buffer[9]);
            
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
        FileInfo * temp = malloc((number_of_files + 1) * sizeof(FileInfo));

        for(int i = 0; i < number_of_files; i++){
            temp[i] = files[i];
        }

        sprintf(temp[number_of_files].filename, "%s/%s", foldername, entry->d_name);

        temp[number_of_files].isChecked = 1;

        stat(temp[number_of_files].filename, &temp[number_of_files].fileStat);

        temp[number_of_files].isDirectory = (entry->d_type == DT_DIR) ? 1 : 0;

        free(files);

        files = temp;

        number_of_files++;

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
                        send_file(clientfd, currentFile, semaphore);
                        files[i].fileStat = filestatus;
                    }
                }
                files[i].isChecked = 1;
                isNew = 0;
                break;
            }
        }
        if(isNew){
            printf("%s is added.\n", currentFile);
            if(entry->d_type == DT_DIR){
                send_folder(clientfd, currentFile, semaphore);
                addFileToFiles(currentFile, filestatus, 1);

            }else{
                send_file(clientfd, currentFile, semaphore);
                addFileToFiles(currentFile, filestatus, 0);
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

void send_file(int clientfd, char * filename, sem_t * semaphore){
    FILE * file = fopen(filename, "r");
    if(file == NULL){
        errExit("fopen");
    }
    char message[10240], buffer[9600];
    
    int bytesRead;

    sprintf(message, "FILE#0000%s", &filename[strlen(dirname) + 1]);

    write(clientfd, message, sizeof(message));

    memset(message, 0, sizeof(message));

    sem_wait(semaphore);

    while((bytesRead = fread(buffer, sizeof(char), sizeof(buffer), file)) > 0){
        sprintf(message, "FILE#0000%s %.*s", &filename[strlen(dirname) + 1], bytesRead, buffer);

        write(clientfd, message, strlen(message));

        memset(message, 0, sizeof(message));

        sem_wait(semaphore);
    }

    sprintf(message, "FILE#9999");

    write(clientfd, message, sizeof(message));

    sem_wait(semaphore);

    fclose(file);
}

void send_folder(int clientfd, char * folder, sem_t * semaphore){
    DIR * dir = opendir(folder);
    if(dir == NULL){
        errExit("opendir");
    }

    char message[512], path[512];

    memset(message, 0, sizeof(message));

    sprintf(message, "DIRECTORY#0000%s", &folder[strlen(dirname)]);

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

void * handleClient(){
    int bytesRead;

    char buffer[10240];

    char prevPath[512] = "", currentPath[512] = "";

    FILE * file = NULL;

    while((bytesRead = read(clientfd, buffer, sizeof(buffer)) > 0)){
        if(strncmp(buffer, "DELETEFILE#0000", 15) == 0){
            char filename[512];

            sprintf(filename, "%s/%.*s", dirname, 496, &buffer[15]);

            remove(filename);

        }else if(strncmp(buffer, "DELETEDIR#0000", 14) == 0){
            printf("REMOVING FOLDERS ARE NOT CURRENTLY SUPPORTED!\n");
        }else if(strncmp(buffer, "DIRECTORY#0000", 14) == 0 && strcmp(&buffer[14], "") != 0){
            char path[512];
            sprintf(path, "%s/%.*s", dirname, 350, &buffer[14]);
            mkdir(path, 0777);
        }else if(strncmp(buffer, "FILE#0000", 9) == 0){
            int length = 0;
            for(int i = 0; i < 10240; i++){
                if(buffer[i] == ' '){
                    length = i;
                    break;
                }
            }

            if(length > 0){

                sprintf(currentPath, "%s/%.*s", dirname, length - 9, &buffer[9]);
                
                if(strcmp(prevPath, currentPath) != 0){

                    file = fopen(currentPath, "w");
                    if(file == NULL){
                        errExit("fopen");
                    }

                    strcpy(prevPath, currentPath);
                }

                fwrite(&buffer[length + 1], sizeof(char), strlen(buffer) - length - 1, file);

                fflush(file);
            }
            
        }else if(strncmp(buffer, "FILE#9999", 9) == 0){
            if(file != NULL)
                fclose(file);

            memset(prevPath, 0, sizeof(prevPath));
        }

        memset(buffer, 0, sizeof(buffer));

        sem_post(semaphore);
    }  
    pthread_exit(NULL);
}

void removeFileFromFiles(int index){
    FileInfo * temp = malloc((number_of_files - 1) * sizeof(FileInfo));
    for(int j = 0; j < number_of_files - 1; j++){
        if(j < index){
            temp[j] = files[j];
        }
        else{
            temp[j] = files[j + 1];
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
