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

int main (int argc, char **argv) 
{
    int i = 0;
    pid_t pid;
    int fd[2];

    while (argv[++i] != NULL) 
    {
        pipe(fd);
        pid = fork();
        if (pid == -1)
        {
            perror("System error with pid_i");
            exit(1);
            break;
        }
        else if (pid == 0)
        {
            if (i + 1 != argc) 
            {
                dup2(fd[1], 1);
            }
            close(fd[1]);
            close(fd[0]);

            execlp(argv[i], argv[i], (char *)0);

            exit(2);
            break;
        }
        dup2(fd[0], 0);

        close(fd[1]);
        close(fd[0]);
    }

    while (wait(NULL) != -1);
}