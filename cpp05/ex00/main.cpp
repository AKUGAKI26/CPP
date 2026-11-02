#include "Bureaucrat.hpp"
#include <iostream>

int main() {
    try {
        Bureaucrat alice("Alice", 2);

        std::cout << alice << std::endl;
        alice.incrementGrade();
        std::cout << alice << std::endl;
        alice.incrementGrade();
    } catch (const std::exception &error) {
        std::cout << "Caught: " << error.what() << std::endl;
    }

    try {
        Bureaucrat invalid("Invalid", 151);
    } catch (const std::exception &error) {
        std::cout << "Caught: " << error.what() << std::endl;
    }
    return 0;
}
