/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Get.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:58:06 by rferradi          #+#    #+#             */
/*   Updated: 2023/09/21 21:49:29 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Get.hpp"
# include "Cgi.hpp"
# include "FileReader.hpp"
# include "Page.hpp"

/*--------------------------------------------------CONSTRUCTOR/DESTRUCTOR--------------------------------------------------*/

Get::Get(std::string &req, map_locate const loc, Cgi *_cgi): Methods(req, loc, _cgi){}

Get::~Get(){}

/*--------------------------------------------------CONSTRUCTOR/DESTRUCTOR--------------------------------------------------*/

/*--------------------------------------------------MEMBER FUNCTION--------------------------------------------------*/

std::string	Get::HttPage(int epfd)
{
	int code = checkRequest();
	std::string html;

	if (_isCgi && code == OK)
	{
		struct epoll_event ev;
		_cgi->setupCgi(this);
		_cgi->createPage();
		ev.events = EPOLLIN;
		ev.data.ptr = _cgi;
		epoll_ctl(epfd, EPOLL_CTL_ADD, _cgi->getOutPipe(), &ev);
		_request.clear();
		return "";
	}
	else if (code == OK || code == DIRECTORY)
	{
		if (code == DIRECTORY)
		{
			_textType = "html";
			return CreatePage(OK, Page::autoIndex(_file), "OK");
		}
		html = FileReader::readHTMLFile(_file);
		if (html != "")
			return CreatePage(OK, html, "OK");
	}
	else if (code == REDIRECT)
	{
		html = "HTTP/1.1 302 Moved Permanently\r\n" \
							"Location: " + _redirect + \
							"\r\n\r\n";
		return html;
	}
	else if (code == FORBIDDEN)
		return Page::errorPage(403, "Forbidden");
	else if (code == NOTFOUND)
	{
		_textType = "html";
		if ((html = FileReader::readHTMLFile(_errorPage)) == "" || _errorPage == "")			
			return Page::errorPage(404, "Not Found");
		return CreatePage(NOTFOUND, html, "Not Found");
	}
	else if (code == METHODNOTALLOW)
		return Page::errorPage(405, "Method Not Allowed");
	else if (code == UNAUTHORIZED)
		return Page::errorPage(401, "Unauthorized");
	return Page::errorPage(500, "Internal Server Error");
}

/*--------------------------------------------------MEMBER FUNCTION--------------------------------------------------*/
