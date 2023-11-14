/* pr1 arg1 arg2 | pr2; pr3 >> f1.dat */
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    if (argc != 7)
    {
        fprintf(stderr, "There is not 7 arguments\n");
        exit(1);
    }

    int fd[2];
    pipe(fd);

    pid_t pid1 = fork();

    if (pid1 == -1)
    {
        perror("System error with pid1");
        exit(2);
    }
    else if (pid1 == 0)
    {
        dup2(fd[1], 1);
        close(fd[1]);
        close(fd[0]);

        execlp(argv[1], argv[1], argv[2], argv[3], (char *)0);

        perror("Error with exec pr1");
        exit(3);
    }

    pid_t pid2 = fork();

    if (pid2 == -1)
    {
        perror("System error with pid2");
        exit(4);
    }
    else if (pid2 == 0)
    {
        dup2(fd[0], 0);
        close(fd[1]);
        close(fd[0]);

        execlp(argv[4], argv[4], (char *)0);

        perror("Error with exec pr2");
        exit(5);
    }

    close(fd[1]);
    close(fd[0]);

    while (wait(NULL) != -1);

    pid_t pid3 = fork();
    if (pid3 == -1)
        {
            perror("System error with pid3");
            exit(6);
        }
    else if (pid3 == 0) 
    {
            int file_out;
            if ((file_out = open(argv[6], O_WRONLY | O_CREAT | O_APPEND, 0777)) == -1) 
            {
                perror(argv[6]);
                exit(7);
            }
            dup2(file_out, 1);
            close(fd[1]);
            close(fd[0]);
            close(file_out);

            execlp(argv[5], argv[5], (char *)0);

            perror("Error with exec pr3");
            exit(8);
    }
    wait(NULL);
}