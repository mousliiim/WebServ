/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LibHelp.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:33:02 by jewancti          #+#    #+#             */
/*   Updated: 2023/09/19 23:17:37 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef __LIB_HELP_HPP__
# define __LIB_HELP_HPP__

# include "main.hpp"

class LibHelp
{
  public:
	static int toInt(string_it begin, string_it end);
	static int toInt(cstring_it begin, cstring_it end);
	static int toInt(const std ::string &format);
	static std ::string toString(const vstring &vect,
			const std ::string &delim = "\n");
	static std ::string toString(const int &number);
	static vstring toVString(const std ::string &str, const char &c);
	static std ::string ltrim(const std ::string &str);
	static string_it search(string_it begin, string_it end,
			const std ::string &sep);
	static cstring_it search(cstring_it begin, cstring_it end,
			const std ::string &sep);
	static cstring_it search(cstring_it begin, cstring_it end, const char &c);
	static bool find(cstring_it begin, cstring_it end, const char &c);
	static bool find(cstring_it begin, cstring_it end, const std ::string str);
	static vstring split(const std ::string &str, const char &c = ' ');
	static vstring split(const std ::string &str,
			const std ::string &sep = " ");
	static bool all_of(cstring_it begin, cstring_it end, bool(predicat)(int));
	static bool all_of(cstring_it begin, cstring_it end, int(predicat)(int));
	static bool setNonBlocking(int sockfd);
	static bool fileExists(const std::string &filename);
	static bool isDirectory(std::string path);

	static std::map<std::string, std::string> setMimType();
};

#endif
