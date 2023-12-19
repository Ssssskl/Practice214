#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <signal.h>

#define n  5

int main(void)
{
    key_t key = ftok("connection.txt", 'a');
    int sem = semget(key, n, 0666);
    struct sembuf op = {0,1,0};
    for (int k = 1; semctl(sem, n - 1, GETVAL, 0) == 0; k++)
    {
        printf("Manufacturing of the detail A begins, this is №%d\n", k);
        sleep(2);
        printf("Detail A №%d is done\n", k);
        semop(sem, &op, 1);
    }
    return 0;
}