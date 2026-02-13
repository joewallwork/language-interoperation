#include <stdio.h>

#ifndef DATA_H
#define DATA_H

#ifdef __cplusplus
extern "C" {
#endif

// C struct that holds person data
// Using raw pointers is common in C but not ideal in C++
typedef struct {
    char* name;  // Raw pointer to dynamically allocated string
    int age;
} Person;

// Function declarations
Person* create_person(const char* name, int age);
void destroy_person(Person* p);
void display_person(const Person* p);

#ifdef __cplusplus
}
#endif

#endif
