# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/16 15:37:56 by lzaccome          #+#    #+#              #
#    Updated: 2021/11/04 20:52:49 by lzaccome         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = clang

CFLAGS =  -Wall -Wextra -Werror -I proto.h #-g3 -fsanitize=address

SRCS =	split.c \
		main.c \
		utils.c

_GREY=	$'\033[1;30m
_RED=	$'\033[1;31m
_GREEN=	$'\033[1;32m
_YELLOW=$'\033[1;33m
_BLUE=	$'\033[1;34m
_PURPLE=$'\033[1;35m
_CYAN=	$'\033[1;36m
_WHITE=	$'\033[1;37m

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		@echo "$(_YELLOW)[Compilation ongoing ...]"
		@sleep 1
		@echo "$(_GREEN)[Compilation finished]"
		$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
		@echo "$(_CYAN)[Executable created]"
		@echo [Name : pipex]

%o: %.c
	$(CC) $(FLAGS) -o $@ -c $< -I includes

clean:
	@rm -f $(OBJ)
	@echo "$(_RED)[All .o removed]"

fclean: clean
	@rm -f $(NAME)
	@echo "$(_RED)[Executable removed]"

re: fclean all

.PHONY : all bonus clean fclean re
