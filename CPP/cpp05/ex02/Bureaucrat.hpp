#ifndef Bureaucrat_hpp
#define Bureaucrat_hpp

#include <iostream>
#include <string>

# define RESET		"\033[0m"
# define RED		"\033[31m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"
# define MAGENTA	"\033[35m"
# define CYAN		"\033[36m"
# define BROWN		"\033[38;5;173m"
# define WHITE		"\033[37m"

class AForm;

class Bureaucrat {
	
private:
	std::string const 	_name;
	int					_grade;
	
public:
	Bureaucrat();
	Bureaucrat(std::string const &name, int grade);
	Bureaucrat(const Bureaucrat &other);
	Bureaucrat &operator=(const Bureaucrat &other);
	~Bureaucrat();
	
	std::string const	&getName() const;
	int					getGrade() const;
	
	void	incrementGrade();
	void	decrementGrade();
	
	void	signForm(AForm &form) const;
	void	executeForm(AForm const &form);
	
	class	GradeTooHighException : public std::exception {
	public:
		virtual const char* what() const throw();
	};
	
	class	GradeTooLowException : public std::exception {
	public:
		virtual const char* what() const throw();
	};
};

std::ostream &operator<< (std::ostream &os, const Bureaucrat &b);
#endif
