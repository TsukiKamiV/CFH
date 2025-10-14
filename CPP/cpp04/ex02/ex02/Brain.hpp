#ifndef Brain_hpp
#define Brain_hpp

#include <iostream>
#include <string>

class Brain {
public:
	Brain();
	Brain(const Brain &other);
	Brain &operator=(const Brain &other);
	~Brain();
	
	std::string getIdea(int index) const;
	void		setIdea(int index, const std::string &idea);
	
private:
	std::string ideas[100];
};

#endif /* Brain_hpp */
