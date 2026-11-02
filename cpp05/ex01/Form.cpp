#include "Form.hpp"
#include "Bureaucrat.hpp"

#include <ostream>

Form::Form() : _name("Default"), _signed(false), _signGrade(150), _executeGrade(150) {}

Form::Form(const std::string &name, int signGrade, int executeGrade)
    : _name(name), _signed(false), _signGrade(signGrade), _executeGrade(executeGrade) {
    if (signGrade < 1 || executeGrade < 1)
        throw GradeTooHighException();
    if (signGrade > 150 || executeGrade > 150)
        throw GradeTooLowException();
}

Form::Form(const Form &other)
    : _name(other._name), _signed(other._signed),
      _signGrade(other._signGrade), _executeGrade(other._executeGrade) {}

Form &Form::operator=(const Form &other) {
    if (this != &other)
        _signed = other._signed;
    return *this;
}

Form::~Form() {}

const std::string &Form::getName() const {
    return _name;
}

bool Form::getIsSigned() const {
    return _signed;
}

int Form::getGradeToSign() const {
    return _signGrade;
}

int Form::getGradeToExecute() const {
    return _executeGrade;
}

void Form::beSigned(const Bureaucrat &bureaucrat) {
    if (bureaucrat.getGrade() > _signGrade)
        throw GradeTooLowException();
    _signed = true;
}

const char *Form::GradeTooHighException::what() const throw() {
    return "form grade is too high";
}

const char *Form::GradeTooLowException::what() const throw() {
    return "form grade is too low";
}

std::ostream &operator<<(std::ostream &out, const Form &form) {
    out << form.getName()
        << " [signed: " << (form.getIsSigned() ? "yes" : "no")
        << ", sign grade: " << form.getGradeToSign()
        << ", execute grade: " << form.getGradeToExecute() << ']';
    return out;
}
