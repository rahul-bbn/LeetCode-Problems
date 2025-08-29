<<<<<<< HEAD
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int maxDepth(struct TreeNode* root) {
    int left,right;
    if(root==NULL){
        return 0;
    }
    left=maxDepth(root->left)+1;
    right=maxDepth(root->right)+1;

    return left>right?left:right;
    
}
=======
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int maxDepth(struct TreeNode* root) {
    int left,right;
    if(root==NULL){
        return 0;
    }
    left=maxDepth(root->left)+1;
    right=maxDepth(root->right)+1;

    return left>right?left:right;
    
}
>>>>>>> 3a12b13235e62db151d7ffefc36abc2501b6336c
