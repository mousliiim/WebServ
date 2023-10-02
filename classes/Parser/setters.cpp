/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 02:14:37 by jewancti          #+#    #+#             */
/*   Updated: 2023/09/20 15:45:50 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Parser.hpp"
# include "LibHelp.hpp"

bool	Parser :: setServerName(const std :: string &serverName, Location &locate)
{
	locate.setServerName(serverName);
	return true;
}

bool	Parser :: setListen(const std :: string &listen, Location &locate)
{
	cstring_it	it;
	cstring_it	tmp;
	for (it = listen.begin(); it != listen.end(); it++)
	{
		tmp = LibHelp :: search(it, listen.end(), '.');
		if (tmp == listen.end()) {
			tmp = LibHelp :: search(it, listen.end(), ':');
			break ;
		}
		if (tmp - it <= 0 || tmp - it > 3 ||
            ! LibHelp :: all_of(it, tmp, isdigit) ||
            LibHelp :: toInt(it, tmp) > 255)
			return false;
		it = tmp;
	}
    if (tmp - it <= 0 || tmp - it > 3 ||
        ! LibHelp :: all_of(it, tmp, isdigit) ||
        LibHelp :: toInt(it, tmp) > 255)
		return false;
	if (tmp == listen.end() || *tmp != ':') {
		if (listen.end() - it <= 0 || listen.end() - it > 3)
			return false;
		locate.setListen(listen);
		return true;
	}
	locate.setListen(std :: string(listen.begin(), tmp));
	return setPort(std :: string(tmp + 1, listen.end()), locate);
}

bool	Parser :: setRoot(const std :: string &root, Location &locate)
{
	DIR* directory = opendir(root.c_str());
	if (directory == NULL) {
		std :: cerr << "Bad root" << std::endl;
		return false;
	}
	locate.setRoot(root);
	closedir(directory);
	return true;
}

bool	Parser :: setIndex(const std :: string &index, Location &locate)
{
	locate.setIndex(index);
	return true;
}

bool	Parser :: setRedirect(const std :: string &redirect, Location &locate)
{
	locate.setRedirect(redirect);
	return true;
}

bool	Parser :: setAllowedMethods(const std :: string &methods, Location &locate)
{
	static const std :: string	allowed[4] = { "GET", "POST", "PUT", "DELETE" };
	int							indexs[4] = { 0 };
	vstring						fields = LibHelp :: toVString(methods, '|');

	if (fields.size() > 4)
		return false;
	for (vstring_it v_it = fields.begin(); v_it != fields.end(); v_it++) {
		int	status = -1;
		for (int i = 0; i < 4; i++) {
			if ((status = *v_it == allowed[i] ? i : -1) != -1)
				break ;
		}
		if (status < 0 || ++indexs[status] > 1)
			return false;
	}
	locate.setAllowedMethods(fields);
	return true;
}

bool	Parser :: setPort(const std :: string &port, Location &locate)
{
    const int   port_ = LibHelp :: toInt(port);
	if (port_ <= 0 || port_ > 10000)
		return false;
	locate.setPort(port_);
	return true;
}

bool	Parser :: setMaxBodySize(const std :: string &max_body_size, Location &locate)
{
	const size_t   body_size = LibHelp :: toInt(max_body_size);
	if (body_size <= 0 || body_size > 10000)
		return false;
	locate.setMaxBodySize(body_size);
	return true;
}

bool	Parser :: setRoute(const std :: string &index, Location &locate)
{
	locate.setRoute(index);
	return true;
}

bool	Parser :: setErrorPage(const std :: string &errorPage, Location &locate)
{
	if (LibHelp :: fileExists(locate.getRoot() + errorPage))
		locate.setErrorPage(errorPage);
	else
		locate.setErrorPage("");
	return true;
}

bool	Parser :: setFilePathPost(const std :: string &path, Location &locate)
{
	locate.setFilePathPost(path);
	return true;
}

bool	Parser :: setAutoIndex(const std :: string &active, Location &locate)
{
	if (active != "on" && active != "off")
		return false;
	locate.setAutoIndex(active);
	return true;
}