# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/10 03:16:15 by mmourdal          #+#    #+#              #
#    Updated: 2023/09/28 18:39:57 by rferradi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                                  ASCII ART                                   #
################################################################################

WHITE	= \033[1;37m
GREY 	= \033[1;90m
BLINK	= \033[5m
END		= \033[0m

ART_NAME_1 = ██     ██ ███████ ██████  ███████ ███████ ██████      ██  ██     ██████  		   \n
ART_NAME_2 = ██     ██ ██      ██   ██    ███  ██      ██   ██    ██  ███    ██  ████ 		   \n
ART_NAME_3 = ██  █  ██ █████   ██████    ███   █████   ██████    ██    ██    ██ ██ ██ 		   \n
ART_NAME_4 = ██ ███ ██ ██      ██   ██  ███    ██      ██   ██  ██     ██    ████  ██ 		   \n
ART_NAME_5 =  ███ ███  ███████ ██████  ███████ ███████ ██   ██ ██      ██ ██  ██████ 		   \n

PRINT_NAME = printf "\n$(GREY) %4s $(ART_NAME_1) %4s $(ART_NAME_2) %4s $(ART_NAME_3) %4s $(ART_NAME_4) %5s $(ART_NAME_5) $(END)\n"

################################################################################
#                                  SOURCES                                     #
################################################################################

CLASS_DIR				= classes/
STRING_HELP_DIR			= $(CLASS_DIR)LibHelp/
FILE_READER_DIR			= $(CLASS_DIR)FileReader/
PARSER_DIR				= $(CLASS_DIR)Parser/
STREAM_DIR				= $(CLASS_DIR)Stream/
LOCATION_DIR			= $(CLASS_DIR)Location/
HTTP_SERVER_DIR			= $(CLASS_DIR)HttpServer/
PAGE					= $(CLASS_DIR)Page/
LOGS_DIR				= $(CLASS_DIR)Logs/

SRC_FILES	=	$(addprefix $(STRING_HELP_DIR), LibHelp.cpp) \
				$(addprefix $(FILE_READER_DIR), FileReader.cpp) \
				$(addprefix $(PARSER_DIR), Parser.cpp setters.cpp Methods.cpp Get.cpp Post.cpp Cgi.cpp Delete.cpp) \
				$(addprefix $(STREAM_DIR), Server.cpp) \
				$(addprefix $(STREAM_DIR), Stream.cpp) \
				$(addprefix $(STREAM_DIR), Client.cpp) \
				$(addprefix $(LOCATION_DIR), Location.cpp) \
				$(addprefix $(HTTP_SERVER_DIR), HttpServer.cpp) \
				$(addprefix $(PAGE), Page.cpp) \
				$(addprefix $(LOGS_DIR), logs.cpp) \
				main.cpp \

################################################################################
#                                  OBJETS                                      #
################################################################################

OBJS_DIR	= .objets
OBJS 		= $(SRC_FILES:%.cpp=$(OBJS_DIR)/%.o)

################################################################################
#                                COMPILATION                                   #
################################################################################

CXX			= @c++
INCLUDES	=	-Iincludes \
				-Iincludes/FileReader \
				-Iincludes/Parser \
				-Iincludes/LibHelp \
				-Iincludes/Stream \
				-Iincludes/Location \
				-Iincludes/HttpServer \
				-Iincludes/Page \

CXXFLAGS 	= -g3 -Wall -Wextra -Werror -std=c++98 $(INCLUDES)
CDFLAGS		= -MMD -MP

################################################################################
#                                  MAKEFILE                                    #
################################################################################

NAME = webserv

all : $(NAME)

$(NAME) : $(OBJS_DIR) $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(CDFLAGS) -o $(NAME)
	
$(OBJS_DIR) :
	@$(PRINT_NAME)
	@printf "$(GREY)%20s Création des dossiers content les $(END)$(WHITE).o : \n"
	@sleep 0.1
	@printf "$(GREY)%24s Création du dossier $(END)$(WHITE)$(OBJS_DIR)...\n"
	@mkdir $(OBJS_DIR)
	@sleep 0.1
	@printf "$(GREY)%21s Création du dossier $(END)$(WHITE)$(OBJS_DIR)/$(CLASS_DIR)...\n"
	@mkdir $(OBJS_DIR)/$(CLASS_DIR)
	@sleep 0.1
	@printf "$(GREY)%21s Création du dossier $(END)$(WHITE)$(OBJS_DIR)/$(STRING_HELP_DIR)...\n"
	@mkdir $(OBJS_DIR)/$(STRING_HELP_DIR)
	@sleep 0.1
	@printf "$(GREY)%21s Création du dossier $(END)$(WHITE)$(OBJS_DIR)/$(FILE_READER_DIR)...\n"
	@mkdir $(OBJS_DIR)/$(FILE_READER_DIR)
	@sleep 0.1
	@printf "$(GREY)%21s Création du dossier $(END)$(WHITE)$(OBJS_DIR)/$(PARSER_DIR)...\n"
	@mkdir $(OBJS_DIR)/$(PARSER_DIR)
	@sleep 0.1
	@printf "$(GREY)%21s Création du dossier $(END)$(WHITE)$(OBJS_DIR)/$(STREAM_DIR)...\n"
	@mkdir $(OBJS_DIR)/$(STREAM_DIR)
	@sleep 0.1
	@printf "$(GREY)%21s Création du dossier $(END)$(WHITE)$(OBJS_DIR)/$(LOCATION_DIR)...\n"
	@mkdir $(OBJS_DIR)/$(LOCATION_DIR)
	@sleep 0.1
	@printf "$(GREY)%21s Création du dossier $(END)$(WHITE)$(OBJS_DIR)/$(HTTP_SERVER_DIR)...\n"
	@mkdir $(OBJS_DIR)/$(HTTP_SERVER_DIR)
	@sleep 0.1
	@printf "$(GREY)%21s Création du dossier $(END)$(WHITE)$(OBJS_DIR)/$(PAGE)...\n"
	@mkdir $(OBJS_DIR)/$(PAGE)
	@sleep 0.1
	@printf "$(GREY)%21s Création du dossier $(END)$(WHITE)$(OBJS_DIR)/$(LOGS_DIR)...\n"
	@mkdir $(OBJS_DIR)/$(LOGS_DIR)
	@sleep 0.1
	@printf "$(GREY)%20s Création des dossiers $(END)$(BLINK)$(WHITE)objets terminée$(END)\n\n"
	@sleep 0.1
	@printf "$(GREY)%25s Compilation de $(END)$(WHITE)$(NAME)...\n"
	@sleep 0.1
	@printf "$(GREY)%20s Compilation de $(END)$(BLINK)$(WHITE)$(NAME) terminée [✅]$(END)\n\n"

-include $(OBJS:%.o=%.d)

$(OBJS) : $(OBJS_DIR)/%.o : %.cpp
	$(CXX) $(CXXFLAGS) $(CDFLAGS) -c $< -o $@

clean :
	@rm -rf $(OBJS_DIR)
	@printf "$(GREY)%20s Suppression du dossier $(END)$(WHITE)$(OBJS_DIR)...\n"

fclean : clean
	@rm -rf $(NAME)
	@printf "$(GREY)%20s Suppression de $(END)$(WHITE)$(NAME) [✅]\n"

re : fclean all

.PHONY: all clean fclean re