#include <stdio.h>
#include <stdlib.h>

typedef struct AVLNode {
    int val;
    int count;     // number of duplicates of val
    int size;      // total number of nodes in this subtree
    int height;
    struct AVLNode* left;
    struct AVLNode* right;
} AVLNode;

int height(AVLNode* node) {
    return node ? node->height : 0;
}

int size(AVLNode* node) {
    return node ? node->size : 0;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

AVLNode* newNode(int val) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    node->val = val;
    node->count = 1;
    node->size = 1;
    node->height = 1;
    node->left = node->right = NULL;
    return node;
}

void update(AVLNode* node) {
    if (!node) return;
    node->height = 1 + max(height(node->left), height(node->right));
    node->size = node->count + size(node->left) + size(node->right);
}

int getBalance(AVLNode* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

// Right rotation
AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    update(y);
    update(x);

    return x;
}

// Left rotation
AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    update(x);
    update(y);

    return y;
}

/**
 * Insert value into AVL tree, while updating "smaller" count.
 */
AVLNode* insertAVL(AVLNode* node, int val, int* smaller) {
    if (node == NULL) {
        return newNode(val);
    }

    if (val == node->val) {
        node->count++;
        *smaller += size(node->left);
    } else if (val < node->val) {
        node->left = insertAVL(node->left, val, smaller);
    } else { // val > node->val
        *smaller += size(node->left) + node->count;
        node->right = insertAVL(node->right, val, smaller);
    }

    update(node);

    int balance = getBalance(node);

    // LL
    if (balance > 1 && val < node->left->val)
        return rightRotate(node);

    // RR
    if (balance < -1 && val > node->right->val)
        return leftRotate(node);

    // LR
    if (balance > 1 && val > node->left->val) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // RL
    if (balance < -1 && val < node->right->val) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void freeAVL(AVLNode* root) {
    if (!root) return;
    freeAVL(root->left);
    freeAVL(root->right);
    free(root);
}

int* countSmaller(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;
    int* result = (int*)malloc(numsSize * sizeof(int));
    AVLNode* root = NULL;

    for (int i = numsSize - 1; i >= 0; i--) {
        int smaller = 0;
        root = insertAVL(root, nums[i], &smaller);
        result[i] = smaller;
    }

    freeAVL(root);
    return result;
}t