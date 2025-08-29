#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    long val;
    int height;
    int size; // number of nodes in this subtree
    struct Node* left;
    struct Node* right;
} Node;

int height(Node* root) {
    return root ? root->height : 0;
}

int size(Node* root) {
    return root ? root->size : 0;
}

Node* newNode(long val) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->val = val;
    n->height = 1;
    n->size = 1;
    n->left = n->right = NULL;
    return n;
}

int max(int a, int b) {
    return a > b ? a : b;
}

void update(Node* root) {
    if (root) {
        root->height = 1 + max(height(root->left), height(root->right));
        root->size = 1 + size(root->left) + size(root->right);
    }
}

int balanceFactor(Node* root) {
    return root ? height(root->left) - height(root->right) : 0;
}

Node* rotateRight(Node* y) {
    if (!y || !y->left) return y;   // guard
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    update(y);
    update(x);

    return x;
}

Node* rotateLeft(Node* x) {
    if (!x || !x->right) return x;  // guard
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    update(x);
    update(y);

    return y;
}


Node* insert(Node* root, long val) {
    if (!root) return newNode(val);
    if (val < root->val) root->left = insert(root->left, val);
    else root->right = insert(root->right, val);

    update(root);

    int bf = balanceFactor(root);

    // Left Heavy
    if (bf > 1) {
        if (val < root->left->val) {
            return rotateRight(root); // Left-Left
        } else {
            root->left = rotateLeft(root->left); // Left-Right
            return rotateRight(root);
        }
    }

    // Right Heavy
    if (bf < -1) {
        if (val > root->right->val) {
            return rotateLeft(root); // Right-Right
        } else {
            root->right = rotateRight(root->right); // Right-Left
            return rotateLeft(root);
        }
    }

    return root;
}

// count how many nodes <= val
int countLessEqual(Node* root, long val) {
    if (!root) return 0;
    if (root->val <= val)
        return 1 + size(root->left) + countLessEqual(root->right, val);
    else
        return countLessEqual(root->left, val);
}

int countRangeSum(int* nums, int numsSize, int lower, int upper) {
    long sum = 0;
    Node* root = NULL;
    root = insert(root, 0); // prefix[0] = 0
    int count = 0;

    for (int i = 0; i < numsSize; i++) {
        sum += nums[i];
        int high = countLessEqual(root, sum - lower);
        int low  = countLessEqual(root, sum - upper - 1);
        count += high - low;
        root = insert(root, sum);
    }
    return count;
}