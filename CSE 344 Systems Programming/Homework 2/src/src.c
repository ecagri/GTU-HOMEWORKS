#define _POSIX_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <fcntl.h>
#include <time.h>
#include <signal.h>

#define TRUE 1
#define MAXARGUMENT 10
#define MAXCOMMANDSIZE 20

typedef enum Direction{
    IN,
    OUT,
    NO
}Direction;

char ** parseCommand(char * command, int * number_of_args);
char ** setArgs(char ** args, char ** filename, int * number_of_args, Direction * direction);
void execute(char ** args, int number_of_args);
void sigintHandler();
void sigtermHandler();
extern char* strdup(const char*);

int sigterm = 0;

int main(){
    int status, commandsNumber, fds[2], fdin = 0, number_of_args;

    char * command, *commands[20], input[20 * 120], **args, *filename;

    while(TRUE){

        Direction direction = NO; /* Setting the direction of the command as NO. */

        signal(SIGTERM, sigtermHandler); /* Assigning signal handler for SIGTERM. */

        signal(SIGINT, sigintHandler); /* Assigning signal handler for SIGINT. */

        if(sigterm == 1){   /* If the sigterm is equals to 1, terminates the program. */
            printf("TERMINATING(SIGTERM)...\n");             
            exit(1);
        }

        printf("cagri@terminal$ ");

        fflush(stdin);

        fgets(input, 120, stdin); /* Getting input from the user. */

        if(strcmp(input, ":q\n") == 0){ /* If the input equals to :q, terminates the program. */
            printf("EXITING...\n");
            return 0;
        }

        
        // CHILD //
        if(fork() == 0){ /* Creating a child process and continue. */
    
            command = strtok(input, "\n"); /* Removing '\n' from the input. */

            command = strtok(input, "|"); /* Spliting the commands and keeps it in the commands array. */

            for(commandsNumber = 0; commandsNumber < 20 && command != NULL; commandsNumber++){

                commands[commandsNumber] = command;

                command = strtok(NULL, "|");            
            }

            free(command);

            for(int i = 0; i < commandsNumber - 1; i++){ /* If the command is not the last one, continue. */

                args = parseCommand(commands[i], &number_of_args); /* Parse current command and assign its arguments to args array. */

                args = setArgs(args, &filename, &number_of_args, &direction); /* Set direction of the command and get filename if they exists. */

                if(pipe(fds) == -1){ /* Creating pipe. */
                    printf("error");
                }
                // PARENT //
                if(fork() != 0){ /* Creating a child process and continue. */ 

                    close(fds[1]); /* Closing the write end of the pipe. */
                    
                    fdin = fds[0]; /* Assigning the read end of the pipe to fdin variable. */

                    waitpid(-1, &status, 0); /* Wait until child process finish. */
                }
                // CHILD //
                else{
                    if(fdin != 0){  /* Defensive check. */
                        dup2(fdin, STDIN_FILENO); /* Duplicate fdin onto file descriptor STDIN_FILENO. */

                        close(fdin); /* Close the file descriptor fdin. */

                    }
                    
                    if(fds[1] != 1){ /* Defensive check. */
                        dup2(fds[1], STDOUT_FILENO); /* Duplicate the write end of the pipe onto file descriptor STDOUT_FILENO. */

                        close(fds[1]); /* Close the write end of the pipe. */
                    }

                    if(direction == OUT){ /* If the command needs to write to the file. */
                        int wfd = open(filename, O_WRONLY | O_CREAT| O_TRUNC, S_IWUSR | S_IRUSR); /* Open the file. */

                        dup2(wfd, STDOUT_FILENO); /* Duplicate the new file descriptor onto file descriptor STDOUT_FILENO. */

                        close(wfd); /* Close the new file descriptor. */
                    }

                    execute(args, number_of_args); /* Execute the command. */

                    exit(1); 
                }
            }

            // LAST COMMAND //

            args = parseCommand(commands[commandsNumber - 1], &number_of_args); /* Parse current command and assign its arguments to args array. */

            args = setArgs(args, &filename, &number_of_args, &direction); /* Set direction of the command and get filename if they exists. */

            if(direction == IN){ /* If the command needs input from the file. */
                fdin = open(filename, O_RDONLY); /* Open the file in read only. */

                if(fdin == -1){ /* If the file does not exist, print an error and exit. */
                    printf("No such a file or directory\n");
                    exit(1);
                }
            }
            
            if(fdin != 0){ /* Defensive check. */
                dup2(fdin, STDIN_FILENO); /* Duplicate fdin onto file descriptor STDIN_FILENO. */

                close(fdin); /* Close the file descriptor fdin. */
            }
            
            if(direction == OUT){ /* If the command needs to write to the file. */
                int wfd = open(filename, O_WRONLY | O_CREAT| O_TRUNC, S_IWUSR | S_IRUSR); /* Open the file. */

                dup2(wfd, STDOUT_FILENO); /* Duplicate the new file descriptor onto file descriptor STDOUT_FILENO. */

                close(wfd); /* Close the new file descriptor. */
            }
            
            execute(args, number_of_args); /* Execute the commmand. */

            exit(1);
        }

        else{

            waitpid(-1, &status, 0); /* Wait until child process is completed.*/

            if(status == 1){ 
                perror("INVALID COMMAND OR ERROR");

                break;
            }

        }
    }

    return 0;
}

char** parseCommand(char * command, int * number_of_args){ /* PArse the commands and returns commands array and number of arguments. */
    char ** args = (char**) malloc(MAXARGUMENT * sizeof(char*)); /* Allocate memory for the arguments. */

    char * argument; 

    argument = strtok(command, " "); /* Remove space from the arguments and keeps it in the args array. */

    for(*number_of_args = 0; *number_of_args < MAXARGUMENT && argument != NULL; (*number_of_args)++){
        args[*number_of_args] = strdup(argument);

        argument = strtok(NULL, " ");
    }

    free(argument); 

    args[*number_of_args] = NULL; /* Set the last argument as NULL. */

    return args; /* REturn the arguments. */

}

void execute(char ** args, int number_of_args){ /* Executes the giving command and frees the memory. */

    char path[MAXCOMMANDSIZE] = "/bin/";

    /* Writes pid and the command to the file which is named according to timestampt. */

    time_t current = time(NULL); 

    struct tm * local = localtime(&current);

    char filename[50], pid[50];

    strcat(path, args[0]);

    strftime(filename, sizeof(filename), "%Y-%m-%d %H:%M:%S", local);

    sprintf(pid, "%d", getpid());

    int wfd = open(filename, O_WRONLY | O_CREAT| O_APPEND, S_IWUSR | S_IRUSR);

    write(wfd, "PID: ", 5);

    write(wfd, pid, strlen(pid));

    write(wfd, "\nCommand: ", 10);

    write(wfd, path, strlen(path));

    write(wfd, "\n", 1);

    close(wfd);

    execv(path, &args[0]); /* Execute the command. */

    for(int i = 0; i < number_of_args; i++){ /* Free the each element of the args array. */
        free(args[i]);
    }

    free(args); /* Free the args array. */

    exit(1);
}

char ** setArgs(char ** args, char ** filename, int * number_of_args, Direction * direction){ /* Sets direction of the command and returns new version of arguments array and filename and number of arguments.*/
    *direction = NO; /* Sets direction as NO. */
    
    for(int i = 0; i < *number_of_args; i++){ /* Check every argument of the args array. */
        
        if(strcmp(args[i], ">") == 0){ /* If the ith element of the args array is equals to '>', continue. */

            *filename = args[i + 1]; /* Gets next element as filename. */
    
            for(int j = i; j < (*number_of_args); j++){ /* Deletes the '>' symbol and filename from the args array. */
                args[j] = args[j+2];
            }

            *number_of_args -= 2; /* Decreases the number of arguments by 2. */

            *direction = OUT; /* Sets the direction as OUT.*/

            break;
            
        }

        else if(strcmp(args[i], "<") == 0){ /* If the ith element of the args array is equals to '<', continue. */

            *filename = args[i + 1]; /* Gets next element as filename. */

            for(int j = i; j < (*number_of_args); j++){ /* Deletes the '<' symbol and filename from the args array. */
                args[j] = args[j+2];
            }

            *number_of_args -= 2; /* Decreases the number of arguments by 2. */

            *direction = IN; /* Sets the direction as IN.*/

            break;
        }

    } 

    return args;
}

void sigintHandler(){ /* Stops the process */
    printf("TERMINATING(SIGINT)...\n");             

    exit(100);
}
 
void sigtermHandler(){ /* Sets sigterm as 1 if the SIGTERM signal is send. */
    sigterm = 1;
}