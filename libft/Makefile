# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkremen <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/24 18:15:35 by vkremen           #+#    #+#              #
#    Updated: 2018/10/30 16:36:36 by vkremen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

LIB = libft.h

GCC = clang

FLAGS = -Wall -Werror -Wextra

SRC = ft_memset.c\
	  ft_bzero.c\
	  ft_memcpy.c\
	  ft_memccpy.c\
	  ft_memmove.c\
	  ft_memchr.c\
	  ft_memcmp.c\
	  ft_strlen.c\
	  ft_strdup.c\
	  ft_strcpy.c\
	  ft_strncpy.c\
	  ft_strcat.c\
	  ft_strncat.c\
	  ft_strlcat.c\
	  ft_strchr.c\
	  ft_strrchr.c\
	  ft_strstr.c\
	  ft_strnstr.c\
	  ft_strcmp.c\
	  ft_strncmp.c\
	  ft_atoi.c\
	  ft_isalpha.c\
	  ft_isdigit.c\
	  ft_isalnum.c\
	  ft_isascii.c\
	  ft_isprint.c\
	  ft_toupper.c\
	  ft_tolower.c\
	  ft_memalloc.c\
	  ft_memdel.c\
	  ft_strnew.c\
	  ft_strdel.c\
	  ft_strclr.c\
	  ft_striter.c\
	  ft_striteri.c\
	  ft_strmap.c\
	  ft_strmapi.c\
	  ft_strequ.c\
	  ft_strnequ.c\
	  ft_strsub.c\
	  ft_strjoin.c\
	  ft_strtrim.c\
	  ft_strsplit.c\
	  ft_itoa.c\
	  ft_putchar.c\
	  ft_putstr.c\
	  ft_putendl.c\
	  ft_putnbr.c\
	  ft_putchar_fd.c\
	  ft_putstr_fd.c\
	  ft_putendl_fd.c\
	  ft_putnbr_fd.c\
	  ft_lstnew.c\
	  ft_lstdelone.c\
	  ft_lstdel.c\
	  ft_lstadd.c\
	  ft_lstiter.c\
	  ft_lstmap.c\
	  ft_strrvr.c\
	  ft_strcap.c\
	  ft_strrep.c\
	  ft_range.c\
	  ft_slice.c\
	  get_next_line.c\
	  ft_printf.c\
	  useful_function.c\
	  find_flags.c\
	  return_value.c\
	  ft_itoa_base.c\
	  ft_itoa_float.c\
	  printf_diouxf.c\
	  printf_int_and_dec.c\
	  support_function.c\
	  printf_unsigned.c\
	  printf_oct_and_hex.c\
	  printf_float.c\
	  printf_other_type.c\
	  printf_str.c

OB = $(SRC:%.c=%.o)

all: $(NAME)

$(OB):%.o:%.c
	@$(GCC) -c $(FLAGS) $< -o $@

$(NAME): $(OB)
	@ar rc $(NAME) $(OB)
	@ranlib $(NAME)

clean: 
	@rm -f *.o

fclean: clean
	@rm -f $(NAME)

re: fclean all
