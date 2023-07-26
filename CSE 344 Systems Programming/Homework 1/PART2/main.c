#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include "duplicates.h"


void dup_test(){

    printf("******** DUP FUNCTION TESTS ********\n");

    int oldfd = open("test1.txt", O_WRONLY | O_CREAT | O_APPEND, S_IWUSR | S_IRUSR);

    printf("DUPLICATE VALID FILE DESCRIPTOR WITH ORIGINAL DUP FUNCTION\n");

    int newfd = dup(oldfd);

    printf("NEW FILE DESCRIPTOR: %d\n", newfd);

    close(newfd);

    printf("DUPLICATE VALID FILE DESCRIPTOR WITH MY DUP FUNCTION\n");

    newfd = duplicate(oldfd);

    printf("NEW FILE DESCRIPTOR: %d\n", newfd);
    
    close(newfd);

    printf("DUPLICATE UNVALID FILE DESCRIPTOR WITH ORIGINAL DUP FUNCTION\n");

    newfd = dup(-5);

    printf("NEW FILE DESCRIPTOR: %d\n", newfd);

    close(newfd);

    printf("DUPLICATE UNVALID FILE DESCRIPTOR WITH MY DUP FUNCTION\n");

    newfd = duplicate(-5);

    printf("NEW FILE DESCRIPTOR: %d\n", newfd);

    int oldfd2 = open("test2.txt", O_WRONLY | O_CREAT | O_APPEND, S_IWUSR | S_IRUSR);

    close(oldfd);

    printf("DUPLICATE VALID FILE DESCRIPTOR WITH ORIGINAL DUP FUNCTION\n");

    newfd = dup(oldfd2);

    printf("NEW FILE DESCRIPTOR: %d\n", newfd);

    close(newfd);

    printf("DUPLICATE VALID FILE DESCRIPTOR WITH MY DUP FUNCTION\n");

    newfd = duplicate(oldfd2);

    printf("NEW FILE DESCRIPTOR: %d\n", newfd);

    close(newfd);

    close(oldfd2);
}

void dup2_test(){

    printf("******** DUP2 FUNCTION TESTS ********\n");

    int fd = open("test1.txt", O_WRONLY | O_CREAT | O_APPEND, S_IWUSR | S_IRUSR);

    printf("DUPLICATE INVALID OLD FILE DESCRIPTOR WITH ORIGINAL DUP2 FUNCTION\n");

    int newfd = dup2(-5, fd);

    printf("NEW FILE DESCRIPTOR: %d\n", newfd);

    close(newfd);

    printf("DUPLICATE INVALID OLD FILE DESCRIPTOR WITH MY DUP2 FUNCTION\n");

    newfd = duplicate2(-5, fd);

    printf("NEW FILE DESCRIPTOR: %d\n", newfd);

    close(newfd);

    printf("DUPLICATE INVALID NEW FILE DESCRIPTOR WITH ORIGINAL DUP2 FUNCTION\n");

    newfd = dup2(fd, -5);

    printf("NEW FILE DESCRIPTOR: %d\n", newfd);

    close(newfd);

    printf("DUPLICATE INVALID NEW FILE DESCRIPTOR WITH MY DUP2 FUNCTION\n");

    newfd = duplicate2(fd, -5);

    printf("NEW FILE DESCRIPTOR: %d\n", newfd);

    close(newfd);

    printf("DUPLICATE OLDFD EQUALS NEWFD WITH ORIGINAL DUP2 FUNCTION\n");

    newfd = dup2(fd, fd);

    printf("NEW FILE DESCRIPTOR: %d\n", newfd);

    close(newfd);

    close(fd);

    fd = open("test1.txt", O_WRONLY | O_CREAT | O_APPEND, S_IWUSR | S_IRUSR);

    printf("DUPLICATE OLDFD EQUALS NEWFD WITH MY DUP2 FUNCTION\n");

    newfd = duplicate2(fd, fd);

    printf("NEW FILE DESCRIPTOR: %d\n", newfd);

    close(newfd);

    close(fd);

    fd = open("test1.txt", O_WRONLY | O_CREAT | O_APPEND, S_IWUSR | S_IRUSR);

    int oldfd2 = open("test2.txt", O_WRONLY | O_CREAT | O_APPEND, S_IWUSR | S_IRUSR);
    
    printf("DUPLICATE OLDFD AND ALREADY OPENED NEWFD (4) WITH ORIGINAL DUP2 FUNCTION\n");

    newfd = dup2(fd, oldfd2);

    printf("NEW FILE DESCRIPTOR: %d\n", newfd);

    close(newfd);
    
    close(oldfd2);

    oldfd2 = open("test2.txt", O_WRONLY | O_CREAT | O_APPEND, S_IWUSR | S_IRUSR);

    printf("DUPLICATE OLDFD AND ALREADY OPENED NEWFD (4) WITH MY DUP2 FUNCTION\n");

    newfd = duplicate2(fd, oldfd2);

    printf("NEW FILE DESCRIPTOR: %d\n", newfd);

    close(newfd);

    close(oldfd2);

    close(fd);
    
}

int main(int argc, char * argv[]){

    dup_test();

    dup2_test();

    return 0;
}

