
#include "Bureaucrat.hpp"
#include "AForm.hpp"

Bureaucrat::Bureaucrat(): _name(""), _grade(150) {
	std::cout << GREEN << "Bureaucrat default constructor called" << std::endl << RESET;
}

Bureaucrat::Bureaucrat(std::string const &name, int grade) : _name(name) {
	if (grade < 1)
		throw Bureaucrat::GradeTooHighException();
	else if (grade > 150)
		throw Bureaucrat::GradeTooLowException();
	this->_grade = grade;
	std::cout << GREEN << "Bureaucrat constructor called for " << this->_name << " with grade" << std::endl << RESET;
}

Bureaucrat::Bureaucrat(const Bureaucrat &other) : _name(other._name), _grade(other._grade) {
	std::cout << GREEN << "Bureaucrat copy constructor called for " << this->_name << RESET << std::endl;
}

Bureaucrat &Bureaucrat::operator=(const Bureaucrat &other) {
	std::cout << GREEN << "Bureaucrat copy assignment operator called for " << this->_name << std::endl << RESET;
	if (this != &other)
		this->_grade = other._grade;
	return *this;
}

Bureaucrat::~Bureaucrat() {
	std::cout << CYAN << "Bureaucrat destructor called for " << this->_name << std::endl << RESET;
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
	std::cout << this->_name << " promoted from " << this->_grade + 1 << " to " << this->_grade << std::endl;
}

void	Bureaucrat::decrementGrade() {
	if (this->_grade >= 150)
		throw Bureaucrat::GradeTooLowException();
	this->_grade += 1;
	std::cout << this->_name << " demoted from " << this->_grade - 1 << " to " << this->_grade << std::endl;
}

std::ostream &operator<< (std::ostream &os, const Bureaucrat &b) {
	os << b.getName() << ", bureaucrat grade " << b.getGrade() << ".";
	return os;
}

void	Bureaucrat::signForm(AForm &form) const {
	try {
		form.beSigned(*this);
		std::cout << this->_name << " signed " << form.getName() << std::endl;
	}
	catch (std::exception &e) {
		std::cout << RED << this->_name << " couldn't sign " << form.getName()
		<< " because " << e.what() << std::endl << RESET;
	}
}

void	Bureaucrat::executeForm(AForm const &form) {
	try {
		form.execute(*this);
		std::cout << this->_name << " executed " << form.getName() << std::endl;
	}
	catch (std::exception &e) {
		std::cout << RED << this->_name << " couldn't execute because " << e.what() << RESET << std::endl;
	}
}

