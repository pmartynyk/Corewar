/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbakhari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 20:12:01 by kbakhari          #+#    #+#             */
/*   Updated: 2019/05/12 20:12:02 by kbakhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

static void		ft_lfork_2(t_token **token, int *n)
{
	char		*tmp;

	tmp = (*token)->value;
	(*token)->value = ft_strsub((*token)->value, 1,
	(int)(ft_strlen((*token)->value) - 1));
	ft_strdel(&tmp);
	(*n) = ft_atoi((*token)->value);
}

void			ft_lfork(t_token **token, t_label **labels, int fd2)
{
	char	*res;
	int		n;

	n = 0;
	if ((*token)->next)
		(*token) = (*token)->next;
	g_byte_pos++;
	if ((*token)->type != 2 && (*token)->type != 5)
		ft_death("Bad argument for lfork!!!");
	if ((*token)->type == 2)
		ft_lfork_2(token, &n);
	else
	{
		n = ft_get_label_val((*token)->value + 1, labels);
		n = n - g_byte_pos + 1;
	}
	g_byte_pos += 2;
	res = ft_hex_conv(15, 1);
	ft_write(fd2, &res, 1);
	res = ft_hex_conv(n, 2);
	ft_write(fd2, &res, 2);
}
