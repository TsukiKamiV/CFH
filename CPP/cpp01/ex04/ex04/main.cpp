#include "Replacer.hpp"

int main(int argc, const char * argv[]) {
	if (argc != 4) {
		std::cerr << "Please enter the arguments as: <filename> <s1> <s2>\nExiting..." << std::endl;
		return 1;
	}
	std::string filename_source = argv[1];
	std::string s1 = argv[2];
	std::string s2 = argv[3];
	
	if (filename_source.empty()) {
		std::cerr << "Empty file name detected\nExiting..." << std::endl;
		return 1;
	}
	if (s1.empty()) {
		std::cerr << "the first string cannot be empty.\nExiting..." << std::endl;
		return 1;
	}
	replaceInFile(filename_source, s1, s2);
	return 0;
}
