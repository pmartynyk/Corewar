/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utilities3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbakhari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 16:46:35 by kbakhari          #+#    #+#             */
/*   Updated: 2019/05/14 16:46:37 by kbakhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

void		ft_check_separators(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == SEPARATOR_CHAR)
		{
			while (str[++i] == ' ' || str[i] == '\t' ||
				str[i] == SEPARATOR_CHAR)
				if (str[i] == SEPARATOR_CHAR)
					ft_death("Too many separators!");
		}
	}
}

void		ft_check_digit(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '-')
			;
		else if (str[i] == ' ' || str[i] == '\t')
			;
		else if (!ft_isdigit(str[i]))
			ft_death("Bad argument!");
	}
}
