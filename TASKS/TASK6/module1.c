#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <signal.h>

#define n 5

int main(void) 
{
    key_t key = ftok("connection.txt", 'a');
    int sem = semget(key, n, 0666);
    struct sembuf op = {0,0,0};
    for (int k = 1; semctl(sem, n - 1, GETVAL, 0) == 0; k++) 
    {
        op.sem_op = -1;
        for (int j = 0; j < 2; j++) 
        {
            op.sem_num = j;
            semop(sem, &op, 1);
        }
        printf("Manufacturing of the module 1 begins, this is%d\n", k);
        sleep(1);
        printf("Module 1 №%d is ready\n", k);
        op.sem_num = 2;
        op.sem_op = 1;
        semop(sem, &op, 1);
    }
    return 0;
}