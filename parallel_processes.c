#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    int i;
    int k = 0;
    int status;
    
    for(i = 1; i < argc; i++)
    {
        pid_t pid = fork();

        if (pid == -1)
        {
            perror("System error");
            exit(1);
        }
        else if (pid == 0)
        {
            execlp(argv[i], argv[i], (char *)0);
            perror("Error with exec");
            exit(2);
        }
    }

    for (int i = 1; i < argc; i++) 
    {
        wait(&status);
        if (WIFEXITED(status)) // determines whether the child process ended normally
        {
            k++;
        } 
    }
    printf("Number of successfully executed processes: %d\n", k);
    return 0;
}
