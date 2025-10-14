//
//  Harl.cpp
//  ex05
//
//  Created by Luyao Xu on 07/10/2025.
//

#include "Harl.hpp"

Harl::Harl() {};
Harl::~Harl() {};

void	Harl::debug(void) {
	std::cout << "this is a [DEBUG] message:\n" << "Well, there is a bug" << std::endl;
}

void	Harl::info(void) {
	std::cout << "this is an [INFO] message:\n" << "Since you are already informed, bye." << std::endl;
}

void	Harl::warning(void) {
	std::cout << "this is a [WARNING] message:\n" << "Don's say I didn't warn you." << std::endl;
}

void	Harl::error(void) {
	std::cout << "this is an [ERROR] message:\n" << "Evething is just tooooooo late." << std::endl;
}

void	Harl::complain(std::string level) {
	std::string lv[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};
	void	(Harl::*funcs[4])(void) = {
		&Harl::debug,
		&Harl::info,
		&Harl::warning,
		&Harl::error
	};
	for(int i = 0; i < 4; i++) {
		if (level == lv[i]) {
			(this->*funcs[i])();
			return;
		}
	}
	std::cout << "[ Probably complaining about insignificant problems ]" <<std::endl;
}
