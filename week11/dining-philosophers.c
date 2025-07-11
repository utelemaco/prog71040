#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Define the number of philosophers
#define NUM_PHILOSOPHERS 5

// Define a structure for a philosopher
typedef struct {
    int id;
    int fork;
} Philosopher;

// Function to get a fork (returns -1 if unavailable)
int getFork(Philosopher* philos, int num) {
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        if ((philos[i].fork == -1 || philos[i].id != num) && (i != num || (i == num && philos[num].fork != -2))) {
            return i;
        }
    }
    return -1; // No fork available
}

// Function to release a fork
void releaseFork(Philosopher* philos, int id) {
    if (id >= 0 && id < NUM_PHILOSOPHERS) {
        philos[id].fork = -2;
    }
}

// Function for a philosopher to eat
void eat(Philosopher* philos, int num) {
    // Acquire two forks: the one in front of yourself and the one on your left (or right if you're at either end)
    int forkLIndex = num;
    int forkRIndex = (num == NUM_PHILOSOPHERS-1) ? 0 : num+1;
    

    int forkL = -1;
    int forkR = -1;

    while(forkL < 0) {
        printf("Philosopher %d trying to get fork %d\n", num +1 , forkLIndex + 1);
        forkL = getFork(philos, forkLIndex);
        if (forkL < 0) {
            printf("Philosopher %d is wating fork %d\n", num + 1, forkLIndex + 1);
            sleep(2);
        }
    }

    while(forkR < 0) {
        printf("Philosopher %d trying to get fork %d\n", num +1 , forkRIndex + 1);
        forkR = getFork(philos, forkRIndex);
        if (forkR < 0) {
            printf("Philosopher %d is wating fork %d ", num + 1, forkRIndex + 1);
            sleep(2);
        }
    }

    printf("Philosopher %d is eating...\n", num + 1);

    // Use the forks
    philos[num].fork = forkL;
    releaseFork(philos, forkL);
    releaseFork(philos, forkR);

    // Simulate eating (you can adjust this to simulate real-world activities)
    sleep(2);

    printf("Philosopher %d has finished eating.\n", num + 1);

    releaseFork(philos, num); // Release your fork
}

// Test function to see if the program deadlocks (runs forever without producing output)
void testDiningPhilosophers() {
    Philosopher philos[NUM_PHILOSOPHERS];

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philos[i].id = i;
        philos[i].fork = -2;
    }

    int running[NUM_PHILOSOPHERS];
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        running[i] = 1;
    }

    while (1) {
        for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
            if (running[i]) {
                eat(philos, i);
                running[i] = 0;

                // If all philosophers are waiting or have finished eating and released their forks, consider the program deadlocked
                int allWaiting = 1;
                for (int j = 0; j < NUM_PHILOSOPHERS; j++) {
                    if (!running[j]) {
                        allWaiting = 0;
                        break;
                    }
                }

                // If the program has not produced output and is waiting, consider it deadlocked
                if (!allWaiting) {
                    printf("Deadlock detected!\n");
                    //return;
                }
            } else {
                sleep(1);
            }
        }
    }
}

int main() {
    testDiningPhilosophers();

    // Run the Dining Philosophers program to see if it leads to deadlock
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        Philosopher philos[NUM_PHILOSOPHERS];
        eat(philos, i);
    }

    return 0;
}
