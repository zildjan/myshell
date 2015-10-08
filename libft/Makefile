#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/04 17:14:24 by pbourrie          #+#    #+#              #
#    Updated: 2015/04/29 20:38:22 by pbourrie         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = 		libft.a

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

SRCS =		ft_bzero.c \
			ft_memset.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memccpy.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memalloc.c \
			ft_memrealloc.c \
			ft_memdel.c \
			ft_strlen.c \
			ft_strdup.c \
			ft_strndup.c \
			ft_strcpy.c \
			ft_strncpy.c \
			ft_strlcpy.c \
			ft_strcat.c \
			ft_strncat.c \
			ft_strlcat.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strrev.c \
			ft_strstr.c \
			ft_strnstr.c \
			ft_strcmp.c \
			ft_strncmp.c \
			ft_atoi.c \
			ft_btoi.c \
			ft_pow.c \
			ft_degree_to_radian.c \
			ft_strnew.c \
			ft_strdel.c \
			ft_strclr.c \
			ft_striter.c \
			ft_striteri.c \
			ft_strmap.c \
			ft_strmapi.c \
			ft_strequ.c \
			ft_strnequ.c \
			ft_strsub.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_strsplit.c \
			ft_count_word.c \
			ft_isalpha.c \
			ft_isdigit.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_isupper.c \
			ft_islower.c \
			ft_toupper.c \
			ft_tolower.c \
			ft_strtoupper.c \
			ft_itoa.c \
			ft_ltoa.c \
			ft_ultoa.c \
			ft_ultoa_base.c \
			ft_dtoa.c \
			ft_nbrlen.c \
			ft_u_nbrlen.c \
			ft_nbrlen_base.c \
			ft_u_nbrlen_base.c \
			ft_isspace.c \
			ft_putchar.c \
			ft_putstr.c \
			ft_putsubstr.c \
			ft_putendl.c \
			ft_putnbr.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_putnspace.c \
			ft_putnchar.c \
			ft_putwchar.c \
			ft_putwstr.c \
			ft_wcharlen.c \
			ft_wstrlen.c \
			ft_wstrdup.c \
			ft_wstrndup.c \
			ft_lstnew.c \
			ft_lstdelone.c \
			ft_lstdel.c \
			ft_lstdelcontent.c \
			ft_lstadd.c \
			ft_lstiter.c \
			ft_lstmap.c \
			ft_lstaddend.c \
			ft_lstsplit.c \
			ft_putlst_str.c \
			ft_printf/ft_printf.c \
			ft_printf/process_flags.c \
			ft_printf/process_flags_tools.c \
			ft_printf/new.c \
			ft_printf/get_arg.c \
			ft_printf/check_aparam.c \
			ft_printf/get_signed_param.c \
			ft_printf/get_unsigned_param.c \
			ft_printf/get_text_param.c \
			ft_printf/print.c \
			ft_printf/process_width.c \
			ft_printf/process_precision.c \
			ft_printf/print_unicode.c \
			ft_printf/color_tag.c \
			get_next_line.c \
			ft_get_file_size.c \
			ft_get_file_size_str.c \
			ft_get_file_type.c \
			ft_get_basename.c \
			ft_is_hidden_file.c \
			ft_list_dir_content.c \
			ft_rgbtohex.c 
SRC = $(sort $(SRCS))
SRC_PATH = src/
OBJ_PATH = obj/
INC_PATH = includes/
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))

all : $(NAME)

$(NAME) : $(OBJS)
	@printf "                                                 \r"
	@echo "	$(B)Creation of $(NAME)$(RT)"
	@ar rc $(NAME) $(addprefix $(OBJ_PATH), $(OBJ))
	@echo "	$(B)Creation of index to $(NAME)$(RT)"
	@ranlib $(NAME)

$(OBJ_PATH)%.o : $(SRC_PATH)%.c
	@[ -e $(OBJ_PATH) ] || (mkdir $(OBJ_PATH))
	@[ -e $(OBJ_PATH)/ft_printf ] || (mkdir $(OBJ_PATH)/ft_printf)
	@printf "	*$(B)Compiling$(RT) $?                         \r"
	@gcc $(CFLAGS) -I $(INC_PATH) -c -o $@ $?

clean :
	@echo "	$(B)Removing libft object files$(RT)"
	@rm -rf $(OBJ_PATH)
	@echo "	$(B)Removing libft temporary files$(RT)"
	@find . -name "*~" -delete

fclean : clean
	@echo "	$(B)Removing $(NAME)$(RT)"
	@rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re