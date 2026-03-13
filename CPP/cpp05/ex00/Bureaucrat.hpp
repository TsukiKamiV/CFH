//
//  Bureaucrat.hpp
//  ex00
//
//  Created by Luyao Xu on 06/11/2025.
//

#ifndef Bureaucrat_hpp
#define Bureaucrat_hpp

#include <iostream>
/**
 *@brief: Nested class（嵌套类）:
 *定义：嵌套类（Nested Class）是定义在另一个类内部的类。
 *也就是说，它不是独立存在的，而是属于某个外部类的一部分。
 *class Outer {
  public:
 	class Inner {
 	public:
 		void hello();
 	};
  };
 *Inner 是 Outer 的嵌套类。在外部访问时，必须写作：Outer::Inner obj;
 *嵌套类的核心作用是逻辑归属。
 	当一个类只在另一个类的上下文中使用时，
 	把它写在外部显得混乱，而嵌套可以清楚地表达“这是谁的内部机制”。
 */
/**
 *std::exception
 *当你在代码中写：class GradeTooHighException : public std::exception
 *意思是说：
 	这个类继承了系统提供的标准异常类型。
 * 	这让我们可以：
 •	使用标准的 try / catch 语法；
 •	统一地用 std::exception &e 捕获所有异常；
 •	利用 std::exception 的虚函数 what() 返回错误描述。
 */
//try {
//	throw std::runtime_error("Something went wrong");
//} catch (std::exception &e) {
//	std::cout << e.what() << std::endl;
//}
/**
 *what() 是 std::exception 类里的一个虚函数（virtual const char* what() const throw()），
 	它的作用是返回一段描述错误的字符串*(error message)。
 *  throw()是C++的异常规范(exception specification)：
 *  void func() throw();
 *	这个函数承诺不会抛出任何异常。
 	如果真的抛出了异常，程序会调用 std::unexpected() 终止运行。
 */

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
	
	//getters
	std::string	const	&getName() const;
	int					getGrade() const;
	
	//increment & decrement
	void	incrementGrade();//(number decreasing)
	void	decrementGrade();//(number increasing)
	
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
