/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utilities2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbakhari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 05:27:04 by kbakhari          #+#    #+#             */
/*   Updated: 2019/05/11 05:27:05 by kbakhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

char				*ft_destroy_comments(char *str)
{
	int				i;
	char			*tmp;

	if (ft_strchr(str, COMMENT_CHAR) ||
		ft_strchr(str, ALT_COMMENT_CHAR))
	{
		i = 0;
		tmp = str;
		while (tmp[i] != COMMENT_CHAR && tmp[i] != ALT_COMMENT_CHAR)
			i++;
		str = ft_strsub(tmp, 0, i);
		ft_strdel(&tmp);
	}
	ft_check_separators(str);
	return (str);
}

int					ft_get_label_val(char *str, t_label **labels)
{
	t_label			*label;

	label = *labels;
	while (label->next)
	{
		if (ft_strequ(str + 1, label->name))
			return (label->position);
		label = label->next;
	}
	ft_death("No label found");
	return (-1);
}

char				*ft_hex_conv(int32_t nbr, int size)
{
	unsigned int	tmp;
	int				i;
	unsigned int	max;
	char			*res;

	if (size == 1)
		max = 255;
	if (size == 2)
		max = 65535;
	if (size == 4)
		max = 4294967295;
	if (nbr < 0)
		tmp = max + nbr + 1;
	else
		tmp = nbr;
	res = ft_strnew(size);
	i = size;
	while (--i >= 0)
	{
		res[i] = tmp % 256;
		tmp /= 256;
	}
	return (res);
}

void				ft_find_lable(t_label **labels, char *str)
{
	t_label			*label;

	label = *labels;
	while (label->next)
	{
		if (ft_strequ(str, label->name))
			label->position = g_byte_pos;
		label = label->next;
	}
}

void				ft_free_mass(char **mass, int step)
{
	while (mass[++step] && mass[step][0] != '\0')
	{
		free(mass[step]);
		mass[step] = NULL;
	}
	free(mass);
	mass = NULL;
}
