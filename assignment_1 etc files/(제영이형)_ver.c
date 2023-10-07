#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 1000
typedef struct _MinMaxHeap {
    int* storage;
    int indicator;  // 마지막 요소의 index
} MinMaxHeap;

void initMinMaxHeap(MinMaxHeap* h) {
    h->storage = (int*)malloc(sizeof(int) * (MAX_SIZE + 1));
    h->indicator = 0;
}
int addItemToStorage(MinMaxHeap* h, int item) {
    h->storage[++h->indicator] = item;
    return h->indicator;
}

int isMaxLevel(int index) { return (int)log2(index) & 1; }
int isMinLevel(int index) { return !((int)log2(index) & 1); }
void swap(MinMaxHeap* h, int a, int b) {
    int temp = h->storage[a];
    h->storage[a] = h->storage[b];
    h->storage[b] = temp;
}
int getValue(MinMaxHeap* h, int index) { return h->storage[index]; }
int getParentIndex(int index) { return index / 2; }
int getGrandParentIndex(int index) { return index / 4; }
int getLeftChildIndex(int index) { return 2 * index; }
int getRightChildIndex(int index) { return ((2 * index) + 1); }

int isExist(MinMaxHeap* h, int index) { return index <= h->indicator && index >= 1; }
int isLesserThanParent(MinMaxHeap* h, int index) { return h->storage[index] < h->storage[getParentIndex(index)]; }
int isGreaterThanParent(MinMaxHeap* h, int index) { return h->storage[index] > h->storage[getParentIndex(index)]; }
int isLesserThanGrandParent(MinMaxHeap* h, int index) { return h->storage[index] < h->storage[getGrandParentIndex(index)]; }
int isGreaterThanGrandParent(MinMaxHeap* h, int index) { return h->storage[index] > h->storage[getGrandParentIndex(index)]; }
int hasGrandParent(int index) { return getGrandParentIndex(index) >= 1; }

void pushUpMin(MinMaxHeap* h, int index) {
    while (hasGrandParent(index) && isLesserThanGrandParent(h, index)) {
        int grandParentIndex = getGrandParentIndex(index);
        swap(h, index, grandParentIndex);
        index = grandParentIndex;
    }
}
void pushUpMax(MinMaxHeap* h, int index) {
    while (hasGrandParent(index) && isGreaterThanGrandParent(h, index)) {
        int grandParentIndex = getGrandParentIndex(index);
        swap(h, index, grandParentIndex);
        index = grandParentIndex;
    }
}
void pushUp(MinMaxHeap* h, int index) {
    if (index == 1) return;
    if (isMinLevel(index) && isLesserThanParent(h, index)) pushUpMin(h, index);
    if (isMinLevel(index) && isGreaterThanParent(h, index)) {
        int parentIndex = getParentIndex(index);
        swap(h, index, parentIndex);
        pushUpMax(h, parentIndex);
    }
    if (isMaxLevel(index) && isGreaterThanParent(h, index)) pushUpMax(h, index);
    if (isMaxLevel(index) && isLesserThanParent(h, index)) {
        int parentIndex = getParentIndex(index);
        swap(h, index, parentIndex);
        pushUpMin(h, parentIndex);
    }
}
void insertToMinMaxHeap(MinMaxHeap* h, int item) {
    if (h->indicator == 0) {
        addItemToStorage(h, item);
    } else if (h->indicator <= MAX_SIZE) {
        int itemIndex = addItemToStorage(h, item);
        pushUp(h, itemIndex);
    } else
        exit(0);
}
int getIndexOfSmallestDescendant(MinMaxHeap* h, int index) {
    int minIndex = getLeftChildIndex(index);
    int minValue = getValue(h, minIndex);

    int rightChildIndex = getRightChildIndex(index);
    int rightChildValue = getValue(h, rightChildIndex);
    if (isExist(h, rightChildIndex)) {
        if (rightChildValue < minValue) {
            minIndex = rightChildIndex;
            minValue = rightChildValue;
        }
    } else
        return minIndex;

    int leftleftChildIndex = getLeftChildIndex(getLeftChildIndex(index));
    int leftleftChildValue = getValue(h, leftleftChildIndex);
    if (isExist(h, leftleftChildIndex)) {
        if (leftleftChildValue < minValue) {
            minIndex = leftleftChildIndex;
            minValue = leftleftChildValue;
        }
    } else
        return minIndex;

    int leftrightChildIndex = getRightChildIndex(getLeftChildIndex(index));
    int leftrightChildValue = getValue(h, leftrightChildIndex);
    if (isExist(h, leftrightChildIndex)) {
        if (leftrightChildValue < minValue) {
            minIndex = leftrightChildIndex;
            minValue = leftrightChildValue;
        } else
            return minIndex;
    }

    int rightleftChildIndex = getLeftChildIndex(getRightChildIndex(index));
    int rightleftChildValue = getValue(h, rightleftChildIndex);
    if (isExist(h, rightleftChildIndex)) {
        if (rightleftChildValue < minValue) {
            minIndex = rightleftChildIndex;
            minValue = rightleftChildValue;
        }
    } else
        return minIndex;

    int rightrightChildIndex = getRightChildIndex(getRightChildIndex(index));
    int rightrightChildValue = getValue(h, rightrightChildIndex);
    if (isExist(h, rightrightChildIndex)) {
        if (rightrightChildValue < minValue) {
            minIndex = rightrightChildIndex;
            minValue = rightrightChildValue;
        }
    } else
        return minIndex;
    exit(0);
}
int getIndexOfBiggestDescendant(MinMaxHeap* h, int index) {
    int maxIndex = getLeftChildIndex(index);
    int maxValue = getValue(h, maxIndex);

    int rightChildIndex = getRightChildIndex(index);
    int rightChildValue = getValue(h, rightChildIndex);
    if (isExist(h, rightChildIndex)) {
        if (rightChildValue > maxValue) {
            maxValue = rightChildIndex;
            maxIndex = rightChildValue;
        }
    } else
        return maxIndex;

    int leftleftChildIndex = getLeftChildIndex(getLeftChildIndex(index));
    int leftleftChildValue = getValue(h, leftleftChildIndex);
    if (isExist(h, leftleftChildIndex)) {
        if (leftleftChildValue > maxValue) {
            maxIndex = leftleftChildIndex;
            maxValue = leftleftChildValue;
        }
    } else
        return maxIndex;

    int leftrightChildIndex = getRightChildIndex(getLeftChildIndex(index));
    int leftrightChildValue = getValue(h, leftrightChildIndex);
    if (isExist(h, leftrightChildIndex)) {
        if (leftrightChildValue > maxValue) {
            maxIndex = leftrightChildIndex;
            maxValue = leftrightChildValue;
        }
    } else
        return maxIndex;

    int rightleftChildIndex = getLeftChildIndex(getRightChildIndex(index));
    int rightleftChildValue = getValue(h, rightleftChildIndex);
    if (isExist(h, rightleftChildIndex)) {
        if (rightleftChildValue > maxValue) {
            maxIndex = rightleftChildIndex;
            maxValue = rightleftChildValue;
        }
    } else
        return maxIndex;

    int rightrightChildIndex = getRightChildIndex(getRightChildIndex(index));
    int rightrightChildValue = getValue(h, rightrightChildIndex);
    if (isExist(h, rightrightChildIndex)) {
        if (rightrightChildValue > maxValue) {
            maxIndex = rightrightChildIndex;
            maxValue = rightrightChildValue;
        }
    } else
        return maxIndex;
    exit(0);
}
void pushDownMin(MinMaxHeap* h, int index) {
    while (isExist(h, getLeftChildIndex(index))) {
        int indexOfSmallest = getIndexOfSmallestDescendant(h, index);
        if (getValue(h, indexOfSmallest) < getValue(h, index)) {
            if (getGrandParentIndex(indexOfSmallest) == index) {
                if (getValue(h, indexOfSmallest) < getValue(h, index)) {
                    swap(h, indexOfSmallest, index);
                    if (getValue(h, indexOfSmallest) > getValue(h, getParentIndex(indexOfSmallest))) {
                        swap(h, indexOfSmallest, getParentIndex(indexOfSmallest));
                    }
                }
            } else if (getValue(h, indexOfSmallest) < getValue(h, index)) {
                swap(h, indexOfSmallest, index);
            }

        } else
            break;
        index = indexOfSmallest;
    }
}
void pushDownMax(MinMaxHeap* h, int index) {  // 오류나면 여기부터 볼 것.
    while (isExist(h, getLeftChildIndex(index))) {
        int indexOfBiggest = getIndexOfBiggestDescendant(h, index);
        if (getValue(h, indexOfBiggest) > getValue(h, index)) {
            if (getGrandParentIndex(indexOfBiggest) == index) {
                if (getValue(h, indexOfBiggest) > getValue(h, index)) {
                    swap(h, indexOfBiggest, index);
                    if (getValue(h, indexOfBiggest) < getValue(h, getParentIndex(indexOfBiggest))) {
                        swap(h, indexOfBiggest, getParentIndex(indexOfBiggest));
                    }
                }
            } else if (getValue(h, indexOfBiggest) > getValue(h, index)) {
                swap(h, indexOfBiggest, index);
            }

        } else
            break;
        index = indexOfBiggest;
    }
}
void pushDown(MinMaxHeap* h, int index) {
    if (isMinLevel(index)) pushDownMin(h, index);
    if (isMaxLevel(index)) pushDownMax(h, index);
}
int removeLocalMin(MinMaxHeap* h) {
    // 필요하면 갯수 0개일 때 방어 처리
    int localMinValue = getValue(h, 1);
    if (h->indicator == 1) {
        h->indicator -= 1;
        return localMinValue;
    }
    swap(h, 1, h->indicator--);
    pushDown(h, 1);
    return localMinValue;
}
int removeLocalMax(MinMaxHeap* h) {
    // 필요하면 갯수 0개일 때 방어 처리
    int localMaxValue;
    int localMaxIndex;
    if (h->indicator == 1) {
        localMaxValue = getValue(h, 1);
        h->indicator -= 1;
        return localMaxValue;
    }
    if (h->indicator == 2) {
        localMaxValue = getValue(h, 2);
        h->indicator -= 1;
        return localMaxValue;
    }
    if (h->indicator > 2) {
        localMaxIndex = getValue(h, 2) > getValue(h, 3) ? 2 : 3;
        localMaxValue = getValue(h, localMaxIndex);
    }
    swap(h, localMaxIndex, h->indicator--);
    pushDown(h, localMaxIndex);
    return localMaxValue;
}
int getLocalMax(MinMaxHeap* h) {
    if (h->indicator == 1) return getValue(h, 1);
    if (h->indicator == 2) return getValue(h, 2);
    if (h->indicator > 2) return getValue(h, 2) > getValue(h, 3) ? getValue(h, 2) : getValue(h, 3);
    exit(0);
}
int getLocalMin(MinMaxHeap* h) { return getValue(h, 1); }

typedef struct _MinMaxMedianHeap {
    MinMaxHeap* lesserHalf;
    MinMaxHeap* largerHalf;
} MinMaxMedianHeap;

void initMinMaxMedianHeap(MinMaxMedianHeap* h) {
    initMinMaxHeap(h->lesserHalf);
    initMinMaxHeap(h->largerHalf);
}

void insertToMinMaxMedianHeap(MinMaxMedianHeap* h, int item) {
    if (h->largerHalf->indicator + h->lesserHalf->indicator == 0) {
        insertToMinMaxHeap(h->lesserHalf, item);
        return;
    } else if (h->lesserHalf->indicator > h->largerHalf->indicator) {
        if (getLocalMax(h->lesserHalf) > item) {
            int lesserMax = removeLocalMax(h->lesserHalf);
            insertToMinMaxHeap(h->lesserHalf, item);
            insertToMinMaxHeap(h->largerHalf, lesserMax);
        } else if (getLocalMax(h->lesserHalf) <= item) {
            insertToMinMaxHeap(h->largerHalf, item);
        }
    } else if (h->lesserHalf->indicator == h->largerHalf->indicator) {
        if (getLocalMin(h->largerHalf) < item) {
            int largerMin = removeLocalMin(h->largerHalf);
            insertToMinMaxHeap(h->largerHalf, item);
            insertToMinMaxHeap(h->lesserHalf, largerMin);
        } else if (getLocalMin(h->largerHalf) >= item) {
            insertToMinMaxHeap(h->lesserHalf, item);
        }
    }
}
int getGlobalMin(MinMaxMedianHeap* h) { return getLocalMin(h->lesserHalf); }
int getGlobalMax(MinMaxMedianHeap* h) { return getLocalMax(h->largerHalf); }
int getGlobalMedian(MinMaxMedianHeap* h) { return getLocalMax(h->lesserHalf); }
int removeGlobalMin(MinMaxMedianHeap* h) {
    int globalMin = removeLocalMin(h->lesserHalf);
    if (h->lesserHalf->indicator < h->largerHalf->indicator) {
        int balance = removeLocalMin(h->largerHalf);
        insertToMinMaxHeap(h->lesserHalf, balance);
    }
    return globalMin;
}
int removeGlobalMax(MinMaxMedianHeap* h) {
    int globalMax = removeLocalMax(h->largerHalf);
    if (h->lesserHalf->indicator - h->largerHalf->indicator > 1) {
        int balance = removeLocalMax(h->lesserHalf);
        insertToMinMaxHeap(h->largerHalf, balance);
    }
    return globalMax;
}
int removeGlobalMedian(MinMaxMedianHeap* h) {
    int globalMedian = removeLocalMax(h->lesserHalf);
    if (h->lesserHalf->indicator < h->largerHalf->indicator) {
        int balance = removeLocalMin(h->largerHalf);
        insertToMinMaxHeap(h->lesserHalf, balance);
    }
    return globalMedian;
}

int main() { return 0; }