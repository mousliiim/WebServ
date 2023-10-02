/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Page.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 21:19:34 by rferradi          #+#    #+#             */
/*   Updated: 2023/09/19 23:17:19 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef	PAGE_HPP_
# define	PAGE_HPP_
# include "main.hpp"

class Page
{
	public:

	static std::string		errorPage(int code, std::string ret);
	static std::string 		autoIndex(const std::string& directoryPath);
};
#endif