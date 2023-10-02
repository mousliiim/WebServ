/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LibHelp.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:42:41 by jewancti          #+#    #+#             */
/*   Updated: 2023/09/20 20:21:07 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "LibHelp.hpp"

/*--------------------------------------------------MEMBER FUNCTION--------------------------------------------------*/

int	LibHelp :: toInt(string_it begin, string_it end)
{
	return LibHelp :: toInt(std :: string(begin, end));
}

int	LibHelp :: toInt(cstring_it begin, cstring_it end)
{
	return LibHelp :: toInt(std :: string(begin, end));
}

int	LibHelp :: toInt(const std :: string &format)
{
	std :: istringstream	is(format);
	int	val = 0;

	is >> val;
	return val;
}

std :: string	LibHelp :: toString(const vstring &vect, const std :: string &delim)
{
	std :: string	content;
	for (cvstring_it it = vect.begin(); it != vect.end(); it++) {
		content += *it + (it + 1 != vect.end() ? delim : "");
	}
	return content;
}

std :: string	LibHelp :: toString(const int &number)
{
	std :: stringstream	ss;
	ss << number;
	return ss.str();
}

vstring	LibHelp :: toVString(const std :: string &str, const char &c)
{
	return LibHelp :: split(str, std :: string(1, c));
}

std :: string	LibHelp :: ltrim(const std :: string &str)
{
	cstring_it	it = LibHelp :: search(str.begin(), str.end(), " \t\v\n\r\f");
	return it == str.end() ? str : std :: string(it, str.end());
}

string_it	LibHelp :: search(string_it begin, string_it end, const std :: string &sep)
{
	string_it   it;
	for (it = begin; it != end; it++)
	{
		for (cstring_it b = sep.begin(); b != sep.end(); b++) {
			if (*b == *it)
				return it;
		}
	}
	return end;
}

cstring_it	LibHelp :: search(cstring_it begin, cstring_it end, const std :: string &sep)
{
	cstring_it   it;
	for (it = begin; it != end; it++)
	{
		for (cstring_it b = sep.begin(); b != sep.end(); b++) {
			if (*b == *it)
				return it;
		}
	}
	return end;
}

cstring_it	LibHelp :: search(cstring_it begin, cstring_it end, const char &c)
{
	cstring_it it;
    for (it = begin; it != end; it++) {
		if (c == *it)
			return it;	
	}
    return end;
}

bool	LibHelp :: find(cstring_it begin, cstring_it end, const char &c)
{
    return LibHelp :: search(begin, end, c) != end;
}

bool	LibHelp :: find(cstring_it begin, cstring_it end, const std :: string str)
{
    return LibHelp :: search(begin, end, str) != end;
}

vstring	LibHelp :: split(const std :: string &str, const std :: string &sep)
{
	vstring	list;
	
	cstring_it	it = LibHelp :: search(str.begin(), str.end(), sep);
	cstring_it	begin = str.begin();

	while (it != str.end())
	{
		const std :: string word(begin, it);
		if (! word.empty())
			list.push_back(word);
		begin = it + 1;
		it = LibHelp :: search(it + 1, str.end(), sep);
	}
	const std :: string word(begin, it);
	if (! word.empty())
		list.push_back(word);
	return list;
}

vstring	LibHelp :: split(const std :: string& str, const char &c)
{
	return LibHelp :: split(str, std :: string(1, c));
}

bool	LibHelp :: all_of(cstring_it begin, cstring_it end, bool (predicat)(int))
{
	for (cstring_it it = begin; it != end; it++) {
		if (! predicat(*it))
			return false;
	}
	return true;
}

bool	LibHelp :: all_of(cstring_it begin, cstring_it end, int (predicat)(int))
{
	for (cstring_it it = begin; it != end; it++) {
		if (! predicat(*it))
			return false;
	}
	return true;
}

bool	LibHelp :: setNonBlocking(int sockfd)
{
    int flags = fcntl(sockfd, F_GETFL, 0);
    if (flags == -1) 
		return false;
    return fcntl(sockfd, F_SETFL, flags | O_NONBLOCK) != -1;
}

bool LibHelp::fileExists(const std::string& filename)
{
    return (access(filename.c_str(), F_OK) != -1);
}

std::map<std::string, std::string>	LibHelp::setMimType()
{
	std::ifstream mimtxt("mimtype.txt");
	std::map<std::string, std::string> res;
	std::string key, value;

	while (mimtxt)
	{
		mimtxt >> key;
		mimtxt >> value;
		res[key] = value;
		/* code */
	}
	return res;	
}

bool LibHelp::isDirectory(std::string path)
{
	DIR* dir = opendir(path.c_str());

	if (dir)
	{
		closedir(dir);
		return true;
	}
	closedir(dir);
	return false;
}

/*--------------------------------------------------MEMBER FUNCTION--------------------------------------------------*/
