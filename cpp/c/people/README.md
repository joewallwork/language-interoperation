# C/C++ Best Practices: Managing Memory

This example demonstrates how to call C code from C++ while following best
practices for memory management in each language. We illustrate this using a C
`struct` for holding data related to a person.

## The Problem: Raw Pointers in C vs C++

In C, raw pointers are the standard way to manage dynamic memory:
```c
Person* create_person(const char* name, int age) {
    Person* p = (Person*)malloc(sizeof(Person));
    // ... initialization ...
    return p;
}
```

However, **raw pointers are NOT considered good practice in modern C++** because:
- You must manually `free()` or `delete` the memory
- Easy to forget cleanup, causing memory leaks
- Exception safety issues if an exception occurs before cleanup
- No clear ownership semantics

## The Solution: RAII and Smart Pointers in C++

C++ provides better tools for memory management:

### 1. The C Code (`data.c` and `data.h`)
Defines a simple `Person` struct with creation and destruction functions using standard C patterns:
```c
Person* p = create_person("Alice", 30);
destroy_person(p);  // Manual cleanup required
```

### 2. The C++ Wrapper (`main.cpp`)
Wraps the C code with a C++ class that uses:
- **`std::unique_ptr`**: Smart pointer with automatic cleanup
- **RAII**: Resource Acquisition Is Initialization - cleanup happens automatically when object goes out of scope
- **Deleted copy operations**: Prevents accidental double-deletion
- **Move semantics**: Allows efficient ownership transfer

```cpp
class PersonManager {
    std::unique_ptr<Person, decltype(&destroy_person)> person;
    // ... rest of class ...
};

// Usage:
{
    PersonManager p("Alice", 30);
    p.display();
}  // Automatically cleaned up here!
```

## Compilation

Compile the C code as C and the C++ code as C++:
```sh
gcc -c data.c -o data.o
g++ -std=c++14 -c main.cpp -o main.o
g++ data.o main.o -o best_practices
```

Or simply use the Makefile:
```sh
make
```

## Running the Example

```sh
./best_practices
```

## Key Takeaways

| Aspect | C | C++ |
|--------|---|-----|
| Memory Management | Manual with malloc/free | Smart pointers (unique_ptr, shared_ptr) |
| Ownership Model | Raw pointers (unclear) | Smart pointers (explicit ownership) |
| Cleanup | Explicit destroy_person() calls | Automatic via RAII |
| Exception Safety | Manual cleanup required | Automatic via RAII |
| Best Practice | Raw pointers standard | Raw pointers only for non-owning references |

When calling C code from C++, always wrap raw pointers in smart pointers and use RAII principles to ensure safe, automatic resource management.
