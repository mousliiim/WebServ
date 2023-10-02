/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 23:15:38 by jewancti          #+#    #+#             */
/*   Updated: 2023/09/21 14:30:19 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# ifndef __PARSER_HPP__
# define __PARSER_HPP__
# include "HttpServer.hpp"

class Location;
class HttpServer;
class	Parser
{
	private:
		typedef bool	(*t_setters)(const std :: string &, Location &);
		typedef const std :: string	(Location :: *t_getters)() const;
		typedef const size_t	&(Location :: *t_getters_n)() const;

		static std :: string	_error;

		static bool				setServerName(const std :: string &serverName, Location &server);
		static bool				setListen(const std :: string &listen, Location &locate);
		static bool				setRoot(const std :: string &root, Location &locate);
		static bool				setIndex(const std :: string &index, Location &locate);
		static bool				setRedirect(const std :: string &redirect, Location &locate);
		static bool				setAllowedMethods(const std :: string &methods, Location &locate);
		static bool				setRoute(const std :: string &route, Location &locate);
		static bool				setErrorPage(const std :: string &errorPage, Location &locate);
		static bool				setFilePathPost(const std :: string &path, Location &locate);
		static bool				setAutoIndex(const std :: string &active, Location &locate);
		static bool				setPort(const std :: string &port, Location &locate);
		static bool				setMaxBodySize(const std :: string &max_body_size, Location &locate);

		static void				notifyError(const std :: string& error, map_locate *locate);
		static std :: string	getBlockName(string_it begin, string_it end);
		static string_it		bracket(string_it begin, string_it end, const char c);
		static bool				checkIndent(std :: string& line, const int indent, const size_t nbline);
		static bool				setConfig(std :: string &line, Location &locate);
	public:
		static bool				parse(const std :: string& filename, HttpServer &httpServ);
		inline static	std :: string	getError() { return Parser :: _error; }
};

#endif