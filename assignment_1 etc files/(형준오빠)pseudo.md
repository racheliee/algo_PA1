# structure priority queue

#define MAX_SIZE 500000

typedef struct priorityQueue{
    int pq.lh[MAX_SIZE/2+2]
    int pq.bh[MAX_SIZE/2+2]
} priorityQueue;

priorityQueue pq

## Insert

```c
insert(int element) { 
    if (both pq.lh & pq.bh is empty) {
        append in pq.bh
        adjust pq.bh
    }
    if (element > median) {
        append in pq.bh
        adjust pq.bh
        if (# pq.bh.element > # pq.lh.element + 2) {
            extract pq.bh.min (= median) & append to pq.lh
            adjust pq.lh & pq.bh
        }
    }
    else if (element < median) {
        append in pq.lh
        adjust pq.lh
        if (# pq.bh.element == # pq.lh.element) {
            extract pq.lh.max ( = median) & append to pq.bh
            adjust pq.lh & pq.bh
        }
    }
}
```

## Find (both heap empty case 고려 X)
```c
find_min() {
    return pq.lh.min
}

find_max() {
    return pq.bh.max
}

find_median() {
    return pq.bh.min
}
```
## Delete (both heap empty case 고려 X)
```c
delete_min() {
    extract pq.lh.min
    adjust pq.lh
    if (# pq.bh.element > # pq.lh.element + 1)
        {
            extract pq.bh.min ( = median) & append to pq.lh
            adjust pq.lh & pq.bh
        }
}

delete_max() {
    extract pq.bh.max
    adjust pq.bh
    if (# pq.bh.element == # pq.lh.element) {
            extract pq.lh.max ( = median) & append to pq.bh
            adjust pq.lh & pq.bh
        }
}

delete_median() {
    extract pq.bh.min
    adjust pq.bh
    if (# pq.bh.element == # pq.lh.element) {
            extract pq.lh.max ( = median) & append to pq.bh
            adjust pq.lh & pq.bh
        }
}
```
