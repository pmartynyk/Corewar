/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkremen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 12:39:09 by vkremen           #+#    #+#             */
/*   Updated: 2019/05/09 10:50:02 by oandrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# define MIN_BOT_SIZE (4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH + 4)
# define MAX_BOT_SIZE (MIN_BOT_SIZE + CHAMP_MAX_SIZE)
# define MAX_BIT 2147483648
# define WAV_PATH "Eminem - Rap God.mp3"
# define MUS_PATH "HR2_Friska.ogg"

# include "../libft/libft.h"
# include "op.h"
# include <stdio.h>
# include <stdint.h>
# include <stdbool.h>
# include <limits.h>
# include <ncurses.h>
# include <unistd.h>
# include <SDL.h>
# include <SDL_mixer.h>

Mix_Chunk *g_wave;
Mix_Music *g_music;

/*
**	Структура игроков (скорее всего ещё дополнять нужно будет)
**	id_bot - порядковый номер игрока
**	code_size - размер кода игрока в байтах
**	name - имя игрока
**	comment - комментарий игрока
**	code - выполняемый код игрока
*/

typedef struct			s_bot
{
	int					id_bot;
	int					code_size;
	char				*name;
	char				*comment;
	unsigned char		*code;
}						t_bot;

/*
**	Структура поля
**	place - размещение выполняемого кода игрока на поле
**	id_bot - порядковый номер игрока
*/

typedef struct			s_battlefield
{
	unsigned char		place;
	int					id_bot;
}						t_batfield;

/*
**	Структура кареток (скорее всего ещё дополнять нужно будет)
**	id_carr - порядковый номер каретки
**	carry - переменная, которая влияет на работу функции zjmp
**	poss_carr - текущая позиция каретки
**	last_live - цикл, в котором в последний раз была выполнена операция live
**	reg_carr - регист игрока с отрицательным знаком, на коде игрока на
**	котором стоит каретка
*/

typedef struct			s_carriages
{
	int					id_carr;
	int					carr_color;
	bool				carry;
	int					stay;
	int					poss_carr;
	int					last_live;
	int					reg_carr[REG_NUMBER];
	int					iter_to_wait;
	unsigned char		args_type[3];
	unsigned char		args_size[3];
	unsigned char		oper;
	struct s_carriages	*next;
	struct s_carriages	*prev;
}						t_carr;

/*
**	Структура виртуалки
**	t_bot - массив структур игроков
**	t_field - указатель на структуру арены
**	t_carr - указатель на структуру кареток
**	nbr_cycles - количество цыклов, посе которых прекратить
**	игру (если была задана)
**	nbr_carr - количество кареток
**	nbr_players - количество игроков
**	visual - флаг для визуализации
**	cycles - количество выполнених циклов
**	lives - количество выполненых операций live
*/

typedef struct			s_vmka
{
	t_bot				**bot;
	t_batfield			*field;
	t_carr				*carr;
	int					visual;
	int					dump_cycles;
	int					cycles_to_die;
	int					nbr_carr;
	int					nbr_players;
	int					speed;
	int					cycles;
	int					lives;
	int					last_alive;
}						t_vmka;

/*
**	Структура операций
**	name - имя операции
**	code - порядковый номер аргумента
**	args_num - максимальное количество принимаемых аргументов
**	types - включает ли байткод код типа аргумента
**	args_types - типы аргументов
**	dir_size - размер T_DIR аргумента
*/

typedef struct			s_oper
{
	char				*name;
	unsigned char		code;
	unsigned char		args_num;
	unsigned char		types;
	unsigned char		args_types[3];
	unsigned char		dir_size;
	int					wait;
}						t_oper;

/*
**	g_id_players - Переменная для определения порядковых номеров игроков
**	g_count_bot - Переменная подсчёта игроков
**	g_oper - Переменная операций
*/

int						*g_id_players;
int						g_count_bot;
t_oper					g_oper[16];

/*
** parsing_bot.c
*/

void					parsing_argv_params(int argc, char **argv,
								t_vmka **vmka, int i);

/*
** init.c
*/

void					init_vm(t_vmka **vmka, int i);
void					init_field(t_vmka **vmka, int i, int j);
void					init_carriages(t_vmka **vmka, int step);

/*
** add_bot.c
*/

void					add_bot_to_battle(char *bot_file, t_bot **bot);

/*
** something_useful.c
*/

void					error_management(char *error);
void					reverse_bits(void *b, int len);
int						return_bot_id(char *param);
int						abs(int number);
void					modify_field(t_vmka **vmka, int place,
								unsigned char *value, int *mass);

/*
** start_fight.c
*/

void					start_fight(t_vmka **vmka);

/*
** start_fight_2.c
*/

void					start_fight_2(t_vmka **vmka);

/*
** visual.c visual2.c visual3.c
*/

void					visual(t_vmka **all);
void					fill_info(t_vmka *all, WINDOW **info, int i);
void					config(t_vmka **all, int key);
void					fill_winner(t_vmka *all);
int						last_live(t_carr *all, int id);
int						count_live(t_carr *all, int id);

/*
** operations_1.c
*/

void					live(t_vmka **vmka, t_carr *carr);
void					st(t_vmka **vmka, t_carr *carr);
void					sti(t_vmka **vmka, t_carr *carr);
void					zjmp(t_vmka **vmka, t_carr *carr);
void					add_sub(t_vmka **vmka, t_carr *carr);

/*
** operations_2.c
*/

void					aff(t_vmka **vmka, t_carr *carr);
void					forkk(t_vmka **vmka, t_carr *carr);
void					ld(t_vmka **vmka, t_carr *carr);
void					ldi(t_vmka **vmka, t_carr *carr);

/*
** operations_3.c
*/

void					and_or_xor(t_vmka **vmka, t_carr *carr);

static void		(*g_op[16])() = {&live, &ld, &st, &add_sub,
	&add_sub, &and_or_xor, &and_or_xor, &and_or_xor, &zjmp,
	&ldi, &sti, &forkk, &ld, &ldi, &forkk, &aff};

/*
** utils_for_oper.c
*/

void					value(t_vmka **vmka, int start_pos, int dir_size,
								int *arg);
int						ind(t_vmka **vmka, t_carr *carr, int step, int size);
void					reg_num(t_vmka **vmka, t_carr *carr, int arg, int *res);
int						return_arg(t_carr *carr, int size);
void					sti_2(t_vmka **vmka, t_carr *carr, int *address);

#endif
