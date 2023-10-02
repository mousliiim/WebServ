/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 23:26:38 by rferradi          #+#    #+#             */
/*   Updated: 2023/09/19 23:16:43 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CLIENT_HPP
# define CLIENT_HPP

# include "Stream.hpp"
# include "Cgi.hpp"
# include "Methods.hpp"

class Server;
class Methods;
class Cgi;

enum e_type
{
	GET,
	POST,
	DELETE
};

class Client: public Stream
{
	private:
		std::string 	_request;
		std::string 	_requestType;
		std::ofstream 	_outfile;
		std::string		_getFile;
		static char		_buff[BUF_SIZE];
		static char		_error[9];
		int				_reqType;
		Methods			*_method;
		std::string 	_response;
		Cgi 			*_cgi;

	public:
		Client(int fd, Server *ptr);
		Client(int fd, Server *ptr, int epfd);
		~Client();

		virtual int		handleRequest(int epfd, epoll_event& ev);
		bool			didIreadAll();
		int				readingHttpRequest(epoll_event&);
		void			setMethods(Methods *);
};
#endif