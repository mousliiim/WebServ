/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 00:21:15 by jewancti          #+#    #+#             */
/*   Updated: 2023/09/28 18:23:01 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef __MAIN_HPP__
# define __MAIN_HPP__

# define BUF_SIZE 42000


# include <iostream>
# include <cstring>
# include <string>
# include <fstream>
# include <sstream>
# include <istream>
# include <algorithm>
# include <vector>
# include <map>
# include <sys/epoll.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/stat.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <fcntl.h>
# include <fstream>
# include <string>
# include <signal.h>

# define B_WHITE "\033[0;37m"
# define B_GREEN "\033[0;32m"
# define B_CYAN "\033[0;36m"
# define B_GREY "\033[0;90m"
# define RESET "\033[0m"

typedef struct sockaddr_in  t_sockaddr;
typedef const std :: vector<std :: string>				cvstring;
typedef std :: vector<std :: string> :: iterator		vstring_it;
typedef std :: vector<std :: string> :: const_iterator	cvstring_it;

typedef std :: string :: iterator						string_it;
typedef std :: string :: const_iterator					cstring_it;
typedef std :: vector<std :: string>					vstring;

void displayTime ( std::string color = B_WHITE);
void newClient ( std::string color = B_GREEN, int fd = 0);




#endif