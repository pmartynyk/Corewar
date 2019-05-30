/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkremen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 13:59:42 by vkremen           #+#    #+#             */
/*   Updated: 2019/04/30 13:59:44 by vkremen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

/*
**	Сортировка игроков по возрастанию их порядковых номеров
*/

static void		sort_bot(t_vmka **vmka, int step)
{
	t_bot		*tmp;

	while (++step < g_count_bot)
	{
		if ((*vmka)->bot[step]->id_bot > (*vmka)->bot[step + 1]->id_bot)
		{
			tmp = (*vmka)->bot[step];
			(*vmka)->bot[step] = (*vmka)->bot[step + 1];
			(*vmka)->bot[step + 1] = tmp;
			step = -1;
		}
	}
	(*vmka)->nbr_carr = g_count_bot + 1;
	(*vmka)->nbr_players = g_count_bot + 1;
}

/*
**	Присвоение игрокам порядковых номеров
*/

static void		get_id_bot(t_vmka **vmka, int step)
{
	while (++step < MAX_PLAYERS)
	{
		if (!(*vmka)->bot[step]->id_bot && !g_id_players[0])
		{
			(*vmka)->bot[step]->id_bot = 1;
			g_id_players[0] = 1;
		}
		else if (!(*vmka)->bot[step]->id_bot && !g_id_players[1])
		{
			(*vmka)->bot[step]->id_bot = 2;
			g_id_players[1] = 2;
		}
		else if (!(*vmka)->bot[step]->id_bot && !g_id_players[2])
		{
			(*vmka)->bot[step]->id_bot = 3;
			g_id_players[2] = 3;
		}
		else if (!(*vmka)->bot[step]->id_bot && !g_id_players[3])
		{
			(*vmka)->bot[step]->id_bot = 4;
			g_id_players[3] = 4;
		}
	}
	sort_bot(vmka, -1);
}

/*
**	Парсинг флага -n
*/

static void		pars_flag_n(int argc, char **argv, t_vmka **vmka, int *i)
{
	if ((*i) + 2 >= argc || !ft_strstr(argv[(*i) + 2], ".cor"))
		error_management("ERROR: invalid params!\n");
	if (g_count_bot > MAX_PLAYERS - 1)
		error_management("ERROR: too much players!\n");
	g_count_bot++;
	(*vmka)->bot[g_count_bot]->id_bot = return_bot_id(argv[(*i) + 1]);
	(*i) += 2;
	add_bot_to_battle(argv[(*i)], &(*vmka)->bot[g_count_bot]);
}

/*
**	Парсинг флага -dump
*/

static void		pars_flag_dump(int argc, char **argv, t_vmka **vmka, int *i)
{
	int			index;

	if ((*vmka)->visual)
		error_management("ERROR: don't use -dump/-dump64 with -v!\n");
	if ((*i) + 1 >= argc || (*vmka)->dump_cycles > 0)
		error_management("ERROR: invalid number of cycles1!\n");
	index = 0;
	while (argv[(*i) + 1][index])
	{
		if (argv[(*i) + 1][index] >= '0' && argv[(*i) + 1][index] <= '9')
			index++;
		else
			error_management("ERROR: invalid number of cycles!\n");
	}
	if (ft_atoi(argv[(*i) + 1]) > INT_MAX || argv[(*i) + 1] < 0)
		error_management("ERROR: invalid number of cycles!\n");
	if (!(*vmka)->octet_dump && !ft_strcmp(argv[(*i)], "-dump"))
		(*vmka)->octet_dump = 32;
	else if (!(*vmka)->octet_dump && !ft_strcmp(argv[(*i)], "-dump64"))
		(*vmka)->octet_dump = 64;
	else
		error_management("ERROR: don't use -dump with -dump64!\n");
	(*vmka)->dump_cycles = ft_atoi(argv[(*i) + 1]);
	(*i) += 1;
}

/*
**	Парсинг параметров заданых пользователем
*/

void			parsing_argv_params(int argc, char **argv, t_vmka **vmka, int i)
{
	while (++i < argc)
	{
		if (!ft_strcmp(argv[i], "-dump") || !ft_strcmp(argv[i], "-dump64"))
			pars_flag_dump(argc, argv, vmka, &i);
		else if (!ft_strcmp(argv[i], "-n"))
			pars_flag_n(argc, argv, vmka, &i);
		else if (ft_strstr(argv[i], ".cor"))
		{
			g_count_bot++;
			if (g_count_bot > MAX_PLAYERS - 1)
				error_management("ERROR: too much players!\n");
			add_bot_to_battle(argv[i], &(*vmka)->bot[g_count_bot]);
		}
		else if (!ft_strcmp(argv[i], "-v") && !(*vmka)->visual)
		{
			if ((*vmka)->dump_cycles > 0)
				error_management("ERROR: don't use -v with -dump!\n");
			(*vmka)->visual = 1;
		}
		else
			error_management("ERROR: unknown type of data!\n");
	}
	get_id_bot(vmka, -1);
}
