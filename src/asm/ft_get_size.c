/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbakhari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 05:51:55 by kbakhari          #+#    #+#             */
/*   Updated: 2019/05/11 05:51:56 by kbakhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

void		ft_identify_op(int *dir, char *str)
{
	g_byte_pos++;
	if (ft_strequ(str, "zjmp") || ft_strequ(str, "ldi") ||
		ft_strequ(str, "sti") || ft_strequ(str, "fork") ||
		ft_strequ(str, "lldi") || ft_strequ(str, "lfork"))
		*dir = 2;
	else
		*dir = 4;
	if (!ft_strequ(str, "live") && !ft_strequ(str, "zjmp") &&
		!ft_strequ(str, "fork") && !ft_strequ(str, "lfork"))
	{
		g_code_size++;
		g_byte_pos++;
	}
}

void		ft_get_size(t_token **tokens, t_label **labels)
{
	t_token	*token;
	t_label	*label;
	int		dir;

	token = *tokens;
	label = *labels;
	dir = 4;
	while (token->next)
	{
		if (token->type == 0)
			ft_identify_op(&dir, token->value);
		if (token->type == 1)
			g_byte_pos++;
		if (token->type == 2 || token->type == 5)
		{
			g_code_size += dir;
			g_byte_pos += dir;
		}
		if (token->type == 3 || token->type == 6)
			g_byte_pos += 2;
		if (token->type == 4)
			ft_find_lable(labels, token->value);
		token = token->next;
	}
}
