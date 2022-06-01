# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: stapioca <stapioca@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/20 19:04:36 by stapioca          #+#    #+#              #
#    Updated: 2022/04/20 19:04:36 by stapioca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Philosophers

WAY = philo/

HEADER = $(WAY)Philosophers.h

LIST = $(WAY)Philosophers.c \
		$(WAY)unit.c

OBJS = $(patsubst %.c,%.o,$(LIST))

FLAGS = -Wall -Wextra -Werror -fsanitize=thread -g

.PHONY : all clean fclean re

all : $(NAME) $(HEADER)

$(NAME) : $(OBJS)
	CC $(FLAGS) $(OBJS) -I $(HEADER) -o $@

%.o : %.c $(HEADER)
	CC $(FLAGS) -c $< -o $@ -I ${HEADER}

clean :
	@rm -f $(OBJS)

fclean : clean
	@rm -f $(NAME)

re : fclean all