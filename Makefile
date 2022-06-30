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
		$(WAY)unit.c \
		$(WAY)do_philo.c \
		$(WAY)monitor_death.c

OBJS = $(patsubst %.c,%.o,$(LIST))

FLAGS = -Wall -Wextra -fsanitize=thread -g

.PHONY : all clean fclean re

all : $(NAME) $(HEADER)

$(NAME) : $(OBJS)
	cc $(FLAGS) $(OBJS) -I $(HEADER) -o $@

%.o : %.c $(HEADER)
	cc $(FLAGS) -c $< -o $@ -I ${HEADER}

clean :
	@rm -f $(OBJS)

fclean : clean
	@rm -f $(NAME)

re : fclean all