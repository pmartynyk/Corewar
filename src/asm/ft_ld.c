/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbakhari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 10:02:21 by kbakhari          #+#    #+#             */
/*   Updated: 2019/05/11 10:02:24 by kbakhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

static void		ft_ld_3(t_token **token, t_label **labels, int *n)
{
	char		*tmp;

	if ((*token)->type == 2)
	{
		tmp = (*token)->value;
		(*token)->value = ft_strsub((*token)->value, 1,
		(int)(ft_strlen((*token)->value) - 1));
		ft_strdel(&tmp);
		(*n) = ft_atoi((*token)->value);
	}
	else if ((*token)->type == 3)
		(*n) = ft_atoi((*token)->value);
	else
	{
		(*n) = ft_get_label_val((*token)->value + ((*token)->type == 6 ? 0 : 1),
			labels);
		(*n) = (*n) - g_byte_pos + 2;
	}
	g_byte_pos += (*token)->type == 2 || (*token)->type == 5 ? 4 : 2;
}

static void		ft_ld_2(t_token **token, int fd2)
{
	char		*res;

	g_byte_pos++;
	res = ft_hex_conv(2, 1);
	ft_write(fd2, &res, 1);
	if ((*token)->next)
		(*token) = (*token)->next;
	if ((*token)->type != 2 && (*token)->type != 5 &&
		(*token)->type != 3 && (*token)->type != 6)
		ft_death("Bad argument for ld!!!");
	if ((*token)->type != 2 && (*token)->type != 5)
		res = ft_hex_conv(208, 1);
	else
		res = ft_hex_conv(144, 1);
	ft_write(fd2, &res, 1);
	g_byte_pos++;
}

void			ft_ld(t_token **token, t_label **labels, int fd2)
{
	char	*res;
	int		n;

	n = 0;
	ft_ld_2(token, fd2);
	ft_ld_3(token, labels, &n);
	res = ft_hex_conv(n, (*token)->type == 2 || (*token)->type == 5 ? 4 : 2);
	ft_write(fd2, &res, (*token)->type == 2 || (*token)->type == 5 ? 4 : 2);
	if ((*token)->next)
		(*token) = (*token)->next;
	if ((*token)->type != 1)
		ft_death("Bad argument for ld!!!");
	n = ft_atoi((*token)->value + 1);
	if (n > 99 || n < 0)
		ft_death("Bad register!!!");
	res = ft_hex_conv(n, 1);
	ft_write(fd2, &res, 1);
	g_byte_pos++;
}
