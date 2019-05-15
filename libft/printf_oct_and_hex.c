/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_oct_and_hex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkremen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 16:25:47 by vkremen           #+#    #+#             */
/*   Updated: 2019/01/17 16:25:49 by vkremen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	pritf_flag_zero_oct_hex(char *num, t_struct_d x)
{
	int		step;

	if ((int)ft_strlen(num) > x.width && (int)ft_strlen(num) > x.prec)
	{
		(num[0] == '0' && x.prec == 0 ? 0 : fill_buff(num));
		return ;
	}
	step = -1;
	if ((int)ft_strlen(num) > x.prec)
		while (++step < x.width - (int)ft_strlen(num))
			(x.zero == '0' ? fill_buff("0") : fill_buff(" "));
	else
		while (++step < x.width - x.prec)
			fill_buff(" ");
	step = -1;
	while (++step < x.prec - (int)ft_strlen(num))
		fill_buff("0");
	(num[0] == '0' && x.prec == 0 ? fill_buff(" ") : fill_buff(num));
}

void	printf_other_flags_oct(char *num, t_struct_d x)
{
	int step;

	if ((int)ft_strlen(num) > x.width && (int)ft_strlen(num) > x.prec)
	{
		if ((x.width == 0 || x.prec == 0) && num[0] == '0')
			return ;
		(x.sh == '#' && num[0] != '0' ? fill_buff("0") : 0);
		fill_buff(num);
		return ;
	}
	step = -1;
	if ((int)ft_strlen(num) > x.prec)
		while (++step < x.width - (int)ft_strlen(num) - 1)
			(x.prec == -1 ? fill_buff("0") : fill_buff(" "));
	else
		while (++step < x.width - x.prec)
			fill_buff(" ");
	step = 0;
	while (++step < x.prec - (int)ft_strlen(num))
		fill_buff("0");
	if (x.sh == '#')
		fill_buff("0");
	fill_buff(num);
}

void	printf_other_flags_hex_part_1(char *num, t_struct_d x, char *fl)
{
	int step;

	if ((int)ft_strlen(num) > x.width && (int)ft_strlen(num) > x.prec)
	{
		if ((x.width == 0 || x.prec == 0) && num[0] == '0')
			return ;
		(x.sh == '#' && num[0] != '0' ? fill_buff(ft_strjoin("0", fl)) : 0);
		fill_buff(num);
		return ;
	}
	printf_other_flags_hex_part_2(num, x, fl);
	step = -1;
	while (++step < x.prec - (int)ft_strlen(num))
		fill_buff("0");
	fill_buff(num);
}

void	printf_other_flags_hex_part_2(char *num, t_struct_d x, char *fl)
{
	int		step;

	step = 1;
	if ((int)ft_strlen(num) > x.prec && x.prec < 0)
	{
		(x.sh == '#' && num[0] != '0' ? fill_buff(ft_strjoin("0", fl)) : 0);
		while (++step < x.width - (int)ft_strlen(num))
			fill_buff("0");
	}
	else
	{
		while (++step < x.width - x.prec - 2)
			fill_buff(" ");
		(x.sh == '#' && num[0] != '0' ? fill_buff(ft_strjoin("0", fl)) : 0);
	}
}
