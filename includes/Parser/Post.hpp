/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Post.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 21:11:21 by rferradi          #+#    #+#             */
/*   Updated: 2023/09/20 23:32:31 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef POST_HPP
# define POST_HPP
# include "main.hpp"
# include "Methods.hpp"
#define BUFFPOST 2000

class Post: public Methods
{
	private:
		std::string 	_contentType;
		std::string		_boundary;
		size_t 			_head;
		bool			_inbody;
		bool			_headerReaded;
		std::ofstream	_fileStream;
		std::string 	_filename;
		size_t			_contentLen;
		size_t			_body;
		size_t			_nextBoundary;
		static int		_number;
		bool			_open;
		std::string		_postPath;
		
	public:
		Post(std::string &req, map_locate const loc, Cgi *_cgi);
		
		~Post();
		bool 			handle();
		bool			parseBody();
		bool			writeFileMulti();
		bool			writeFile();
		int 			multipartData();
		int 			binaryData();
		size_t 			findNextBound();
		size_t 			findNextBoundBegin();
		std::string 	makeFilename(std::string file);
		std::string 	generateRandomFileName();
		std::string		HttPage(int epfd);
		std::string		getBody();
		void			parseHeader();
};
#endif