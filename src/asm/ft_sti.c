/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbakhari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 19:45:36 by kbakhari          #+#    #+#             */
/*   Updated: 2019/05/12 19:45:37 by kbakhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

static void		ft_sti_4(t_token **token, t_label **labels, int *n)
{
	if ((*token)->next)
		(*token) = (*token)->next;
	if ((*token)->type == 1)
		(*n) = ft_atoi((*token)->value + 1);
	else if ((*token)->type == 2)
		(*n) = ft_atoi((*token)->value + 1);
	else if ((*token)->type == 5)
		(*n) = ft_get_label_val((*token)->value + 1, labels) - g_byte_pos + 4;
	else
		ft_death("Bad third argument for sti!!!");
}

static void		ft_sti_3(t_token **token, t_label **labels, int *n, int fd2)
{
	char		*res;

	if ((*token)->type != 1)
		ft_death("Bad first argument for sti!!!");
	(*n) = ft_atoi((*token)->value + 1);
	if ((*n) > 99 || (*n) < 0)
		ft_death("Bad register!!!");
	res = ft_hex_conv((*n), 1);
	ft_write(fd2, &res, 1);
	g_byte_pos++;
	if ((*token)->next)
		(*token) = (*token)->next;
	if ((*token)->type == 1)
		(*n) = ft_atoi((*token)->value + 1);
	else if ((*token)->type == 3)
		(*n) = ft_atoi((*token)->value);
	else if ((*token)->type == 2)
		(*n) = ft_atoi((*token)->value + 1);
	else if ((*token)->type == 5)
		(*n) = ft_get_label_val((*token)->value + 1, labels) - g_byte_pos + 3;
	else if ((*token)->type == 6)
		(*n) = ft_get_label_val((*token)->value, labels) - g_byte_pos + 3;
	else
		ft_death("Bad second argument for sti!!!");
}

static void		ft_sti_2(t_token **token, int fd2, int *tmp)
{
	char		*res;

	res = ft_hex_conv(11, 1);
	ft_write(fd2, &res, 1);
	g_byte_pos++;
	if ((*token)->next)
		(*token) = (*token)->next;
	if ((*token)->next->type == 1)
		(*tmp) += 16;
	else if ((*token)->next->type == 2 || (*token)->next->type == 5)
		(*tmp) += 32;
	else
		(*tmp) += 48;
	if ((*token)->next->next->type == 1)
		(*tmp) += 4;
	else
		(*tmp) += 8;
	res = ft_hex_conv((*tmp), 1);
	ft_write(fd2, &res, 1);
	g_byte_pos++;
}

void			ft_sti(t_token **token, t_label **labels, int fd2)
{
	char		*res;
	int			n;
	int			tmp;

	n = 0;
	tmp = 64;
	ft_sti_2(token, fd2, &tmp);
	ft_sti_3(token, labels, &n, fd2);
	tmp = (*token)->type == 1 ? 1 : 2;
	res = ft_hex_conv(n, tmp);
	ft_write(fd2, &res, tmp);
	g_byte_pos += tmp;
	ft_sti_4(token, labels, &n);
	tmp = (*token)->type == 1 ? 1 : 2;
	res = ft_hex_conv(n, tmp);
	ft_write(fd2, &res, tmp);
	g_byte_pos += tmp;
}
