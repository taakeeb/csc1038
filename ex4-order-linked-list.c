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

// Function prototypes
num* constructList(int capacity, char**argv);
int checkOrder(num* head);
void freeList(num* head);

int main(int argc, char**argv) {
    // Initialize Variables
    int size;
    num* head;

    // Get size and construct linked list
    size = argc - 1;
    head = constructList(size, argv);

    // Print result of checkOrder()
    printf("%d\n", checkOrder(head));

    // Free all memory associated with the list
    freeList(head);
    head = NULL;

    return 0; // End program
}

// Creates a linked list for allocating enough memory for a node each time and then storing command line args into the nodes, linking nodes afterwards
num* constructList(int capacity, char**argv) {
    // Initialize variables
    num* head;
    num* curr;
    num* tmp;

    // Create head node
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

// Returns 0 at any point if the next node contains a value greater than the previous, else return 1
int checkOrder(num* head) {
    while (head->next) {
        if (head->val < head->next->val) {
            return 0;
        }

        head = head->next;
    }
    
    return 1;
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