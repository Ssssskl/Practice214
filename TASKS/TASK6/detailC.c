#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <signal.h>

int main(void)
{
    key_t key = ftok("connection.txt", 1);
    int sem = semget(key, 5, 0666);
    struct sembuf op = {2,1,0};
    for (int k = 1; semctl(sem, 4, GETVAL, 0) == 0; k++)
    {
        printf("Manufacturing of the detail C begins, this is №%d\n", k);
        sleep(4);
        printf("Detail C №%d is done\n", k);
        semop(sem, &op, 1);
    }
    return 0;
}