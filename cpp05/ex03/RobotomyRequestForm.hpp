#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP

#include "AForm.hpp"

class RobotomyRequestForm : public AForm {
private:
    const std::string _target;
    virtual void performAction() const;

public:
    RobotomyRequestForm();
    explicit RobotomyRequestForm(const std::string &target);
    RobotomyRequestForm(const RobotomyRequestForm &other);
    RobotomyRequestForm &operator=(const RobotomyRequestForm &other);
    virtual ~RobotomyRequestForm();
    const std::string &getTarget() const;
};

#endif
