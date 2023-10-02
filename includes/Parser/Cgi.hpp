/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 23:21:46 by mmourdal          #+#    #+#             */
/*   Updated: 2023/09/28 18:00:19 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CGI_HPP
# define CGI_HPP

# include "Stream.hpp"
# include "Methods.hpp"
# include "Client.hpp"

# define TIMEOUT 4

# define INTERNAL_SERVER_ERROR_HTML() "<html><head><title>500 Internal Server Error</title></head><body><center><h1>500 Internal Server Error</h1></center></body></html>"
# define BAD_GATEWAY_HTML() "<html><head><title>502 Bad Gateway</title></head><body><center><h1>502 Bad Gateway</h1></center></body></html>"

class Client;

class Cgi : public Stream
{
	public:
		Cgi ( int fd, Client * );
		Cgi ( Methods *req );
		Cgi ( Cgi const & src );
		Cgi &operator= ( Cgi const & rhs );
		~Cgi ( void );
		
		void			setupCgi ( Methods *req, std::string body );
		void 			setupCgi ( Methods * );
		void 			setCgiEnv ( void );
		char **			mapToDoubleArrayEnv ( void );
		std::string		executeCgi ( void );
		std::string 	createPage ( void );
		std::string 	setCookies(void);

		void			checkHeaderCGI ( std::string &body );
		bool 			ErrorStatusInBody ( std::string body );
		void 			checkContentType ( std::string &body );
		
		void			clearCgi(void);
		void 			DisplayEnv ( void );
		
		int 			resetCgi(const int&);
		virtual int		handleRequest(int epfd, epoll_event& ev);
		const int& 		getOutPipe(void);


	private:
		Methods *							_req;
		Client 								*_client;
		pid_t								_pid;
		
		char **								_envp;

		std::string 						_method;
		std::string 						_response;
		std::string 						_body;
		std::string 						_typeCgi;
		std::string 						_binPathExec;
		std::string 						_scriptName;
		std::string 						_pathFile;
		std::string							_contentType;
		std::string							_queryString;
		
		int									_out_pipe[2];
		int 								_in_pipe[2];
		size_t 								_code;

		struct timeval						_begin;
		struct timeval						_end;
		static std::string					_cookies;
		
		std::map <std::string, std::string> _env;
};

#endif