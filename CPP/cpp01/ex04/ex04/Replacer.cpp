#include "Replacer.hpp"

static std::string replaceString(const std::string &src, const std::string &s1, const std::string &s2) {
	std::string out;
	std::string::size_type pos = 0, found;
	while ((found = src.find(s1, pos)) != std::string::npos) {
		out.append(src, pos, found - pos);
		out.append(s2);
		pos = found + s1.length();
	}
	out.append(src, pos, src.length() - pos);
	return out;
}

void	replaceInFile(const std::string &filename, const std::string &s1, const std::string &s2) {
	std::ifstream input(filename.c_str());
	if (!input.is_open()) {
		std::cerr << "Error: cannot open file " << filename << std::endl;
		return ;
	}
	
	std::ofstream output((filename + ".replace").c_str());
	if (!output.is_open()) {
	std::cerr << "Error: cannot create output file." << std::endl;
		return ;
	}
	
	std::string line;
	while (std::getline(input, line)) {
		std::string replaced_line = replaceString(line, s1, s2);
		output << replaced_line << std::endl;
	}
	input.close();
	output.close();
}
