/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Post.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 21:13:52 by rferradi          #+#    #+#             */
/*   Updated: 2023/09/28 18:37:38 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Post.hpp"
# include "Cgi.hpp"
# include "LibHelp.hpp"
# include "Page.hpp"

# define NPOS std::string::npos

/*--------------------------------------------------CONSTRUCTOR--------------------------------------------------*/

Post::Post(std::string &req, map_locate const loc, Cgi *_cgi): Methods(req, loc, _cgi)
{
	_headerReaded = false;
	parseHeader();
}

Post::~Post()
{
	_fileStream.close();
}

/*--------------------------------------------------CONSTRUCTOR--------------------------------------------------*/

/*--------------------------------------------------MEMBER FUNCTION--------------------------------------------------*/

void Post::parseHeader()
{
	size_t pos = _request.find("Content-Type:");
	if (pos == std::string::npos)
		return;
	_headerReaded = true;
	size_t pointvirgule = _request.find(";", pos);
	size_t eol = _request.find("\r\n", pos);
	size_t endType = eol < pointvirgule ? eol : pointvirgule;
	pos += 14;
	_postPath = _locate[_location]->getFilePathPost();
		if (_postPath == "" || !LibHelp::isDirectory(_postPath))
		_postPath = _siteRoot;
	_contentType = _request.substr(pos, (endType - pos));
	size_t boundaryDash = _request.find("boundary=", pointvirgule);
	if (boundaryDash != std::string::npos && (boundaryDash += 9))
		_boundary = _request.substr(boundaryDash, (eol - boundaryDash));
	else
		std::string mimtype = mimType(_contentType);
	size_t poslen = _request.find("Content-Length");
	_head = _request.find("\r\n\r\n", poslen);
	if (_head == NPOS)
		{_headerReaded = false; return;}
	std::string contlen = _request.substr(poslen + 16, _head - (poslen + 16));
	std::stringstream ss(contlen);
	ss >> _contentLen;
	if (_boundary != "")
		_head = _request.find(_boundary, eol) + _boundary.size() + 6;
	_body = _head + 4;
	_inbody = false;
	_boundary = "\r\n--" + _boundary;
}

bool Post::handle()
{
	if (!_headerReaded) parseHeader();
	if (_headerReaded != true)
		return 0;
	if (_code != OK)
		return 1;
	size_t max = _locate[_location]->getMaxBodySize();
	if (_contentLen > max && max != 0)
	{
		_code = TOLARGE;
		return 1;
	}
	return parseBody();
}

size_t 	Post::findNextBound()
{
	if (_boundary == "")
		return (_request.size());
	_nextBoundary = _request.find(_boundary, _head);
	if (_nextBoundary != NPOS)
		_nextBoundary += _boundary.size() + 2;
	else
		_nextBoundary = _request.size();
	return (_nextBoundary);
}

size_t 	Post::findNextBoundBegin()
{
	_nextBoundary = _request.find(_boundary, _head);
	if (_nextBoundary == NPOS)
		_nextBoundary = _request.size();
	return (_nextBoundary);
}

int Post::multipartData()
{
	static int a = 0;
	a++;
	if (_head == _request.find(_boundary + "--") + _boundary.size() + 2)
		return (1);
	size_t eol = _request.find("\r\n", _head);
	size_t filename = _request.find("; filename=\"", _head);
	if (eol == NPOS)
		return (0);
	if (filename != NPOS && filename < eol)
	{
		filename += 12;
		_filename = _postPath + _request.substr(filename, (eol - filename) - 1);
		if (!_fileStream.is_open())
			_fileStream.open(_filename.c_str(), std::ios::binary);
	}
	else if (_filename == "")
	{
		_head = findNextBound();
		return -1;
	}
	if (!_inbody)
	{
		size_t bodypos = _request.find("\r\n\r\n", _head);
		if (bodypos != NPOS)
		{
			_head = bodypos + 4;
			_inbody = true;
		}
		else
			return (0);
	}
	if (_inbody)
		writeFileMulti();
	
	return false;
}

std::string Post::makeFilename(std::string file)
{
	std::string filename;
	int 		number = 2;

	std::string	extension = mimType(_contentType);
	filename = file + "(1)";
	while (LibHelp::fileExists(_postPath + filename + extension))
	{
		filename = file + "(" + LibHelp::toString(number) + ")";
		number++;
	}
	return (_postPath + filename + extension);
}

std::string Post::generateRandomFileName()
{
	std::string filename = "file";
	std::string extension = mimType(_contentType);
	if (LibHelp::fileExists(_postPath + filename + extension))
		return makeFilename(filename);
	return (_postPath + filename + extension);
}

int Post::binaryData()
{
	if (_isFile && !_open && LibHelp::fileExists(_file))
		_filename = makeFilename(_file);
	else if (!_isFile && !_open)
		_filename = generateRandomFileName();
	else
		_filename =  _postPath + _path.substr(1);
	if (!_open)
	{
		_fileStream.open(_filename.c_str(), std::ios::binary);
		_open = _fileStream.is_open();
		if (!_open)
		{
			_code = INTERNALERROR;
			return (1);
		}
	}
	if (writeFile())
		return (1);
	return 0;
}

bool	Post::writeFile()
{
	_nextBoundary = findNextBound();
	std::string toWrite = _request.substr(_head, _nextBoundary);
	_fileStream.write(toWrite.c_str(), toWrite.size());
	if ( (_fileStream.rdstate() & std::ifstream::failbit ) != 0 )
		std::cerr << "Error opening 'test.txt'\n";
	if (_request.size() - _body == _contentLen)
	{
		_fileStream.close();
		_filename.clear();
		_head = _nextBoundary;
		_inbody = false;
		return (true);
	}
	_head = _nextBoundary;
	return (false);
}

bool Post::parseBody()
{
	if (_contentType == "multipart/form-data")
	{
		if (_boundary != "" && _request.find(_boundary + "--\r\n") == NPOS)
			return (false);
		while (1)
			if (multipartData() > 0)
				return (true);
	}
	else if(_isCgi)
		return true;
	else
	{
		if (_request.size() - _body != _contentLen)
			return (false);
		_open = false;
		_head = _body;
		_boundary = "";
		while (1)
			if (binaryData() > 0)
				return (true);
	}
	return (false);
}

bool Post::writeFileMulti()
{
	if (!_fileStream.is_open())
		return (false);
	findNextBoundBegin();
	std::string toWrite = _request.substr(_head, _nextBoundary - _head);
	_fileStream.write(toWrite.c_str(), toWrite.size());
	if ( (_fileStream.rdstate() & std::ifstream::failbit ) != 0 )
		std::cerr << "Error opening 'test.txt'\n";
	if (_nextBoundary != _request.size())
	{
		_fileStream.close();
		_filename.clear();
		_head = findNextBound();
		_inbody = false;
	}
	return (false);
}

std::string Post::getBody()
{
	return (_request.substr(_body, _contentLen));
}

std::string	Post::HttPage(int epfd)
{
	std::string html;
	if (_isCgi && _code == OK)
	{
		struct epoll_event ev;

		_cgi->setupCgi(this, this->getBody());
		_cgi->createPage();
		ev.events = EPOLLIN;
		ev.data.ptr = _cgi;
		epoll_ctl(epfd, EPOLL_CTL_ADD, _cgi->getOutPipe(), &ev);
		_request.clear();
	}
	if (_code == OK)
		return ("HTTP/1.1 201 Created\r\nContent-Length: 0\r\n\r\n");
	else if (_code == REDIRECT)
	{
		html = "HTTP/1.1 302 Moved Permanently\r\n" \
							"Location: " + _redirect + \
							"\r\n\r\n";
		return html;
	}
	else if (_code == TOLARGE)
		return Page::errorPage(413, "Content Too Large");
	else if (_code == METHODNOTALLOW)
		return Page::errorPage(405, "Method Not Allowed");
	else if (_code == UNAUTHORIZED)
		return Page::errorPage(401, "Unauthorized");
	else if (_code == FORBIDDEN)
		return Page::errorPage(403, "Forbidden");
	return Page::errorPage(BADREQUEST, "Bad Request");
}

/*--------------------------------------------------MEMBER FUNCTION--------------------------------------------------*/
