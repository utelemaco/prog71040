#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

#define NUM_PHILOSOPHERS 5
#define THINKING_TIME 2
#define EATING_TIME 1

// Mutex for each fork
pthread_mutex_t forks[NUM_PHILOSOPHERS];

// Mutex for printing to avoid garbled output
pthread_mutex_t print_mutex;

// Philosopher states for visualization
enum State { THINKING, HUNGRY, EATING };
enum State philosopher_states[NUM_PHILOSOPHERS];

void print_state(int id, const char* action) {
    pthread_mutex_lock(&print_mutex);
    printf("Philosopher %d is %s\n", id, action);
    pthread_mutex_unlock(&print_mutex);
}

void print_table_state() {
    pthread_mutex_lock(&print_mutex);
    printf("\nTable State: ");
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        switch (philosopher_states[i]) {
            case THINKING: printf("T "); break;
            case HUNGRY: printf("H "); break;
            case EATING: printf("E "); break;
        }
    }
    printf("\n");
    pthread_mutex_unlock(&print_mutex);
}

void think(int id) {
    philosopher_states[id] = THINKING;
    print_state(id, "thinking");
    sleep(rand() % THINKING_TIME + 1);
}

void eat(int id) {
    philosopher_states[id] = EATING;
    print_state(id, "eating");
    print_table_state();
    sleep(rand() % EATING_TIME + 1);
}

void* philosopher(void* arg) {
    int id = *(int*)arg;
    int left_fork = id;
    int right_fork = (id + 1) % NUM_PHILOSOPHERS;
    
    // To prevent deadlock, we use a simple ordering strategy:
    // Always pick up the lower-numbered fork first
    int first_fork = right_fork;//(left_fork < right_fork) ? left_fork : right_fork;
    int second_fork = left_fork;//(left_fork < right_fork) ? right_fork : left_fork;
    
    while (1) {
        // Think
        think(id);
        
        // Get hungry
        philosopher_states[id] = HUNGRY;
        print_state(id, "hungry - trying to pick up forks");
        
        // Pick up forks (in order to prevent deadlock)
        printf("Philosopher %d is trying to pick up fork %d\n", id, first_fork);
        pthread_mutex_lock(&forks[first_fork]);
        printf("Philosopher %d picked up fork %d\n", id, first_fork);
        
        sleep(rand() % EATING_TIME + 1);
        
        printf("Philosopher %d is trying to pick up fork %d\n", id, second_fork);
        while (pthread_mutex_trylock(&forks[second_fork]) == EBUSY) {
            printf("Fork %d is in use. Philosopher %d is waiting to pick up it\n", second_fork, id);
            sleep(rand() % EATING_TIME + 1);
        }

        pthread_mutex_lock(&forks[second_fork]);
        printf("Philosopher %d picked up fork %d\n", id, second_fork);
        
        // Eat
        eat(id);
        
        // Put down forks
        pthread_mutex_unlock(&forks[second_fork]);
        printf("Philosopher %d put down fork %d\n", id, second_fork);
        
        pthread_mutex_unlock(&forks[first_fork]);
        printf("Philosopher %d put down fork %d\n", id, first_fork);
        
        print_state(id, "finished eating");
    }
    
    return NULL;
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];
    
    // Initialize random seed
    srand(time(NULL));
    
    // Initialize mutexes
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
        philosopher_states[i] = THINKING;
    }
    pthread_mutex_init(&print_mutex, NULL);
    
    printf("Dining Philosophers Problem\n");
    printf("==========================\n");
    printf("5 philosophers sitting around a table\n");
    printf("States: T=Thinking, H=Hungry, E=Eating\n\n");
    
    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosopher_ids[i] = i;
        if (pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]) != 0) {
            perror("Failed to create philosopher thread");
            exit(1);
        }
    }
    
    // Wait for all philosophers (this will run indefinitely)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }
    
    // Cleanup mutexes (this code won't be reached in this infinite loop version)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }
    pthread_mutex_destroy(&print_mutex);
    
    return 0;
}