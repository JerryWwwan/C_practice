#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

sem_t sem;

void* change_resource(void *res)
{
    char *msg = (char*)res;
    int s;
    printf("loop get to start...\n");
    while (1) {
        // sem_wait(&sem);
        struct timespec ts;
        if (clock_gettime(CLOCK_REALTIME, &ts) == -1){
            return -1;
        }

        ts.tv_sec += 10;
        while ((s = sem_timedwait(&sem, &ts)) == -1 && errno == EINTR)
                    continue;       /* Restart if interrupted by handler */
        /* Check what happened */
        if (s == -1){
            if (errno == ETIMEDOUT){
                printf("sem_timedwait() timed out\n");
                sem_destroy(&sem);
            } else{
                perror("sem_timedwait");
            }
        } else{
            printf("sem_timedwait() succeeded\n");
        }
        strcat(msg, "a");
        printf("resource changed with value: %s\n", msg);
    }
}

int main()
{
    int ret = -1;
    pthread_t thread;
    char *resource;
    int delay = 0;

    ret = sem_init(&sem, 0, 0);
    if (ret == -1) {
        printf("sem_init failed \n");
        return -1;
    }

    ret = pthread_create(&thread, NULL, change_resource, (void*)resource);
    if (ret != 0) {
        printf("pthread_create failed \n");
        return -1;
    }

    while (1) {
        if(sem_post(&sem)){
            break;
        }
        sleep(delay++);
    }
}