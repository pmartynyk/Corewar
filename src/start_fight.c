/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_fight.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartyny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 13:24:46 by pmartyny          #+#    #+#             */
/*   Updated: 2019/05/07 05:01:08 by oandrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

static void		return_reg(t_vmka **vmka, t_carr *carr, int i, int *res)
{
	int			index;
	int			step;

	index = -1;
	step = 1 + g_oper[carr->oper - 1].types;
	while (++index < i)
		step += carr->args_size[index];
	if ((*vmka)->field[(carr->poss_carr + step) % MEM_SIZE].place <= 0 ||
		(*vmka)->field[(carr->poss_carr + step) % MEM_SIZE].place > REG_NUMBER)
		(*res) = 0;
}

static int		check_oper(t_vmka **vmka, t_carr *carr, int i, int j)
{
	int			code;
	int			res;

	res = 1;
	code = (*vmka)->field[(carr->poss_carr + 1) % MEM_SIZE].place;
	while (++i < g_oper[carr->oper - 1].args_num)
	{
		carr->args_type[i] = (code >> j) % 4;
		if (carr->args_type[i] == REG_CODE)
		{
			carr->args_size[i] = REG_CODE;
			return_reg(vmka, carr, i, &res);
		}
		else if (carr->args_type[i] == DIR_CODE)
			carr->args_size[i] = g_oper[carr->oper - 1].dir_size;
		else if (carr->args_type[i] == IND_CODE)
			carr->args_size[i] = IND_SIZE;
		if (!((g_oper[carr->oper - 1].args_types[i] >>
			(carr->args_type[i] - 1)) & 1))
			res = 0;
		j -= 2;
	}
	return (res);
}

static void		make_oper_or_skip(t_vmka **vmka, t_carr *carr, int step)
{
	if (g_oper[carr->oper - 1].types)
	{
		if (check_oper(vmka, carr, -1, 6))
			(*g_op[carr->oper - 1])(vmka, carr);
	}
	else
		(*g_op[carr->oper - 1])(vmka, carr);
	if (carr->stay)
	{
		carr->stay = 0;
		return ;
	}
	if (g_oper[carr->oper - 1].types)
		carr->poss_carr += 2;
	else
		carr->poss_carr += g_oper[carr->oper - 1].dir_size + 1;
	while (++step < g_oper[carr->oper - 1].args_num &&
		g_oper[carr->oper - 1].types)
		carr->poss_carr += carr->args_size[step];
	carr->poss_carr %= MEM_SIZE;
}

static void		get_oper(t_carr *tmp, unsigned char place)
{
	tmp->oper = place;
	if (place >= 0x01 && place <= 0x10)
		tmp->iter_to_wait = g_oper[place - 1].wait;
}

void			start_fight(t_vmka **vmka)
{
	t_carr		*tmp;

	while (1)
	{
		tmp = (*vmka)->carr;
		while (tmp)
		{
			if (!tmp->iter_to_wait)
				get_oper(tmp, (*vmka)->field[tmp->poss_carr].place);
			if (tmp->iter_to_wait > 0)
				tmp->iter_to_wait--;
			if (!tmp->iter_to_wait)
			{
				if (tmp->oper >= 0x01 && tmp->oper <= 0x10)
				{
					ft_bzero(tmp->args_size, 3);
					make_oper_or_skip(vmka, tmp, -1);
				}
				else
					tmp->poss_carr = (tmp->poss_carr + 1) % MEM_SIZE;
			}
			tmp = tmp->next;
		}
		start_fight_2(vmka);
	}
}
