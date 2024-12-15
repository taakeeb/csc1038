// Includes
#include <stdio.h>
#include <stdlib.h> // Required for atoi(), atof(), malloc(), free()

// Struct Definition
typedef struct product product;

struct product {
    char* code;
    float price;
    int sold;
    int status;

    product* next;
    product* prev;
};

// Function Prototypes
product* createList(int size, char*argv[]);
float calculateSaltes(product* node);
float getAverage(product* linkedList, int size);
void setStatus(product* linkedList, float average);
char* getCountry(char* code);
void printItems(product* linkedList);
void freeList(product* linkedList);

int main(int argc) {
    // Initialize variables
    int size;
    float average;
    product* head;

    // TEST
    char* argv[] = {"exclude", "IE213", "50", "20", "FR345", "20", "30", "SP213", "30", "40", "US999", "30", "40", "RU111", "10", "50"};

    // Get size and create linked list using createList()
    size = (argc - 1) / 3;
    head = createList(size, argv);

    // Get the average sales and set status of each node
    average = getAverage(head, size);
    setStatus(head, average);

    // Output each status with prodcut country
    printItems(head);

    // Free all memory associated with the linked list
    freeList(head);
    head = NULL;

    return 0; // End program
}

// Creates a doubly linked list using args from argv by storing into a struct then linking each struct
product* createList(int size, char*argv[]) {
    // Initialize variables
    product* head;
    product* curr;
    product* tmp;

    // Create head node
    head = (product*) malloc(sizeof(product));
    if (!head) {
        printf("Initial Allocation failed.\n");
        head = NULL;
        exit -1;
    }

    head->code = argv[1];
    head->price = atof(argv[2]);
    head->sold = atoi(argv[3]);
    head->status = 0;
    
    head->next = NULL;
    head->prev = NULL;

    // Create rest of the linked list
    curr = head;
    for (int i = 1; i < size; i++) {
        tmp = (product*) malloc(sizeof(product));
        if (!tmp) {
            printf("Further allocation failed.\n");
            free(head);
            head = NULL;
            curr = NULL;
            exit -2;
        }
        
        tmp->code = argv[1 + (i * 3)];
        tmp->price = atof(argv[2 + (i * 3)]);
        tmp->sold = atoi(argv[3 + (i * 3)]);
        tmp->status = 0;

        tmp->next = NULL;
        tmp->prev = curr;

        curr->next = tmp;
        curr = tmp;
    }

    // Set used pointers to NULL;
    curr = NULL;
    tmp = NULL;

    return head;
}

// Calculates the sales of a given node (Price * Sold);
float calculateSales(product* node) {
    return (node->price * node->sold);
}

// Traverses through the linked list and gets the average sales
float getAverage(product* linkedList, int size) {
    float average = 0;

    while (linkedList) {
        average += calculateSales(linkedList);
        linkedList = linkedList->next;
    }

    linkedList = NULL;

    return (average / size);
}

// Traverses through the linked list and sets the status of each node
void setStatus(product* linkedList, float average) {
    while (linkedList) {
        if (calculateSales(linkedList) >= average) {
            linkedList->status = 1;
        }

        linkedList = linkedList->next;
    }

    linkedList = NULL;
}

// Checks the first 2 characters of the given code and returns the appropriate country;
char* getCountry(char* code) {
    char* returnVal;

    if ((code[0] == 'I') && (code[1] == 'E')) {
        returnVal = "Ireland";
    }
    else if ((code[0] == 'F') && (code[1] == 'R')) {
        returnVal = "France";
    }
    else if ((code[0] == 'S') && (code[1] == 'P')) {
        returnVal = "Spain";
    }
    else if ((code[0] == 'U') && (code[1] == 'S')) {
        returnVal = "USA";
    }
    else if ((code[0] == 'R') && (code[1] == 'U')) {
        returnVal = "Russia";
    }

    return returnVal;
}

void printItems(product* linkedList) {
    while (linkedList) {
        printf("%d\n%s\n", linkedList->status, getCountry(linkedList->code));

        linkedList = linkedList->next;
    }

    linkedList = NULL;
}

void freeList(product* linkedList) {
    product* prev;
    
    while (linkedList)
    {
        prev = linkedList;
        linkedList = linkedList->next;

        free(prev);
    }
    
    prev = NULL;
}