#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>


sem_t arr_fork[5];
sem_t WAIT;
sem_t bowls;
int arr_eat[5];

void fun(int);


void *philosophers_eat_test(void *num)
{
    int checkvar=1;
    while (checkvar)
    {
        int *i = num;
        sleep(1);
        sem_wait(&WAIT);
        printf("Philosopher no. %d is trying to eat\n", *i);
        fun(*i);
        sem_post(&WAIT);
        sem_wait(&arr_fork[*i]);
        sleep(1);
        sem_wait(&bowls);
        printf("Philosopher no. %d takes up a bowl\n", *i);
        printf("Philosopher no. %d is Eating\n", *i);
        sleep(1);
        sem_wait(&WAIT);
        arr_eat[*i] = 0;
        printf("Philosopher no. %d has finished eating\n", *i);
        fun((*i + 1) % 5);
        fun((*i + 4) % 5);
        sem_post(&WAIT);
        sem_post(&bowls);
    }
}



void fun(int nump)
{
    if (arr_eat[(nump + 1) % 5] != 1 && arr_eat[(nump + 4) % 5] != 1)
    {
        arr_eat[nump] = 1;
        sleep(2);
        
        printf("Philosopher no. %d picks up forks\n",nump);

        sem_post(&arr_fork[nump]);
    }
}


int main()
{
    pthread_t philosophers[5];

    int n_philosopher[5]={0,1,2,3,4};

    sem_init(&WAIT, 0, 1);
    sem_init(&bowls,0,2);
    int i=0;
    while (i<5)
    {
        sem_init(&arr_fork[i], 0, 1);
        i++;
    }
    
    i=0;
    while (i<5)
    {
        pthread_create(&philosophers[i], NULL, philosophers_eat_test, &n_philosopher[i]);
        i++;
    }
    
    for (i = 0; i < 5; i++)
        pthread_join(philosophers[i], NULL);
}
