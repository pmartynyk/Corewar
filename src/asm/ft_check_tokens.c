/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbakhari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 17:24:04 by kbakhari          #+#    #+#             */
/*   Updated: 2019/05/24 17:24:06 by kbakhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

void		ft_validate_operations(t_token *cur)
{
	if (!ft_strequ(cur->value, "live") && !ft_strequ(cur->value, "zjmp") &&
		!ft_strequ(cur->value, "fork") && !ft_strequ(cur->value, "lfork") &&
		!ft_strequ(cur->value, "st") && !ft_strequ(cur->value, "sti") &&
		!ft_strequ(cur->value, "ld") && !ft_strequ(cur->value, "ldi") &&
		!ft_strequ(cur->value, "lld") && !ft_strequ(cur->value, "lldi") &&
		!ft_strequ(cur->value, "and") && !ft_strequ(cur->value, "or") &&
		!ft_strequ(cur->value, "xor") && !ft_strequ(cur->value, "add") &&
		!ft_strequ(cur->value, "sub") && !ft_strequ(cur->value, "aff"))
		ft_death("Bad line!");
}

void		ft_check_spaces(t_token *cur)
{
	int		i;
	char	*tmp;

	tmp = cur->value;
	i = -1;
	while (tmp[++i])
		if (tmp[i] == ' ' || tmp[i] == '\t')
			ft_death("Space in arg!");
	i = 0;
	if (cur->type == 2)
		i++;
	else
		i += cur->type == 5 ? 2 : 0;
	if (tmp[i] == '-' && (tmp[i + 1] == ' ' || tmp[i + 1] == '\t' ||
		tmp[i + 1] == '\n' || tmp[i + 1] == '\0'))
		ft_death("Bad argument!");
	if (tmp[i] == '-')
		i++;
	while (cur->type != 5 && cur->type != 6 && tmp[++i])
		if (!ft_isdigit(tmp[i]) || tmp[i] == '-')
			ft_death("Bad argument!");
}

void		ft_validate_tokens(t_token **tokens)
{
	t_token	*cur;
	int		i;

	cur = (*tokens);
	while (cur->next)
	{
		i = -1;
		if (cur->type == 0)
			ft_validate_operations(cur);
		else if (cur->type == 4)
		{
			while (cur->value[++i])
				if (cur->value[i] == '\n' || cur->value[i] == ' ' ||
					cur->value[i] == '\t')
					if (cur->value[i - 1] != LABEL_CHAR)
						ft_death("Bad label line!");
		}
		else
			ft_check_spaces(cur);
		cur = cur->next;
	}
}

void		ft_check_tokens(t_token **tokens)
{
	t_token	*cur;

	cur = (*tokens);
	while (cur->next)
	{
		if (ft_strchr(cur->value, SEPARATOR_CHAR))
			ft_death("Too many separators!");
		if (ft_strchr(cur->value, '+'))
			ft_death("No plusses here boi!");
		if (cur->type == 2 || cur->type == 5)
		{
			if (ft_strchr(cur->value + 1, DIRECT_CHAR) ||
				!ft_check_empty(cur->value + 1))
				ft_death("Error in token!");
			if (ft_strchr(cur->value + 2, LABEL_CHAR) ||
				!ft_check_empty(cur->value + 1))
				ft_death("Error in token!");
		}
		if (cur->type == 1)
			if (ft_strchr(cur->value + 1, 'r') ||
				!ft_check_empty(cur->value + 1))
				ft_death("Error in token!");
		cur = cur->next;
	}
}
