# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lwang <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/13 10:12:52 by lwang             #+#    #+#              #
#    Updated: 2017/04/13 10:12:54 by lwang            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC = main.c sort_lst.c list_directory.c

OBJ = $(SRC:.c=.o)

OBJLIB = ./libft/*.o

CFLAGS = -Wall -Wextra -Werror -g

$(NAME): $(OBJ)
	make -C ./libft
	gcc $(CFLAGS) -o $(NAME) $(OBJ) -L libft/ -lft

all: $(NAME)

clean:
	make -C ./libft clean
	rm -f *.o

fclean:
	make -C ./libft fclean
	rm -f $(NAME)

re: fclean all