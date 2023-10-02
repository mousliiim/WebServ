/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Page.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 21:21:39 by rferradi          #+#    #+#             */
/*   Updated: 2023/09/19 22:57:08 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Page.hpp"
# include "main.hpp"
# include "LibHelp.hpp"

std::string Page::errorPage(int code, std::string ret)
{
    std::string body = "<!DOCTYPE html>\n"
                      "<html>\n"
                      "<head>\n"
                      " <title>" + LibHelp::toString(code) + " " + ret + "</title>\n"
                      "</head>\n"
                      "<body>\n"
                      "<h1>" + LibHelp::toString(code) + " " + ret + "</h1>\n"
					  "<p> Default Error Page </p>\n"
                      "</body>\n"
                      "</html>";

    std::string response = "HTTP/1.1 " + LibHelp::toString(code) + " " + ret + "\r\n";
    response += "Content-Length: " + LibHelp::toString(body.size()) + "\r\n";
    response += "Content-Type: text/html\r\n\r\n";
    response += body;

    return response;
}

std::string Page::autoIndex(const std::string& directoryPath)
{
    std::string html = "<html><head><title>Auto index</title></head><body><h1>Directory Listing</h1><ul>";
    DIR* dir = opendir(directoryPath.c_str());

    if (dir) {
        struct dirent* entry;
        while ((entry = readdir(dir)) != NULL) {
            if (std::string(entry->d_name) != "." && std::string(entry->d_name) != "..") {
                std::string fileName = entry->d_name;
                html += "<li><a href=\"" + fileName + "\">" + fileName + "</a></li>";
            }
        }
        closedir(dir);
    } else {
        return Page::errorPage(404, "Not Found");
    }
    html += "</ul></body></html>";
    return html;
}