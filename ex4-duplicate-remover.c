// Includes
#include <stdio.h>
#include <stdlib.h> // Required for atoi(), malloc(), free()

// Struct Definition
typedef struct num num;
struct num {
    int val;

    num* next;
    num* prev;
};

// Function Prototypes
num* constructList(int capacity, char**argv);
int checkDupe(num* head, int n);
num* deleteNodes(num* head, int n);
num* removeDupes(num* head);
void printList(num* head);
void freeList(num* head);

int main(int argc, char**argv) {
    // Initialize Variables
    num* head;
    int size;

    // Get size and construct the linked list
    size = argc - 1;
    head = constructList(size, argv);

    // Remove any duplicate numbers including the original
    head = removeDupes(head);

    // Output linked list
    printList(head);

    // Free memory associated with linked list
    freeList(head);
    head = NULL;

    return 0; //End program
}

// Creates a linked list for allocating enough memory for a node each time and then storing command line args into the nodes, linking nodes afterwards
num* constructList(int capacity, char**argv) {
    // Initialize variables
    num* head;
    num* curr;
    num* tmp;

    // Create head node;
    head = (num*) malloc(sizeof(num));
    if (!head) {
        printf("Initial Allocation failed.\n");
        head = NULL;
        exit -1;
    }

    head->val = atoi(argv[1]);
    head->next = NULL;
    head->prev = NULL;

    // Create the rest of the linked list
    curr = head;
    for (int i = 1; i < capacity; i++) {
        tmp = (num*) malloc(sizeof(num));
        if (!tmp) {
            printf("Further Allocation failed.\n");
            free(head);
            head = NULL;
            exit -2;
        }

        tmp->val = atoi(argv[i + 1]);
        tmp->next = NULL;
        
        tmp->prev = curr;
        curr->next = tmp;
        curr = tmp;
    }

    // Discard used pointers
    curr = NULL;
    tmp = NULL;

    return head;
}

// Checks to see if n occurs more than 1 time, if it does return 1
int checkDupe(num* head, int n) {
    int count = 0;

    while (head) {
        if (head->val == n) {
            count++;
        }

        head = head->next;
    }

    if (count > 1) {
        return 1;
    }
    return 0;
}

// Removes any node where node->val == n, returns head afterwards
num* deleteNodes(num* head, int n) {
    num* curr;
    num* toDelete;
    num* tail;

    // Avoid head and tail, remove those later
    curr = head->next;
    toDelete = NULL;
    for (;curr->next; curr = curr->next) {
        if (curr->val == n) {
            toDelete = curr;

            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
            curr = curr->prev;

            free(toDelete);
            toDelete = NULL;
        }
    }

    // Check head
    if (head->val == n) {
        toDelete = head;

        head = head->next;
        head->prev = NULL;

        free(toDelete);
        toDelete = NULL;
    }

    // Check tail
    tail = head;
    while (tail->next) {
        tail = tail->next;
    }

    if (tail->val == n) {
        toDelete = tail;
        tail->prev->next = NULL;

        free(toDelete);
        toDelete = NULL;
    }

    // Discard used pointers
    curr = NULL;
    tail = NULL;

    return head;
}

// Removes all dupilicates including the original numbers, function execution only stops when the end of the list is reached, returns head after
num* removeDupes(num* head) {
    num* curr;
    num* newHead = head;

    curr = newHead;
    while (curr) {
        if (checkDupe(newHead, curr->val)) {
            newHead = deleteNodes(newHead, curr->val);
            curr = newHead;
        }
        else {
            curr = curr->next;
        }
    }

    return newHead;
}

// Prints each nide in a formatted manner (%d\n)
void printList(num* head) {
    while (head) {
        printf("%d\n", head->val);

        head = head->next;
    }
}

// Frees a node on each iteration until the end of the list is reached
void freeList(num* head) {
    num* prev;

    while (head) {
        prev = head;
        head = head->next;

        free(prev);
    }

    prev = NULL;
}