/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
#include <stdio.h>
#include <stdlib.h>
struct TreeNode* newNode(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = node->right = NULL;
    return node;
}

void inorder(struct TreeNode* root, int* arr, int* idx) {
    if (!root) return;
    inorder(root->left, arr, idx);
    arr[(*idx)++] = root->val;
    inorder(root->right, arr, idx);
}


struct TreeNode* buildBST(int* arr, int l, int r) {
    if (l > r) return NULL;
    int mid = l + (r - l) / 2;
    struct TreeNode* root = newNode(arr[mid]);
    root->left = buildBST(arr, l, mid - 1);
    root->right = buildBST(arr, mid + 1, r);
    return root;
}


struct TreeNode* balanceBST(struct TreeNode* root) {
    
    int arr[10000]; 
    int idx = 0;
    inorder(root, arr, &idx);

    return buildBST(arr, 0, idx - 1);
}