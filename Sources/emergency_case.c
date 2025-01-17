#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include "../Headers/emergency.h"

static void downheap(PriorityQueue* pq, int index);
static void upheap(PriorityQueue* pq, int index);

void initializeQueue(PriorityQueue* pq) {
    pq->size = 0;
}

static void upheap(PriorityQueue* pq, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (pq->queue[index].priority > pq->queue[parent].priority) {
            break;
        }

        EmergencyCase temp = pq->queue[index];
        pq->queue[index] = pq->queue[parent];
        pq->queue[parent] = temp;

        index = parent;
    }
}

void enqueue(PriorityQueue* pq, EmergencyCase newCase) {
    if (pq->size >= MAX_QUEUE_SIZE) {
        return;
    }

    pq->queue[pq->size] = newCase;
    pq->size++;
    upheap(pq, pq->size - 1);
}


static void downheap(PriorityQueue* pq, int index) {
    int leftChild, rightChild, smallest;

    while (2 * index + 1 < pq->size) {
        leftChild = 2 * index + 1;
        rightChild = 2 * index + 2;
        smallest = index;

        if (leftChild < pq->size && pq->queue[leftChild].priority < pq->queue[smallest].priority) {
            smallest = leftChild;
        }
        if (rightChild < pq->size && pq->queue[rightChild].priority < pq->queue[smallest].priority) {
            smallest = rightChild;
        }
        if (smallest == index) {
            break;
        }

        EmergencyCase temp = pq->queue[index];
        pq->queue[index] = pq->queue[smallest];
        pq->queue[smallest] = temp;

        index = smallest;
    }
}

EmergencyCase dequeue(PriorityQueue* pq) {
    if (pq->size == 0) {
        EmergencyCase empty = {0};
        return empty;
    }

    EmergencyCase highestPriorityCase = pq->queue[0];

    pq->queue[0] = pq->queue[pq->size - 1];
    pq->size--;
    
    downheap(pq, 0);

    return highestPriorityCase;
}

EmergencyCase peek(PriorityQueue* pq) {
    if (pq->size == 0) {
        EmergencyCase empty = {0};
        return empty;
    }
    return pq->queue[0];
}

