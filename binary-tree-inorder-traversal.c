<<<<<<< HEAD
void dfs(struct TreeNode* root, int* res, int* idx) {
    if (root == NULL) return;
    dfs(root->left, res, idx);
    res[(*idx)++] = root->val;
    dfs(root->right, res, idx);
}

int* inorderTraversal(struct TreeNode* root, int* returnSize) {
    int* res = (int*)malloc(100 * sizeof(int));  // assuming max 1000 nodes
    int idx = 0;
    dfs(root, res, &idx);
    *returnSize = idx;
    return res;
}
=======
void dfs(struct TreeNode* root, int* res, int* idx) {
    if (root == NULL) return;
    dfs(root->left, res, idx);
    res[(*idx)++] = root->val;
    dfs(root->right, res, idx);
}

int* inorderTraversal(struct TreeNode* root, int* returnSize) {
    int* res = (int*)malloc(100 * sizeof(int));  // assuming max 1000 nodes
    int idx = 0;
    dfs(root, res, &idx);
    *returnSize = idx;
    return res;
}
>>>>>>> 3a12b13235e62db151d7ffefc36abc2501b6336c
