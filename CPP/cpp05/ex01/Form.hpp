#ifndef Form_hpp
#define Form_hpp

#include <iostream>
#include <iomanip>
#include "Bureaucrat.hpp"


class Form {
public:
	Form();
	Form(std::string const &name, int gradeToSign, int gradeToExecute);
	Form(const Form &other);
	Form &operator=(const Form &other);
	~Form();
	
	std::string const 	&getName() const;
	bool				getSignStatus() const;
	int					getGradeToSign() const;
	int					getGradeToExecute() const;
	
	void	beSigned(const Bureaucrat &b);
	
	class GradeTooHighException : public std::exception {
	public:
		virtual const char* what() const throw();
	};
	class GradeTooLowException : public std::exception {
	public:
		virtual const char* what() const throw();
	};
	
private:
	std::string const 	_name;
	bool 				_isSigned;
	int const			_gradeToSign;
	int const			_gradeToExecute;
};

std::ostream &operator<< (std::ostream &os, const Form &f);
#endif
