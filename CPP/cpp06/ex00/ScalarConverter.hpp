
#ifndef ScalarConverter_hpp
#define ScalarConverter_hpp

#include <string>

# define RESET      "\033[0m"
# define RED        "\033[31m"
# define GREEN      "\033[32m"
# define YELLOW     "\033[33m"
# define BLUE       "\033[34m"
# define MAGENTA    "\033[35m"
# define CYAN       "\033[36m"
# define BROWN      "\033[38;5;173m"
# define WHITE      "\033[37m"
# define BW         "\033[30;47m"

class ScalarConverter {
private:
	
	ScalarConverter();
	ScalarConverter(const ScalarConverter &other);
	ScalarConverter &operator=(const ScalarConverter &other);
	~ScalarConverter();
	
	enum Type {
		CHAR,
		INT,
		FLOAT,
		DOUBLE,
		PSEUDO_LITERAL,
		INVALID
	};
	
	static bool	isPseudoLiteral(const std::string &input);
	static bool isCharLiteral(const std::string &input);
	static bool isIntLiteral(const std::string &input);
	static bool isFloatLiteral(const std::string &input);
	static bool isDoubleLiteral(const std::string &input);
	
	static void	handleChar(char input);
	static void	handleInt(int input);
	static void	handleFloat(float input);
	static void handleDouble(double input);
	static void	handlePseudoLiteral(const std::string &input);
	
	static void	charConversion(char c);
	static void	intConversion(int i);
	static void floatConversion(float f);
	static void	doubleConversion(double d);
	
	static Type parseInput(const std::string &input);
	static std::string trimInput(const std::string &input);
	
public:
	
	static void	convert(const std::string &input);
};

#endif
