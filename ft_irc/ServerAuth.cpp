#include "Server.hpp"

void	Server::handlePass(size_t clientIndex, const parseMessage &msg) {
	if (clientIndex >= _clients.size())
		return ;
	if (_clients[clientIndex].isPassApprouved()) {
		std::cout << "[PASS] client has already entered password" << std::endl;
		sendToClient(clientIndex, "[PASS] you've already entered password\r\n");
		return ;
	}
	if (msg.params.size() < 1) {
		std::cout << "[PASS] missing password parameter" << std::endl;
		sendToClient(clientIndex, "[PASS] missing password parameter\r\n");
		return ;
	}
	if (_clients[clientIndex].isRegistered()) {
		std::cout << "[PASS] client already registered" << std::endl;
		return ;
	}
	if (msg.params[0] != _password) {
		std::cout << "[PASS] wrong password" << std::endl;
		sendToClient(clientIndex, "Wrong password\r\n");
		return ;
	}
	_clients[clientIndex].setPassApprouved(true);
	std::cout << "[PASS] password accepted for fd " << _clients[clientIndex].getFd() << std::endl;
	checkRegistration(clientIndex);
}

void	Server::handleNick(size_t clientIndex, const parseMessage &msg) {
	std::string	oldNick;
	std::string	newNick;
	int			clientFd;
	if (clientIndex >= _clients.size())
		return ;
	if (msg.params.size() < 1) {
		std::cout << "[NICK] missing nickname parameter" << std::endl;
		sendToClient(clientIndex, "[NICK] missing nickname parameter\r\n");
		return ;
	}
	newNick = msg.params[0];
	if (newNick.empty()) {
		std::cout << "[NICK] invalid nickname" << std::endl;
		sendToClient(clientIndex, "[NICK] invalid nickname\r\n");
		return ;
	}
	for (size_t i = 0; i < _clients.size(); ++i) {
		if (i != clientIndex && newNick == _clients[i].getNick()) {
			std::cout << "[NICK] nickname already exists, please choose another one" << std::endl;
			sendToClient(clientIndex, "[NICK] nickname already exists, please choose another one\r\n");
			return ;
		}
	}
	oldNick = _clients[clientIndex].getNick();
	clientFd = _clients[clientIndex].getFd();
	if (oldNick == newNick) {
		sendToClient(clientIndex, "[NICK] nickname unchanged\r\n");
		return ;
	}
	_clients[clientIndex].setNick(newNick);
	std::cout << "[NICK] fd" << clientFd << " set nickname to " << newNick << std::endl;
	if (_clients[clientIndex].isRegistered() && !oldNick.empty()) {
		sendToClient(clientIndex, "[NICK] you are now known as "+ newNick + "\r\n");
		broadcastNickChange(clientFd, oldNick, newNick);
		return ;
	}
	checkRegistration(clientIndex);
}

void	Server::handleUser(size_t clientIndex, const parseMessage &msg) {
	if (clientIndex >= _clients.size())
		return ;
	if (msg.params.size() < 4) {
		std::cout << "[USER] not enough parameters" << std::endl;
		sendToClient(clientIndex, "[USER] not enough parameters\r\nExample: USER alice 0 * :Alice Example\r\n");
		return ;
	}
	if (!msg.hasTrailingParam) {
		std::cout << "[USER] invalid user format" << std::endl;
		sendToClient(clientIndex, "[USER] invalid user format. Use: USER username 0 * :realname\r\n");
		return ;
	}
	if (_clients[clientIndex].isRegistered()) {
		std::cout << "[USER] client already registered" << std::endl;
		sendToClient(clientIndex, "[USER] client already registered\r\n");
		return ;
	}
	if (!_clients[clientIndex].getUsername().empty()) {
		std::cout << "[USER] username already set" << std::endl;
		sendToClient(clientIndex, "[USER] username already set\r\n");
		return ;
	}
	_clients[clientIndex].setUsername(msg.params[0]);
	std::cout << "[USER] fd " << _clients[clientIndex].getFd() << " set username to " << _clients[clientIndex].getUsername() << std::endl;
	checkRegistration(clientIndex);
}

void	Server::checkRegistration(size_t clientIndex) {
	if (clientIndex >= _clients.size())
		return ;
	if (_clients[clientIndex].isPassApprouved() && !_clients[clientIndex].getNick().empty() && !_clients[clientIndex].getUsername().empty()) {
		_clients[clientIndex].setRegistered(true);
		std::cout << "[REGISTER] client fd " << _clients[clientIndex].getFd() << " is registered." << std::endl;
		sendToClient(clientIndex, ">>> Registration success <<<\r\nYou can start chatting now\r\n");
	}
}

bool	Server::isClientRegistered(size_t clientIndex) const {
	if (clientIndex >= _clients.size())
		return false;
	return (_clients[clientIndex].isRegistered());
}

int		Server::findClientIndexByNick(const std::string &nick) const {
	for (size_t i = 0; i < _clients.size(); ++i) {
		if (_clients[i].getNick() == nick)
			return static_cast<int>(i);
	}
	return -1;
}
