#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>


struct node {
    int data;
    struct node* small;
    struct node* large;
};

typedef struct node* Node;





/* Create a new node */
Node newNode(int data) {
    Node node = (Node) malloc(sizeof(struct node));
    node->data = data;
    node->small = NULL;
    node->large = NULL;
    return(node);
}


/* Add a new node into a tree */
void treeInsert(Node* rootRef, int data) {
    Node root = *rootRef;
    if (root == NULL) *rootRef = newNode(data);
    else {
        if (data <= root->data) treeInsert(&(root->small), data);
        else treeInsert(&(root->large), data);
    }
}


void printList(Node head) {
    Node current = head;
    
    while(current != NULL) {
        printf("%d ", current->data);
        current = current->large;
        if (current == head) break;
    }
    printf("\n");
}

// YOUR CODE HERE
Node remainer = NULL;

void rec_tree_to_list(Node root){
    //recursive in-order tree walk
    if (root != NULL){
        rec_tree_to_list(root->small);
        
        if(remainer == NULL){
            remainer = root;
        }
        
        else {
            root -> small = remainer;
            remainer -> large = root;
            remainer = root;
        }
        
        rec_tree_to_list(root->large);
        
    }
    return;  
} 



Node treeToList(Node root) {

    if(root == NULL){
        return root;
    }

    //find the head - smallest in the tree
    Node head = root;
    while(head->small != NULL){
            head = head -> small; 
    }
    
    //find the end of the list
    Node tail = root;
    while(tail->large != NULL){
            tail = tail -> large; 
    }


    rec_tree_to_list(root);

    tail->large = head;
    head->small = tail;
    
    return head;
}


/* Demo that the code works */
int main() {
    Node root = NULL;
    Node head;
    
    treeInsert(&root, 4);
    treeInsert(&root, 2);
    treeInsert(&root, 1);
    treeInsert(&root, 3);
    treeInsert(&root, 5);
    
    head = treeToList(root);
    
    printList(head);    /* prints: 1 2 3 4 5  */
    
    return(0);
}
