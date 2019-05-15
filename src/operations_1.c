/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartyny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 11:13:49 by pmartyny          #+#    #+#             */
/*   Updated: 2019/05/07 11:13:51 by pmartyny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		live(t_vmka **vmka, t_carr *carr)
{
	int		arg;

	value(vmka, (carr->poss_carr + 1) % MEM_SIZE,
		g_oper[carr->oper - 1].dir_size, &arg);
	if (arg < 0 && abs(arg) <= (*vmka)->nbr_players)
		(*vmka)->last_alive = abs(arg);
	carr->last_live = (*vmka)->cycles;
	(*vmka)->lives++;
}

void		st(t_vmka **vmka, t_carr *carr)
{
	int		number;
	int		val;
	int		place;
	int		mass[2];

	reg_num(vmka, carr, 1, &number);
	val = carr->reg_carr[number - 1];
	if (carr->args_type[1] == REG_CODE)
	{
		reg_num(vmka, carr, 2, &place);
		carr->reg_carr[place - 1] = val;
	}
	else
	{
		value(vmka, return_arg(carr, 2), IND_SIZE, &place);
		place = (MEM_SIZE + (carr->poss_carr + place % IDX_MOD) %
			MEM_SIZE) % MEM_SIZE;
		reverse_bits(&val, 4);
		mass[0] = REG_SIZE;
		mass[1] = carr->carr_color;
		modify_field(vmka, place, (unsigned char *)(&val), mass);
	}
}

void		sti(t_vmka **vmka, t_carr *carr)
{
	int		number;
	int		val;
	int		address;
	int		res[2];

	reg_num(vmka, carr, 1, &number);
	val = carr->reg_carr[number - 1];
	sti_2(vmka, carr, &address);
	reverse_bits(&val, 4);
	res[0] = REG_SIZE;
	res[1] = carr->carr_color;
	modify_field(vmka, (MEM_SIZE + address) % MEM_SIZE,
		(unsigned char *)(&val), res);
}

void		zjmp(t_vmka **vmka, t_carr *carr)
{
	int		arg;
	int		tmp;

	value(vmka, (carr->poss_carr + 1) % MEM_SIZE,
		g_oper[carr->oper - 1].dir_size, &arg);
	if (carr->carry)
	{
		tmp = arg % IDX_MOD;
		carr->poss_carr = (MEM_SIZE + (carr->poss_carr + tmp) % MEM_SIZE) %
		MEM_SIZE;
		carr->stay = 1;
	}
}

void		add_sub(t_vmka **vmka, t_carr *carr)
{
	int		i;
	int		numb[3];
	int		add_sub;

	i = -1;
	while (++i < 3)
		reg_num(vmka, carr, i + 1, &numb[i]);
	if (carr->oper == 0x04)
		add_sub = carr->reg_carr[numb[0] - 1] + carr->reg_carr[numb[1] - 1];
	else
		add_sub = carr->reg_carr[numb[0] - 1] - carr->reg_carr[numb[1] - 1];
	carr->reg_carr[numb[2] - 1] = add_sub;
	if (add_sub == 0)
		carr->carry = 1;
	else
		carr->carry = 0;
}
