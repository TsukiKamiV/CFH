#include "Server.hpp"


void	Server::handleKick(size_t clientIndex, const parseMessage &msg) {
	if (msg.params.size() < 2){
		std::cout << "[KICK] not enough parameters" << std::endl;
		sendToClient(clientIndex, "[KICK] not enough parameters\r\n");
		return ;
	}
		
	std::string channelName = msg.params[0];
	std::string targetNick = msg.params[1];
	std::string reason = "";
	if (msg.params.size() >= 3)
		reason = msg.params[2];
	int clientFd = _clients[clientIndex].getFd();
	
	if (channelName.empty() || targetNick.empty()) {
		std::cout << "[KICK] invalid parameter" << std::endl;
		sendToClient(clientIndex, "[KICK] invalid parameter\r\n");
		return ;
	}
	if (channelName[0] != '#') {
		std::cout << "[KICK] invalid channel name" << std::endl;
		sendToClient(clientIndex, "[KICK] invalid channel name\r\n");
		return ;
	}
	int	channelIndex = findChannelIndex(channelName);
	if (channelIndex == -1) {
		std::cout << "[KICK] channel not found" << std::endl;
		sendToClient(clientIndex, "[KICK] channel not found\r\n");
		return;
	}
	if (!_clients[clientIndex].isRegistered()) {
		std::cout << "[KICK] client fd " << _clients[clientIndex].getFd() << " is not registered, kick refused" << std::endl;
		sendToClient(clientIndex, "[KICK] not registered, kick refused\r\n");
		return ;
	}
	if (!_channels[channelIndex].hasMember(clientFd)) {
		std::cout << "[KICK] caller is not a member of the channel" << std::endl;
		sendToClient(clientIndex, "[KICK] caller is not a member of the channel\r\n");
		return ;
	}
	if (!_channels[channelIndex].hasOperator(clientFd)) {
		std::cout << "[KICK] caller is not an operator of the channel" << std::endl;
		sendToClient(clientIndex, "[KICK] caller is not an operator of the channel\r\n");
		return ;
	}
	int	targetIndex = findClientIndexByNick(targetNick);
	int targetFd;
	if (targetIndex >= 0)
		targetFd = _clients[targetIndex].getFd();
	else {
		std::cout << "[KICK] target nick not found" << std::endl;
		sendToClient(clientIndex, "[KICK] target nickname not found\r\n");
		return ;
	}
	if (!_channels[channelIndex].hasMember(targetFd)) {
		std::cout << "[KICK] target is not a member of the channel" << std::endl;
		sendToClient(clientIndex, "[KICK] target is not a member of the channel\r\n");
		return ;
	}
	if (msg.params.size() < 2 || msg.params.size() > 3) {
		std::cout << "[KICK] invalid format" << std::endl;
		sendToClient(clientIndex, "[KICK] invalid format, use: KICK #channel nickname :reason\r\n");
		return ;
	}
	if (msg.params.size() == 3 && msg.hasTrailingParam == false) {
		std::cout << "[KICK] invalid reason format" << std::endl;
		sendToClient(clientIndex, "[KICK] invalid format, use: KICK #channel nickname :reason\r\n");
		return ;
	}
	//if (_channels[channelIndex].hasOperator(targetFd))
	//	_channels[channelIndex].removeOperator(targetFd);
	_channels[channelIndex].removeMember(targetFd);
	std::cout << "[KICK] target kicked out from channel" << std::endl;
	sendToClient(clientIndex, "[KICK] target kicked out from channel\r\n");
	sendToClient(targetIndex, "[KICK] you were kicked from " + channelName + "\r\n");
	if (!reason.empty()) {
		sendToClient(targetIndex, "[KICK] reason: " + reason + "\r\n");
		channelBroadcast(channelIndex, "[KICK] " + targetNick + " kicked out from channel: " + reason + "\r\n");
	}
	else
		channelBroadcast(channelIndex, "[KICK] " + targetNick + " kicked out from channel\r\n");
	if (_channels[channelIndex].isEmpty())
		removeChannel(channelIndex);
}

void	Server::handleInvite(size_t clientIndex, const parseMessage &msg) {
	if (msg.params.size() < 2) {
		std::cout << "[INVITE] not enough parameters" << std::endl;
		sendToClient(clientIndex, "[INVITE] not enough parameters\r\n");
		return ;
	}
	std::string targetNick = msg.params[0];
	std::string channelName = msg.params[1];
	int clientFd = _clients[clientIndex].getFd();
	if (targetNick.empty() || channelName.empty()) {
		std::cout << "[INVITE] invalid parameter" << std::endl;
		sendToClient(clientIndex, "[INVITE] invalid parameter\r\n");
		return ;
	}
	if (!_clients[clientIndex].isRegistered()) {
		std::cout << "[INVITE] client fd " << clientFd << " is not registered, invite refused" << std::endl;
		sendToClient(clientIndex, "[INVITE] caller not registered, invete refused\r\n");
		return ;
	}
	if (channelName[0] != '#') {
		std::cout << "[INVITE] invalid channel name" << std::endl;
		sendToClient(clientIndex, "[INVITE] invalid channel name\r\n");
		return ;
	}
	int channelIndex = findChannelIndex(channelName);
	if (channelIndex == -1) {
		std::cout << "[INVITE] channel not found" << std::endl;
		sendToClient(clientIndex, "[INVITE] channel not found\r\n");
		return ;
	}
	if (!_channels[channelIndex].hasMember(clientFd)) {
		std::cout << "[INVITE] caller is not a member of the channel" << std::endl;
		sendToClient(clientIndex, "[INVITE] caller is not a member of the channel\r\n");
		return ;
	}
	if (!_channels[channelIndex].hasOperator(clientFd)) {
		std::cout << "[INVITE] caller is not an operator of the channel" << std::endl;
		sendToClient(clientIndex, "[INVITE] caller is not an operator of the channel\r\n");
		return ;
	}
	int targetIndex = findClientIndexByNick(targetNick);
	int targetFd;
	if (targetIndex >= 0)
		targetFd = _clients[targetIndex].getFd();
	else {
		std::cout << "[INVITE] target nick not found" << std::endl;
		sendToClient(clientIndex, "[INVITE] tartget nickname not found\r\n");
		return ;
	}
	if (!_clients[targetIndex].isRegistered()) {
		std::cout << "[INVITE] target is not registered" << std::endl;
		sendToClient(clientIndex, "[INVITE] target is not registered\r\n");
		return ;
	}
	if (_channels[channelIndex].hasMember(targetFd)) {
		std::cout << "[INVITE] target already in channel" << std::endl;
		sendToClient(clientFd, "[INVITE] target already in channel\r\n");
		return ;
	}
	_channels[channelIndex].addInvite(targetFd);
	std::cout << "[INVITE] " << targetNick << " invited to " << channelName << std::endl;
	sendToClient(clientIndex, "[INVITE] invitation sent to " + targetNick + "\r\n");
	sendToClient(targetIndex, "[INVITE] you are invited to " + channelName + " by " + _clients[clientIndex].getNick() + "\r\n");
	channelBroadcast(channelIndex, _clients[clientIndex].getNick() + " has invited " + targetNick + " to join the channel\r\n");
}


void	Server::   handleTopic(size_t clientIndex, const parseMessage &msg) {
	if (msg.params.size() < 1) {
		std::cout << "[TOPIC] not enough parameters" << std::endl;
		sendToClient(clientIndex, "[TOPIC] not enough parameters\r\n");
		return ;
	}
	std::string channelName = msg.params[0];
	int clientFd = _clients[clientIndex].getFd();
	if (channelName.empty() || channelName[0] != '#') {
		std::cout << "[TOPIC] invalid channel name" << std::endl;
		sendToClient(clientIndex, "[TOPIC] invalid channel name\r\n");
		return ;
	}
	if (!_clients[clientIndex].isRegistered()) {
		std::cout << "[TOPIC] client fd " << clientFd << " is not registered, topic refused" << std::endl;
		sendToClient(clientIndex, "[TOPIC] caller not registered, topic refused\r\n");
		return ;
	}
	
	int channelIndex = findChannelIndex(channelName);
	if (channelIndex == -1) {
		std::cout << "[TOPIC] channel not found" << std::endl;
		sendToClient(clientIndex, "[TOPIC] channel not found\r\n");
		return ;
	}
	if (!_channels[channelIndex].hasMember(clientFd)) {
		std::cout << "[TOPIC] caller is not a member of the channel" << std::endl;
		sendToClient(clientIndex, "[TOPIC] caller is not a member of the channel\r\n");
		return ;
	}
	
	if (msg.params.size() == 1) {
		if (_channels[channelIndex].getTopic().empty())
			sendToClient(clientIndex, "[TOPIC] no topic is set\r\n");
		else
			sendToClient(clientIndex, "[TOPIC] current topic: " + _channels[channelIndex].getTopic() + "\r\n");
		return ;
	}
	if (_channels[channelIndex].isTopicRestricted() && !_channels[channelIndex].hasOperator(clientFd)) {
		std::cout << "[TOPIC] caller is not channel operator" << std::endl;
		sendToClient(clientIndex, "[TOPIC] caller is not channel operator\r\n");
		return ;
	}
	if (msg.params.size() != 2 || msg.hasTrailingParam == false) {
		std::cout << "[TOPIC] invalid topic format" << std::endl;
		sendToClient(clientIndex, "[TOPIC] invalid format, use: TOPIC #channel :new topic\r\n");
		return ;
	}
	std::string newTopic = msg.params[1];
	_channels[channelIndex].setTopic(newTopic);
	if (newTopic.empty()) {
		std::cout << "[TOPIC] topic cleared on " << _channels[channelIndex].getName() << std::endl;
		sendToClient(clientIndex, "[TOPIC] topic cleared\r\n");
		channelBroadcast(channelIndex, "[TOPIC] topic cleared by " + _clients[clientIndex].getNick() + "\r\n");
	}
	else {
		std::cout << "[TOPIC] topic changed on " << _channels[channelIndex].getName() << std::endl;
		sendToClient(clientIndex, "[TOPIC] topic changed\r\n");
		channelBroadcast(channelIndex, "[TOPIC] new topic set by " + _clients[clientIndex].getNick() + ": " + newTopic + "\r\n");
	}
}

void	Server::handlePrivmsg(size_t clientIndex, const parseMessage &msg) {
	std::string	messageTarget;
	std::string	messageBody;
	std::string	formattedMessage;
	int			clientFd = _clients[clientIndex].getFd();
	int			targetIndex;
	int			channelIndex;
	int 		targetFd;
	size_t		i, j;
	const std::vector<int> *memberFds;
	
	if (msg.params.size() != 2 || msg.hasTrailingParam == false) {
		std::cout << "[PRIVMSG] invalid format" << std::endl;
		sendToClient(clientIndex, "[PRIVMSG] invalid format, use: PRIVMSG target :message\r\n");
		return ;
	}
	if (!_clients[clientIndex].isRegistered()) {
		std::cout << "[PRIVMSG] client fd " << clientFd << " is not registered, PRIVMSG refused" << std::endl;
		sendToClient(clientIndex, "[PRIVMSG] caller not registered, PRIVMSG refused\r\n");
		return ;
	}
	messageTarget = msg.params[0];
	messageBody = msg.params[1];
	if (messageTarget.empty() || messageBody.empty()) {
		std::cout << "[PRIVMSG] invalid parameter" << std::endl;
		sendToClient(clientIndex, "[PRIVMSG] invalid parameter\r\n");
		return ;
	}
	
	if (messageTarget[0] == '#') {
		channelIndex = findChannelIndex(messageTarget);
		if (channelIndex == -1) {
			std::cout << "[PRIVMSG] channel not found" << std::endl;
			sendToClient(clientIndex, "[PRIVMSG] channel not found\r\n");
			return ;
		}
		if (!_channels[channelIndex].hasMember(clientFd)) {
			std::cout << "[PRIVMSG] caller is not a member of the channel" << std::endl;
			sendToClient(clientIndex, "[PRIVMSG] caller is not a member of the channel\r\n");
			return ;
		}
		memberFds = &_channels[channelIndex].getMemberFds();
		i = 0;
		while (i < memberFds->size()) {
			if ((*memberFds)[i] != clientFd) {
				j = 0;
				while (j < _clients.size()) {
					if (_clients[j].getFd() == (*memberFds)[i]) {
						formattedMessage = _clients[clientIndex].getNick() + " PRIVMSG " + messageTarget + " :" + messageBody + "\r\n";
						sendToClient(j, formattedMessage);
						break;
					}
					j++;
				}
			}
			i++;
		}
		return ;
	}
	targetIndex = findClientIndexByNick(messageTarget);
	if (targetIndex < 0) {
		std::cout << "[PRIVMSG] target nickname not found" << std::endl;
		sendToClient(clientIndex, "[PRIVMSG] target nickname not found\r\n");
		return ;
	}
	targetFd = _clients[targetIndex].getFd();
	formattedMessage = _clients[clientIndex].getNick() + " PRIVMSG " + messageTarget + " :" + messageBody + "\r\n";
	if (targetFd == clientFd) {
		sendToClient(clientIndex, formattedMessage);
		return ;
	}
	sendToClient(static_cast<size_t>(targetIndex), 	formattedMessage);
}

