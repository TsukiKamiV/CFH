//
//  Contact.hpp
//  phonebook
//
//  Created by Luyao Xu on 01/10/2025.
//

#ifndef Contact_hpp
#define Contact_hpp

#include <iostream>
#include <string>

class Contact {
private:
	//在成员变量前面加 前缀 _，用来区分 类的内部属性 和 函数里的局部变量/参数。
	std::string _firstName;
	std::string _lastName;
	std::string _nickName;
	std::string _phoneNumber;
	std::string _darkestSecret;
	
/**
 * 构造函数 (Constructor)
 * 作用：在创建对象时自动调用，用来初始化对象。
 * 特点：
 * 函数名和类名一样（如 Contact()）。
 * 没有返回类型（连 void 都不能写）。
 * 可以有参数（用来传递初始化数据）。
 * 可以有多个构造函数（函数重载）。 */
/**
 *析构函数 (Destructor)
 * 作用：在对象销毁时自动调用，用来清理资源（释放内存、关闭文件等）。
 * 特点：
 * 名字是 ~类名，比如 ~Contact()。
 * 没有参数，也没有返回值。
 * 每个类只能有一个析构函数。
 * 如果你不写，编译器会自动生成一个默认析构函数。
 */
public:
	Contact();//构造函数 Constructor
	~Contact();//析构函数 Destructor
	
	void	fillFirstName(const std::string str);
	void	fillLastName(const std::string str);
	void	fillNickName(const std::string str);
	void	fillPhoneNumber(const std::string str);
	void	fillDarkestSecret(const std::string str);
	
	/**
	 *返回对象里的 _firstName 这个成员变量的“别名”。
	 * 调用者拿到的是原始对象里的那个字符串，而不是复制品。
	 */
	const	std::string &getFirstName() const;
	const	std::string &getLastName() const;
	const	std::string &getNickName() const;
	const	std::string &getPhoneNumber() const;
	const	std::string &getDarkestSecret() const;
	
	//A saved contact can't have empty fields
	bool	isEmpty() const;
};

#endif /* Contact_hpp */
