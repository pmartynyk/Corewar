/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_oper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartyny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 14:51:41 by pmartyny          #+#    #+#             */
/*   Updated: 2019/05/07 14:51:42 by pmartyny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		value(t_vmka **vmka, int start_pos, int dir_size, int *arg)
{
	char	*str;
	int		i;

	i = -1;
	str = (char *)ft_memalloc(sizeof(char) * 4);
	while (++i < dir_size)
		str[i + dir_size % 4] =
	(*vmka)->field[(start_pos + i) % MEM_SIZE].place;
	if (str[2] >> 7 && dir_size == 2)
	{
		str[0] = -1;
		str[1] = -1;
	}
	ft_memcpy(&(*arg), str, 4);
	reverse_bits(&(*arg), 4);
	free(str);
}

int			ind(t_vmka **vmka, t_carr *carr, int step, int size)
{
	int		address;
	int		result;

	value(vmka, return_arg(carr, step), IND_SIZE, &address);
	if (carr->oper != 0x0D)
		address %= IDX_MOD;
	address = (MEM_SIZE + (carr->poss_carr + address) % MEM_SIZE) % MEM_SIZE;
	value(vmka, address, size, &result);
	return (result);
}

void		reg_num(t_vmka **vmka, t_carr *carr, int arg, int *res)
{
	int		step;
	int		jump;

	step = -1;
	jump = 1 + g_oper[carr->oper - 1].types;
	while (++step < arg - 1)
		jump += carr->args_size[step];
	(*res) = (*vmka)->field[(carr->poss_carr + jump) % MEM_SIZE].place;
}

int			return_arg(t_carr *carr, int size)
{
	int		step;
	int		jump;

	step = -1;
	jump = 1;
	while (++step < size - 1)
		jump += carr->args_size[step];
	jump++;
	return ((carr->poss_carr + jump) % MEM_SIZE);
}

void		sti_2(t_vmka **vmka, t_carr *carr, int *address)
{
	int		step;
	int		var;
	int		mass[2];

	step = -1;
	while (++step < 2)
		if (carr->args_type[step + 1] == DIR_CODE)
			value(vmka, return_arg(carr, step + 2),
				g_oper[carr->oper - 1].dir_size, &mass[step]);
		else if (carr->args_type[step + 1] == IND_CODE)
			mass[step] = ind(vmka, carr, step + 2, 4);
		else
		{
			reg_num(vmka, carr, step + 2, &var);
			mass[step] = carr->reg_carr[var - 1];
		}
	(*address) = carr->poss_carr + (mass[0] + mass[1]) % IDX_MOD;
}
