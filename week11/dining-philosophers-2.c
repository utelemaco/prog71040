#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define NUM_PHILOSOPHERS 5
#define EATING_TIME 2
#define THINKING_TIME 3

// Mutex for each fork
pthread_mutex_t forks[NUM_PHILOSOPHERS];

// Mutex for printing (to avoid mixed output)
pthread_mutex_t print_mutex = PTHREAD_MUTEX_INITIALIZER;

// Philosopher states
enum State {
    THINKING,
    HUNGRY,
    EATING
};

// Function to print philosopher state
void print_state(int id, enum State state) {
    pthread_mutex_lock(&print_mutex);
    
    switch(state) {
        case THINKING:
            printf("Philosopher %d is thinking...\n", id);
            break;
        case HUNGRY:
            printf("Philosopher %d is hungry and trying to pick up forks\n", id);
            break;
        case EATING:
            printf("Philosopher %d is eating\n", id);
            break;
    }
    
    pthread_mutex_unlock(&print_mutex);
}

// Philosopher function
void* philosopher(void* arg) {
    int id = *(int*)arg;
    int left_fork = id;
    int right_fork = (id + 1) % NUM_PHILOSOPHERS;
    
    // To prevent deadlock, philosopher with higher ID picks up right fork first
    int first_fork = (id < right_fork) ? left_fork : right_fork;
    int second_fork = (id < right_fork) ? right_fork : left_fork;
    
    while(1) {
        // Think
        print_state(id, THINKING);
        sleep(rand() % THINKING_TIME + 1);
        
        // Get hungry
        print_state(id, HUNGRY);
        
        // Pick up forks (in order to prevent deadlock)
        pthread_mutex_lock(&forks[first_fork]);
        pthread_mutex_lock(&forks[second_fork]);
        
        // Eat
        print_state(id, EATING);
        sleep(rand() % EATING_TIME + 1);
        
        // Put down forks
        pthread_mutex_unlock(&forks[second_fork]);
        pthread_mutex_unlock(&forks[first_fork]);
        
        // Brief pause before next cycle
        usleep(100000); // 0.1 second
    }
    
    return NULL;
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];
    
    // Initialize random seed
    srand(time(NULL));
    
    // Initialize fork mutexes
    for(int i = 0; i < NUM_PHILOSOPHERS; i++) {
        if(pthread_mutex_init(&forks[i], NULL) != 0) {
            fprintf(stderr, "Failed to initialize mutex for fork %d\n", i);
            return 1;
        }
    }
    
    printf("=== Dining Philosophers Problem ===\n");
    printf("Number of philosophers: %d\n", NUM_PHILOSOPHERS);
    printf("Starting simulation...\n\n");
    
    // Create philosopher threads
    for(int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosopher_ids[i] = i;
        if(pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]) != 0) {
            fprintf(stderr, "Failed to create thread for philosopher %d\n", i);
            return 1;
        }
    }
    
    // Wait for all threads to complete (they won't in this infinite loop)
    for(int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }
    
    // Clean up mutexes
    for(int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }
    pthread_mutex_destroy(&print_mutex);
    
    return 0;
}