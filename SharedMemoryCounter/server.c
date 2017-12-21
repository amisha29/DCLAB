#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHMKEY 5678
#define SHMSIZE 4096

int main()
{
    int shmid, counter = 1;
    key_t key = SHMKEY;
    int* shm_addr;

    shmid = shmget(key, SHMSIZE, IPC_CREAT | 0666);
    printf("\nShared memory created with ID : %d\n", shmid);

    shm_addr = (int *) shmat(shmid, NULL, 0);
    printf("\nShared memory address : %d\n", shm_addr);

    *shm_addr = counter;

    while(1) {
        if(*shm_addr != counter) {
            counter = *shm_addr;
            puts("\nCounter value incremented to : ");
            printf("%d", counter);
        }
    }
    return 0;
}
