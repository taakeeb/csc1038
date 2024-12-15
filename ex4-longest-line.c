// Includes
#include <stdio.h>
#include <stdlib.h> // Required for malloc(), free()
#include <string.h> // Required for strlen(), strcmp()

// Struct Definition
typedef struct sentence sentence;
struct sentence {
    char* str;
    int length;

    sentence* next;
    sentence* prev;
};

// Function Prototypes
char* getSentence(char* string, int* lowerBound, int* upperBound);
sentence* breakdownParagraph(char**argv);
sentence* longest(sentence* head);
sentence* shortest(sentence* head);
void output(sentence* (*functionPointer)(sentence*), sentence* head);
void freeList(sentence* head);

int main(int argc, char**argv) {
    // Initialize Variables
    sentence* head;
    sentence* (*pFunction)(sentence*) = NULL;

    // Create linked list and assign to head
    head = breakdownParagraph(argv);

    // Output longest/shortest to stdout
    if (!(strcmp(argv[2], "longest"))) {
        pFunction = longest;
        output(pFunction, head);
    }
    else if (!(strcmp(argv[2], "shortest"))) {
        pFunction = shortest;
        output(pFunction, head);
    }
    else {
        printf("Not valid!\n");
    }

    // Free all memory associated to the linked list
    freeList(head);
    head = NULL;

    return 0; // End program
}

char* getSentence(char* string, int* lowerBound, int* upperBound) {
    char* returnString;

    while (string[*lowerBound] == ' ') {
        *lowerBound += 1;

    }

    *upperBound = *lowerBound;
    while((string[*upperBound] != '.') && (string[*upperBound] != '?') && (string[*upperBound] != '\0')) {
        if (string[*upperBound] == '\'') {
            *upperBound += 1;
             while (string[*upperBound] != '\'') {
                *upperBound += 1;
            }
        }

        *upperBound += 1;
    }

    returnString = (char*) malloc(sizeof(char) * (*upperBound - *lowerBound + 5));
    if (!returnString) {
        printf("String Allocation failed.\n");
        exit -2;
    }

    for (int i = *lowerBound; i < (*upperBound + 1); i++) {
        returnString[i - *lowerBound] = string[i];
    }
    returnString[(*upperBound - *lowerBound) + 1] = '\0';

    *lowerBound = *upperBound;
    return returnString;
}

sentence* breakdownParagraph(char**argv) {
    // Initialize varaibles
    sentence* head;
    sentence* curr;
    sentence* tmp;
    char* paragraph = argv[1];
    char** pArray;
    int lower = 0;
    int upper = 0;
    int length = 0;

    // Create array to hold pointers
    pArray = (char**) calloc(50, sizeof(char*));
    int i = 0;
    length = strlen(paragraph);
    while(paragraph[lower] && (lower < length)) {
        pArray[i] = getSentence(paragraph, &lower, &upper);
        lower++;
        i++;
    }
    
    // Create head node
    head = (sentence*) malloc(sizeof(sentence));
    if (!head) {
        printf("Allocation failed.\n");
        exit -3;
    }

    head->str = pArray[0];
    head->length = strlen(head->str);
    head->next = NULL;
    head->prev = NULL;

    i = 1;
    curr = head;
    while (pArray[i]) {
        tmp = (sentence*) malloc(sizeof(sentence));
        if (!tmp) {
            printf("Further Allocation failed.\n");
            free(head);
            head = NULL;
            exit -4;
        }

        tmp->str = pArray[i];
        tmp->length = strlen(tmp->str);
        tmp->next = NULL;

        curr->next = tmp;
        tmp->prev = curr;
        curr = tmp;

        i++;
    }

    // Discard unnecessary pointers and free
    free(pArray);

    pArray = NULL;
    curr = NULL;
    tmp = NULL;

    return head;
}

sentence* longest(sentence* head) {
    int largest = 0;
    sentence* returnStruct;
    sentence* curr;

    curr = head;
    while (curr) {
        if (curr->length > largest) {
            largest = curr->length;
        }

        curr = curr->next;
    }

    curr = head;
    while (curr) {
        if (curr->length == largest) {
            returnStruct = curr;
        }

        curr = curr->next;
    }

    return returnStruct;
}

sentence* shortest(sentence* head) {
    int smallest = head->length;
    sentence* curr;
    sentence* returnStruct;

    curr = head;
    while (curr) {
        if (curr->length <= smallest) {
            smallest = curr->length;
        }

        curr = curr->next;
    }

    curr = head;
    while (curr) {
        if (curr->length == smallest) {
            returnStruct = curr;
        }

        curr = curr->next;
    }

    return returnStruct;
}

void output(sentence* (*functionPointer)(sentence*), sentence* head) {
    sentence* tmp = functionPointer(head);
    
    printf("%d\n%s\n", tmp->length, tmp->str);
}

void freeList(sentence* head) {
    sentence* prev;

    while (head) {
        prev = head;
        head = head->next;

        free(prev->str);
        prev->str = NULL;
        free(prev);
    }

    prev = NULL;
}