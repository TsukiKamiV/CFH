
#include "ShrubberyCreationForm.hpp"
#include "AForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm() : AForm(), _target("Default") {
	std::cout << GREEN << "ShrubberyCreationForm default constructor called" << std::endl << RESET;
}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target) : AForm("Shrubbery", 145, 137), _target(target) {
	std::cout << GREEN << "ShrubberyCreationForm constructor called with target <" << this->_target << ">" << std::endl << RESET;
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &other) : AForm(), _target(other._target) {
	std::cout << GREEN << "ShrubberyCreationForm copy constructor called" << std::endl << RESET;
}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm &other) {
	if (this != &other)
		this->_target = other._target;
	std::cout << GREEN << "ShrubberyCreationForm copy assignment operator called" << RESET << std::endl;
	return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm() {
	std::cout << CYAN << "ShrubberyCreationForm destructor called" << RESET << std::endl;
}

void	ShrubberyCreationForm::doExecute() const {
	std::ofstream ofs((this->_target + "_shrubbery").c_str());
	if (!ofs)
		return ;
	ofs << GREEN << "      _''''__、" << '\n';
	ofs << GREEN << "   _''       '''__'" << '\n';
	ofs << GREEN << "  ;               ''." << '\n';
	ofs << GREEN << " `;                 .;" << '\n';
	ofs << GREEN << "  )                  /'" << '\n';
	ofs << GREEN << " `\\                /." << '\n';
	ofs << GREEN << "   ._            ,-" << '\n';
	ofs << GREEN << "      '-、     /-'" << '\n';
	ofs << BROWN << "         '|   |" << '\n';
	ofs << BROWN << "           | |" << '\n';
	ofs << BROWN << "           | |" << '\n';
	ofs << BROWN << "          /   \\" << RESET << std::endl;
	ofs.close();
}
