#include "Server.hpp"
#include "Channel.hpp"
#include "Client.hpp"


void	Server::handleClientBuffer(size_t clientIndex, const std::string &chunk) {
	std::string &clientBuffer = _clients[clientIndex].getBuffer();
	size_t		pos;
	std::string line;
	int			fd;
	
	fd = _clients[clientIndex].getFd();
	_clients[clientIndex].appendBuffer(chunk);
	while (true) {
		pos = clientBuffer.find('\n');
		if (pos == std::string::npos)
			break;
		line = clientBuffer.substr(0, pos);
		if (!line.empty() && line[line.size() - 1] == '\r')
			line.erase(line.size() - 1);
		clientBuffer.erase(0, pos + 1);
		processLine(clientIndex, line);
		std::cout << "[Buffer fd " << fd << "] " << line << std::endl;
	}
}

void	Server::handleSendBuffer(size_t index, const std::string &chunk) {
	if (index >= _clients.size())
		return ;
	std::string	&sendBuffer = _clients[index].getSendBuffer();
	ssize_t		sentBytes;
	int			fd;
	
	fd = _clients[index].getFd();
	if (!chunk.empty())
		_clients[index].appendSendBuffer(chunk);
	while (!sendBuffer.empty()) {
		sentBytes = send(fd, sendBuffer.c_str(), sendBuffer.size(), 0);
		if (sentBytes > 0) {
			sendBuffer.erase(0, sentBytes);
			continue;
		}
		if (sentBytes == 0) {
			_clients[index].setShouldDisconnect(true);
			break;
		}
		
		//throw std::runtime_error("Error: send returned 0");
		if (sentBytes == -1) {
			if (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR)
				break ;
			_clients[index].setShouldDisconnect(true);
			break;
		}
	}
	updateClientPollEvent(index);
}

void	Server::updateClientPollEvent(size_t clientIndex) {
	size_t	pollIndex;
	if (clientIndex >= _clients.size())
		return ;
	pollIndex = clientIndex + 1;
	if (pollIndex >= _fds.size())
		return ;
	if (_clients[clientIndex].getSendBuffer().empty())
		_fds[pollIndex].events = POLLIN;
	else
		_fds[pollIndex].events = POLLIN | POLLOUT;
}

void	Server::processLine(size_t clientIndex, const std::string &line) {
	parseMessage msg;
	if (line.empty())
		return ;
	msg = parseLine(line);
	if (msg.command.empty())
		return ;
	//std::cout << "Input message command: " << msg.command << ", params: " << msg.params[0] << std::endl;
	if (msg.command == "PASS")
		handlePass(clientIndex, msg);
	else if (msg.command == "NICK")
		handleNick(clientIndex, msg);
	else if (msg.command == "USER")
		handleUser(clientIndex, msg);
	else if (msg.command == "JOIN")
		handleJoin(clientIndex, msg);
	else if (msg.command == "MODE")
		handleMode(clientIndex, msg);
	else if (msg.command == "KICK")
		handleKick(clientIndex, msg);
	else if (msg.command == "INVITE")
		handleInvite(clientIndex, msg);
	else if (msg.command == "TOPIC")
		handleTopic(clientIndex, msg);
	else if (msg.command == "PRIVMSG")
		handlePrivmsg(clientIndex, msg);
	else {
		std::cout << "[INFO] Unknown command: " << msg.command << std::endl;
		sendToClient(clientIndex, "[INFO] unknown command\r\n");
	}
}

parseMessage	Server::parseLine(const std::string &line) {
	parseMessage 	msg;
	size_t			i;
	size_t			start;
	
	i = 0;
	while (i < line.size() && line[i] == ' ')
		i++;
	start = i;
	while (i < line.size() && line[i] != ' ')
		i++;
	if (start < i)
		msg.command = line.substr(start, i - start);
	while (i < line.size()) {
		while (i < line.size() && line[i] == ' ')
			i++;
		if (i >= line.size())
			break;
		if (line[i] == ':') {
			msg.hasTrailingParam = true;
			msg.params.push_back(line.substr(i + 1));
			break;
		}
		start = i;
		while (i < line.size() && line[i] != ' ')
			i++;
		msg.params.push_back(line.substr(start, i - start));
	}
	return msg;
}

/**
 *@func : send(fd, message.c_str(), message.size(), 0);
 *❗️❗️To be improuved for non-blocking partial chunck sending/ EAGAIN / EWOULDBLOCK / Buffer zone sending
 */
void	Server::sendToClient(size_t clientIndex, const std::string &message) {
	//if (clientIndex >= _clients.size())
	//	return ;
	//ssize_t	sentBytes;
	//int		fd = _clients[clientIndex].getFd();
	//sentBytes = send(fd, message.c_str(), message.size(), 0);
	//if (sentBytes == -1)
	//	std::cerr << "[SEND] failed to fd " << fd << ": " << std::strerror(errno) << //std::endl;
	//size_t	pollIndex;
	
	if (clientIndex >= _clients.size())
		return ;
	if (message.empty())
		return ;
	handleSendBuffer(clientIndex, message);
	updateClientPollEvent(clientIndex);
	//POLLIN => this fd is readable (has something inside to recv())
	//POLLOUT => this fd is writable (socket can continue to send())
	//when you have something left in _sendBuffer, you wait for poll to tell you "now you can continue to send
	
}

void	Server::channelBroadcast(int channelIndex, const std::string &message) {
	size_t	i = 0, j;
	if (channelIndex < 0)
		return ;
	if (channelIndex >= static_cast<int>(_channels.size()))
		return ;
	const std::vector<int> &memberFds = _channels[channelIndex].getMemberFds();
	while (i < memberFds.size()) {
		j = 0;
		while (j < _clients.size()) {
			if (_clients[j].getFd() == memberFds[i]) {
				sendToClient(j, message);
				break;
			}
			j++;
		}
		i++;
	}
}

void	Server::broadcastNickChange(int clientFd, const std::string &oldNick, const std::string &newNick) {
	size_t	channelIndex;
	size_t	memberIndex;
	size_t	clientIndex;
	const std::vector<int>	*memberFds;
	
	channelIndex = 0;
	while (channelIndex < _channels.size()) {
		if (_channels[channelIndex].hasMember(clientFd)) {
			memberFds = &_channels[channelIndex].getMemberFds();
			memberIndex = 0;
			while (memberIndex < memberFds->size()) {
				if ((*memberFds)[memberIndex] != clientFd) {
					clientIndex = 0;
					while (clientIndex < _clients.size()) {
						if (_clients[clientIndex].getFd() == (*memberFds)[memberIndex]) {
							sendToClient(clientIndex, "[NICK] in " + _channels[channelIndex].getName() + ": " + oldNick + " is now known as " + newNick + "\r\n");
							break;
						}
						clientIndex++;
					}
				}
				memberIndex++;
			}
		}
		channelIndex++;
	}
}

