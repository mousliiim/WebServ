/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileReader.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:42:41 by jewancti          #+#    #+#             */
/*   Updated: 2023/09/21 18:57:38 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "FileReader.hpp"

cvstring	FileReader :: readAllLines(const std :: string& filename)
{
	vstring	lines;
	std :: ifstream	ift(filename.c_str());

	if (!ift.good()) {
		return lines;
	}
	std :: string	tmp;
	while ((std :: getline(ift, tmp))) {
		lines.push_back(tmp);
	}
    return lines;
}

const std :: string	FileReader :: readAllText(const std :: string& filename)
{
	std :: ifstream	ift(filename.c_str());
	if (!ift.good())
		return "";
	return std :: string(
		std :: istreambuf_iterator<char>(ift),
		std :: istreambuf_iterator<char>()
	);
}

const std :: string	FileReader :: readHTMLFile(const std :: string& filename)
{
	std::string res;
	try
	{
		res = readAllText(filename);
		return res;
	}
	catch(const std::exception& e)
	{
		std::cerr << "Erreur lors de l'ouverture de " \
		<< filename << " " << e.what() << '\n';
	}
	return ("");
}