#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>

int arr_fork[5];
int bowls;


void *philosophers_eat_test(void *var)
{
    int nump = *(int *)var;
    int check=1;
    while (check)
    {
        if (nump == 4)
        {

            printf("\nPhilospher no. %d is trying to eat", nump);
            if (bowls > 0)
            {bowls --;
            }
            else
            {while (bowls < 1);
            }
            printf("\nPhilospher no. %d takes the bowl", nump);
            sleep(1);
            if (arr_fork[(nump + 1) % 5] == 1)
            {
                arr_fork[(nump + 1) % 5] = 0;
            }
            else
            {
                while (arr_fork[(nump + 1) % 5] == 0);
            }
            printf("\nPhilospher no. %d takes the right fork", nump);
            sleep(1);
            if (arr_fork[nump] == 1)
            {arr_fork[nump] = 0;}
            else
            {
                while (arr_fork[nump] == 0);
            }
            printf("\nPhilospher no. %d takes the left fork", nump);
            printf("\nPhilospher no. %d is eating!", nump);
            printf("\nPhilospher no. %d has finished eating", nump);
            bowls += 1;
            arr_fork[nump] = 1;
            arr_fork[(nump + 1) % 5] = 1;
        }
        else
        {
            printf("\nPhilospher %d is trying to eat", nump);
            if (bowls > 0)
            {bowls--;
            }
            else
            {while (bowls < 1);
            }
            printf("\nPhilospher %d picks up a bowl", nump);
            sleep(1);
            lock(nump);
            printf("\nPhilospher %d picks left fork", nump);
            lock((nump + 1) % 5);
            printf("\nPhilospher %d picks right fork", nump);
            sleep(1);
            printf("\nPhilospher %d is eating!", nump);
            printf("\nPhilospher %d finished eating", nump);
            bowls += 1;
            arr_fork[(nump + 1) % 5] = 1;
            arr_fork[nump] = 1;
        }
    }
}




int main()
{

    pthread_t philosophers[5];
    bowls = 2;
    int num[5]={0,1,2,3,4};
    
    int i = 0;
    while (i <= 4)
    {
        arr_fork[i]=1;
        pthread_create(&philosophers[i], NULL, philosophers_eat_test, (void *)&num[i]);
        i++;
    }
    i=0;
    while (i<=4){
        pthread_join(philosophers[i], NULL);
        i++;
    }
    
}

