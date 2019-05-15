/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   something_useful.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkremen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 11:41:52 by vkremen           #+#    #+#             */
/*   Updated: 2019/04/25 11:41:54 by vkremen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

/*
**	Вывода ошибок и прекращения работы программы
*/

void			error_management(char *error)
{
	ft_printf("%s", error);
	exit(0);
}

/*
**	Перевод битов в обратном порядке
*/

void			reverse_bits(void *b, int len)
{
	int			step;
	char		*tmptmp;
	char		tmp;

	step = -1;
	tmptmp = (char *)b;
	while (++step < len / 2)
	{
		tmp = tmptmp[step];
		tmptmp[step] = tmptmp[len - step - 1];
		tmptmp[len - step - 1] = tmp;
	}
}

/*
**	Возвращения порядкового номера игрока, если номер был явно указан
*/

int				return_bot_id(char *param)
{
	int			res;
	int			step;

	step = -1;
	while (param[++step])
		if (!ft_isdigit(param[step]))
			error_management("ERROR: invalid params for id player!\n");
	if (ft_atoi(param) > INT_MAX)
		error_management("ERROR: invalid params for id player!\n");
	res = ft_atoi(param);
	if (res < 1 || res > MAX_PLAYERS || (res == g_id_players[0] ||
		res == g_id_players[1] || res == g_id_players[2] ||
		res == g_id_players[3]))
		error_management("ERROR: invalid params for id player!\n");
	g_id_players[res - 1] = res;
	return (res);
}

/*
**	Возвращает абсолютное значение
*/

int				abs(int number)
{
	if (number < 0)
		return (number * -1);
	return (number);
}

void			modify_field(t_vmka **vmka, int place, unsigned char *value,
								int *mass)
{
	int			step;

	step = -1;
	while (++step < mass[0])
	{
		(*vmka)->field[(place + step) % MEM_SIZE].place = value[step];
		(*vmka)->field[(place + step) % MEM_SIZE].id_bot = mass[1];
	}
}
