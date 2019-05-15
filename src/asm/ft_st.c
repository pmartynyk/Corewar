/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbakhari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 10:44:08 by kbakhari          #+#    #+#             */
/*   Updated: 2019/05/11 10:44:13 by kbakhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

static void		ft_st_2(t_token **token, char *res, int fd2, int n)
{
	g_byte_pos++;
	res = ft_hex_conv(3, 1);
	ft_write(fd2, &res, 1);
	if ((*token)->next)
		(*token) = (*token)->next;
	if ((*token)->next->type == 1)
		res = ft_hex_conv(80, 1);
	else
		res = ft_hex_conv(112, 1);
	ft_write(fd2, &res, 1);
	g_byte_pos++;
	if ((*token)->type != 1)
		ft_death("Bad argument for st!!!");
	n = ft_atoi((*token)->value + 1);
	if (n > 99 || n < 0)
		ft_death("Bad register!!!");
	res = ft_hex_conv(n, 1);
	ft_write(fd2, &res, 1);
	g_byte_pos++;
	if ((*token)->next)
		(*token) = (*token)->next;
	if ((*token)->type != 1 && (*token)->type != 3 &&
		(*token)->type != 6)
		ft_death("Bad argument for st!!!");
}

void			ft_st(t_token **token, t_label **labels, int fd2)
{
	char		*res;
	int			n;

	ft_st_2(token, NULL, fd2, 0);
	if ((*token)->type == 1)
	{
		n = ft_atoi((*token)->value + 1);
		if (n > 99 || n < 0)
			ft_death("Bad register!!!");
	}
	else if ((*token)->type == 3)
		n = ft_atoi((*token)->value);
	else
	{
		n = ft_get_label_val((*token)->value, labels);
		n = n - g_byte_pos + 3;
	}
	g_byte_pos += ((*token)->type == 1 ? 1 : 2);
	res = ft_hex_conv(n, ((*token)->type == 1 ? 1 : 2));
	ft_write(fd2, &res, ((*token)->type == 1 ? 1 : 2));
}
