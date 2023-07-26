#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <pthread.h>
#include <signal.h>

char ** buffer;
int out = 0, count = 0, buffer_size, done = 0, number_of_consumers, sigint = 0, number_of_dir, regular_files = 0, directories = 0;
long long int bytes = 0;
pthread_cond_t notFull, notEmpty;
pthread_mutex_t mutex;
pthread_t producer, *consumers;

void produce_item(DIR *, DIR *, char *, char *);
void * consume();
void * produce(void *);


void SIGINTHandler(){
    pthread_mutex_lock(&mutex);
    sigint = 1;
    pthread_mutex_unlock(&mutex);
    for(int i = 0; i < number_of_consumers; i++){
        pthread_join(consumers[i], NULL);
    }
    pthread_join(producer, NULL);
    free(consumers);
    free(buffer);

    pthread_cond_destroy(&notEmpty);
    pthread_cond_destroy(&notFull);

    exit(0);
}

void* produce(void * argv){
    char ** pathnames = (char **) argv;
    char * source = pathnames[3];

    if(!done){
        for(int i = 0; i < number_of_dir; i++){
            DIR * directory = opendir(source);

            if(!directory){

                pthread_mutex_lock(&mutex);
                
                done = 1;

                pthread_mutex_unlock(&mutex);

                printf("%s directory couldn't opened successfully.\n", source);

            }
            char * destination = pathnames[4 + i];
            DIR * destinationDir = opendir(destination);
            produce_item(directory, destinationDir, source, destination);
        }
    }

    pthread_mutex_lock(&mutex);
    
    done = 1;

    pthread_mutex_unlock(&mutex);

    for(int i = 0; i < number_of_consumers; i++){
        pthread_cond_signal(&notEmpty);
    }

    pthread_exit(NULL);  

}

void produce_item(DIR * directory, DIR * destinationDir, char * source, char * destination){
    if(!destinationDir){
        if(mkdir(destination, 0777) == -1)
            return;
    }

    struct dirent * files;

    while((files = readdir(directory)) != NULL && !sigint){
        char * sourceFilePath = malloc(2 * (strlen(source) + strlen(files->d_name)) * sizeof(char));
        char * destinationFilePath = malloc(2 * (strlen(destination) + strlen(files->d_name)) * sizeof(char));

        sprintf(sourceFilePath, "%s/%s",source, files->d_name);
        sprintf(destinationFilePath, "%s/%s", destination, files->d_name);
        if(files->d_type == DT_REG){
            int sourceFile = open(sourceFilePath, O_RDONLY, 0666);
            if(sourceFile == -1){
                printf("An error happened when opening source file: %s\n", files->d_name);
                continue;
            }
            int destinationFile = open(destinationFilePath, O_WRONLY | O_CREAT | O_TRUNC | O_NONBLOCK, S_IRWXU | S_IRWXO | S_IRWXG);
            if(destinationFile == -1){
                close(sourceFile);
                printf("An error happened when creating destionation file: %s\n", files->d_name);
                continue;
            }
            regular_files++;
            pthread_mutex_lock(&mutex);

            while(count == buffer_size){
                pthread_cond_wait(&notFull, &mutex);
            }

            buffer[count] = malloc(1024 * sizeof(char));

            sprintf(buffer[count], "%s %d %s %d", sourceFilePath, sourceFile, destinationFilePath, destinationFile);

            count++;

            pthread_cond_signal(&notEmpty);
            pthread_mutex_unlock(&mutex);

        }else if(files->d_type == DT_DIR && strncmp(files->d_name, "..", 2) != 0 && strncmp(files->d_name, ".", 1) != 0){
            directories++;
            DIR * newDirectory = opendir(sourceFilePath);

            DIR * newDestinationDir = opendir(destinationFilePath);

            produce_item(newDirectory, newDestinationDir, sourceFilePath, destinationFilePath);
        }
        free(sourceFilePath);
        free(destinationFilePath);
    }  

    //printf("%s directory copied succesfully.\n", source);
    closedir(directory);
    closedir(destinationDir);

}

void* consume(){

    while(!sigint){

        pthread_mutex_lock(&mutex);

        while(count == 0 && !done){
            pthread_cond_wait(&notEmpty, &mutex);
        }
        if(count == 0 && done){
            pthread_mutex_unlock(&mutex);
            pthread_exit(NULL);
        }

        char * sourceFilePath = strtok(buffer[count - 1], " ");

        int sourceFile = atoi(strtok(NULL, " "));

        char * destinationFilePath = strtok(NULL, " ");

        int destinationFile = atoi(strtok(NULL, "\n"));

        char input[1024];

        int bytesRead;

        while((bytesRead = read(sourceFile, input, sizeof(input))) > 0){
            bytes += bytesRead;
            write(destinationFile, input, bytesRead);
        }
    
        count--;

        close(sourceFile);
        close(destinationFile);;

        //printf("%s file copied successfully.\n", sourceFilePath);

        free(buffer[count]);


        pthread_cond_signal(&notFull);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}


int main(int argc, char * argv[]){

    if(argc < 4){
        printf("Insufficient number of arguments.\n");
        return -1;
    }

    number_of_dir = argc - 4;

    signal(SIGINT, SIGINTHandler);

    buffer_size = atoi(argv[1]);

    buffer = (char**) malloc(buffer_size * sizeof(char*));

    number_of_consumers = atoi(argv[2]);

    consumers = malloc(number_of_consumers * sizeof(pthread_t));

    pthread_cond_init(&notEmpty, NULL);
    pthread_cond_init(&notFull, NULL);

    struct timeval first, last;

    gettimeofday(&first, NULL);

    pthread_create(&producer, NULL, produce, (void *)argv);

    for(int i = 0; i < number_of_consumers; i++){
        pthread_create(&consumers[i], NULL, consume, NULL);
    }

    pthread_join(producer, NULL);

    for(int i = 0; i < number_of_consumers; i++){
        pthread_join(consumers[i], NULL);
    }

    gettimeofday(&last, NULL);

    long seconds = last.tv_sec - first.tv_sec, microseconds = last.tv_usec - first.tv_usec;

    if(microseconds < 0){
        microseconds += 1000000;
        seconds--;
    }

    printf("STATISTICS:\n%d number of files are copied.\n%d number of subdirectories are copied.\n%lld number of bytes copied.\n", regular_files, directories, bytes);

    printf("The process takes %ld.%ld seconds.\n", seconds, microseconds);

    free(buffer);
    free(consumers);

    pthread_cond_destroy(&notEmpty);
    pthread_cond_destroy(&notFull);
}

/*
    FOR MULTIPLE DESTINATIONS

    FOR NOT EXISTING  FOLDERS

*/