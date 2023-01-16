#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "List.h"

// Constructors-Destructors ---------------------------------------------------
List newList(void){
    List L = (List) malloc(sizeof(struct ListObj)); //defines L and allocates memory for the struct List and assigns to L
    if(L == NULL) {
        printf("Error: memory allocation failed in List creation\n");
        return NULL;
    }  //check the case of the above line failing
    L->numItems = 0; //set list size to 0
    L->front = L->back = L->cursor = NULL; //sets pointers to Null
    return L; //return the new list
}


//this is for function use only, not inside the list.h file
Node newNode(int x) {
    Node N = (Node) malloc(sizeof(struct NodeObj)); //defines N and creates a new node
    if(N == NULL) {
        printf("Error: memory allocation failed in Node creation\n");
        return NULL;
    }  //check the case of the above line failing
    N->data = x;
    N->next = NULL;
    return N;
}

void freeList(List* pL){
    if (pL == NULL || *pL == NULL){
        return;
    } //check if pL or *pL are NULL so the function is exited before wasting time
    
    //free the elements in the list
    Node curr = (*pL) -> front;
    while (curr != NULL) {
        Node temp = curr;
        curr = curr->next;
        free(temp);
    }
    free(*pL);
    *pL = NULL;
    //free *pL and set *pL to NULL
}
// Frees all heap memory associated with *pL, and sets
 // *pL to NULL



//this is for function use only, not inside the list.h file
void freeNode(Node* pN){
    if (pN == NULL || *pN == NULL){
        return;
    } //check if pN or *pN are NULL so the function is exited before wasting time
    free(*pN);
    *pN = NULL;
}


// Access functions -----------------------------------------------------------
int length(List L){
    return L -> numItems;
} // Returns the number of elements in L.


int index(List L){
    if(L == NULL){
        printf("Error: List is NULL\n");
        return -1;
    }
    if(L->cursor == NULL){
        return -1;
    }
    
    return L->cursor->index;
} // Returns index of cursor element if defined, -1 otherwise.


int front(List L){
    if ((L -> numItems) > 0){
        return L -> front -> data;
    }
    return 0;
} // Returns front element of L. Pre: length()>0


int back(List L){
    if ((L -> numItems) > 0){
        return L -> back -> data;
    }
    return 0;
} // Returns back element of L. Pre: length()>0


int get(List L){
    if (L->cursor != NULL && L->numItems > 0 && index(L) >= 0){
        return L -> cursor -> data;
    }
    return 0;
} // Returns cursor element of L. Pre: length()>0, index()>=0


bool equals(List A, List B){
    if (A == NULL || B == NULL || A->numItems != B->numItems){
        return false;
    }
    //check conditions that would immediately mean false

    //loop through the list comparing between the two lists
    Node currA = A->front;
    Node currB = B->front;
    while (currA != NULL && currB != NULL) {
        if (currA->data != currB->data){
            return false;
        }
        currA = currA->next;
        currB = currB->next;
    }
    //if it gets to here then they match so return true
    return true;
} // Returns true if Lists A and B are in same
 // state, and returns false otherwise.





// Manipulation procedures ----------------------------------------------------
void clear(List L){
    if (L == NULL) {
        return;
    }
    Node curr = L->front;
    while (curr != NULL) {
        Node temp = curr;
        curr = curr->next;
        free(temp);
    }
    (L -> numItems) = 0;
    (L -> front) = (L -> back) = (L -> cursor) = NULL;
} // Resets L to its original empty state.


void set(List L, int x){
    if(L->cursor != NULL && L->numItems > 0 && index(L) >= 0) {
        L->cursor->data = x;
    }
} // Overwrites the cursor element’s data with x.
 // Pre: length()>0, index()>=0


void moveFront(List L){
    if (L != NULL && L-> numItems > 0){
        L -> cursor = L -> front;
    }
} // If L is non-empty, sets cursor under the front element,
 // otherwise does nothing.


void moveBack(List L){
    if (L != NULL && L-> numItems > 0){
        L -> cursor = L -> back;
    }
} // If L is non-empty, sets cursor under the back element,
 // otherwise does nothing.


void movePrev(List L){
    if (L->cursor != NULL && L->cursor != L->front){
        L->cursor = L->cursor->prev;
    }
} // If cursor is defined and not at front, move cursor one
 // step toward the front of L; if cursor is defined and at
 // front, cursor becomes undefined; if cursor is undefined
 // do nothing


void moveNext(List L){
    if (L->cursor != NULL && L->cursor != L->back){
        L->cursor = L->cursor->next;
    }
} // If cursor is defined and not at back, move cursor one
 // step toward the back of L; if cursor is defined and at
 // back, cursor becomes undefined; if cursor is undefined
 // do nothing


void prepend(List L, int x){
    if (L != NULL){
        Node temp = newNode(x);
        if(L->numItems == 0){
            L->front = temp;
            temp->prev = temp;
            temp->next = temp;
        }
        else{
            temp->next = L->front;
            temp->prev = L->front->prev;
            L->front->prev->next = temp;
            L->front->prev = temp;
            L->front = temp;
        }
        temp->index = 0;
        L->numItems++;

        for (Node curr = temp->next; curr != temp; curr = curr->next) {
            curr->index++;
        }
    }
} // Insert new element into L. If L is non-empty,
 // insertion takes place before front element.


void append(List L, int x){
    if (L != NULL){
        Node temp = newNode(x);
        if (L->numItems == 0) {
            temp->next = temp;
            temp->prev = temp;
            L->front = temp;
        }
        else {
            temp->prev = L->back;
            temp->next = L->back->next;
            L->back->next->prev = temp;
            L->back->next = temp;
            L->back = temp;
        }
        temp->index = L->numItems;
        L->numItems++;
    }
} // Insert new element into L. If L is non-empty,
 // insertion takes place after back element.


void insertBefore(List L, int x){
    if (L->numItems > 0 && index(L) >= 0){
        
    }
} // Insert new element before cursor.
 // Pre: length()>0, index()>=0


void insertAfter(List L, int x){
    if (L->numItems > 0 && index(L) >= 0){
        
    }
} // Insert new element after cursor.
 // Pre: length()>0, index()>=0


void deleteFront(List L){
    if (L->numItems > 0){
        
    }
} // Delete the front element. Pre: length()>0


void deleteBack(List L){
    if (L->numItems > 0){
        
    }
} // Delete the back element. Pre: length()>0


void delete(List L){
    return;
} // Delete cursor element, making cursor undefined.
 // Pre: length()>0, index()>=0



// Other operations -----------------------------------------------------------
void printList(FILE* out, List L){

} // Prints to the file pointed to by out, a
 // string representation of L consisting
 // of a space separated sequence of integers,
// with front on left.


List copyList(List L){

} // Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.


List concatList(List A, List B){


} // Returns a new List which is the concatenation of
 // A and B. The cursor in the new List is undefined,
 // regardless of the states of the cursors in A 