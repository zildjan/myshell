#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/04 17:14:24 by pbourrie          #+#    #+#              #
#    Updated: 2016/02/02 00:42:49 by pbourrie         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME=21sh

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
			builtin_cd_tools.c \
			builtin_env.c \
			builtin_env_tools.c \
			builtin_setenv.c \
			builtin_exit.c \
			builtin_history.c \
			builtin_hash.c \
			builtin_hash_print.c \
			get_bin_path.c \
			hash_table.c \
			hash_table_tools.c \
			sort.c \
			home.c \
			get_cmd.c \
			editor.c \
			editor_control_key.c \
			editor_cursor_key.c \
			editor_edition_key.c \
			editor_edition.c \
			editor_cursor.c \
			editor_tools.c \
			editor_completion.c \
			completion.c \
			history.c \
			parse_cmd.c \
			parse_cmd_element_p1.c \
			parse_cmd_element_p2.c \
			parse_cmd_add_element.c \
			parse_cmd_add_redirection.c \
			parse_cmd_tools.c \
			parse_cmd_expansion.c \
			redirection.c \
			redirection_tools.c \
			heredoc.c \
			execute.c \
			wait.c \
			pipe.c \
			term.c \
			term_load_info.c \
			prompt.c \
			error.c \
			jobs.c \
			signal.c \
			free_env.c \
			free_cmd.c 
SRC = $(sort $(SRCS))
SRC_PATH = src/
OBJ_PATH = obj/
INC_PATH = -I libft/includes/ -I includes/
LIBS = libft/libft.a -ltermcap
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

fclean : clean
	@echo "	$(B)Removing '$(NAME)'$(RT)"
	@rm -f $(NAME)

cleanall : clean
	@make clean -C libft

fcleanall : fclean
	@make fclean -C libft

re : fclean all

.PHONY : all clean fclean re relib lib fcleanall cleanall