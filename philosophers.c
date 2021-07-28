#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

pthread_mutex_t chopstick[5];

void *run(int n){
    int next = 0;

    printf("Philosopher %d is thinking.\n", n + 1);

    pthread_mutex_lock(&chopstick[n]);
    
    next = (n+1)%5;
    pthread_mutex_lock(&chopstick[next]);

    printf("Philosopher %d is eating with : chopstick[%d] & chopstick[%d].\n", n + 1, n, next);
    
    sleep(5);

    pthread_mutex_unlock(&chopstick[n]);
    pthread_mutex_unlock(&chopstick[next]);

    printf("Philosopher %d finished eating.\n", n + 1);   
}

int main(){
    pthread_t threads[5];
    for (int i = 0; i < 5; i++){
        pthread_mutex_init(&chopstick[i], NULL);
    }
    for (int i = 0; i < 5; i++){
        pthread_create(&threads[i], NULL, (void *) run, (void *)(intptr_t) i);
    }
    for (int i = 0; i < 5; i++){
        pthread_join(threads[i], NULL);
    }
    return 0;
}