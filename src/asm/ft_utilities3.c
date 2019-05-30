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

void		ft_validate_register(t_token **token)
{
	t_token	*cur;
	int		i;
	int		num;

	cur = (*token);
	num = 0;
	while (cur->next)
	{
		i = 0;
		if (cur->type == 1)
		{
			num = ft_atoi(&cur->value[1]);
			if (num > 99 || num < 0)
				ft_death("Bad register!");
			while (cur->value[++i])
				if (!ft_isdigit(cur->value[i]))
					ft_death("Bad register!");
		}
		cur = cur->next;
	}
}

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

int			ft_empty(char *line)
{
	int		i;

	i = 0;
	if (!line[1])
		return (1);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

void		ft_add_separators(char *line)
{
	int		i;
	char	*tmp;

	i = -1;
	if (line[0] == SEPARATOR_CHAR)
		ft_death("Bad separator!");
	tmp = ft_strrchr(line, ',');
	if (tmp)
		if (ft_empty(tmp))
			ft_death("Bad separator!");
}
