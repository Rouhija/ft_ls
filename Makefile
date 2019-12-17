  
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/15 16:29:02 by srouhe            #+#    #+#              #
#    Updated: 2019/12/04 19:08:18 by srouhe           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= 	ft_ls
C		= 	gcc
FLAGS 	=  

FILES 	=	main.c \
			ft_ls.c \
			utils.c \
			object.c \
			directory.c \
			lst.c \
			sort.c \
			recurse.c \
			print.c

SRCS 	=	$(addprefix srcs/, $(FILES))
OBJS 	=	$(FILES:.c=.o)

all: $(NAME)

$(NAME):
	@make -C libft
	@$(C) $(FLAGS) -o $(NAME) $(SRCS) -I includes/ -I libft/includes -Llibft -lft

clean:
	@make clean -C libft
	@/bin/rm -f $(OBJS)

fclean: clean
	@make fclean -C libft
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
