#include<stdio.h>
#include<stdlib.h>

#define HASH_SIZE 10007

typedef struct Node
{
    int key;
    int value;
    struct Node* prev;
    struct Node* next;
}Node;

typedef struct Entry 
{
    int key;
    Node* node;
    struct Entry* next;
}Entry;


typedef struct {
    int capacity;
    int size;
    Entry* hashTable[HASH_SIZE];
    Node* head;
    Node* tail;   
} LRUCache;

unsigned int hash(int key)
{
    return key % HASH_SIZE;
}

//create Node
Node* createNode(int key, int value)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->value = value;
    node->prev = node->next = NULL;
    return node;
}

//add Node to head
void addToHead(LRUCache* object, Node* node)
{
    node->next = object->head;
    node->prev = NULL;

    if(object->head)
    {
        object->head->prev = node;
    }
    object->head = node;

    if(!object->tail)
    {
        object->tail = node;
    }
}

//remove Node
void removeNode(LRUCache* object, Node* node)
{
    if(node->prev)
    {
        node->prev->next = node->next;
    }
    else
    {
        object->head = node->next;
    }

    if(node->next)
    {
        node->next->prev = node->prev;
    }
    else
    {
        object->tail = node->prev;
    }
}

//remove from Tail
Node* removeTail(LRUCache* object)
{
    Node* tail = object->tail;
    removeNode(object, tail);
    return tail;
}

//moveToHead
void moveToHead(LRUCache* object, Node* node)
{
    removeNode(object, node);
    addToHead(object, node);
}

Entry* hashGetEntry(LRUCache* object, int key)
{
    unsigned int hashValue = hash(key);
    Entry* entry = object->hashTable[hashValue];

    while (entry){
        if(entry->key == key)
        {
            return entry;
        }

        entry = entry->next;
    }

    return NULL;
}

//hashget
Node* hashGet(LRUCache* object, int key)
{
    Entry* entry = hashGetEntry(object, key);
    return entry ? entry->node : NULL;
}



//hashput
void hashPut(LRUCache* object, int key, Node* node)
{
    Entry* entry = hashGetEntry(object, key);

    if(entry)
    {
        entry->node = node;
    }
    else
    {
        unsigned int hashValue = hash(key);

        Entry* newEntry = (Entry*)malloc(sizeof(Entry));

        newEntry->key = key;
        newEntry->node = node;
        newEntry->next = object->hashTable[hashValue];
        object->hashTable[hashValue] = newEntry;
    }  
}

//hashremove
void hashRemove(LRUCache* object, int key)
{
    unsigned int hashValue = hash(key);
    Entry* entry = object->hashTable[hashValue];
    Entry* prev = NULL;

    while(entry)
    {
        if(entry->key == key)
        {
            if(prev)
            {
                prev->next = entry->next;
            }
            else
            {
                object->hashTable[hashValue] = entry->next;
            }

            free(entry);
            return;
        }

        prev = entry;
        entry = entry->next;
    }
}


LRUCache* lRUCacheCreate(int capacity) {
    LRUCache* object = (LRUCache*)malloc(sizeof(LRUCache));
    object->capacity = capacity;
    object->size = 0;
    object->head = object->tail = NULL;

    for (int iterator = 0; iterator <  HASH_SIZE; iterator++)
    {
        object->hashTable[iterator] = NULL;
    }
    return object;
}

int lRUCacheGet(LRUCache* obj, int key) {
    Node* node = hashGet(obj, key);

    if(!node)
    {
        return -1;
    }
    moveToHead(obj, node);
    return node->value;
}

void lRUCachePut(LRUCache* obj, int key, int value) {
    Node* node = hashGet(obj, key);

    if(node)
    {
        node->value = value;
        moveToHead(obj, node);
    }
    else
    {
        Node* newNode = createNode(key, value);
        addToHead(obj, newNode);
        hashPut(obj, key, newNode);
        obj->size++;

        if(obj->size > obj->capacity)
        {
            Node* tail = removeTail(obj);
            hashRemove(obj, tail->key);
            free(tail);
            obj->size--;
        }
    }
}

void lRUCacheFree(LRUCache* obj) {
    Node* current = obj->head;

    while(current)
    {
        Node* next = current->next;
        free(current);
        current = next;
    }

    for(int iterator = 0; iterator < HASH_SIZE; iterator++)
    {
        Entry* entry = obj->hashTable[iterator];
        while(entry)
        {
            Entry* next = entry->next;
            free(entry);
            entry = next;
        }
    }
    free(obj);
}