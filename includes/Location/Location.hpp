/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 00:30:35 by jewancti          #+#    #+#             */
/*   Updated: 2023/09/19 23:17:33 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef		__LOCATION_HPP__
# define	__LOCATION_HPP__
# include "main.hpp"

class	Location
{
	private:
		std :: string	_serverName;
		std :: string	_listen;
		std :: string	_root;
		std :: string	_index;
		std :: string	_redirect;
		std :: string	_route;
		std :: string	_errorPage;
		std :: string	_filePathPost;
		std :: string	_autoIndex;

		vstring			_allowedMethods;

		size_t			_port;
		size_t			_max_body_size;
	public:
		Location();
		Location(const Location &lct);
		Location &operator=(const Location &rhs);
		~Location();


		void	setServerName(const std :: string &serverName);
		void	setListen(const std :: string &listen);
		void	setRoot(const std :: string &root);
		void	setIndex(const std :: string &index);
		void	setRedirect(const std :: string &redirect);
		void	setAllowedMethods(cvstring &methods);
		void	setAllowedMethods(cvstring_it &begin, cvstring_it &end);
		void	setRoute(const std :: string &route);
		void	setErrorPage(const std :: string &errorPage);
		void	setFilePathPost(const std :: string &path);
		void	setAutoIndex(const std :: string &active);
		void	setAutoIndex(bool active);
		void	setPort(const size_t &port);
		void	setMaxBodySize(const size_t &max_body_size);

		const std :: string	getServerName() const;
		const std :: string	getListen() const;
		const std :: string	getRoot() const;
		const std :: string	getIndex() const;
		const std :: string	getRedirect() const;
		const std :: string	getAllowedMethodsToString() const;
		const std :: string	getRoute() const;
		const std :: string	getErrorPage() const;
		const std :: string	getFilePathPost() const;
		const std :: string	getAutoIndex() const;
		bool				getAutoIndexBool() const;
		cvstring			&getAllowedMethods() const;
		const size_t		&getPort() const;
		const size_t		&getMaxBodySize() const;
};

typedef std :: pair<std :: string, Location *>				p_locate;
typedef std :: map<std :: string, Location *>				map_locate;
typedef std :: map<std :: string, Location *> :: iterator	map_locate_it;

#endif