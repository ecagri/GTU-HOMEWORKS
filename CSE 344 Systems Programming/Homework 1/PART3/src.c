#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include "../PART2/duplicates.h"

void test_offset(int oldfd, int newfd);

int main(int argc, char * argv[]){
    int oldfd = open("test.txt", O_WRONLY | O_CREAT | O_APPEND, S_IWUSR | S_IRUSR); /* Open a file and set the file descriptor as oldfd. */

    int newfd = dup(oldfd); /* Duplicate oldfd and set it as newfd. */

    int newfd2 = duplicate(oldfd);

    char * str = "my name is cagri ";

    size_t size = strlen(str);

    char * str1 = "1901042629 ";

    size_t size1 = strlen(str1);

    write(oldfd, str, size); /* Write something to file with oldfd. */

    write(newfd, str1, size1); /* Write something to file with newfd. */

    write(newfd2, str1, size1);  /* Write something to file with newfd. */

    test_offset(oldfd, newfd); /* Write something to file with newfd. */

    test_offset(oldfd, newfd2); /* Write something to file with newfd. */

    close(oldfd); /* Close the oldfd. */

    close(newfd); /* Close the newfd. */

    close(newfd2); /* Close the newfd. */
}


void test_offset(int oldfd, int newfd){ /* Compare two file descriptor offset. */
    long int offset0 = lseek(oldfd, 0, SEEK_CUR); /* Get current offset of oldfd. */

    long int offset1 = lseek(newfd, 0, SEEK_CUR); /* Get current offset of newfd. */

    printf("ARE OFFSETS EQUAL?\n");

    printf("EXPECTED RESULT: YES\n");

    printf("RESULT: ");

    if(offset0 == offset1){
        printf("YES\n");
        printf("OFFSETS: %ld-%ld\n", offset0, offset1);
    }
    else{
        printf("NO\n");
    }
}