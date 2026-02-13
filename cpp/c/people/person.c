#include <stdlib.h>
#include <string.h>
#include "person.h"

// C function that allocates memory and returns a pointer
// This is a common pattern in C
Person* create_person(const char* name, int age) {
    Person* p = (Person*)malloc(sizeof(Person));
    if (p != NULL) {
        p->name = (char*)malloc(strlen(name) + 1);
        if (p->name != NULL) {
            strcpy(p->name, name);
        }
        p->age = age;
    }
    return p;
}

// C function to free allocated memory
// Manual memory management is required in C
void destroy_person(Person* p) {
    if (p != NULL) {
        if (p->name != NULL) {
            free(p->name);
        }
        free(p);
    }
}

// C function to display person information
void display_person(const Person* p) {
    if (p != NULL) {
        printf("Name: %s, Age: %d\n", p->name, p->age);
    }
}
