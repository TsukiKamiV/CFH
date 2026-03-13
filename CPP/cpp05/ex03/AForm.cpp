#include "AForm.hpp"
AForm::AForm() : _name(""), _isSigned(false), _gradeToSign(150), _gradeToExecute(150) {
	std::cout << GREEN << "Default constructor called for " << this->_name << std::endl;
}

AForm::AForm(std::string const &name, int gradeToSign, int gradeToExecute) :
_name(name), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute) {
	std::cout << GREEN << "Form constructor called for: " << this->_name << std::endl << RESET;
	if (gradeToSign < 1 || gradeToExecute < 1)
		throw AForm::GradeTooHighException();
	else if (gradeToSign > 150 || gradeToExecute > 150)
		throw AForm::GradeTooLowException();
}

AForm::AForm(const AForm &other) :
_name(other._name),
_isSigned(other._isSigned),
_gradeToSign(other._gradeToSign),
_gradeToExecute(other._gradeToExecute) {
	std::cout << GREEN << "Copy constructor called for " << this->_name << std::endl << RESET;
}

AForm &AForm::operator=(const AForm &other) {
	if (this != &other)
		this->_isSigned = other._isSigned;
	std::cout << GREEN << "Copy assignment operator called for " << this->_name << std::endl << RESET;
	return *this;
}

AForm::~AForm() {
	std::cout << CYAN << "Form destructor called for " << this->_name << std::endl;
}

std::string const &AForm::getName() const {
	return this->_name;
}

bool	AForm::getSignStatus() const {
	return this->_isSigned;
}

int	AForm::getGradeToSign() const {
	return this->_gradeToSign;
}

int	AForm::getGradeToExecute() const {
	return this->_gradeToExecute;
}

const char* AForm::GradeTooHighException::what() const throw() {
	return "Grade too high.";
}

const char* AForm::GradeTooLowException::what() const throw() {
	return "Grade too low.";
}

const char* AForm::FormUnsignedException::what() const throw() {
	return "Form not signed yet.";
}

std::ostream &operator<< (std::ostream &os, const AForm &f) {
	const int w = 10;
	os << std::setw(w) << std::right << "NAME" << '|'
	<< std::setw(w) << std::right << "STATUS" << '|'
	<< std::setw(w) << std::right << "SIGN GRD" << '|'
	<< std::setw(w) << std::right << "EXEC GRD" << '|' << '\n';
	os << std::setw(w) << std::right << f.getName() << '|'
	<< std::setw(w) << std::right << (f.getSignStatus() ? "Y" : "N") << '|'
	<< std::setw(w) << std::right << f.getGradeToSign() << '|'
	<< std::setw(w) << std::right << f.getGradeToExecute() << '|';
	return os;
}

void	AForm::beSigned(const Bureaucrat &b) {
	if (this->_isSigned) {
		std::cout << this->_name << " is already signed." << std::endl;
		return ;
	}
	if (b.getGrade() > this->_gradeToSign)
		throw AForm::GradeTooLowException();
	this->_isSigned = true;
}

void	AForm::execute(Bureaucrat const & executor) const {
	if (!this->_isSigned)
		throw AForm::FormUnsignedException();
	if (executor.getGrade() > this->_gradeToExecute)
		throw AForm::GradeTooLowException();
	this->doExecute();
}

