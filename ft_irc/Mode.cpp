#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"

bool	Server::checkModeParams(size_t clientIndex, const parseMessage &msg) {
	std::string modeString;
	int			channelIndex;
	
	if (clientIndex >= _clients.size())
		return false;
	if (!_clients[clientIndex].isRegistered()) {
		std::cout << "[MODE] client not registered" << std::endl;
		sendToClient(clientIndex, "[MODE] client not registered\r\n");
		return false;
	}
	if (msg.params.size() < 2) {
		std::cout << "[MODE] not enough parameters" << std::endl;
		sendToClient(clientIndex, "[MODE] not enough parameters\r\n");
		return false;
	}
	if (msg.params[0].empty() || msg.params[0][0] != '#') {
		std::cout << "[MODE] invalid channel name" << std::endl;
		sendToClient(clientIndex, "[MODE] invalid channel name\r\n");
		return false;
	}
	channelIndex = findChannelIndex(msg.params[0]);
	if (channelIndex == -1) {
		std::cout << "[MODE] channel not found" << std::endl;
		sendToClient(clientIndex, "[MODE] channel not found\r\n");
		return false;
	}
	modeString = msg.params[1];
	if (modeString != "+o" && modeString != "-o"
		&& modeString != "+i" && modeString != "-i"
		&& modeString != "+t" && modeString != "-t"
		&& modeString != "+k" && modeString != "-k"
		&& modeString != "+l" && modeString != "-l") {
		std::cout << "[MODE] unsupported mode string" << std::endl;
		sendToClient(clientIndex, "[MODE] unsupported mode string\r\n");
		return false;
	}
	if ((modeString == "+o" || modeString == "-o" || modeString == "+k") && msg.params.size() < 3) {
		std::cout << "[MODE] missing mode parameter" << std::endl;
		sendToClient(clientIndex, "[MODE] missing mode parameter\r\n");
		return false;
	}
	return true;
}

void	Server::handleMode(size_t clientIndex, const parseMessage &msg) {
	std::string channelName;
	std::string modeString;
	std::string targetNick;
	int			channelIndex;
	int			nickIndex;
	int			targetFd;
	
	if (!checkModeParams(clientIndex, msg))
		return ;
	channelName = msg.params[0];
	modeString = msg.params[1];
	channelIndex = findChannelIndex(channelName);
	if (msg.params.size() >= 3)
		targetNick = msg.params[2];
	if (modeString == "+o" || modeString == "-o") {
		nickIndex = findClientIndexByNick(targetNick);
		if (nickIndex == -1) {
			std::cout << "[MODE] target nickname not found" << std::endl;
			sendToClient(clientIndex, "[MODE] target nick not found\r\n");
			return ;
		}
		targetFd = _clients[nickIndex].getFd();
		operatorManager(clientIndex, modeString, channelIndex, targetFd);
	}
	else if (modeString == "+i" || modeString == "-i") {
		if (msg.params.size() != 2) {
			std::cout << "[MODE] invalid format for invite-only mode" << std::endl;
			sendToClient(clientIndex, "[MODE] invalid format, use: MODE #channel +/-i\r\n");
			return ;
		}
		inviteOnlyManager(clientIndex, modeString, channelIndex);
	}
	else if (modeString == "+t" || modeString == "-t") {
		if (msg.params.size() != 2) {
			std::cout << "[MODE] invalid format for topic restriction" << std::endl;
			sendToClient(clientIndex, "[MODE] invalid format, use: MODE #channel +/-t\r\n");
			return ;
		}
		topicManager(clientIndex, modeString, channelIndex);
	}
	else if (modeString == "+k" || modeString == "-k") {
		std::string key = "";
		if (modeString == "+k") {
			if (msg.params.size() != 3) {
				std::cout << "[MODE] channel key needed" << std::endl;
				sendToClient(clientIndex, "[MODE] channel key needed\r\n");
				return ;
			}
			key = msg.params[2];
		}
		keyManager(clientIndex, modeString, key, channelIndex);
	}
	else if (modeString == "+l" || modeString == "-l") {
		long	maxNumber;
		char	*end;
		
		maxNumber = 0;
		if (modeString == "+l") {
			if (msg.params.size() != 3) {
				std::cout << "[MODE] limit number needed" << std::endl;
				sendToClient(clientIndex, "[MODE] limit number needed\r\n");
				return ;
			}
			errno = 0;
			end = NULL;
			maxNumber = std::strtol(msg.params[2].c_str(), &end, 10);
			if (errno == ERANGE || end == msg.params[2].c_str() || *end != '\0'
				|| maxNumber <= 0 || maxNumber > INT_MAX) {
				std::cout << "[MODE] invalid limit number" << std::endl;
				sendToClient(clientIndex, "[MODE] invalid limit number\r\n");
				return ;
			}
		}
		maxMemberManager(clientIndex, modeString, static_cast<int>(maxNumber), channelIndex);
	}
	else
		sendToClient(clientIndex, "[MODE] invalid option flag\r\n");
}

void	Server::operatorManager(size_t clientIndex, const std::string &modeString, int channelIndex, int targetFd) {
	if (!_channels[channelIndex].hasOperator(_clients[clientIndex].getFd())) {
		std::cout << "[MODE] caller is not channel operator" << std::endl;
		sendToClient(clientIndex, "[MODE] caller is not channel operator\r\n");
		return ;
	}
	if (modeString == "+o") {
		int res = _channels[channelIndex].addOperator(targetFd);
		if (res == Channel::OPERATOR_ADDED)
			sendToClient(clientIndex, "[MODE] operator granted\r\n");
		else if (res == Channel::OPERATOR_NOT_MEMBER)
			sendToClient(clientIndex, "[MODE] target is not a channel member\r\n");
		else if (res == Channel::OPERATOR_ALREADY_SET)
			sendToClient(clientIndex, "[MODE] target already operator\r\n");
	}
	else if (modeString == "-o") {
		int res = _channels[channelIndex].removeOperator(targetFd);
		if (res == Channel::OPERATOR_NOT_FOUND)
			sendToClient(clientIndex, "[MODE] operator not found\r\n");
		else if (res == Channel::OPERATOR_REMOVED)
			sendToClient(clientIndex, "[MODE] operator removed\r\n");
		//else if (res == Channel::OPERATOR_LESS_THAN_ONE)
		//	sendToClient(clientIndex, "[MODE] cannot remove last //operator\r\n");
		
	}
}

void	Server::inviteOnlyManager(size_t clientIndex, const std::string &modeString, int channelIndex) {
	int clientFd = _clients[clientIndex].getFd();
	if (!_channels[channelIndex].hasOperator(clientFd)) {
		std::cout << "[MODE] caller is not channel operator" << std::endl;
		sendToClient(clientIndex, "[MODE] caller is not channel operator\r\n");
		return ;
	}
	if (modeString == "+i") {
		if (_channels[channelIndex].isInviteOnly()) {
			sendToClient(clientIndex, "[MODE] channel already invite only\r\n");
			return ;
		}
		_channels[channelIndex].setInviteOnly(true);
		std::cout << "[MODE] invite-only enabled" << std::endl;
		sendToClient(clientIndex, "[MODE] invite-only enabled\r\n");
		channelBroadcast(channelIndex, "[MODE] channel invite-only enabled by " + _clients[clientIndex].getNick() + "\r\n");
	}
	else if (modeString == "-i") {
		if (!_channels[channelIndex].isInviteOnly()) {
			sendToClient(clientIndex, "[MODE] channel already open\r\n");
			return ;
		}
		_channels[channelIndex].setInviteOnly(false);
		std::cout << "[MODE] invite-only disabled on " << _channels[channelIndex].getName() << std::endl;
		sendToClient(clientIndex, "[MODE] channel invite-only disabled\r\n");
		channelBroadcast(channelIndex, "[MODE] channel invite-only disabled by " + _clients[clientIndex].getNick() + "\r\n");
	}
}

void	Server::topicManager(size_t clientIndex, const std::string &modeString, int channelIndex) {
	int clientFd = _clients[clientIndex].getFd();
	if (!_channels[channelIndex].hasOperator(clientFd)) {
		std::cout << "[MODE] caller is not channel operator" << std::endl;
		sendToClient(clientIndex, "[MODE] caller is not channel operator\r\n");
		return ;
	}
	if (modeString == "+t") {
		if (_channels[channelIndex].isTopicRestricted()) {
			sendToClient(clientIndex, "[MODE] channel topic already restricted\r\n");
			return ;
		}
		_channels[channelIndex].setTopicRestricted(true);
		std::cout << "[MODE] channel topic restricted" << std::endl;
		sendToClient(clientIndex, "[MODE] channel topic restricted\r\n");
		channelBroadcast(channelIndex, "[MODE] channel topic restricted: operator only; set by " + _clients[clientIndex].getNick() + "\r\n");
	}
	else if (modeString == "-t") {
		if (!_channels[channelIndex].isTopicRestricted()) {
			sendToClient(clientIndex, "[MODE] channel topic already open\r\n");
			return ;
		}
		_channels[channelIndex].setTopicRestricted(false);
		std::cout << "[MODE] channel topic restriction disabled on " << _channels[channelIndex].getName() << std::endl;
		sendToClient(clientIndex, "[MODE] channel topic restriction disabled\r\n");
		channelBroadcast(channelIndex, "[MODE] channel topic restricted by " + _clients[clientIndex].getNick() + "\r\n");
	}
}

void	Server::keyManager(size_t clientIndex, const std::string &modeString, const std::string &key, int channelIndex) {
	int	clientFd = _clients[clientIndex].getFd();
	if (!_channels[channelIndex].hasOperator(clientFd)) {
		std::cout << "[MODE] caller is not channel operator" << std::endl;
		sendToClient(clientIndex, "[MODE] caller is not channel operator\r\n");
		return ;
	}
	if (modeString == "+k") {
		if (key.empty()) {
			std::cout << "[MODE] missing channel key" << std::endl;
			sendToClient(clientIndex, "[MODE] missing channel key\r\n");
			return ;
		}
		if (!_channels[channelIndex].getKey().empty()) {
			_channels[channelIndex].setKey(key);
			std::cout << "[MODE] channel key modified on " << _channels[channelIndex].getName() << std::endl;
			sendToClient(clientIndex, "[MODE] channel key modified\r\n");
			channelBroadcast(channelIndex, "[MODE] channel key modified by " + _clients[clientIndex].getNick() + "\r\n");
			
		}
		else {
			_channels[channelIndex].setKey(key);
			std::cout << "[MODE] channel key enabled on " << _channels[channelIndex].getName() << 	std::endl;
			sendToClient(clientIndex, "[MODE] channel key enabled\r\n");
			channelBroadcast(channelIndex, "[MODE] channel key enabled by " + _clients[clientIndex].getNick() + "\r\n");
		}
	}
	else if (modeString == "-k") {
		if (!_channels[channelIndex].isKeyNeeded()) {
			sendToClient(clientIndex, "[MODE] channel key is not set\r\n");
			return ;
		}
		_channels[channelIndex].removeKey();
		std::cout << "[MODE] channel key disabled on " << _channels[channelIndex].getName() << std::endl;
		sendToClient(clientIndex, "[MODE] channel key disabled by " + _clients[clientIndex].getNick() + "\r\n");
		channelBroadcast(channelIndex, "[MODE] channel key disabled by " + _clients[clientIndex].getNick() + "\r\n");
	}
}

void	Server::maxMemberManager(size_t clientIndex, const std::string &modeString, int maxNumber, int channelIndex) {
	int clientFd = _clients[clientIndex].getFd();
	if (!_channels[channelIndex].hasOperator(clientFd)) {
		std::cout << "[MODE] caller is not channel operator" << std::endl;
		sendToClient(clientIndex, "[MODE] caller is not channel operator\r\n");
		return ;
	}
	
	if (modeString == "+l") {
		if (_channels[channelIndex].isNumLimited()) {
			_channels[channelIndex].setMaxMemberNum(maxNumber);
			std::cout << "[MODE] channel member limit modified on " << _channels[channelIndex].getName() << std::endl;
			sendToClient(clientIndex, "[MODE] channel member limit modified\r\n");
			channelBroadcast(channelIndex, "[MODE] channel member limit modified by " + _clients[clientIndex].getNick() + "\r\n");
		}
		else {
			_channels[channelIndex].setMaxMemberNum(maxNumber);
			std::cout << "[MODE] channel member limit enabled on " << _channels[channelIndex].getName() << std::endl;
			sendToClient(clientIndex, "[MODE] channel member limit enabled\r\n");
			channelBroadcast(channelIndex, "[MODE] channel member limit enabled by " + _clients[clientIndex].getNick() + "\r\n");
		}
	}
	else if (modeString == "-l") {
		if (!_channels[channelIndex].isNumLimited()) {
			sendToClient(clientIndex, "[MODE] channel member limit is not set\r\n");
			return ;
		}
		_channels[channelIndex].removeMaxMemberNum();
		std::cout << "[MODE] channel member limit disabled on " << _channels[channelIndex].getName() << std::endl;
		sendToClient(clientIndex, "[MODE] channel member limit disabled\r\n");
		channelBroadcast(channelIndex, "[MODE] channel member limit disabled by " + _clients[clientIndex].getNick() + "\r\n");
	}
}
