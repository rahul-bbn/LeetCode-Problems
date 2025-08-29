#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

typedef struct AVLNode {
    int val, height, count, size;
    struct AVLNode *left, *right;
} AVLNode;

int max(int a, int b){
    return a > b ? a : b;
    }
int height(AVLNode* n){
    return n ? n->height : 0;
    }
int size(AVLNode* n){
    return n ? n->size : 0;
    }

AVLNode* newNode(int val) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    node->val = val;
    node->height = 1;
    node->count = 1;
    node->size = 1;
    node->left = node->right = NULL;
    return node;
}

void update(AVLNode* n) {
    if (!n) return;
    n->height = 1 + max(height(n->left), height(n->right));
    n->size = size(n->left) + size(n->right) + n->count;
}

AVLNode* rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    update(y);
    update(x);
    return x;
}

AVLNode* rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    update(x);
    update(y);
    return y;
}

int getBalance(AVLNode* n) {
    return n ? height(n->left) - height(n->right) : 0;
}

AVLNode* insert(AVLNode* node, int val) {
    if (!node) return newNode(val);

    if (val == node->val) {
        node->count++;
    } else if (val < node->val) {
        node->left = insert(node->left, val);
    } else {
        node->right = insert(node->right, val);
    }

    update(node);

    int balance = getBalance(node);
    if (balance > 1 && val < node->left->val)
        return rotateRight(node);
    if (balance < -1 && val > node->right->val)
        return rotateLeft(node);
    if (balance > 1 && val > node->left->val) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && val < node->right->val) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}

int getSmallerCount(AVLNode* root, int val) {
    if (!root) return 0;
    if (val == root->val) return size(root->left);
    else if (val < root->val) return getSmallerCount(root->left, val);
    else return size(root->left) + root->count + getSmallerCount(root->right, val);
}

int getGreaterCount(AVLNode* root, int val) {
    if (!root) return 0;
    if (val == root->val) return size(root->right);
    else if (val < root->val) return root->count + size(root->right) + getGreaterCount(root->left, val);
    else return getGreaterCount(root->right, val);
}

int createSortedArray(int* instructions, int instructionsSize) {
    AVLNode* root = NULL;
    long long ans = 0;

    for (int i = 0;  i< instructionsSize; i++) {
        int x = instructions[i];
        int smaller = getSmallerCount(root, x);
        int greater = getGreaterCount(root, x);
        ans = (ans + (smaller < greater ? smaller : greater)) % MOD;
        root = insert(root, x);
    }
    return ans;
}