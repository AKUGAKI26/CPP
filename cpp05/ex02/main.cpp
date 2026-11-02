#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>
int main() {
    Bureaucrat chief("Chief", 1);
    Bureaucrat low("Low-level", 150);
    ShrubberyCreationForm shrub("garden");
    RobotomyRequestForm robot("Bender");
    PresidentialPardonForm pardon("Arthur Dent");

    low.signForm(shrub);
    chief.executeForm(shrub);

    chief.signForm(shrub);
    chief.executeForm(shrub);

    chief.signForm(robot);
    chief.executeForm(robot);

    chief.signForm(pardon);
    chief.executeForm(pardon);

    std::cout << pardon << std::endl;
    return 0;
}
