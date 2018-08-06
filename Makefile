# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: itiievsk <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/24 14:51:09 by itiievsk          #+#    #+#              #
#    Updated: 2018/04/24 14:51:11 by itiievsk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C = gcc

NAME = lem-in

FLAGS = -Wall -Wextra -Werror

DIR_S = ./

DIR_O = obj

HEADER = lemin.h

LIB = libft/libft.a

SOURCES =	main.c\
			validate.c\
			parse.c\
			slists.c\
			solve.c\
			clean.c\
			print.c\
			utils.c\

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	make -C ./libft/
#	make -C ./visual/
	$(C) $(FLAGS) -o $(NAME) $(OBJS) $(LIB)

$(DIR_O)/%.o: $(DIR_S)/%.c
	@mkdir -p $(DIR_O)
	$(C) $(FLAGS) -I $(HEADER) -o $@ -c $<

norme:
	@norminette $(HEADER)
	@norminette $(SOURCES)
	make norme -C ./libft/
#	make norme -C ./visual/

clean:
	make clean -C ./libft/
#	make clean -C ./visual/
	@rm -f $(OBJS)
	@rm -rf $(DIR_O)

fclean: clean
	make fclean -C ./libft/
#	make fclean -C ./visual/
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re norme
