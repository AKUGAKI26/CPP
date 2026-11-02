#include "AForm.hpp"
#include "Bureaucrat.hpp"

#include <ostream>

AForm::AForm()
    : _name("Default"), _signed(false), _signGrade(150),
      _executeGrade(150) {}

AForm::AForm(const std::string &name, int signGrade, int executeGrade)
    : _name(name), _signed(false), _signGrade(signGrade),
      _executeGrade(executeGrade) {
    if (signGrade < 1 || executeGrade < 1)
        throw GradeTooHighException();
    if (signGrade > 150 || executeGrade > 150)
        throw GradeTooLowException();
}

AForm::AForm(const AForm &other)
    : _name(other._name), _signed(other._signed),
      _signGrade(other._signGrade), _executeGrade(other._executeGrade) {}

AForm &AForm::operator=(const AForm &other) {
    if (this != &other)
        _signed = other._signed;
    return *this;
}

AForm::~AForm() {}

const std::string &AForm::getName() const {
    return _name;
}

bool AForm::getIsSigned() const {
    return _signed;
}

int AForm::getGradeToSign() const {
    return _signGrade;
}

int AForm::getGradeToExecute() const {
    return _executeGrade;
}

void AForm::beSigned(const Bureaucrat &bureaucrat) {
    if (bureaucrat.getGrade() > _signGrade)
        throw GradeTooLowException();
    _signed = true;
}

void AForm::execute(const Bureaucrat &executor) const {
    if (!_signed)
        throw NotSignedException();
    if (executor.getGrade() > _executeGrade)
        throw GradeTooLowException();
    performAction();
}

const char *AForm::GradeTooHighException::what() const throw() {
    return "form grade is too high";
}

const char *AForm::GradeTooLowException::what() const throw() {
    return "form grade is too low";
}

const char *AForm::NotSignedException::what() const throw() {
    return "form is not signed";
}

std::ostream &operator<<(std::ostream &out, const AForm &form) {
    out << form.getName()
        << " [signed: " << (form.getIsSigned() ? "yes" : "no")
        << ", sign grade: " << form.getGradeToSign()
        << ", execute grade: " << form.getGradeToExecute() << ']';
    return out;
}
