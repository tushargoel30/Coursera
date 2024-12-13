
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

int arr_f[5];

void *p_eat(void *var)
{
    int nump = *(int *)var;
    while (1)
    {
        if (nump == 4)
        {
            printf("\nPhilospher %d is trying to eat", nump);
            if (arr_f[(nump + 1) % 5]==1)
            {
                arr_f[(nump + 1) % 5]=0;
            }
            else
            {
                while (arr_f[(nump + 1) % 5]==0)
                {}
            }
            printf("\nPhilospher %d picks right fork", nump);
            if (arr_f[nump]==1)
            {
                arr_f[nump]=0;
            }
            else
            {
                while (arr_f[nump]==0)
                {}
            }
            printf("\nPhilospher %d picks left fork", nump);
            printf("\nPhilospher %d is eating!", nump);
            printf("\nphilosopher is eating");
            sleep(2);
            printf("\nPhilospher %d has finished eating", nump);
            arr_f[nump]=1;
            arr_f[(nump + 1) % 5]=1;
        }
        else
        {
            printf("\nPhilospher %d is trying to eat", nump);
            if (arr_f[nump]==1)
            {
                arr_f[nump]=0;
            }
            else
            {
                while (arr_f[nump]==0)
                {}
            }
            printf("\nPhilospher %d picks left fork", nump);
            if (arr_f[(nump + 1) % 5]==1)
            {
                arr_f[(nump + 1) % 5]=0;
            }
            else
            {
                while (arr_f[(nump + 1) % 5]==0)
                {}
            }
            printf("\nPhilospher %d picks right fork", nump);
            printf("\nPhilospher %d is eating!", nump);
            printf("\nphilospher is eating");
            sleep(2);
            printf("\nPhilospher %d has finished eating", nump);
            arr_f[(nump + 1) % 5]=1;
            arr_f[nump]=1;
        }
    }
}


int main()
{
    pthread_t philosophers[5];

    int num[5]={0,1,2,3,4};
    
    int i = 0;
    while (i <= 4)
    {
        arr_f[i]=1;
        pthread_create(&philosophers[i], NULL, p_eat, (void *)&num[i]);
        i++;
    }
    i=0;
    while (i<=4){
        pthread_join(philosophers[i], NULL);
        i++;
    }
    
}

