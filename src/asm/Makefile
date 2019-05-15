# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbakhari <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/06 13:32:19 by kbakhari          #+#    #+#              #
#    Updated: 2019/05/12 18:01:14 by kbakhari         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COREWAR = asmMY

FLAGS = -Wall -Werror -Wextra

SRC = 	./main.c\
		./ft_utility.c\
		./ft_write.c\
		./ft_functions.c\
		./ft_labels.c\
		./ft_get_tokens.c\
		./ft_utilities2.c\
		./ft_utilities3.c\
		./ft_get_size.c\
		./ft_write_code.c\
		./ft_live.c\
		./ft_ld.c\
		./ft_st.c\
		./ft_add.c\
		./ft_sub.c\
		./ft_and.c\
		./ft_or.c\
		./ft_xor.c\
		./ft_zjmp.c\
		./ft_ldi.c\
		./ft_sti.c\
		./ft_fork.c\
		./ft_lld.c\
		./ft_lldi.c\
		./ft_lfork.c\
		./ft_aff.c

OB = $(SRC:%.c=%.o) 

all: $(COREWAR)

%.o:%.c
	@gcc -c $(FLAGS) $< -o $@

$(COREWAR): $(OB)
	@make -C ../../libft
	@gcc $(OB) ../../libft/libft.a -o $(COREWAR)

clean: 
	@make clean -C ../../libft
	@rm -f $(OB)

fclean: clean
	@make fclean -C ../../libft
	@rm -f $(COREWAR)

re: fclean all
