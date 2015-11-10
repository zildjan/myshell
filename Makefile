#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/04 17:14:24 by pbourrie          #+#    #+#              #
#    Updated: 2015/11/10 18:59:42 by pbourrie         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME=minishell

ifdef FLAGS 
ifeq ($(FLAGS), no) 
CFLAGS= 
endif 
ifeq ($(FLAGS), debug) 
CFLAGS= -Wall -Wextra -Werror -ansi -pedantic -g
endif 
else 
CFLAGS = -Wall -Wextra -Werror -O3
endif 

B  =		\033[1m
UL =		\033[4m
RT =		\033[0m

SRCS =		main.c \
			init_env.c \
			get_env.c \
			set_env.c \
			builtin_cd.c \
			builtin_setenv.c \
			builtin_exit.c \
			get_bin_path.c \
			home.c \
			get_cmd.c \
			parse_cmd.c \
			parse_cmd_var.c \
			execute.c \
			free_cmd.c \
			prompt.c \
			error.c
SRC = $(sort $(SRCS))
SRC_PATH = src/
OBJ_PATH = obj/
INC_PATH = -I libft/includes/ -I includes/
LIBS = libft/libft.a
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))

all : $(NAME)

$(NAME) : $(OBJS)
	@make -s -C libft/
	@echo "	$(B)Linking Files$(RT)"
	@gcc -o $(NAME) $(LIBS) $(OBJS)
	@echo "	$(B)Done$(RT)"

$(OBJ_PATH)%.o : $(SRC_PATH)%.c
	@[ -e $(OBJ_PATH) ] || (mkdir $(OBJ_PATH))
	@echo "	*$(B)Compiling$(RT) $?"
	@gcc $(CFLAGS) $(INC_PATH) -c -o $@ $?

relib :
	@make -C libft/ fclean
	@make re

lib :
	@make -C libft/
	@echo "	$(B)Linking Files$(RT)"
	@gcc -o $(NAME) $(LIBS) $(OBJS)
	@echo "	$(B)Done$(RT)"

clean :
	@echo "	$(B)Removing object files$(RT)"
	@rm -rf $(OBJ_PATH)
	@echo "	$(B)Removing temporary files$(RT)"
	@find . -name "*~" -delete
	@find . -name "a.out" -delete

fclean : clean
	@echo "	$(B)Removing '$(NAME)'$(RT)"
	@rm -f $(NAME)

cleanall : clean
	@make clean -C libft

fcleanall : fclean
	@make fclean -C libft

re : fclean all

.PHONY : all clean fclean re relib lib fcleanall cleanall