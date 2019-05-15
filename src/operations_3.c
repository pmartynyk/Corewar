/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartyny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 18:29:00 by pmartyny          #+#    #+#             */
/*   Updated: 2019/05/07 18:29:04 by pmartyny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

static void		xor(int x, int y, int *res)
{
	unsigned int	tmp;

	(*res) = 0;
	tmp = MAX_BIT;
	while (tmp)
	{
		if ((x & tmp || y & tmp) && ((x & tmp) != (y & tmp)))
			(*res) += tmp;
		tmp >>= 1;
	}
}

static void		or(int x, int y, int *res)
{
	unsigned int	tmp;

	(*res) = 0;
	tmp = MAX_BIT;
	while (tmp)
	{
		if (x & tmp || y & tmp)
			(*res) += tmp;
		tmp >>= 1;
	}
}

static void		and(int x, int y, int *res)
{
	unsigned int	tmp;

	(*res) = 0;
	tmp = MAX_BIT;
	while (tmp)
	{
		if (x & tmp && y & tmp)
			(*res) += tmp;
		tmp >>= 1;
	}
}

void			and_or_xor(t_vmka **vmka, t_carr *carr)
{
	int			number;
	int			mass[2];
	int			step;
	int			tmp;

	reg_num(vmka, carr, 3, &number);
	step = -1;
	while (++step < 2)
		if (carr->args_type[step] == DIR_CODE)
			value(vmka, return_arg(carr, step + 1),
				g_oper[carr->oper - 1].dir_size, &mass[step]);
		else if (carr->args_type[step] == IND_CODE)
			mass[step] = ind(vmka, carr, step + 1, 4);
		else if (carr->args_type[step] == REG_CODE)
		{
			reg_num(vmka, carr, step + 1, &tmp);
			mass[step] = carr->reg_carr[tmp - 1];
		}
	if (carr->oper == 0x06)
		and(mass[0], mass[1], &carr->reg_carr[number - 1]);
	else if (carr->oper == 0x07)
		or(mass[0], mass[1], &carr->reg_carr[number - 1]);
	else
		xor(mass[0], mass[1], &carr->reg_carr[number - 1]);
	carr->carry = carr->reg_carr[number - 1] == 0 ? 1 : 0;
}
