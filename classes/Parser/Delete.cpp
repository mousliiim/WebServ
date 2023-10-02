/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Delete.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 19:10:27 by rferradi          #+#    #+#             */
/*   Updated: 2023/09/20 15:45:59 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Delete.hpp"
# include "Cgi.hpp"
# include "Page.hpp"

/*--------------------------------------------------CONSTRUCTOR/DESTRUCTOR--------------------------------------------------*/

Delete::Delete(std::string &req, map_locate const loc, Cgi *_cgi): Methods(req, loc, _cgi)
{
	_fileDel = _locate[_location]->getFilePathPost() + _path.substr(1);
}

Delete::~Delete(){}

/*--------------------------------------------------CONSTRUCTOR/DESTRUCTOR--------------------------------------------------*/

/*--------------------------------------------------MEMBER FUNCTION--------------------------------------------------*/

bool	Delete::handle()
{
	if (_code == METHODNOTALLOW)
		return (false);
	if (access(_fileDel.c_str(), F_OK) == -1 || access(_fileDel.c_str(), W_OK) == -1)
	{
		_code = NOTFOUND;
		return (false);
	}
	else
		_code = OK;
	if (std::remove ("var/downloads/style.css") != 0)
	{
        perror("DELETE -> remove error");
		_code = NOTFOUND;
		return (false);
	}
	return (true);
}

std::string		Delete::HttPage(int /*epfd*/)
{
	if (_code == OK)
		return ("HTTP/1.1 204 No Content\r\n\r\n");
	else if (_code == NOTFOUND)
		return (Page::errorPage(NOTFOUND, "Not Found"));
	else if (_code == METHODNOTALLOW)
		return (Page::errorPage(METHODNOTALLOW, "Method Not Allowed"));
	else if (_code == FORBIDDEN)
		return (Page::errorPage(FORBIDDEN, "Forbidden"));
	else if (_code == UNAUTHORIZED)
		return (Page::errorPage(UNAUTHORIZED, "Unauthorized"));
	return (Page::errorPage(500, "Internal Server Error"));
}

/*--------------------------------------------------MEMBER FUNCTION--------------------------------------------------*/
