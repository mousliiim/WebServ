/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Get.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:55:02 by rferradi          #+#    #+#             */
/*   Updated: 2023/09/19 23:16:27 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# ifndef GET_HPP
# define GET_HPP

# include "Methods.hpp"
# include "Cgi.hpp"

class Get : public Methods
{
	protected:

	public:
		Get(std::string &req, map_locate const loc, Cgi *_cgi);
		~Get();

		bool		handle(){return true;};
		std::string	HttPage(int epfd);
};
#endif