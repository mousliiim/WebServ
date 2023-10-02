/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 23:16:40 by jewancti          #+#    #+#             */
/*   Updated: 2023/09/21 18:58:34 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Parser.hpp"
# include "Server.hpp"
# include "LibHelp.hpp"
# include "FileReader.hpp"

/**
 * Static variables
*/

std :: string	Parser :: _error;

# define PARAMS_SIZE	12
/**
 * Parser's methods
*/

string_it	Parser :: bracket(string_it begin, string_it end, const char c)
{
	string_it it = begin;
	for (; it != end; it++)
	{
		if (*it == '{') {
			if ((it = bracket(it + 1, end, '}')) == end)
				return end;
		}
		else if (*it == '}')
			return *it == c ? it : end;
	}
	return *it == c ? begin : end;
}

std :: string	Parser :: getBlockName(string_it begin, string_it end)
{
	string_it	start;
	for (start = begin; start != end && isspace(*start); start++) ;
	string_it	endblockName = LibHelp :: search(start, end, "{");
	if (endblockName == end || (endblockName != start && (endblockName + 1) != end))
		return "";
	return start == endblockName ? "" : std :: string(start, endblockName - 1);
}

bool	Parser :: checkIndent(std :: string &line, const int indent, const size_t nbline)
{
	int index = 0;
	string_it s_it;
	for (s_it = line.begin(); s_it != line.end() && *s_it == '\t'; s_it++)
		index++;
	if (index != indent || s_it == line.end())
		notifyError("Bad Indentation at line " + LibHelp :: toString(nbline) + ".", NULL);
	if (isspace(*(line.begin() + index)))
		notifyError("Only tabulations are accepted as indentation, at line " + LibHelp :: toString(nbline) + ".", NULL);
	return _error.empty();
}


bool	Parser :: setConfig(std :: string &line, Location &locate)
{
	static const std :: string	params[PARAMS_SIZE] = {
		"server_name", "listen", "root", "index",
		"redirect", "allowed_methods", "route", "error_page", "filepath_post",
		"autoindex", "port", "max_body_size",
	};
	vstring words = LibHelp :: split(line, " \t");
	if (words.empty() || words.size() != 2)
		return false;
	int	index = -1;
	for (int i = 0; i < PARAMS_SIZE; i++) {
		if ((index = words.at(0) == params[i] ? i : -1) != -1)
			break ;
	}
	if (index == -1)
		return false;
	static const t_setters	setters[PARAMS_SIZE] = {
		& Parser :: setServerName,
		& Parser :: setListen,
		& Parser :: setRoot,
		& Parser :: setIndex,
		& Parser :: setRedirect,
		& Parser :: setAllowedMethods,
		& Parser :: setRoute,
		& Parser :: setErrorPage,
		& Parser :: setFilePathPost,
		& Parser :: setAutoIndex,
		& Parser :: setPort,
		& Parser :: setMaxBodySize,
	};
	static const t_getters	getters[PARAMS_SIZE] = {
		& Location :: getServerName,
		& Location :: getListen,
		& Location :: getRoot,
		& Location :: getIndex,
		& Location :: getRedirect,
		& Location :: getAllowedMethodsToString,
		& Location :: getRoute,
		& Location :: getErrorPage,
		& Location :: getFilePathPost,
		& Location :: getAutoIndex,
	};
	static const t_getters_n	getters_n[2] = {
		& Location :: getPort,
		& Location :: getMaxBodySize,
	};
	if (index >= PARAMS_SIZE - 2)
		return ((locate.*getters_n[index - (PARAMS_SIZE - 2)])() == 0 && (*setters[index])(words.at(1), locate));
	return ((locate.*getters[index])().empty() && (*setters[index])(words.at(1), locate));
}

bool	Parser :: parse(const std :: string &filename, HttpServer &httpServ)
{
	vstring	lines = FileReader :: readAllLines(filename);
	if (lines.empty())
		return false;

	std :: string content = LibHelp :: toString(lines);
	if (lines.empty() || bracket(content.begin(), content.end(), 0) == content.end()) {
		notifyError("Bracket not closed", NULL);
		return false;
	}
	
	int				indent(0);
	int				first_server(-1);
	std :: string	blockName("");
	map_locate		locate;
	for (vstring_it it = lines.begin(); it != lines.end(); it++)
	{
		if (it -> empty())
			continue ;
		if (LibHelp :: find(it -> begin(), it -> end(), '}')) {
			indent -= indent != 0;
			if (! checkIndent(*it, indent, (it - lines.begin()) + 1))
				return false;
			continue ;
		}
		if (LibHelp :: find(it -> begin(), it -> end(), '{')) {
			vstring tmp;
			if ((blockName = getBlockName(it -> begin(), it -> end())) == "") {
				notifyError("No spaces/chars accepted after braces", &locate);
				return false;
			}
			tmp = LibHelp :: split(blockName, ' ');
			if (blockName == "server")
				first_server++;
			//if (it != lines.begin())
			//	notifyError("Server block must be at the top of file", &locate);
			if (blockName != "server") {
				if (tmp.size() <= 0 || tmp.size() > 2)
					notifyError("Wrong args at: " + blockName, &locate);
				else if (tmp.at(0) != "location")				
					notifyError("Wrong block name: " + blockName, &locate);
			}

			if (! _error.empty() || ! checkIndent(*it, indent, (it - lines.begin()) + 1))
				return false;
			blockName = blockName == "server" ? "/" : tmp.at(1);
			if (blockName == "/" && first_server >= 1) {
				Server *server = new Server(locate);
				httpServ.addServer(server);
				locate.clear();
			}
			locate[blockName] = new Location();
			indent++;
			continue ;
		}
		if (! checkIndent(*it, indent, (it - lines.begin()) + 1))
			return false;
		if (! setConfig(*it, *locate[blockName])) {
			notifyError("Wrong parameters", &locate);
			return false;
		}
	}
	if (! locate.empty()) {
		Server *server = new Server(locate);
		httpServ.addServer(server);
	}
	return true;
}


void	Parser::notifyError(const std :: string& error, map_locate *locate)
{
	Parser :: _error = error;
	if (locate != NULL)
		for (map_locate_it it = locate->begin(); it != locate->end(); it++)
			delete it -> second;
}