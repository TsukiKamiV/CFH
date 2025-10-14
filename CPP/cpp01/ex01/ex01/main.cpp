
#include "Zombie.hpp"

/**
 * @delete: free the memory allocated by "new[]"
 */

int main() {
	std::string	line;
	std::cout << "Enter the size of the 🧟Horde: " << std::flush;
	if (!std::getline(std::cin, line)) {
		std::cerr << "🧟Input error." << std::endl;
		return 1;
	}
	
	std::stringstream ss(line);
	int	z_count;
	if (!(ss >> z_count) || z_count <= 0) {
		std::cerr << "🧟Invalid input (must be positive integer)." << std::endl;
		return 1;
	}
	std::string name;
	std::cout << "🧟And now you can name your brain eater:" << std::flush;
	if (!std::getline(std::cin, name)) {
		std::cerr << "🧟Naming failed, lucky for you." << std::endl;
		return 1;
	}
	if (name.empty() || name[0] == ' ') {
		std::cerr << "🧟The zombies without name lost their apetite. (exiting...)" << std::endl;
		return 1;
	}
	Zombie* horde = zombieHorde(z_count, name);
	if (!horde) {
		std::cerr << "🧟Allocation failed, lucky for you." << std::endl;
		return 1;
	}
	for (int i = 0; i < z_count; i++) {
		horde[i].announce();
	}
	
	delete [] horde;
	return 0;
}

