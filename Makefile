# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkremen <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/24 18:15:35 by vkremen           #+#    #+#              #
#    Updated: 2019/05/07 04:56:54 by oandrosh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COREWAR = corewar

ASM = asm

GCC = clang

FLAGS = -Wall -Werror -Wextra

INC  = -I ./SDL/SDL2.framework/Headers\
  -I ./SDL/SDL2_image.framework/Headers\
  -I ./SDL/SDL2_ttf.framework/Headers \
  -I ./SDL/SDL2_mixer.framework/Headers

FRM  = -F ./SDL/ -framework SDL2 -framework SDL2_image -framework SDL2_ttf\
  -framework SDL2_mixer

SRC_COREWAR = 	./src/main.c\
				./src/init.c\
				./src/add_bot.c\
				./src/something_useful.c\
				./src/parsing_bot.c\
				./src/start_fight.c\
				./src/start_fight_2.c\
				./src/operations_1.c\
				./src/operations_2.c\
				./src/operations_3.c\
				./src/utils_for_oper.c\
				./src/visual.c\
				./src/visual2.c\
				./src/visual3.c

SRC_ASM = 	./src/asm/main.c\
			./src/asm/ft_utility.c\
			./src/asm/ft_write.c\
			./src/asm/ft_functions.c\
			./src/asm//ft_labels.c\
			./src/asm/ft_get_tokens.c\
			./src/asm/ft_utilities2.c\
			./src/asm/ft_utilities3.c\
			./src/asm/ft_get_size.c\
			./src/asm/ft_write_code.c\
			./src/asm/ft_live.c\
			./src/asm/ft_ld.c\
			./src/asm/ft_st.c\
			./src/asm/ft_add.c\
			./src/asm/ft_sub.c\
			./src/asm/ft_and.c\
			./src/asm/ft_or.c\
			./src/asm/ft_xor.c\
			./src/asm/ft_zjmp.c\
			./src/asm/ft_ldi.c\
			./src/asm/ft_sti.c\
			./src/asm/ft_fork.c\
			./src/asm/ft_lld.c\
			./src/asm/ft_lldi.c\
			./src/asm/ft_lfork.c\
			./src/asm/ft_aff.c\
			./src/asm/ft_check_tokens.c\
			./src/asm/ft_validate_args.c

OB_COREWAR = $(SRC_COREWAR:%.c=%.o) 

OB_ASM = $(SRC_ASM:%.c=%.o) 

all: $(COREWAR) $(ASM)

%.o:%.c
	@$(GCC) -c $(FLAGS) $< -o $@ $(INC)

$(COREWAR): $(OB_COREWAR)
	@make -C libft
	@$(GCC) $(OB_COREWAR) libft/libft.a $(FRM) -rpath @loader_path/SDL -lncurses -o $(COREWAR)

$(ASM): $(OB_ASM)
	@$(GCC) $(OB_ASM) libft/libft.a -o $(ASM)

clean: 
	@make clean -C libft
	@rm -f $(OB_COREWAR)
	@rm -f $(OB_ASM)

fclean: clean
	@make fclean -C libft
	@rm -f $(COREWAR)
	@rm -f $(ASM)

re: fclean all
