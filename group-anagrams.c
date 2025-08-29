/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#include <string.h>
#include <stdlib.h>
 
int cmpChar(const void* a, const void* b) {
    return (*(char*)a - *(char*)b);
}

int cmpStr(const void* a, const void* b) {
    return strcmp(*(char**)a, *(char**)b);
}

char* sortedKey(const char* s) {
    int len = strlen(s);
    char* key = (char*)malloc(len + 1);
    strcpy(key, s);
    qsort(key, len, sizeof(char), cmpChar);
    return key;
}

char*** groupAnagrams(char** strs, int strsSize, int* returnSize, int** returnColumnSizes) {
    char*** result = (char***)malloc(sizeof(char**) * strsSize);
    *returnColumnSizes = (int*)malloc(sizeof(int) * strsSize);
    char** keys = (char**)malloc(sizeof(char*) * strsSize);
    int groups = 0;

    for (int i = 0; i < strsSize; i++) {
        char* key = sortedKey(strs[i]);
        int found = -1;

        
        for (int g = 0; g < groups; g++) {
            if (strcmp(keys[g], key) == 0) {
                found = g;
                break;
            }
        }

        if (found == -1) {
            
            keys[groups] = key;
            result[groups] = (char**)malloc(sizeof(char*) * strsSize);
            result[groups][0] = strs[i];
            (*returnColumnSizes)[groups] = 1;
            groups++;
        } else {
            
            int idx = (*returnColumnSizes)[found];
            result[found][idx] = strs[i];
            (*returnColumnSizes)[found] += 1;
            free(key);
        }
    }

    *returnSize = groups;
    return result;
}