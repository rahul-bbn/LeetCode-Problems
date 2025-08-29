/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


struct TreeNode* sortedListToBST(struct ListNode* head) {
    if(head == NULL){
        return NULL;
    }
    if(head->next == NULL) {
        struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        root->val = head->val;
        root->left = root->right = NULL;
        return root;
    }
    struct ListNode* slow = head, *fast = head, *slow_prev = NULL;

    while(fast != NULL && fast->next != NULL){
        slow_prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }

    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = slow->val;
    root->left=root->right=NULL;
    if (slow_prev != NULL) {
        slow_prev->next = NULL;  // ✅ split the list safely
    }

    root->left = (slow==head)?NULL:sortedListToBST(head);
    root->right = sortedListToBST(slow->next);
        
    return root;

}