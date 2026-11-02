#include "Intern.hpp"
#include "AForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

#include <iostream>

Intern::Intern() {}

Intern::Intern(const Intern &other) { (void)other; }

Intern &Intern::operator=(const Intern &other) {
    (void)other;
    return *this;
}

Intern::~Intern() {}

AForm *Intern::makeShrubbery(const std::string &target) const {
    return new ShrubberyCreationForm(target);
}

AForm *Intern::makeRobotomy(const std::string &target) const {
    return new RobotomyRequestForm(target);
}

AForm *Intern::makePardon(const std::string &target) const {
    return new PresidentialPardonForm(target);
}

AForm *Intern::makeForm(const std::string &name, const std::string &target) const {
    const std::string names[3] = {
        "shrubbery creation", "robotomy request", "presidential pardon"};
    const FormMaker makers[3] = {
        &Intern::makeShrubbery, &Intern::makeRobotomy, &Intern::makePardon};

    for (int i = 0; i < 3; ++i) {
        if (name == names[i]) {
            AForm *form = (this->*makers[i])(target);

            std::cout << "Intern creates " << form->getName() << std::endl;
            return form;
        }
    }

    std::cout << "Intern cannot create '" << name << "': unknown form name" << std::endl;
    return NULL;
}
