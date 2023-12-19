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
    printf("1\n");
    struct sembuf op = {0,-1,0};
    for (int k = 1; semctl(sem, n - 1, GETVAL, 0) == 0; k++) 
    {
        for (int i = 2; i < 4; i++) 
        {
            op.sem_num = i;
            semop(sem, &op, 1);
        }
        printf("Product №%d is ready\n", k);
    }
    return 0;
}