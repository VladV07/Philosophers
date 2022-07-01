# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: stapioca <stapioca@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/01 21:13:51 by stapioca          #+#    #+#              #
#    Updated: 2022/07/01 21:41:03 by stapioca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo_bonus

SRCS	=	philo_bonus.c	\
			start.c	\
			do_philo.c	\
			unit.c

OBJ		=	$(SRCS:%.c=%.o)

HEADER	=	philo_bonus.h

CC		=	cc

FLAGS	=	-Wall -Wextra -Werror

RM		= 	rm -rf

.PHONY:		all	clean	fclean	re

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o:		%.c $(HEADER)
			$(CC) $(FLAGS)  -c $< -o $@ -I 

clean:
			@$(RM) $(OBJ) $(OBJ_B)

fclean:		clean
			@$(RM) $(NAME) $(NAME_B)

re:			fclean all



