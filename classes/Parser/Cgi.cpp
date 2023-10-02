/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 23:20:51 by mmourdal          #+#    #+#             */
/*   Updated: 2023/09/28 17:59:13 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Cgi.hpp"
# include "LibHelp.hpp"
# include "Page.hpp"
# include <sys/time.h>

std::string Cgi::_cookies = "";

Cgi::Cgi(int fd, Client *ptr):Stream(fd),_envp(NULL)
{
	_in_pipe[0] = -1;
	_in_pipe[1] = -1;
	_out_pipe[0] = -1;
	_out_pipe[1] = -1;
	_client = ptr;
}

Cgi::Cgi ( Cgi const & src ):Stream(src)
{
	_envp = NULL;
	*this = src;
}

Cgi &Cgi::operator=( Cgi const & rhs )
{
	if (this != &rhs)
	{
		this->_env = rhs._env;
		this->_code = rhs._code;
		this->_method = rhs._method;
		this->_body = rhs._body;
		this->_typeCgi = rhs._typeCgi;
		this->_scriptName = rhs._scriptName;
		this->_pathFile = rhs._pathFile;
		this->_contentType = rhs._contentType;
		this->_req = rhs._req;
	}
	return *this;
}

Cgi::~Cgi ( void )
{
	if (_envp)
	{
		for (size_t i = 0; _envp[i] != NULL; i++)
			free(_envp[i]);
		delete[] _envp;
	}
	
	if (_out_pipe[0] > 0)
		close(_out_pipe[0]);
}

void Cgi::setupCgi ( Methods *req )
{
	_method = "GET";
	_pathFile = req->getFile();
	_typeCgi = req->getFileType();
	_queryString = req->getQueryString();
	if (req->getFileType() == "php")
		_binPathExec = "/usr/bin/php-cgi";
	else if (req->getFileType() == "py")
		_binPathExec = "/usr/bin/python3";
	else
		_binPathExec = "usr/bin/" + req->getFileType();
	_req = req;
	_scriptName = req->getPath();
	this->setCgiEnv();
	_envp = mapToDoubleArrayEnv();
}

void Cgi::setupCgi ( Methods *req, std::string body )
{
	_method = "POST";
	_pathFile = req->getFile();
	_contentType = "application/x-www-form-urlencoded";
	_typeCgi = req->getFileType();
	if (_typeCgi == "php")
		_binPathExec = "/usr/bin/php-cgi";
	else if (_typeCgi == "py")
		_binPathExec = "/usr/bin/python3";
	else
		_binPathExec = "usr/bin/" + _typeCgi;
	_req = req;
	_body = body;
	_scriptName = req->getPath();
	this->setCgiEnv();
	_envp = mapToDoubleArrayEnv();
}

const int& Cgi::getOutPipe(void)
{
	return _out_pipe[0];
}

void Cgi::DisplayEnv ( void )
{
	for (std::map<std::string, std::string>::iterator it = this->_env.begin(); it != this->_env.end(); it++)
		std::cerr << it->first << " : " << it->second << std::endl;
}

void Cgi::setCgiEnv ( void )
{
	if (!_env.empty())
		_env.clear();

	this->_env["GATEWAY_INTERFACE"] = "CGI/1.1";
	this->_env["SERVER_PROTOCOL"] = "HTTP/1.1";
	this->_env["REDIRECT_STATUS"] = "200";
	this->_env["HTTP_HOST"] = _req->getLocate()[_req->getLocation()]->getServerName();
	this->_env["REQUEST_METHOD"] = _method;
	this->_env["SCRIPT_FILENAME"] = _pathFile;
	this->_env["SERVER_SOFTWARE"] = "WebServ/1.0";
	this->_env["SERVER_PORT"] = LibHelp::toString(_req->getLocate()[_req->getLocation()]->getPort());
	this->_env["SERVER_NAME"] = _req->getLocate()[_req->getLocation()]->getServerName();
	this->_env["PATH_INFO"] = _req->getPath();
	this->_env["PATH_TRANSLATED"] = _req->getPath();
	this->_env["REQUEST_URI"] = _req->getPath() + "?" + _req->getQueryString();
	this->_env["SCRIPT_NAME"] =  _scriptName;
	if (_cookies != "")
		this->_env["HTTP_COOKIE"] = _cookies;
	if (_method == "GET")
		this->_env["QUERY_STRING"] = _queryString;
	if (_method == "POST")
	{
		this->_env["CONTENT_TYPE"] = _contentType;
		this->_env["CONTENT_LENGTH"] = LibHelp::toString(_body.length());
	}
}

char **Cgi::mapToDoubleArrayEnv ( void )
{
	char **env = new char*[this->_env.size() + 1];
	int i = 0;
	for (std::map<std::string, std::string>::iterator it = this->_env.begin(); it != this->_env.end(); it++)
	{
		std::string tmp = it->first + "=" + it->second;
		env[i] = strdup(tmp.c_str());
		i++;
	}
	env[i] = NULL;
	return (env);
}

std::string Cgi::createPage ( void )
{
	std::string response;

	std::string cgi = this->executeCgi();
	
	return ("");
}

bool Cgi::ErrorStatusInBody ( std::string body )
{
	if (body.find("Status: 500 Internal Server Error") != std::string::npos && body.find("Status: ") < body.find("\r\n"))
		return (true);
	return (false);
}

void Cgi::checkContentType ( std::string &body )
{
		std::string contenttype = body.substr(body.find("Content-type:"), body.find("\r\n", body.find("Content-type:")) - body.find("Content-type:"));
		std::istringstream ss(contenttype);
		std::string checktype;
		std::getline(ss, checktype, ' ');
		std::getline(ss, checktype, ' ');
		if (_req->mimType(checktype).empty())
			contenttype = "Content-type: text/html";
		std::string tmp = body.substr(body.find("Content-type:"), body.find("\r\n", body.find("Content-type:")) - body.find("Content-type:"));
		body.erase(body.find(tmp), tmp.length());
		body = contenttype + "\r\n\r\n" + body;
}


void Cgi::checkHeaderCGI ( std::string &body )
{
	if (ErrorStatusInBody(body) == true)
	{
		_code = INTERNALERROR;
		body = INTERNAL_SERVER_ERROR_HTML();
	}
	if (body.find("Content-type:") == std::string::npos)
		body = "Content-type: text/html\r\n\r\n" + body;
	else
		checkContentType(body);
}

std::string Cgi::executeCgi ( void )
{
	char *const argv[] = {(char *)_typeCgi.c_str(), (char *)_pathFile.c_str(), NULL};
	
	if (pipe(_out_pipe) == -1 || pipe(_in_pipe) == -1)
	{
		perror("CGI :: PIPE FAILED");
		_code = INTERNALERROR;
		return (INTERNAL_SERVER_ERROR_HTML());
	}

	LibHelp::setNonBlocking(_out_pipe[0]);
	gettimeofday(&_begin, NULL);
	_pid  = fork();

	if (_pid < 0)
	{
		perror("CGI :: FORK FAILED");
		_code = INTERNALERROR;
		return (INTERNAL_SERVER_ERROR_HTML());
	}
	else if (_pid == 0)
	{
		if (_method == "POST")
		{
			close(_in_pipe[1]);
			if (dup2(_in_pipe[0], 0) == -1)
			{
				perror("CGI :: DUP2 ERROR");
				_code = INTERNALERROR;
				return (INTERNAL_SERVER_ERROR_HTML());
			}
			close(_in_pipe[0]);
		}
		close(_out_pipe[0]);

		if (dup2(_out_pipe[1], 1) == -1)
		{
			perror("CGI :: DUP2 ERROR");
			_code = INTERNALERROR;
			return (INTERNAL_SERVER_ERROR_HTML());
		}
		close(_out_pipe[1]);
		if (execve(_binPathExec.c_str(), argv, _envp) == -1)
        {
            perror("Erreur lors de l'exécution de execve");
			_code = INTERNALERROR;
            return (INTERNAL_SERVER_ERROR_HTML());
        }
	}
	else
	{
		close(_out_pipe[1]);

		if (_method == "POST")
		{
			close(_in_pipe[0]);
			if (write(_in_pipe[1], _body.c_str(), _body.size()) == -1)
			{
				perror("CGI :: WRITE ERROR");
				_code = INTERNALERROR;
				return (INTERNAL_SERVER_ERROR_HTML());
			}
			close(_in_pipe[1]);
		}

		_code = OK;
		return ("");
	}
	_code = BAD_GATEWAY;
	return (BAD_GATEWAY_HTML());
}


int	Cgi::resetCgi(const int& epfd)
{
	struct epoll_event ev;
	
	ev.events = EPOLLIN;
	ev.data.ptr = _client;

	_response.clear();
	_req->setIsCgi(false);
	
	epoll_ctl(epfd, EPOLL_CTL_MOD, _client->getSocketFd(), &ev);
	epoll_ctl(epfd, EPOLL_CTL_DEL, _out_pipe[0], NULL);
	
	close(_out_pipe[0]);
	
	if (_method == "GET")
	{
		close(_in_pipe[0]);
		close(_in_pipe[1]);
	}
	
	delete _req;
	
	if (_envp)
	{
		for (size_t i = 0; _envp[i] != NULL; i++)
			free (_envp[i]);
		delete[] _envp;
		_envp = NULL;	
	}
	
	_client->setMethods(NULL);
	return 0;
}

int		Cgi::handleRequest(int epfd, epoll_event& /* ev */)
{
	char buffer[BUF_SIZE];
	
	int bytes = read(_out_pipe[0], buffer, BUF_SIZE);
	gettimeofday(&_end, NULL);

	if (_end.tv_sec - _begin.tv_sec > TIMEOUT)
	{
		kill(_pid, SIGKILL);
		_code = INTERNALERROR;
	}
	
	if (bytes < 0)
		return resetCgi(epfd);
	
	if (bytes == 0 || _code != OK)
	{
		std::string contentLen;
		_cookies = _cookies + ";" + setCookies();
		switch (_code)
		{
			case OK:
				if (_response.length() - _response.find("\r\n\r\n") - 4 == 0)
				{
					_response = "HTTP/1.1 200 OK\r\nContent-Length: 0\r\nContent-Type: text/html\r\n\r\n";
					break;
				}
				else
				{
					std::string endline = _typeCgi == "php" ? "\r\n" : "\r\n\r\n";
					contentLen = LibHelp::toString(_response.length() - _response.find("\r\n\r\n") - 4);
					_response = "HTTP/1.1 200 OK\r\nContent-Length: " + contentLen + endline \
						+ _response;
					break;
				}
			case INTERNALERROR:
					_response = Page::errorPage(INTERNALERROR, "Internal Error");
					break;
		}

		if (write(_client->getSocketFd(), _response.c_str(), _response.size()) == -1)
			std::cerr << "CGI :: WRITE ERROR" << std::endl;
		return resetCgi(epfd);
	}

	_response.append(buffer, bytes);
	
	return 0;
}

std::string Cgi::setCookies(void)
{
    std::string cookies;
    
    size_t pos = 0;
 
    while ((pos = _response.find("Set-Cookie:", pos)) != std::string::npos) {
        pos += 11; 
	    size_t endPos = _response.find(";", pos);

        if (endPos != std::string::npos) {
            std::string cookie = _response.substr(pos, endPos - pos);
            if (!cookies.empty()) {
                cookies += ";";
            }
            cookies += cookie;
            pos = endPos + 1;
        } else {
            std::string cookie = _response.substr(pos);
            if (!cookies.empty()) {
                cookies += ";";
            }
            cookies += cookie;
            break;
        }
    }
    return cookies;
}

/*--------------------------------------------------MEMBER FUNCTION--------------------------------------------------*/