# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mjochum <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/05 10:35:10 by mjochum           #+#    #+#              #
#    Updated: 2023/10/15 11:58:03 by mjochum          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		philo

SRCS =		philo.c srcs/ft_exit.c srcs/ft_philosopher.c srcs/ft_utils.c \
		srcs/ft_fourchettes.c

O_SRCS =	$(SRCS:.c=.o)

CC =		clang
CFLAGS =	-Wall -Werror -Wextra -g -pthread

all :		$(NAME)

$(NAME) :	$(O_SRCS)
		$(CC) $(CFLAGS) $(O_SRCS) -o $(NAME)

clean :		
		rm -f $(O_SRCS)

fclean :	clean
		rm -f $(NAME)

re :		fclean all
