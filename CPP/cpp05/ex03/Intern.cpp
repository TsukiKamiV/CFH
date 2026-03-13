
#include "Intern.hpp"

Intern::Intern() {
	std::cout << GREEN << "Intern default constructor called" << RESET << std::endl;
}

Intern:: Intern(const Intern &other) {
	std::cout << GREEN << "Intern copy constructor called" << RESET << std::endl;
	*this = other;
}

Intern	&Intern::operator=(const Intern &other) {
	std::cout << GREEN << "Intern copy assignment operator called" << RESET << std::endl;
	(void)other;
	return *this;
}

Intern::~Intern() {
	std::cout << CYAN << "Intern destructor called" << RESET << std::endl;
}

const char *Intern::WrongFormNameException::what() const throw() {
	return ("Error: Wrong Form Name");
}

static AForm	*createShrub(const std::string &target) {
	return new ShrubberyCreationForm(target);
}

static AForm	*createRobo(const std::string &target) {
	return new RobotomyRequestForm(target);
}

static AForm	*createPardon(const std::string &target) {
	return new PresidentialPardonForm(target);
}

AForm *Intern::makeForm(const std::string &formName, const std::string &target) {
	static const std::string names[3] = {
		"shrubbery creation",
		"robotomy request",
		"presidential pardon"
	};
	static t_formMaker creators[3] = {
		&createShrub,
		&createRobo,
		&createPardon
	};
	for (int i = 0; i < 3; i++) {
		if (formName == names[i]) {
			std::cout << YELLOW << "Intern creates 📑" << names[i] << " for target <"
			<< target << ">" << RESET << std::endl;
			return creators[i](target);
		}
	}
	throw WrongFormNameException();
}
