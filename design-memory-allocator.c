typedef struct {
    int *memory;
    int size;
    int **mIDPositions;
    int *mIDCounts;
    
} Allocator;


Allocator* allocatorCreate(int n) {
    Allocator *obj = (Allocator*)calloc(1, sizeof(Allocator));
    obj->memory = (int*)calloc(n, sizeof(int));
    obj->size = n;
    obj->mIDPositions = (int**)calloc(1001, sizeof(int*));
    obj->mIDCounts = (int*)calloc(1001, sizeof(int));

    return obj;
}

int allocatorAllocate(Allocator* obj, int size, int mID) {
    int count = 0;

    for (int iterator = 0; iterator < obj->size; iterator++)
    {
        if(obj->memory[iterator] == 0)
        {
            count++;
        }
        else{
            count = 0;
        }

        if(count == size)
        {
            int start = iterator - size + 1;
            obj->mIDPositions[mID] = realloc(obj->mIDPositions[mID], sizeof(int) * (obj->mIDCounts[mID]+size));
        

            for (int jterator = 0; jterator < size; jterator++)
            {
                obj->memory[start + jterator] = mID;
                obj->mIDPositions[mID][obj->mIDCounts[mID]++] = start + jterator;
            }

            return start;
        }
    }
    
    return -1;
}

int allocatorFreeMemory(Allocator* obj, int mID) {
    int freed = obj->mIDCounts[mID];

    for (int iterator = 0; iterator < obj->mIDCounts[mID]; iterator++)
    {
        obj->memory[obj->mIDPositions[mID][iterator]] = 0;
    }

    free(obj->mIDPositions[mID]);

    obj->mIDPositions[mID] = NULL;
    obj->mIDCounts[mID] = 0;

    return freed;
}

void allocatorFree(Allocator* obj) {
    for (int iterator = 0; iterator <= 1000; iterator++)
    {
        free(obj->mIDPositions[iterator]);
    }

    free(obj->mIDPositions);
    free(obj->mIDCounts);
    free(obj->memory);
    free(obj);
}