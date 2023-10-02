/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 06:11:03 by jewancti          #+#    #+#             */
/*   Updated: 2023/09/28 17:53:35 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# ifndef __SERVER_HPP__
# define __SERVER_HPP__

# include "main.hpp"
# include "Stream.hpp"
# include "Location.hpp"



class Server: public Stream
{
	private:
		std :: string				_index;
		map_locate					_locate;
		int							_epollFd;
		int							_port;
		
		Location	*_parse(const std :: string);
		bool		_sendHTMLFile(int fd, const std :: string &filename);
		bool		_sendRedirect(int fd, const std :: string &location);
		bool		_send(int fd, const std :: string &content);
	public:
		Server(map_locate &locate);
		~Server();

		map_locate	getLocations() const;
		void		deleteFromMap(Stream*);
		virtual int		handleRequest(int epfd, epoll_event& ev);
};

std :: ostream	&operator<<(std :: ostream &, const Server &);

#endif