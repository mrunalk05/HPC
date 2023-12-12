#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_PRODUCERS 3
#define NUM_CONSUMERS 2
#define NUM_ITEMS 10

int buffer[BUFFER_SIZE];
int count = 0; // Number of items in the buffer
int in = 0;    // Index for inserting into the buffer
int out = 0;   // Index for removing from the buffer

// Mutex for protecting access to the buffer
omp_lock_t buffer_lock;

void produce(int id) {
    int item;

    #pragma omp critical
    {
        item = rand() % 100; // Generate a random item
    }

    sleep(1); // Simulate some work before producing

    // Check if the buffer is full
    while (count == BUFFER_SIZE) {
        printf("Producer %d waiting: Buffer is full.\n", id);
        usleep(100000); // Sleep for a short time
    }

    // Produce an item and add it to the buffer
    omp_set_lock(&buffer_lock);
    buffer[in] = item;
    in = (in + 1) % BUFFER_SIZE;
    count++;
    omp_unset_lock(&buffer_lock);

    printf("Producer %d produced item %d.\n", id, item);
}

void consume(int id) {
    int item;

    // Check if the buffer is empty
    while (count == 0) {
        printf("Consumer %d waiting: Buffer is empty.\n", id);
        usleep(100000); // Sleep for a short time
    }

    // Consume an item from the buffer
    omp_set_lock(&buffer_lock);
    item = buffer[out];
    out = (out + 1) % BUFFER_SIZE;
    count--;
    omp_unset_lock(&buffer_lock);

    printf("Consumer %d consumed item %d.\n", id, item);

    sleep(2); // Simulate some work after consuming
}

int main() {
    int i;

    omp_init_lock(&buffer_lock);

    // Create producer threads
    #pragma omp parallel num_threads(NUM_PRODUCERS + NUM_CONSUMERS)
    {
        int id = omp_get_thread_num();

        if (id < NUM_PRODUCERS) {
            for (i = 0; i < NUM_ITEMS; i++) {
                produce(id);
            }
        } else {
            id -= NUM_PRODUCERS;
            for (i = 0; i < NUM_ITEMS / NUM_CONSUMERS; i++) {
                consume(id);
            }
        }
    }

    omp_destroy_lock(&buffer_lock);

    return 0;
}
