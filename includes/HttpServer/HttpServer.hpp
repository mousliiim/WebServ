/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpServer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 01:16:53 by rferradi          #+#    #+#             */
/*   Updated: 2023/09/21 19:29:31 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef __HTTP_SERVER_HPP__
# define __HTTP_SERVER_HPP__

# define MAX_EPOLL_EVENT 1024
# define B_WHITE "\033[0;37m"

# include "Location.hpp"
# include "main.hpp"

class Server;
class Stream;

class HttpServer
{
	private:
		std::map <int, std::string>	_request;
		std::vector<Stream *>		_servers;
		int 						_epollFd;
		std::vector <epoll_event> 	_events;

	public:
		HttpServer();
		~HttpServer();
		
		std :: vector<Stream *>	getStreams() const;

		void		printServers() const;
		void		addServer(Server *serv);
		void		initEpollInstance();
		void		startServer();
		void		closeAllFd () const;
		static int	_SigInt;
};

std :: ostream	&operator<<(std :: ostream &os, const p_locate &locate);

#endif