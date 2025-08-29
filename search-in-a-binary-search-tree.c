<<<<<<< HEAD
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
// struct TreeNode* searchBSTHelper(struct TreeNode* root,int val)

struct TreeNode* searchBST(struct TreeNode* root, int val) {
    if(root==NULL || root->val==val){
        return root;
    }
    else if(val<root->val){
        root= searchBST(root->left,val);
    }
    else if(val>root->val){
        root= searchBST(root->right,val);
    }
    return root;
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
// struct TreeNode* searchBSTHelper(struct TreeNode* root,int val)

struct TreeNode* searchBST(struct TreeNode* root, int val) {
    if(root==NULL || root->val==val){
        return root;
    }
    else if(val<root->val){
        root= searchBST(root->left,val);
    }
    else if(val>root->val){
        root= searchBST(root->right,val);
    }
    return root;
}
>>>>>>> 3a12b13235e62db151d7ffefc36abc2501b6336c
