
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main() {
	std::srand(std::time(NULL));
	std::cout << BW << "========TEST1 SUBJECT TEST========" << RESET << std::endl;
	try {
		Intern Tommy;
		Bureaucrat boss("Boss", 1);
		AForm *form;
		
		form = Tommy.makeForm("robotomy request", "Bender");
		boss.signForm(*form);
		boss.executeForm(*form);
		delete form;
	}
	catch (std::exception &e) {
		std::cerr << RED << e.what() << RESET << RESET << std::endl;
	}
	
	std::cout << BW << "\n========TEST2 SHRUBBERYCREATION TEST========" << RESET << std::endl;
	try {
		Intern Sarah;
		Bureaucrat gardener("Gardener", 100);
		AForm *shrubForm;
		
		shrubForm = Sarah.makeForm("shrubbery creation", "botanic🌳");
		gardener.signForm(*shrubForm);
		gardener.executeForm(*shrubForm);
		delete shrubForm;
	}
	catch (std::exception &e) {
		std::cerr << RED << e.what() << RESET << std::endl;
	}
	
	std::cout << BW << "\n========TEST3 PRESIDENTIAL PARDON TEST========" << RESET << std::endl;
	try {
		Intern Robert;
		Bureaucrat VP("VP", 2);
		AForm *pardonForm;
		
		pardonForm = Robert.makeForm("presidential pardon", "his son");
		VP.signForm(*pardonForm);
		VP.executeForm(*pardonForm);
		delete pardonForm;
	}
	catch (std::exception &e) {
		std::cerr << RED << e.what() << RESET << std::endl;
	}
	
	std::cout << BW << "\n========TEST4 UNKNOWN FORM NAME========" << RESET << std::endl;
	try {
		Intern Nobody;
		AForm *someForm;
		
		someForm = Nobody.makeForm("Some unknown form type", "random guy");
		delete someForm;
	}
	catch (std::exception &e) {
		std::cerr << RED << e.what() << RESET << std::endl;
	}
	return 0;
}
