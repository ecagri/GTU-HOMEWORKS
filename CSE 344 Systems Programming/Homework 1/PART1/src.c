#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char * argv[]){
    if(argc < 3){
        printf("PLEASE SPECIFY ALL COMMAND LINE ARGUMENTS!");
        return -1;
    }

    mode_t mode = O_WRONLY | O_CREAT;

    mode_t general_mode = (argc == 3) ? mode | O_APPEND: mode; /* If third command line argument (x) is supplied, omit O_APPEND. */
 
    char * path = argv[1]; /* Get path. */

    int zero = 0;
    
    int num_bytes = atoi(argv[2]); /* Convert num-bytes argument into integer. */

    int fd = open(path, general_mode, S_IWUSR | S_IRUSR); /* Open the file and set file descriptor as fd. */

    if(fd == -1){ /* If file descriptor is not valid, print an error. */
        perror("Cannot open");
        return -1;
    }
    for(int i = 0; i < num_bytes; i++){ /* Write a byte at a time. */
        if(argc == 4) /* If third command line argument (x) is supplied, call lseek function to set offset. */
            lseek(fd, 0, SEEK_END);
        write(fd, &zero, 1);
    }

    close(fd); /* Close the file descriptor. */

    return 0;
} 