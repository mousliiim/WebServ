/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 01:30:32 by rferradi          #+#    #+#             */
/*   Updated: 2023/09/28 18:05:05 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "HttpServer.hpp"
# include "Server.hpp"
# include "Stream.hpp"

/*--------------------------------------------------CONSTRUCTOR/DESTRUCTOR--------------------------------------------------*/

HttpServer::HttpServer(): _events(MAX_EPOLL_EVENT){}

HttpServer::~HttpServer()
{
	for (size_t i = 0; i < _servers.size(); i++)
		delete _servers[i];
}

/*--------------------------------------------------CONSTRUCTOR/DESTRUCTOR--------------------------------------------------*/

/*--------------------------------------------------MEMBER FUNCTION--------------------------------------------------*/


void	HttpServer :: printServers() const
{
	int maxDots = 3;
	for (int i = 0; i < maxDots; i++)
	{
		std::cout << B_WHITE << "[INFO] " << "Initializing server(s)";
		for (int j = 0; j < i + 1; j++)
			std::cout << ".";
		std::cout << "\r";
		std::cout.flush();
		usleep(350000);
	}
	std::cout << "\033[2K\r"; //
	std::cout << B_GREEN << "[INFO] " << "Server(s) is ready" << RESET << std::endl << std::endl;
	displayTime();
	std::cout << B_WHITE << "  [INFO]   " << "Server(s) list :" << RESET << std::endl << std::endl;
	for (std :: vector<Stream *> :: const_iterator it = _servers.begin(); it != _servers.end(); it++)
	{
		map_locate currentLocations = static_cast<Server *>(*it)->getLocations();
		displayTime(B_WHITE);
		std::cout << B_WHITE << "  [SERVER_INFO]   " << "Server name : " << currentLocations.begin()->second->getServerName() << std::endl;
		displayTime(B_WHITE);
		std::cout << B_WHITE << "  [SERVER_INFO]   " << "IP : " << currentLocations.begin()->second->getListen() << std::endl;
		displayTime(B_WHITE);
		std::cout << B_WHITE << "  [SERVER_INFO]   " << "Port : " << currentLocations.begin()->second->getPort() << std::endl;
		displayTime(B_WHITE);
		std::cout << B_WHITE << "  [SERVER_INFO]   " << "Index : " << currentLocations.begin()->second->getIndex() << std::endl;
		std::cout << std::endl;
	}
}

void HttpServer::initEpollInstance()
{
	if ((_epollFd = epoll_create1(0)) < 0)
	{
		closeAllFd();
		throw std::runtime_error("Epoll creation failed");
	}
	for (size_t i = 0; i < _servers.size(); i++)
	{
		_events[i].events = EPOLLIN;
		_events[i].data.ptr = _servers[i];
		if (epoll_ctl(_epollFd, EPOLL_CTL_ADD, _servers[i]->getSocketFd(),
				&_events[i]) < 0)
			throw std::runtime_error("Epoll_ctl failed");
	}
}

void HttpServer::closeAllFd() const
{
	_epollFd ? close(_epollFd) : false;
	for (size_t i = 0; i < _servers.size(); i++)
		close(_servers[i]->getSocketFd());
}

void HttpServer::addServer(Server *serv)
{
	_servers.push_back(serv);
}

void HttpServer::startServer(void)
{
	initEpollInstance();
	int numEvents;
	while (!HttpServer::_SigInt)
	{
		if (HttpServer::_SigInt) break;

		if ((numEvents = epoll_wait(_epollFd, _events.data(), _servers.size(), -1)) < 0 && !HttpServer::_SigInt)
			std::cout << "Epoll_wait failed" << std::endl;
		for (int i = 0; i < numEvents; i++)
		{
			Stream *stream = static_cast<Stream *>(_events[i].data.ptr);
			if (stream->handleRequest(_epollFd, _events[i]) == -1)
			{
				stream->getServer()->deleteFromMap(stream);
			}
		}
	}
}

std :: vector<Stream *> HttpServer :: getStreams() const
{
	return _servers;
}

/*--------------------------------------------------MEMBER FUNCTION--------------------------------------------------*/

/*--------------------------------------------------STATIC VARIABLES--------------------------------------------------*/
int HttpServer::_SigInt = 0;
/*--------------------------------------------------STATIC VARIABLES--------------------------------------------------*/
