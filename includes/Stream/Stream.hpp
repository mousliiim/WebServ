/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stream.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 23:26:44 by rferradi          #+#    #+#             */
/*   Updated: 2023/09/20 15:43:35 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef STREAM_HPP
# define STREAM_HPP

# include "main.hpp"

class Server;

class Stream
{
	protected:
		int			_socketFd;
		int			_epfd;
		std::map<Stream *, Stream *>		_servers;
		Server*		_server;

	public:
		Stream();
		Stream(int fd);
		Stream(int fd, Server *ptr);
		Stream(int fd, Server *ptr, int epfd);
		virtual ~Stream(){};

		/*GETTERS*/
		int				getSocketFd() const;
		Server*			getServer(void) const;

		/*SETTERS*/
		void			setSocketFd(int fd);
		
		virtual int		handleRequest(int epfd, epoll_event& ev) = 0;
};
#endif