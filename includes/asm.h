/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbakhari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 13:34:38 by kbakhari          #+#    #+#             */
/*   Updated: 2019/05/06 13:35:04 by kbakhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "../libft/libft.h"
# include <stdio.h>
# include "op.h"
# include <stdint.h>
# include <stdbool.h>
# include <limits.h>
# include <ncurses.h>

enum						e_token_type
{
	OP,
	REG,
	DIR,
	IND,
	LABEL,
	DIR_L,
	IND_L
};

typedef struct				s_token
{
	enum e_token_type		type;
	char					*value;
	int						line;
	struct s_token			*next;
}							t_token;

typedef struct				s_label
{
	char					*name;
	int						position;
	struct s_label			*next;
}							t_label;

/*
**	globals
*/

int							g_code_size;
int							g_byte_pos;
int							g_kostil;

/*
**	ft_utility.c
*/

void						ft_death(char *str);
int							ft_check_empty(char *line);
int							ft_is_label(char *line);
char						*ft_get_filename(char *name);

/*
**	ft_write.c
*/

void						ft_write(int fd, char **str, int size);
void						ft_put_magic(int fd2, int flag);
void						ft_put_null(int fd2);
void						ft_write_name(int fd2, char *str, int flag);

/*
**	ft_functions.c
*/

char						**ft_get_name_comment(int fd);
char						*ft_get_name(int fd, char *line, int flag);
char						*ft_get_comment(char *line);

/*
**	ft_labels.c
*/

void						ft_check_label(char *str);
void						ft_add_label(char *str, t_label **labels,
	t_token **tokens, int i);

/*
**	ft_get_tokens.c
*/

void						ft_get_rest(char *str, t_token **tokens, int i,
	t_label **labels);
void						ft_define_tokens(char *str, t_token **tokens,
	t_label **labels);
void						ft_get_tokens(int fd, t_token **tokens,
	t_label **labels);
void						ft_check_ind(char *str, t_label **labels);

/*
**	ft_utilities2.c
*/

char						*ft_destroy_comments(char *str);
void						ft_find_lable(t_label **labels, char *str);
char						*ft_hex_conv(int32_t nbr, int size);
int							ft_get_label_val(char *str, t_label **labels);
void						ft_free_mass(char **mass, int step);

/*
**	ft_get_size.c
*/

void						ft_identify_op(int *dir, char *str);
void						ft_get_size(t_token **tokens, t_label **labels);

/*
**	ft_write_code.c
*/

void						ft_write_code(int fd2, t_label **labels,
	t_token **tokens);

/*
**	ft_utilities3.c
*/

void						ft_check_separators(char *str);
void						ft_check_digit(char *str);
void						ft_add_separators(char *line);
void						ft_validate_register(t_token **token);

/*
**	ft_check_tokens.c
*/

void						ft_validate_tokens(t_token **tokens);
void						ft_check_tokens(t_token **tokens);
void						ft_validate_operations(t_token *cur);
void						ft_check_spaces(t_token *cur);

/*
**	ft_validate_args.c
*/

void						ft_validate_args(t_token **tokens);

/*
**	ft_operations.c
*/

void						ft_live(t_token **token, t_label **labels, int fd2);
void						ft_ld(t_token **token, t_label **labels, int fd2);
void						ft_st(t_token **token, t_label **labels, int fd2);
void						ft_add(t_token **token, int fd2);
void						ft_sub(t_token **token, int fd2);
void						ft_and(t_token **token, t_label **labels, int fd2);
void						ft_or(t_token **token, t_label **labels, int fd2);
void						ft_xor(t_token **token, t_label **labels, int fd2);
void						ft_zjmp(t_token **token, t_label **labels, int fd2);
void						ft_ldi(t_token **token, t_label **labels, int fd2);
void						ft_sti(t_token **token, t_label **labels, int fd2);
void						ft_fork(t_token **token, t_label **labels, int fd2);
void						ft_lld(t_token **token, t_label **labels, int fd2);
void						ft_lldi(t_token **token, t_label **labels, int fd2);
void						ft_lfork(t_token **token, t_label **labels,
	int fd2);
void						ft_aff(t_token **token, int fd2);

#endif
