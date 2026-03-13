#include "Form.hpp"
Form::Form() : _name(""), _isSigned(false), _gradeToSign(150), _gradeToExecute(150) {
	std::cout << GREEN << "Default constructor called for " << this->_name << std::endl;
}

Form::Form(std::string const &name, int gradeToSign, int gradeToExecute) :
_name(name), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute) {
	if (gradeToSign < 1 || gradeToExecute < 1)
		throw Form::GradeTooHighException();
	else if (gradeToSign > 150 || gradeToExecute > 150)
		throw Form::GradeTooLowException();
	std::cout << GREEN << "Form constructor called for: " << this->_name << std::endl << RESET;
}

Form::Form(const Form &other) :
	_name(other._name),
	_isSigned(other._isSigned),
	_gradeToSign(other._gradeToSign),
	_gradeToExecute(other._gradeToExecute) {
	std::cout << GREEN << "Copy constructor called for " << this->_name << std::endl << RESET;
}

Form &Form::operator=(const Form &other) {
	if (this != &other)
		this->_isSigned = other._isSigned;
	std::cout << GREEN << "Copy assignment operator called for " << this->_name << std::endl << RESET;
	return *this;
}

Form::~Form() {
	std::cout << CYAN << "Form destructor called for " << this->_name << std::endl;
}

std::string const &Form::getName() const {
	return this->_name;
}

bool	Form::getSignStatus() const {
	return this->_isSigned;
}

int	Form::getGradeToSign() const {
	return this->_gradeToSign;
}

int	Form::getGradeToExecute() const {
	return this->_gradeToExecute;
}

const char* Form::GradeTooHighException::what() const throw() {
	return "Grade too high.";
}

const char* Form::GradeTooLowException::what() const throw() {
	return "Grade too low.";
}

//std::ostream &operator<< (std::ostream &os, const Form &f) {
//	os << f.getName() << " ("
//	<< (f.getSignStatus() ? "signed" : "not signed") << ")\nGrade to sign: "
//	<< f.getGradeToSign() << "; Grade to execute: "
//	<< f.getGradeToExecute();
//	return os;
//}

std::ostream &operator<< (std::ostream &os, const Form &f) {
	const int w = 10;
	os << std::setw(w) << std::right << "NAME" << '|'
		<< std::setw(w) << std::right << "STATUS" << '|'
		<< std::setw(w) << std::right << "SIGN GRD" << '|'
	<< std::setw(w) << std::right << "EXEC GRD" << '|' << '\n';
	os << std::setw(w) << std::right << f.getName() << '|'
	<< std::setw(w) << std::right << (f.getSignStatus() ? "signed" : "unsigned") << '|'
	<< std::setw(w) << std::right << f.getGradeToSign() << '|'
	<< std::setw(w) << std::right << f.getGradeToExecute() << '|';
	return os;
}

void	Form::beSigned(const Bureaucrat &b) {
	if (this->_isSigned) {
		std::cout << this->_name << " is already signed." << std::endl;
		return ;
	}
	if (b.getGrade() > this->_gradeToSign)
		throw Form::GradeTooLowException();
	this->_isSigned = true;
}

