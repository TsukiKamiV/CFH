
#ifndef ShrubberyCreationForm_hpp
#define ShrubberyCreationForm_hpp

#include "AForm.hpp"
#include <fstream>
#include <iostream>

class ShrubberyCreationForm : public AForm {
public:
	ShrubberyCreationForm();
	ShrubberyCreationForm(const std::string &target);
	ShrubberyCreationForm(const ShrubberyCreationForm &other);
	ShrubberyCreationForm &operator=(const ShrubberyCreationForm &other);
	~ShrubberyCreationForm();
	
	
private:
	std::string	_target;
	/**
	 *派生类中写 virtual 并不会重新“让它变成抽象函数”，
		 它只是“保留虚函数性质”，即：允许多态调用。
	 *也就是说：
	 •	在基类中第一次写 virtual → 告诉编译器 “这是个虚函数”；
	 •	派生类中写与不写 virtual，都是虚函数（自动继承虚属性）；
	 •	但写上 virtual 可以让代码更清晰地表达意图：
	 “我知道这是个覆盖（override）基类虚函数的实现”。=》可以实例化（写具体实现步骤）
	 */
	virtual	void	doExecute() const;//覆盖AForm::doExecute() const，用于具体实现
};

#endif
