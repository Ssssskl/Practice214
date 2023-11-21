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
        pid_t pid = fork(); // call new process

        if (pid == -1) //process ended with trouble
        {
            perror("System error");
            exit(1);
        }
        else if (pid == 0) // process ended normally
        {
            execlp(argv[i], argv[i], (char *)0);
            perror("Error with exec");
            exit(2);
        }
    }

    for (i = 1; i < argc; i++) 
    {
        wait(&status);
        if (WIFEXITED(status) && WEXITSTATUS(status)) // macro determines whether the child process ended normally
        {
            k++;
        } 
    }
    printf("Number of successfully executed processes: %d\n", k);
    return 0;
}