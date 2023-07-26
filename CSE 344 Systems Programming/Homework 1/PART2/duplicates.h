#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>

int duplicate(int oldfd){
    if(oldfd < 0){ /* If the oldfd is nonnegative, return -1. */
        return -1;
    }
    return fcntl(oldfd, F_DUPFD, 0);
}

int duplicate2(int oldfd, int newfd){
    int fd = fcntl(oldfd, F_GETFL); 

    if(fd == -1 | oldfd < 0 | newfd < 0){ /* If one of the oldfd and newfd is not valid, sets errno as EBADF and return -1. */
        errno = EBADF;
        return -1;
    }
    else{ /* If the fd is valid, continue. */
        if(oldfd == newfd){ /* If the oldfd equal to newfd, return newfd. */
            return newfd;
        }
        else{ /* Otherwise close the newfd and duplicate the fd given in oldfd. */
            close(newfd);
            return fcntl(oldfd, F_DUPFD, newfd);
        }
    }
}