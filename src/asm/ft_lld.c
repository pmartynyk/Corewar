/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbakhari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 20:07:01 by kbakhari          #+#    #+#             */
/*   Updated: 2019/05/12 20:07:03 by kbakhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

static void		ft_lld_3(t_token **token, int **mass, int fd2)
{
	char		*res;

	res = ft_hex_conv((*mass)[1], (*mass)[0]);
	ft_write(fd2, &res, (*mass)[0]);
	g_byte_pos += (*mass)[0];
	if ((*token)->next)
		(*token) = (*token)->next;
	if ((*token)->type != 1)
		ft_death("Bad second argument for lld!!!");
	(*mass)[1] = ft_atoi((*token)->value + 1);
	if ((*mass)[1] > 99 || (*mass)[1] < 0)
		ft_death("Bad register!!!");
	res = ft_hex_conv((*mass)[1], 1);
	ft_write(fd2, &res, 1);
	g_byte_pos++;
}

static void		ft_lld_2(t_token **token, t_label **labels, int **mass, int fd2)
{
	char		*res;

	res = ft_hex_conv((*mass)[0], 1);
	ft_write(fd2, &res, 1);
	g_byte_pos++;
	if ((*token)->type == 3)
		(*mass)[1] = ft_atoi((*token)->value);
	else if ((*token)->type == 2)
		(*mass)[1] = ft_atoi((*token)->value + 1);
	else if ((*token)->type == 5)
		(*mass)[1] = ft_get_label_val((*token)->value + 1, labels) -
	g_byte_pos + 2;
	else if ((*token)->type == 6)
		(*mass)[1] = ft_get_label_val((*token)->value, labels) - g_byte_pos + 2;
	else
		ft_death("Bad first argument for lld!!!");
	if ((*token)->type == 2 || (*token)->type == 5)
		(*mass)[0] = 4;
	else
		(*mass)[0] = 2;
}

void			ft_lld(t_token **token, t_label **labels, int fd2)
{
	char		*res;
	int			*mass;

	mass = (int *)ft_memalloc(sizeof(int) * 2);
	mass[0] = 16;
	res = ft_hex_conv(13, 1);
	ft_write(fd2, &res, 1);
	g_byte_pos++;
	if ((*token)->next)
		(*token) = (*token)->next;
	if ((*token)->type == 2 || (*token)->type == 5)
		mass[0] += 128;
	else
		mass[0] += 192;
	ft_lld_2(token, labels, &mass, fd2);
	ft_lld_3(token, &mass, fd2);
	free(mass);
}
