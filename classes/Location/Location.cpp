/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 00:30:21 by jewancti          #+#    #+#             */
/*   Updated: 2023/09/20 15:46:10 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Location.hpp"
# include "LibHelp.hpp"

Location :: Location() :	_serverName(""), _listen(""), _root(""),
							_index(""), _redirect(""), _errorPage(""), _filePathPost(""), _autoIndex(""),
							 _allowedMethods(vstring()), _port(0), _max_body_size(0)
{
	
}

Location :: Location(const Location &lct)
{
	this -> operator=(lct);
}

Location	&Location :: operator=(const Location &rhs)
{
	if (this == &rhs)
		return *this;
	_serverName = rhs._serverName;
	_listen = rhs._listen;
	_root = rhs._root;
	_index = rhs._index;
	_redirect = rhs._redirect;
	_errorPage = rhs._errorPage;
	_filePathPost = rhs._filePathPost;
	_allowedMethods = rhs._allowedMethods;
	_port = rhs._port;
	_max_body_size = rhs._max_body_size;
	return *this;
}

Location :: ~Location()
{
	
}

/**
 * Setters
*/
void	Location :: setServerName(const std :: string &serverName)
{
	_serverName = serverName;
}

void	Location :: setListen(const std :: string &listen)
{
	_listen = listen;
}

void	Location :: setRoot(const std :: string &root)
{
	_root = root;
}

void	Location :: setIndex(const std :: string &index)
{
	_index = index;
}

void	Location :: setRedirect(const std :: string &redirect)
{
	_redirect = redirect;
}

void	Location :: setAllowedMethods(cvstring &methods)
{
	_allowedMethods = methods;
}

void	Location :: setAllowedMethods(cvstring_it &begin, cvstring_it &end)
{
	_allowedMethods = cvstring(begin, end);
}

void	Location :: setRoute(const std :: string &route)
{
	_route = route;
}

void	Location :: setErrorPage(const std :: string &errorPage)
{
	_errorPage = errorPage;
}

void	Location :: setFilePathPost(const std :: string &path)
{
	_filePathPost = path;
}

void	Location :: setAutoIndex(const std :: string &active)
{
	_autoIndex = active;
}

void	Location :: setAutoIndex(bool active)
{
	_autoIndex = active ? "on": "off";
}

void	Location :: setPort(const size_t &port)
{
	_port = port;
}

void	Location :: setMaxBodySize(const size_t &max_body_size)
{
	_max_body_size = max_body_size;
}

/**
 * Getters
*/

const std :: string	Location :: getServerName() const
{
	return _serverName;
}

const std :: string	Location :: getListen() const
{
	return _listen;
}

const std :: string	Location :: getRoot() const
{
	return _root;
}

const std :: string	Location :: getIndex() const
{
	return _index;
}

const std :: string	Location :: getRedirect() const
{
	return _redirect;
}

const std :: string	Location :: getAllowedMethodsToString() const
{
	return LibHelp :: toString(_allowedMethods);
}

const std :: string	Location :: getRoute() const
{
	return _route;
}

const std :: string	Location :: getErrorPage() const
{
	return _errorPage;
}

const std :: string	Location :: getFilePathPost() const
{
	return _filePathPost;
}

const std :: string	Location :: getAutoIndex() const
{
	return _autoIndex;
}

bool				Location :: getAutoIndexBool() const
{
	return _autoIndex == "on";
}

cvstring	&Location :: getAllowedMethods() const
{
	return _allowedMethods;
}

const size_t	&Location :: getPort() const
{
	return _port;
}

const size_t	&Location :: getMaxBodySize() const
{
	return _max_body_size;
}