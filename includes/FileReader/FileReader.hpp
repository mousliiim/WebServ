/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileReader.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:33:02 by jewancti          #+#    #+#             */
/*   Updated: 2023/09/19 20:52:26 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef __FILE_READER_HPP__
# define __FILE_READER_HPP__

# include "main.hpp"

class	FileReader
{
	public:
		static
			cvstring			readAllLines(const std :: string& filename);
		static
			const std :: string	readAllText(const std :: string& filename);
		static
			const std :: string	readHTMLFile(const std :: string& filename);
};

#endif
