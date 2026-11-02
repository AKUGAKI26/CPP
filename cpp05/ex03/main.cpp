#include "Intern.hpp"
#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include <iostream>
int main() {
    Intern intern;
    Bureaucrat chief("Chief", 1);
    const char *names[] = {
        "robotomy request", "shrubbery creation",
        "presidential pardon", "tax return"};
    const char *targets[] = {
        "Bender", "office", "Arthur Dent", "Nobody"};

    for (int i = 0; i < 4; ++i) {
        AForm *form = intern.makeForm(names[i], targets[i]);

        if (form) {
            chief.signForm(*form);
            chief.executeForm(*form);
            delete form;
        }
        std::cout << std::endl;
    }
    return 0;
}
