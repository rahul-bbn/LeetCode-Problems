/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
bool isValidBSTHelper(struct TreeNode* root,struct TreeNode** prev){
    if(root==NULL){
        return true;
    }
    if(!isValidBSTHelper(root->left,prev)){
        return false;
    }
    if(*prev !=NULL && (*prev)->val>=root->val){
        return false;
    }
    *prev=root;

    return (isValidBSTHelper(root->right,prev));
}

bool isValidBST(struct TreeNode* root) {
    struct TreeNode * prev=NULL;
    return (isValidBSTHelper(root,&prev));
}
