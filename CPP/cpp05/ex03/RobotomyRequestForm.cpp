#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm() : AForm(), _target("Default") {
	std::cout << GREEN << "RobotomyRequestForm default constructor called" << RESET << std::endl;
}

RobotomyRequestForm::RobotomyRequestForm(const std::string &target) : AForm("Robotomy", 72, 45), _target(target) {
	std::cout << GREEN << "RobotomyRequestForm constructor called with target <" << this->_target << ">" << RESET << std::endl;
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &other) : AForm(), _target(other._target) {
	std::cout << GREEN << "RobotomyRequestForm copy constructor called" << RESET << std::endl;
}

RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm &other) {
	if (this != &other)
		this->_target = other._target;
	std::cout << GREEN << "RobotomyRequestForm copy assignment operator called" << RESET << std::endl;
	return *this;
}

RobotomyRequestForm::~RobotomyRequestForm() {
	std::cout << CYAN << "RobotomyRequestForm destructor called" << RESET << std::endl;
}

void	RobotomyRequestForm::doExecute() const {
	std::cout << MAGENTA << "Bzzzzzzzz...⚡️" << RESET << std::endl;
	if (rand() % 2)
		std::cout << MAGENTA << this->_target << " has been robotomized successfully!🤖" << RESET << std::endl;
	else
		std::cout << MAGENTA << "Robotomy failed on " << this->_target << "...💥" << RESET << std::endl;
}
