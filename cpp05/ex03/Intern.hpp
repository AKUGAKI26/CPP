#ifndef INTERN_HPP
#define INTERN_HPP

#include <string>

class AForm;

class Intern {
private:
    typedef AForm *(Intern::*FormMaker)(const std::string &) const;
    AForm *makeShrubbery(const std::string &target) const;
    AForm *makeRobotomy(const std::string &target) const;
    AForm *makePardon(const std::string &target) const;

public:
    Intern();
    Intern(const Intern &other);
    Intern &operator=(const Intern &other);
    ~Intern();
    AForm *makeForm(const std::string &name, const std::string &target) const;
};

#endif
