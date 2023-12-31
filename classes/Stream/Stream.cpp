/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stream.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 00:55:25 by rferradi          #+#    #+#             */
/*   Updated: 2023/09/20 15:47:39 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Stream.hpp"

/*--------------------------------------------------CONSTRUCTOR--------------------------------------------------*/
Stream::Stream():_socketFd(-1),_epfd(-1),_server(NULL){}
Stream::Stream(int fd):_socketFd(fd){}
Stream::Stream(int fd, Server* ptr):_socketFd(fd),_server(ptr){}
Stream::Stream(int fd, Server* ptr, int epfd):_socketFd(fd),_epfd(epfd),_server(ptr){}
/*--------------------------------------------------CONSTRUCTOR--------------------------------------------------*/

/*--------------------------------------------------GETTERS--------------------------------------------------*/
Server* Stream::getServer(void) const { return _server; }
int		Stream::getSocketFd() const { return _socketFd; }
/*--------------------------------------------------GETTERS--------------------------------------------------*/

/*--------------------------------------------------SETTERS--------------------------------------------------*/
void	Stream::setSocketFd(int fd){ _socketFd = fd; }
/*--------------------------------------------------SETTERS--------------------------------------------------*/
