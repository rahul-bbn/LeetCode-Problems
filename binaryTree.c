#include<stdio.h>
#include<stdlib.h>

typedef struct binaryTreeNode{
    int data;
    struct binaryTreeNode* left;
    struct binaryTreeNode* right;
}binaryTreeNode;

binaryTreeNode* createNode(int data){
    binaryTreeNode* newNode=(binaryTreeNode*)malloc(sizeof(binaryTreeNode));
    newNode->data=data;
    newNode->left=NULL;
    newNode->right=NULL;

    return newNode;
}

void traverseTree(binaryTreeNode* node){
    binaryTreeNode* ptr=node;

    if (ptr==NULL)
    {
        return;
    }
    
    printf("%d->",ptr->data);
    traverseTree(node->left);
    traverseTree(node->right);
}

int main()
{
    binaryTreeNode* head=NULL;
    // traverseTree(head);

    head=createNode(5);

    head->left=createNode(4);
    head->right=createNode(3);

    head->left->left=createNode(6);
    head->left->right=createNode(2);

    head->right->right=createNode(1);

    traverseTree(head);

    return 0;

}