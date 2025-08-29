#include <stdio.h>
#include <stdlib.h>

#define MAXN 100000   // max number of elements, can be increased

// ---------- Heap Helper ----------
void swap(int* a, int* b) {
    int tmp = *a; *a = *b; *b = tmp;
}

// ----- Max Heap -----
typedef struct {
    int arr[MAXN];
    int size;
} MaxHeap;

void maxHeapPush(MaxHeap* h, int val) {
    int i = h->size++;
    h->arr[i] = val;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (h->arr[p] >= h->arr[i]) break;
        swap(&h->arr[p], &h->arr[i]);
        i = p;
    }
}

int maxHeapTop(MaxHeap* h) {
    return h->arr[0];
}

int maxHeapPop(MaxHeap* h) {
    int top = h->arr[0];
    h->arr[0] = h->arr[--h->size];
    int i = 0;
    while (1) {
        int l = 2 * i + 1, r = 2 * i + 2, largest = i;
        if (l < h->size && h->arr[l] > h->arr[largest]) largest = l;
        if (r < h->size && h->arr[r] > h->arr[largest]) largest = r;
        if (largest == i) break;
        swap(&h->arr[i], &h->arr[largest]);
        i = largest;
    }
    return top;
}

// ----- Min Heap -----
typedef struct {
    int arr[MAXN];
    int size;
} MinHeap;

void minHeapPush(MinHeap* h, int val) {
    int i = h->size++;
    h->arr[i] = val;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (h->arr[p] <= h->arr[i]) break;
        swap(&h->arr[p], &h->arr[i]);
        i = p;
    }
}

int minHeapTop(MinHeap* h) {
    return h->arr[0];
}

int minHeapPop(MinHeap* h) {
    int top = h->arr[0];
    h->arr[0] = h->arr[--h->size];
    int i = 0;
    while (1) {
        int l = 2 * i + 1, r = 2 * i + 2, smallest = i;
        if (l < h->size && h->arr[l] < h->arr[smallest]) smallest = l;
        if (r < h->size && h->arr[r] < h->arr[smallest]) smallest = r;
        if (smallest == i) break;
        swap(&h->arr[i], &h->arr[smallest]);
        i = smallest;
    }
    return top;
}

// ---------- MedianFinder ----------
typedef struct {
    MaxHeap left;   // max-heap for smaller half
    MinHeap right;  // min-heap for larger half
} MedianFinder;

MedianFinder* medianFinderCreate() {
    MedianFinder* obj = (MedianFinder*)malloc(sizeof(MedianFinder));
    obj->left.size = 0;
    obj->right.size = 0;
    return obj;
}

void medianFinderAddNum(MedianFinder* obj, int num) {
    if (obj->left.size == 0 || num <= maxHeapTop(&obj->left)) {
        maxHeapPush(&obj->left, num);
    } else {
        minHeapPush(&obj->right, num);
    }

    // Balance heaps
    if (obj->left.size > obj->right.size + 1) {
        int moved = maxHeapPop(&obj->left);
        minHeapPush(&obj->right, moved);
    } else if (obj->right.size > obj->left.size) {
        int moved = minHeapPop(&obj->right);
        maxHeapPush(&obj->left, moved);
    }
}

double medianFinderFindMedian(MedianFinder* obj) {
    if (obj->left.size > obj->right.size) {
        return (double)maxHeapTop(&obj->left);
    } else {
        return ((double)maxHeapTop(&obj->left) + (double)minHeapTop(&obj->right)) / 2.0;
    }
}

void medianFinderFree(MedianFinder* obj) {
    free(obj);
}

/**
 * Your MedianFinder struct will be instantiated and called as such:
 * MedianFinder* obj = medianFinderCreate();
 * medianFinderAddNum(obj, num);
 
 * double param_2 = medianFinderFindMedian(obj);
 
 * medianFinderFree(obj);
*/