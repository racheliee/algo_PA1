#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_SIZE 10

typedef struct {
    int capacity;
    int size;
    int* heap;
} MinMaxHeap;

void swap(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

MinMaxHeap* createMinMaxHeap() {
    MinMaxHeap* minMaxHeap = (MinMaxHeap*)malloc(sizeof(MinMaxHeap));
    minMaxHeap->capacity = DEFAULT_SIZE;
    minMaxHeap->size = 0;
    minMaxHeap->heap = (int*)malloc(sizeof(int) * DEFAULT_SIZE);
    return minMaxHeap;
}

MinMaxHeap* createMinMaxHeapWithSize(int size) {
    MinMaxHeap* minMaxHeap = (MinMaxHeap*)malloc(sizeof(MinMaxHeap));
    minMaxHeap->capacity = size;
    minMaxHeap->size = 0;
    minMaxHeap->heap = (int*)malloc(sizeof(int) * size);
    return minMaxHeap;
}

MinMaxHeap* createMinMaxHeapFromArray(int* arr, int size) {
    MinMaxHeap* minMaxHeap = createMinMaxHeapWithSize(size);
    for (int i = 0; i < size; i++) {
        minMaxHeap->heap[i] = arr[i];
        minMaxHeap->size++;
    }
    for (int i = (minMaxHeap->size - 2) / 2; i >= 0; i--) {
        trickleDown(minMaxHeap, i);
    }
    return minMaxHeap;
}

void insert(MinMaxHeap* minMaxHeap, int item) {
    if (minMaxHeap->size >= minMaxHeap->capacity) {
        while (minMaxHeap->size >= minMaxHeap->capacity) {
            resize(minMaxHeap);
        }
    }

    minMaxHeap->heap[minMaxHeap->size] = item;
    bubbleUp(minMaxHeap, minMaxHeap->size);
    minMaxHeap->size++;
}

int getMin(MinMaxHeap* minMaxHeap) {
    if (minMaxHeap->size == 0)
        return -1;
    return minMaxHeap->heap[0];
}

int popMin(MinMaxHeap* minMaxHeap) {
    int temp = minMaxHeap->heap[0];
    minMaxHeap->size--;
    minMaxHeap->heap[0] = minMaxHeap->heap[minMaxHeap->size];
    trickleDown(minMaxHeap, 0);
    return temp;
}

int getMax(MinMaxHeap* minMaxHeap) {
    int index = getMaxIndex(minMaxHeap);
    if (index == -1)
        return -1;
    return minMaxHeap->heap[index];
}

int popMax(MinMaxHeap* minMaxHeap) {
    int index = getMaxIndex(minMaxHeap);
    if (index == -1)
        return -1;
    int temp = minMaxHeap->heap[index];
    minMaxHeap->size--;
    minMaxHeap->heap[index] = minMaxHeap->heap[minMaxHeap->size];
    trickleDown(minMaxHeap, index);
    return temp;
}

int size(MinMaxHeap* minMaxHeap) {
    return minMaxHeap->size;
}

void clear(MinMaxHeap* minMaxHeap) {
    free(minMaxHeap->heap);
    minMaxHeap->heap = (int*)malloc(sizeof(int) * minMaxHeap->capacity);
    minMaxHeap->size = 0;
}

int getMaxIndex(MinMaxHeap* minMaxHeap) {
    switch (minMaxHeap->size) {
        case 0:
            return -1;
        case 1:
            return 0;
        case 2:
            return 1;
        default:
            if (minMaxHeap->heap[1] > minMaxHeap->heap[2])
                return 1;
            return 2;
    }
}

int getLevelOfTree(int index) {
    int level = 0;
    int nodeNumber = index;
    while (nodeNumber != 0) {
        if (nodeNumber % 2 == 0)
            nodeNumber = nodeNumber - 1;
        nodeNumber = nodeNumber / 2;
        level = level + 1;
    }
    return level;
}

int isMinLevel(int index) {
    return getLevelOfTree(index) % 2 == 0;
}

void trickleDown(MinMaxHeap* minMaxHeap, int index) {
    if (isMinLevel(index))
        trickleDownMin(minMaxHeap, index);
    else
        trickleDownMax(minMaxHeap, index);
}

void trickleDownMin(MinMaxHeap* minMaxHeap, int index) {
    int compareIndex = getIndexSmallestOfChildrenAndGrandChildren(minMaxHeap, index);
    if (compareIndex != -1) {
        if (isGrandChild(minMaxHeap, index, compareIndex) && minMaxHeap->heap[index] > minMaxHeap->heap[compareIndex]) {
            swap(&minMaxHeap->heap[index], &minMaxHeap->heap[compareIndex]);
            if (minMaxHeap->heap[compareIndex] > minMaxHeap->heap[(compareIndex - 1) / 2])
                swap(&minMaxHeap->heap[compareIndex], &minMaxHeap->heap[(compareIndex - 1) / 2]);
            trickleDownMin(minMaxHeap, compareIndex);
        } else if (isChild(minMaxHeap, index, compareIndex) && minMaxHeap->heap[index] > minMaxHeap->heap[compareIndex]) {
            swap(&minMaxHeap->heap[index], &minMaxHeap->heap[compareIndex]);
        }
    }
}

int getIndexSmallestOfChildrenAndGrandChildren(MinMaxHeap* minMaxHeap, int index) {
    if (minMaxHeap->size - 1 < 2 * index + 1)
        return -1;

    int minIndex = 2 * index + 1;
    int min = minMaxHeap->heap[minIndex];

    if (2 * index + 2 <= minMaxHeap->size - 1 && min > minMaxHeap->heap[2 * index + 2]) {
        minIndex = 2 * index + 2;
        min = minMaxHeap->heap[minIndex];
    }

    if (4 * index + 3 <= minMaxHeap->size - 1 && min > minMaxHeap->heap[4 * index + 3]) {
        minIndex = 4 * index + 3;
        min = minMaxHeap->heap[minIndex];
    }

    if (4 * index + 4 <= minMaxHeap->size - 1 && min > minMaxHeap->heap[4 * index + 4]) {
        minIndex = 4 * index + 4;
        min = minMaxHeap->heap[minIndex];
    }

    if (4 * index + 5 <= minMaxHeap->size - 1 && min > minMaxHeap->heap[4 * index + 5]) {
        minIndex = 4 * index + 5;
        min = minMaxHeap->heap[minIndex];
    }

    if (4 * index + 6 <= minMaxHeap->size - 1 && min > minMaxHeap->heap[4 * index + 6]) {
        minIndex = 4 * index + 6;
    }

    return minIndex;
}

void trickleDownMax(MinMaxHeap* minMaxHeap, int index) {
    int compareIndex = getIndexBiggestOfChildrenAndGrandChildren(minMaxHeap, index);
    if (compareIndex != -1) {
        if (isGrandChild(minMaxHeap, index, compareIndex) && minMaxHeap->heap[index] < minMaxHeap->heap[compareIndex]) {
            swap(&minMaxHeap->heap[index], &minMaxHeap->heap[compareIndex]);
            if (minMaxHeap->heap[compareIndex] < minMaxHeap->heap[(compareIndex - 1) / 2])
                swap(&minMaxHeap->heap[compareIndex], &minMaxHeap->heap[(compareIndex - 1) / 2]);
            trickleDownMax(minMaxHeap, compareIndex);
        } else if (isChild(minMaxHeap, index, compareIndex) && minMaxHeap->heap[index] < minMaxHeap->heap[compareIndex]) {
            swap(&minMaxHeap->heap[index], &minMaxHeap->heap[compareIndex]);
        }
    }
}

int getIndexBiggestOfChildrenAndGrandChildren(MinMaxHeap* minMaxHeap, int index) {
    if (minMaxHeap->size - 1 < 2 * index + 1)
        return -1;

    int maxIndex = 2 * index + 1;
    int max = minMaxHeap->heap[maxIndex];

    if (2 * index + 2 <= minMaxHeap->size - 1 && max < minMaxHeap->heap[2 * index + 2]) {
        maxIndex = 2 * index + 2;
        max = minMaxHeap->heap[maxIndex];
    }

    if (4 * index + 3 <= minMaxHeap->size - 1 && max < minMaxHeap->heap[4 * index + 3]) {
        maxIndex = 4 * index + 3;
        max = minMaxHeap->heap[maxIndex];
    }

    if (4 * index + 4 <= minMaxHeap->size - 1 && max < minMaxHeap->heap[4 * index + 4]) {
        maxIndex = 4 * index + 4;
        max = minMaxHeap->heap[maxIndex];
    }

    if (4 * index + 5 <= minMaxHeap->size - 1 && max < minMaxHeap->heap[4 * index + 5]) {
        maxIndex = 4 * index + 5;
        max = minMaxHeap->heap[maxIndex];
    }

    if (4 * index + 6 <= minMaxHeap->size - 1 && max < minMaxHeap->heap[4 * index + 6]) {
        maxIndex = 4 * index + 6;
    }

    return maxIndex;
}

int isChild(MinMaxHeap* minMaxHeap, int parent, int child) {
    if (2 * parent + 1 <= child && child <= 2 * parent + 2)
        return 1;
    return 0;
}

int isGrandChild(MinMaxHeap* minMaxHeap, int gParent, int gChild) {
    if (4 * gParent + 3 <= gChild && gChild <= 4 * gParent + 6)
        return 1;
    return 0;
}

void bubbleUp(MinMaxHeap* minMaxHeap, int index) {
    if (index < 1)
        return;

    if (isMinLevel(index)) {
        if (minMaxHeap->heap[index] > minMaxHeap->heap[(index - 1) / 2]) {
            swap(&minMaxHeap->heap[index], &minMaxHeap->heap[(index - 1) / 2]);
            bubbleUpMax(minMaxHeap, (index - 1) / 2);
        } else {
            bubbleUpMin(minMaxHeap, index);
        }
    } else {
        if (minMaxHeap->heap[index] < minMaxHeap->heap[(index - 1) / 2]) {
            swap(&minMaxHeap->heap[index], &minMaxHeap->heap[(index - 1) / 2]);
            bubbleUpMin(minMaxHeap, (index - 1) / 2);
        } else {
            bubbleUpMax(minMaxHeap, index);
        }
    }
}

void bubbleUpMin(MinMaxHeap* minMaxHeap, int index) {
    if (index < 3)
        return;
    if (minMaxHeap->heap[index] < minMaxHeap->heap[(index - 3) / 4]) {
        swap(&minMaxHeap->heap[index], &minMaxHeap->heap[(index - 3) / 4]);
        bubbleUpMin(minMaxHeap, (index - 3) / 4);
    }
}

void bubbleUpMax(MinMaxHeap* minMaxHeap, int index) {
    if (index < 3)
        return;
    if (minMaxHeap->heap[index] > minMaxHeap->heap[(index - 3) / 4]) {
        swap(&minMaxHeap->heap[index], &minMaxHeap->heap[(index - 3) / 4]);
        bubbleUpMax(minMaxHeap, (index - 3) / 4);
    }
}

void resize(MinMaxHeap* minMaxHeap) {
    minMaxHeap->capacity *= 2;
    minMaxHeap->heap = (int*)realloc(minMaxHeap->heap, sizeof(int) * minMaxHeap->capacity);
}

int main() {
    MinMaxHeap* minMaxHeap = createMinMaxHeap();

    insert(minMaxHeap, 3);
    insert(minMaxHeap, 1);
    insert(minMaxHeap, 2);

    printf("Min element: %d\n", getMin(minMaxHeap));
    printf("Pop min element: %d\n", popMin(minMaxHeap));

    insert(minMaxHeap, 5);
    insert(minMaxHeap, 4);

    printf("Max element: %d\n", getMax(minMaxHeap));
    printf("Pop max element: %d\n", popMax(minMaxHeap));

    free(minMaxHeap->heap);
    free(minMaxHeap);

    return 0;
}
