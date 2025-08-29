#include <stdio.h>
#include <stdlib.h>

// O(n) sliding window max using deque (stores indices)
int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
    if (numsSize == 0 || k == 0) {
        *returnSize = 0;
        return NULL;
    }

    int* result = (int*)malloc((numsSize - k + 1) * sizeof(int));
    int* deque = (int*)malloc(numsSize * sizeof(int)); // store indices
    int front = 0, back = 0; // deque head/tail
    int resIndex = 0;

    for (int i = 0; i < numsSize; i++) {
        // 1. Remove indices from front if they are out of this window
        if (front < back && deque[front] <= i - k) {
            front++;
        }

        // 2. Remove indices from back if nums[i] >= nums[deque[back-1]]
        while (front < back && nums[i] >= nums[deque[back - 1]]) {
            back--;
        }

        // 3. Add current index
        deque[back++] = i;

        // 4. Record max when first window is ready
        if (i >= k - 1) {
            result[resIndex++] = nums[deque[front]];
        }
    }

    *returnSize = resIndex;
    free(deque);
    return result;
}