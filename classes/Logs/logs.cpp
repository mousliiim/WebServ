/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 17:52:56 by rferradi          #+#    #+#             */
/*   Updated: 2023/09/28 18:36:55 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

void displayTime ( std::string color)
{
	time_t now = time(0);
	tm *ltm = localtime(&now);
	std::cout << color << "[" << ltm->tm_year + 1900 << "-" << ltm->tm_mon << "-" << ltm->tm_mday << "  " << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec << "]" << RESET;
}


void newClient ( std::string color, int fd)
{
	displayTime(color);
	std::cout << "  New client connected on socket " << fd << std::endl;
}

void logRequest ( std::string color, int fd)
{
	(void)color;
	(void)fd;
	// not done
}
