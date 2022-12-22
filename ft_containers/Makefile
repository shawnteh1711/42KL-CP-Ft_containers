# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/14 15:35:19 by schuah            #+#    #+#              #
#    Updated: 2022/12/22 15:06:59 by schuah           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ft_containers
CXX			=	c++
RM			=	rm -f
CXXFLAGS	=	-Wall -Wextra -Werror -std=c++98 -pedantic #-fsanitize=address -g3
SRCS_FILES	=	main
SRCS		= 	$(addprefix $(SRCS_DIR), $(addsuffix .cpp, $(SRCS_FILES)))
OBJS		= 	$(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRCS_FILES)))
SRCS_DIR	=	srcs/
OBJS_DIR	=	objs/

all:
				mkdir -p $(OBJS_DIR)
				make $(NAME)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.cpp
				$(CXX) $(CXXFLAGS) -c $< -o $@

$(NAME):		$(OBJS)
				$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

vector:
				$(CXX) $(CXXFLAGS) container_testers/vector.cpp -o $(NAME)
				./ft_containers

stack:
				$(CXX) $(CXXFLAGS) container_testers/stack.cpp -o $(NAME)
				./ft_containers
			
map:
				$(CXX) $(CXXFLAGS) container_testers/map.cpp -o $(NAME)
				./ft_containers

set:
				$(CXX) $(CXXFLAGS) container_testers/set.cpp -o $(NAME)
				./ft_containers

clean:
				rm -rf $(OBJS_DIR)

fclean:			clean
				rm -rf $(NAME)

re:				fclean all

.PHONY:			all clean fclean re