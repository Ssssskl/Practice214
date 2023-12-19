#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <signal.h>

key_t key;
int semaphore;

void handler(int sig) 
{
    if (sig == SIGINT) 
    {
        printf("No more details\n");
        struct sembuf exit = {4, 1, 0};
        semop(semaphore, &exit, 1);
    }
}

int main(void) 
{
    key = ftok("connection.txt", 'a');
    semaphore = semget(key, 5, 0666 | IPC_CREAT);
    signal(SIGINT, handler);
    sigset_t mask;
    sigfillset(&mask);
    sigdelset(&mask, SIGINT);
    int mas[6] = {0, 0, 0, 0, 0, 0};
    semctl(semaphore, 0, SETALL, mas);
    for (int i = 0; i < 5; i++) 
    {
        semctl(semaphore, i, GETVAL, 0);
    }
    printf("Ready\n");
    sigsuspend(&mask);
    semctl(semaphore, 0, IPC_RMID, 0);
    return 0;
}