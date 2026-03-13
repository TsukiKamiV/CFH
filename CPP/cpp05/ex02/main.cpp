#include <cstdlib>
#include <ctime>
#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main() {
	srand(time(NULL));
	std::cout << "=============SHRUBBERY TEST=============" << std::endl;
	try {
		//Bureaucrat b1("Alice", 145);
		//Bureaucrat b1("Alice", 137);
		Bureaucrat b1("Alice", 136);
		try {
			ShrubberyCreationForm F1("shrub");
			std::cout << F1 << std::endl;
			b1.signForm(F1);
			std::cout << F1 << std::endl;
			b1.executeForm(F1);
		}
		catch (const std::exception &e) {
			std::cerr << RED << e.what() << RESET << std::endl;
		}
	}
	catch (const std::exception &e) {
		std::cerr << RED << e.what() << RESET << std::endl;
	}
	
	
	std::cout << "=============ROBOTOMY TEST=============" << std::endl;
	try {
		Bureaucrat b2("Bob", 72);
		//Bureaucrat b2("Bob", 45);
		//Bureaucrat b2("Bob", 44);
		try {
			RobotomyRequestForm F2("Robert");
			std::cout << F2 << std::endl;
			b2.signForm(F2);
			std::cout << F2 << std::endl;
			b2.executeForm(F2);
		}
		catch (const std::exception &e) {
			std::cerr << RED << e.what() << RESET << std::endl;
		}
	}
	catch (const std::exception &e) {
		std::cerr << RED << e.what() << RESET << std::endl;
	}
	
	std::cout << "=============PRESIDENTIAL TEST=============" << std::endl;
	try {
		//Bureaucrat b3("Dylan", 25);
		Bureaucrat b3("Dylan", 5);
		//Bureaucrat b3("Dylan", 4);
		try {
			PresidentialPardonForm F3("KUMA🐻");
			std::cout << F3 << std::endl;
			b3.signForm(F3);
			std::cout << F3 << std::endl;
			b3.executeForm(F3);
		}
		catch (const std::exception &e) {
			std::cerr << RED << e.what() << RESET << std::endl;
		}
	}
	catch (const std::exception &e) {
		std::cerr << RED << e.what() << RESET << std::endl;
	}
	return 0;
}
