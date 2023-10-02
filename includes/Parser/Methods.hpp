/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Methods.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 20:06:13 by rferradi          #+#    #+#             */
/*   Updated: 2023/09/11 18:49:00 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef METHODS_HPP
# define METHODS_HPP
# include "Cgi.hpp"
# include "main.hpp"
# include "Location.hpp"

class Cgi;

enum httpCode
{
	OK = 200,
	REDIRECT = 302,
	BADREQUEST = 400,
	UNAUTHORIZED = 401,
	FORBIDDEN = 403,
	NOTFOUND = 404,
	METHODNOTALLOW = 405,
	INTERNALERROR = 500,
	TOLARGE = 413,
	DIRECTORY = 301,
	BAD_GATEWAY = 502
};

class Methods
{
	protected:
		std::string					&_request;
		map_locate					_locate;
		std::string					_path;
		std::string					_file;
		std::string					_requestType;
		bool						_hasLocation;
		bool						_isFile;
		std::string					_location;
		std::vector<std::string>	_methods;
		std::string					_redirect;
		std::string					_textType;
		std::string					_route;
		int							_code;
		std::string 				_reqType;
		bool						_isCgi;
		std::string 				_siteRoot;
		std::string 				_errorPage;
		std::string 				_queryString;
		std::string 				_fileType;
		Cgi 						*_cgi;

	public:
		static const std::map<std::string, std::string> _mimType;
		Methods(std::string &req, map_locate const loc, Cgi *cgi);
		virtual ~Methods();

		int 					checkRequest();
		virtual std::string		HttPage(int epfd) = 0;
		std::string		CreatePage(int code, std::string page, std::string type);
		std::string 	mimType(std::string content);
		cvstring		getMethods();
		std::string		getFileType ( void );
		std::string		getFile ( void );
		std::string 	getReqType ( void );
		std::string 	getPath ( void );
		std::string 	getLocation ( void );
		std::string		getQueryString ( void );
		map_locate		getLocate ( void );
		int				getCode ( void );
		void 			setIsCgi(const bool&);
		virtual bool	handle() = 0;
		bool			isCgi ( void );
};

#endif