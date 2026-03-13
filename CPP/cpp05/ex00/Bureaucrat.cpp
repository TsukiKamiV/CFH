
#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat(): _name(""), _grade(150) {
	std::cout << "Default constructor called" << std::endl;
}

Bureaucrat::Bureaucrat(std::string const &name, int grade) : _name(name) {
	if (grade < 1)
		throw Bureaucrat::GradeTooHighException();
	else if (grade > 150)
		throw Bureaucrat::GradeTooLowException();
	this->_grade = grade;
	std::cout << "Constructor called for " << this->_name << " with grade" << std::endl;
}

Bureaucrat::Bureaucrat(const Bureaucrat &other) : _name(other._name), _grade(other._grade) {
	std::cout << "Copy constructor called for " << this->_name << std::endl;
}

Bureaucrat &Bureaucrat::operator=(const Bureaucrat &other) {
	std::cout << "Copy assignment operator called for " << this->_name << std::endl;
	if (this != &other)
		this->_grade = other._grade;
	return *this;
}

Bureaucrat::~Bureaucrat() {
	std::cout << "Destructor called for " << this->_name << std::endl;
}

std::string const &Bureaucrat::getName() const {
	return this->_name;
}

int			Bureaucrat::getGrade() const {
	return this->_grade;
}

const char*	Bureaucrat::GradeTooHighException::what() const throw() {
	return "Grade out of range (less than 1)";
}

const char* Bureaucrat::GradeTooLowException::what() const throw() {
	return "Grade out of range (more than 150)";
}

void	Bureaucrat::incrementGrade() {
	if (this->_grade <= 1)
		throw Bureaucrat::GradeTooHighException();
	this->_grade -= 1;
}

void	Bureaucrat::decrementGrade() {
	if (this->_grade >= 150)
		throw Bureaucrat::GradeTooLowException();
	this->_grade += 1;
}

std::ostream &operator<< (std::ostream &os, const Bureaucrat &b) {
	os << b.getName() << ", bureaucrat grade " << b.getGrade() << ".";
	return os;
}
