/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartyny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 17:40:19 by pmartyny          #+#    #+#             */
/*   Updated: 2019/05/07 17:40:27 by pmartyny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void			aff(t_vmka **vmka, t_carr *carr)
{
	int			number;

	reg_num(vmka, carr, 1, &number);
	ft_printf("Aff: %c\n", (char)(carr->reg_carr[number - 1]));
}

void			forkk(t_vmka **vmka, t_carr *carr)
{
	t_carr		*new_carr;
	int			place;

	value(vmka, (carr->poss_carr + 1) % MEM_SIZE,
		g_oper[carr->oper - 1].dir_size, &place);
	if (carr->oper == 0x0C)
		place %= IDX_MOD;
	new_carr = (t_carr *)ft_memalloc(sizeof(t_carr));
	ft_memcpy(new_carr, carr, sizeof(t_carr));
	new_carr->id_carr = ++(*vmka)->nbr_carr;
	new_carr->carr_color = carr->carr_color;
	new_carr->poss_carr = (MEM_SIZE + (new_carr->poss_carr + place) %
		MEM_SIZE) % MEM_SIZE;
	new_carr->next = (*vmka)->carr;
	(*vmka)->carr = new_carr;
}

void			ld(t_vmka **vmka, t_carr *carr)
{
	int			number;
	int			var;

	reg_num(vmka, carr, 2, &number);
	if (carr->args_type[0] == DIR_CODE)
		value(vmka, return_arg(carr, 1), REG_SIZE, &var);
	else
		var = ind(vmka, carr, 1, REG_SIZE);
	carr->reg_carr[number - 1] = var;
	if (var == 0)
		carr->carry = 1;
	else
		carr->carry = 0;
}

void			ldi(t_vmka **vmka, t_carr *carr)
{
	int			number;
	int			mass[2];
	int			address;
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
	address = mass[0] + mass[1];
	address = carr->oper == 0x0A ? address % IDX_MOD : address;
	address = (MEM_SIZE + (carr->poss_carr + address) % MEM_SIZE) % MEM_SIZE;
	value(vmka, address, 4, &carr->reg_carr[number - 1]);
	if (carr->oper == 0x0E)
		carr->carry = carr->reg_carr[number - 1] == 0 ? 1 : 0;
}
