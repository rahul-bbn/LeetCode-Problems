#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
}linkList;

// linkList* createNode(int data){
//     linkList* node=(linkList*)malloc(sizeof(linkList));
//     node->data=data;
//     node->next=NULL;

//     return node;
// }

linkList* insertAtFirst(linkList* head,int data){
    // linkList* ptr=head;
    linkList* newNode=(linkList*)malloc(sizeof(linkList));
    newNode->next=head;
    newNode->data=data;
    return newNode;

}

linkList* insertAtEnd(linkList* head,int data){
    linkList* node=(linkList*)malloc(sizeof(linkList));
    node->data=data;
    node->next=NULL;

    if(head==NULL){
        return node;
    }

    linkList* p=head;
    while(p->next!=NULL){
        p=p->next;
    }
    p->next=node;

    return head;
}

linkList* insertAtIndexPos(linkList* head,int pos,int data){
    if (pos == 0) {
        return insertAtFirst(head, data);
    }

    linkList* node=(linkList*)malloc(sizeof(linkList));
    linkList* p=head;
    node->data=data;
    int count=0;

    while(p != NULL && count < pos - 1){
        count++;
        p=p->next;
    }
    if (p == NULL) {
        printf("Position out of range!\n");
        free(node);
        return head;
    }
    node->next=p->next;
    p->next=node;

    return head;
}

linkList* deleteNode(linkList* head, int data){
    linkList* temp=head,*prev=NULL;
    if (head==NULL){
        return NULL;
    }
    
    if(temp!=NULL && head->data==data){
        head=temp->next;
        free(temp);
        return head;
    }
    while (temp!=NULL && temp->data!=data)
    {
        prev=temp;
        temp=temp->next;
    }
    if(temp==NULL){
        return head;
    }
    prev->next = temp->next;
    free(temp);
    return head;
}

linkList* reverseList(linkList* head)
{
    linkList* ptr=head;
    linkList* prev=head;
    linkList* next=head->next;

    while(ptr->next!=NULL){
        ptr=ptr->next;

        
    }
}

void linkedListTraverse(linkList* head){
    linkList* ptr=head;
    while (ptr!=NULL)
    {
        printf("%d->",ptr->data);
        ptr=ptr->next;
    }
    printf("NULL\n");
}

int main()
{
    linkList* head = NULL;
    head = insertAtEnd(head, 7);
    head = insertAtEnd(head, 10);
    head = insertAtEnd(head, 15);
    head = insertAtEnd(head, 5);

    linkedListTraverse(head);

    printf("\nAfter insertion at first:\n");
    head = insertAtFirst(head, 90);
    linkedListTraverse(head);

    printf("\nAfter insertion at last:\n");
    head = insertAtEnd(head, 56);
    linkedListTraverse(head);

    printf("\nAfter insertion at index position:\n");
    head = insertAtIndexPos(head, 2, 100);
    linkedListTraverse(head);

    printf("\nAfter deletion:\n");
    head = deleteNode(head, 90);
    linkedListTraverse(head);

    head = deleteNode(head, 15);
    linkedListTraverse(head);




    // linkList* head=(linkList*)malloc(sizeof(linkList));
    // linkList* second=(linkList*)malloc(sizeof(linkList));
    // linkList* third=(linkList*)malloc(sizeof(linkList));
    // linkList* fourth=(linkList*)malloc(sizeof(linkList));

    // head->data=7;
    // head->next=second;

    // second->data=10;
    // second->next=third;

    // third->data=15;
    // third->next=fourth;

    // fourth->data=5;
    // fourth->next=NULL;

    // linkedListTeaverse(head);

    // printf("\nAfter insertion at first:\n");

    // head=insertAtFirst(head,90);
    // linkedListTeaverse(head);

    // printf("\nAfter insertion at last:\n");
    // head=insertAtEnd(head,56);
    // linkedListTeaverse(head);

    // printf("\nAfter insertion at index position:\n");
    // head=insertAtIndexPos(head,2,100);
    // linkedListTeaverse(head);

    // printf("\nAfter deletion:\n");
    // head=deleteNode(head,90);
    // linkedListTeaverse(head);

    // printf("\nAfter deletion:\n");
    // head=deleteNode(head,15);
    // linkedListTeaverse(head);

    return 0;
}