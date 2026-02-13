#include "person.h"
#include <memory>

// C++ wrapper class that demonstrates best practices
// Using RAII (Resource Acquisition Is Initialization) and smart pointers
class PersonManager {
private:
    // Smart pointer automatically manages memory
    std::unique_ptr<Person, decltype(&destroy_person)> person;

public:
    // Constructor
    PersonManager(const char* name, int age)
        : person(create_person(name, age), &destroy_person) {
        if (!person) {
            throw std::bad_alloc();
        }
    }

    // Destructor - automatic cleanup (no need for manual delete!)
    ~PersonManager() = default;

    // Delete copy operations to prevent dangling pointers
    PersonManager(const PersonManager&) = delete;
    PersonManager& operator=(const PersonManager&) = delete;

    // Allow move operations
    PersonManager(PersonManager&&) = default;
    PersonManager& operator=(PersonManager&&) = default;

    // Member function to display person
    void display() const {
        display_person(person.get());
    }

    // Accessor for the underlying pointer
    const Person* get() const {
        return person.get();
    }
};

int main() {
    PersonManager person1("Alice", 30);
    person1.display();

    PersonManager person2("Bob", 25);
    person2.display();
    return 0;
}
