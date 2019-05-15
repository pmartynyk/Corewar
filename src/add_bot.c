/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_bot.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkremen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 11:33:08 by vkremen           #+#    #+#             */
/*   Updated: 2019/04/25 11:33:10 by vkremen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

/*
**	Проверка на размер кода игрока с CHAMP_MAX_SIZE и запись исполняемого кода
*/

void				get_and_check_bot_code(char *bot_code, t_bot **bot,
									int num)
{
	int				step;

	ft_memcpy(&(*bot)->code_size, &bot_code[4 + PROG_NAME_LENGTH + 4], 4);
	reverse_bits(&(*bot)->code_size, 4);
	if ((*bot)->code_size < 0 || (*bot)->code_size > CHAMP_MAX_SIZE)
		error_management("ERROR: invalid champion code size!\n");
	step = -1;
	while (++step < (*bot)->code_size && step < num)
		(*bot)->code[step] = bot_code[MIN_BOT_SIZE + step];
}

/*
**	Запись имени и комментарий игрока
*/

static void			get_bot_name_and_comment(char *bot_code, t_bot **bot,
									int step)
{
	while (++step < PROG_NAME_LENGTH && bot_code[step + 4])
		(*bot)->name[step] = bot_code[step + 4];
	step = -1;
	while (++step < COMMENT_LENGTH && bot_code[step + PROG_NAME_LENGTH + 12])
		(*bot)->comment[step] = bot_code[step + PROG_NAME_LENGTH + 12];
}

/*
**	Проверка на соответствие магического хедера игрока с COREWAR_EXEC_MAGIC
*/

static void			check_magic_header(char *bot_code)
{
	int				bot_header;

	bot_header = (((bot_code[0] & 0xFF) << 24) | ((bot_code[1] & 0xFF) << 16)
	| ((bot_code[2] & 0xFF) << 8) | ((bot_code[3] & 0xFF)));
	if (bot_header != COREWAR_EXEC_MAGIC)
		error_management("ERROR: champion magic header is wrong!\n");
}

/*
**	Проверка названия файла и запись содержимого в bot_code
*/

static void			check_file_name(char *bot_file, char **bot_code, int *num)
{
	int				fd;

	if (bot_file[0] == '\0' || !ft_strcmp(bot_file, ".cor"))
		error_management("ERROR: incorrect champion name!\n");
	if (ft_strcmp(ft_strrchr(bot_file, '.'), ".cor"))
		error_management("ERROR: invalid file extension!\n");
	if ((fd = open(bot_file, O_RDONLY)) < 0)
		error_management("ERROR: this file doesn't exist!\n");
	if (((*num) = read(fd, (*bot_code), MAX_BOT_SIZE)) < 0)
		error_management("ERROR: unable to read file!\n");
	if ((*num) < MIN_BOT_SIZE || (*num) > MAX_BOT_SIZE)
		error_management("ERROR: wrong champion size!\n");
	close(fd);
}

/*
**	Добавление игрока в массив структур игроков
*/

void				add_bot_to_battle(char *bot_file, t_bot **bot)
{
	int				num;
	char			*bot_code;

	num = -1;
	bot_code = (char *)ft_memalloc(sizeof(char) * 5000);
	check_file_name(bot_file, &bot_code, &num);
	check_magic_header(bot_code);
	get_bot_name_and_comment(bot_code, bot, -1);
	get_and_check_bot_code(bot_code, bot, num);
	free(bot_code);
}
