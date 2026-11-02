#include "Bureaucrat.hpp"
#include "Form.hpp"
#include <iostream>
int main() {
    try {
        Bureaucrat boss("Boss", 1);
        Bureaucrat junior("Junior", 100);
        Form permit("Permit", 50, 25);

        std::cout << permit << std::endl;
        junior.signForm(permit);
        boss.signForm(permit);
        std::cout << permit << std::endl;
    } catch (const std::exception &error) {
        std::cout << "Caught: " << error.what() << std::endl;
    }

    try {
        Form invalid("Invalid", 0, 10);
    } catch (const std::exception &error) {
        std::cout << "Caught: " << error.what() << std::endl;
    }
    return 0;
}
