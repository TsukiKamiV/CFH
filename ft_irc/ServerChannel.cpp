#include "Server.hpp"
#include "Channel.hpp"
#include "Client.hpp"

void	Server::handleJoin(size_t clientIndex, const parseMessage &msg) {
	if (clientIndex >= _clients.size())
		return ;
	if (!_clients[clientIndex].isRegistered()) {
		std::cout << "[JOIN] client fd " << _clients[clientIndex].getFd() << " is not registered, join refused" << std::endl;
		sendToClient(clientIndex, "[JOIN] not registered, join refused\r\n");
		return ;
	}
	if (msg.params.size() < 1) {
		std::cout << "[JOIN] join command params not enough" << std::endl;
		sendToClient(clientIndex, "[JOIN] not enough param\r\n");
		return ;
	}
	std::string channelName = msg.params[0];
	if (channelName.empty() || channelName[0] != '#') {
		std::cout << "[JOIN] invalid channel name" << std::endl;
		sendToClient(clientIndex, "[JOIN] invalid channel name\r\n");
		return ;
	}
	int channelIndex = findChannelIndex(channelName);
	int	clientFd = _clients[clientIndex].getFd();
	if (channelIndex != -1) {
		std::cout << "[JOIN] channel name found" << std::endl;
		if (_channels[channelIndex].isInviteOnly()) {
			if (!_channels[channelIndex].hasInvite(clientFd)) {
				std::cout << "[JOIN] client not invited to join the invite-only channel" << std::endl;
				sendToClient(clientIndex, "[JOIN] channel is invite-only, join refused\r\n");
				return ;
			}
		}
		if (_channels[channelIndex].hasMember(_clients[clientIndex].getFd())) {
			sendToClient(clientIndex, "[JOIN] already in channel\r\n");
			return ;
		}
		if (_channels[channelIndex].isKeyNeeded()) {
			if (msg.params.size() != 2) {
				std::cout << "[JOIN] channel key needed" << std::endl;
				sendToClient(clientIndex, "[JOIN] channel key needed\r\n");
				return ;
			}
			if (msg.params[1] != _channels[channelIndex].getKey()) {
				std::cout << "[JOIN] wrong channel key" << std::endl;
				sendToClient(clientIndex, "[JOIN] wrong channel key\r\n");
				return ;
			}
		}
		if (_channels[channelIndex].isNumLimited()) {
			if (_channels[channelIndex].getMemberFds().size() >= static_cast<size_t>(_channels[channelIndex].getMaxMemberNum())) {
				std::cout << "[JOIN] channel member limit reached, join refused" << std::endl;
				sendToClient(clientIndex, "[JOIN] channel member limit reached, join refused\r\n");
				return ;
			}
		}
		_channels[channelIndex].addMember(_clients[clientIndex].getFd());
		std::cout << "[JOIN] joined existing channel " << channelName << std::endl;
	}
	else {
		_channels.push_back(channelName);
		channelIndex = static_cast<int>(_channels.size() - 1);
		_channels[channelIndex].addMember(clientFd);
		std::cout << "[JOIN] channel " << channelName << " created by fd " << clientFd << std::endl;
		_channels[channelIndex].addOperator(clientFd);
	}
	std::string channelTopic = _channels[channelIndex].getTopic();
	if (channelTopic.empty())
		channelTopic = "no topic is set";
	sendToClient(clientIndex, "[JOIN] joined channel " + channelName + "\r\n");
	sendToClient(clientIndex, "[JOIN] topic of current channel: " + channelTopic + "\r\n");
	if (_channels[channelIndex].hasInvite(clientFd))
		_channels[channelIndex].removeInvite(clientFd);
	channelBroadcast(channelIndex, "[JOIN] " + _clients[clientIndex].getNick() + " has joined this channel\r\n");
}

int	Server::findChannelIndex(const std::string &channelName) const {
	for (size_t i = 0; i < _channels.size(); ++i) {
		if (_channels[i].getName() == channelName)
			return (static_cast<int> (i));
	}
	return -1;
}

void	Server::removeChannel(int channelIndex) {
	if (channelIndex < 0)
		return ;
	if (channelIndex >= static_cast<int>(_channels.size()))
		return ;
	_channels.erase(_channels.begin() + channelIndex);
}

void	Server::removeClientFromChannels(int clientFd) {
	size_t	i = 0;
	while (i < _channels.size()) {
		if (_channels[i].hasOperator(clientFd))
			_channels[i].removeOperator(clientFd);
		if (_channels[i].hasInvite(clientFd))
			_channels[i].removeInvite(clientFd);
		if (_channels[i].hasMember(clientFd))
			_channels[i].removeMember(clientFd);
		if (_channels[i].isEmpty()) {
			_channels.erase(_channels.begin() + i);
			continue;
		}
		i++;
	}
}
