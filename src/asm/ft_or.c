/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_or.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbakhari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 19:05:00 by kbakhari          #+#    #+#             */
/*   Updated: 2019/05/12 19:05:01 by kbakhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

void			ft_arg_2(int fd2, int tmp, t_token **token, t_label **labels)
{
	int			n;
	char		*res;

	n = 0;
	if ((*token)->next)
		(*token) = (*token)->next;
	if ((*token)->type == 1)
		n = ft_atoi((*token)->value + 1);
	else if ((*token)->type == 3)
		n = ft_atoi((*token)->value);
	else if ((*token)->type == 2)
		n = ft_atoi((*token)->value + 1);
	else if ((*token)->type == 5)
		n = ft_get_label_val((*token)->value + 1, labels) - g_byte_pos + 2;
	else if ((*token)->type == 6)
		n = ft_get_label_val((*token)->value, labels) - g_byte_pos + 2;
	else
		ft_death("Bad second argument for or!!!");
	if ((*token)->type == 1)
		tmp = 1;
	else
		tmp = (*token)->type == 2 || (*token)->type == 5 ? 4 : 2;
	res = ft_hex_conv(n, tmp);
	ft_write(fd2, &res, tmp);
	g_byte_pos += tmp;
}

void			ft_arg_1(int fd2, int tmp, t_token **token, t_label **labels)
{
	char		*res;
	int			n;

	n = 0;
	if ((*token)->type == 1)
		n = ft_atoi((*token)->value + 1);
	else if ((*token)->type == 3)
		n = ft_atoi((*token)->value);
	else if ((*token)->type == 2)
		n = ft_atoi((*token)->value + 1);
	else if ((*token)->type == 5)
		n = ft_get_label_val((*token)->value + 1, labels) - g_byte_pos + 2;
	else if ((*token)->type == 6)
		n = ft_get_label_val((*token)->value, labels) - g_byte_pos + 2;
	else
		ft_death("Bad first argument for or!!!");
	if ((*token)->type == 1)
		tmp = 1;
	else if ((*token)->type == 2 || (*token)->type == 5)
		tmp = 4;
	else
		tmp = 2;
	res = ft_hex_conv(n, tmp);
	ft_write(fd2, &res, tmp);
	g_byte_pos += tmp;
}

void			ft_size(int fd2, int tmp, t_token **token, char *res)
{
	if ((*token)->next)
		(*token) = (*token)->next;
	if ((*token)->type == 1)
		tmp += 64;
	else if ((*token)->type == 2 || (*token)->type == 5)
		tmp += 128;
	else
		tmp += 192;
	if ((*token)->next->type == 1)
		tmp += 16;
	else if ((*token)->next->type == 2 || (*token)->next->type == 5)
		tmp += 32;
	else
		tmp += 48;
	res = ft_hex_conv(tmp + 4, 1);
	ft_write(fd2, &res, 1);
	g_byte_pos++;
}

void			ft_or(t_token **token, t_label **labels, int fd2)
{
	char	*res;
	int		n;
	int		tmp;

	res = ft_hex_conv(7, 1);
	n = 0;
	ft_write(fd2, &res, 1);
	g_byte_pos++;
	tmp = 0;
	ft_size(fd2, tmp, token, res);
	ft_arg_1(fd2, tmp, token, labels);
	ft_arg_2(fd2, tmp, token, labels);
	if ((*token)->next)
		(*token) = (*token)->next;
	if ((*token)->type != 1)
		ft_death("Bad third argument for or!!!");
	n = ft_atoi((*token)->value + 1);
	if (n > 99 || n < 0)
		ft_death("Bad register!!!");
	res = ft_hex_conv(n, 1);
	ft_write(fd2, &res, 1);
	g_byte_pos++;
}
