#ifndef RobotomyRequestForm_hpp
#define RobotomyRequestForm_hpp

#include <fstream>
#include <iostream>
#include "AForm.hpp"

class RobotomyRequestForm : public AForm {
public:
	RobotomyRequestForm();
	RobotomyRequestForm(const std::string &target);
	RobotomyRequestForm(const RobotomyRequestForm &other);
	RobotomyRequestForm &operator=(const RobotomyRequestForm &other);
	~RobotomyRequestForm();
	
private:
	std::string		_target;
	virtual void	doExecute() const;
	
};

#endif
