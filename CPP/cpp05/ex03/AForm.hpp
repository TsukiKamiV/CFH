#ifndef Form_hpp
#define Form_hpp

#include <iostream>
#include <iomanip>
#include "Bureaucrat.hpp"

class AForm {
public:
	AForm();
	AForm(std::string const &name, int gradeToSign, int gradeToExecute);
	AForm(const AForm &other);
	AForm &operator=(const AForm &other);
	virtual ~AForm();
	
	std::string const 	&getName() const;
	bool				getSignStatus() const;
	int					getGradeToSign() const;
	int					getGradeToExecute() const;
	
	void	beSigned(const Bureaucrat &b);
	void	execute(Bureaucrat const & executor) const;//only perform checks
	virtual	void	doExecute() const = 0;//纯虚函数,在继承类里分别负责执行各自的具体任务
	
	class GradeTooHighException : public std::exception {
	public:
		virtual const char* what() const throw();
	};
	class GradeTooLowException : public std::exception {
	public:
		virtual const char* what() const throw();
		
	};
	class FormUnsignedException : public std::exception {
	public:
		virtual const char* what() const throw();
	};
	
private:
	std::string const 	_name;
	bool 				_isSigned;
	int const			_gradeToSign;
	int const			_gradeToExecute;
};

std::ostream &operator<< (std::ostream &os, const AForm &f);
#endif

