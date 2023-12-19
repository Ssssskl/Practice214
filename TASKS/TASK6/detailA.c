#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <signal.h>

int main(void)
{
    int num_sem = 5;
    key_t key = ftok("connection.txt", 1);
    int sem = semget(key, num_sem, 0666);
    struct sembuf op = {0,1,0};
    for (int k = 1; semctl(sem, num_sem - 1, GETVAL, 0) == 0; k++)
    {
        printf("Manufacturing of the detail A begins, this is №%d\n", k);
        sleep(2);
        printf("Detail A №%d is done\n", k);
        semop(sem, &op, 1);
    }
    return 0;
}