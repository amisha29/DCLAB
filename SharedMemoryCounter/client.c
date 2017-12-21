#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHMKEY 5678
#define SHMSIZE 4096

int main()
{
    int shmid, counter, num;
    key_t key = SHMKEY;
    int* shm_addr;

    shmid = shmget(key, SHMSIZE, 0666);
    printf("\nShared memory created with ID : %d\n", shmid);

    shm_addr = (int *) shmat(shmid, NULL, 0);
    printf("\nShared memory address : %d\n", shm_addr);
    printf("\nEnter 1 to increment ");
    scanf("%d", &num);
    while(num == 1) {
        counter = *shm_addr;
        counter++;
        *shm_addr = counter;
        printf("\nupdated counter value : %d\n", counter);
        printf("\nEnter 1 to increment ");
        scanf("%d", &num);
    }
    return 0;
}
