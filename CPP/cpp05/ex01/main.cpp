#include "Bureaucrat.hpp"
#include "Form.hpp"

int main() {
	std::cout << YELLOW << "======TEST 1 Sign form=======\n";
	try {
		Bureaucrat a("Alice", 2);
		a.incrementGrade();
		std::cout << a << std::endl;
		try {
			Form f1("F1", 1, 75);
			std::cout << f1 << std::endl;
			a.signForm(f1);
			std::cout << f1 << std::endl;
		} catch (const std::exception &e) {
			std::cout << RED << "[F1]: " << e.what() << std::endl;
		}
	} catch (const std::exception &e) {
		std::cout << RED << "[Alice]: " << e.what() << std::endl;
	}
	
	std::cout << YELLOW << "\n======TEST 2 Couldn't sign form=======\n";
	try {
		Bureaucrat b("Bob", 149);
		b.decrementGrade();
		std::cout << b << std::endl;
		try {
			Form f2("F2", 149, 150);
			std::cout << f2 << std::endl;
			b.signForm(f2);
			std::cout << f2 << std::endl;
		} catch (const std::exception &e) {
			std::cout << RED << "[F2]: " << e.what() << std::endl;
		}
	} catch (const std::exception &e) {
		std::cout << RED << "[Bob]: " << e.what() << std::endl;
	}
	
	std::cout << YELLOW << "\n======TEST 3 Form creation fail=======\n";
	try {
		Form f2("F3", 200, 150);
		std::cout << f2 << std::endl;
	} catch (const std::exception &e) {
		std::cout << RED << "[F3]: " << e.what() << std::endl;
	}
	return 0;
}
