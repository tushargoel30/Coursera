#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>


sem_t arr_fork[5];
sem_t WAIT;
int arr_eat[5];
void fun(int);




void *philosophers_eat_test(void *id_philosophers)
{
    while (1)
    {
        int *i = id_philosophers;
        sleep(1);
        sem_wait(&WAIT);
        printf("Philosopher no. %d is trying to eat\n", *i);
        fun(*i);
        sem_post(&WAIT);
        sem_wait(&arr_fork[*i]);
        sleep(1);
        sem_wait(&WAIT);
        arr_eat[*i] = 0;
        printf("Philosopher no. %d has finished eating\n", *i);
        fun((*i + 1) % 5);
        fun((*i + 4) % 5);
        sem_post(&WAIT);
    }
}


void fun(int nump)
{
    if (arr_eat[(nump + 1) % 5] != 1)
    {
        if (arr_eat[(nump + 4) % 5] != 1)
        {
            arr_eat[nump] = 1;
            sleep(2);
            printf("Philosopher no. %d takes up tne forks\n", nump);
            printf("Philosopher no. %d is Eating\n", nump);
          sleep(2);
            sem_post(&arr_fork[nump]);
        }
    }
}




int main()
{
    pthread_t philosophers[5];

    int n_philosopher[5]={0,1,2,3,4};

    sem_init(&WAIT, 0, 1);

    int i = 0;

    for (i = 0; i <= 4; i++)
    {
        sem_init(&arr_fork[i], 0, 0);
    }

    // int count=0;
  i=0;
    while(1)

    for (i = 0; i <= 4; i++)
    {
        pthread_create(&philosophers[i], NULL,philosophers_eat_test, &n_philosopher[i]);
        i++;
        // count++;
    }

    
  i=0;

    while (i<=4)
    {
        pthread_join(philosophers[i], NULL);
        i++;
    }
    

}
