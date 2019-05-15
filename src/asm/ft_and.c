/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbakhari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 18:45:18 by kbakhari          #+#    #+#             */
/*   Updated: 2019/05/12 18:45:19 by kbakhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

static void		ft_and_4(t_token **token, t_label **labels, int **mass, int fd2)
{
	char		*res;

	res = ft_hex_conv((*mass)[0], (*mass)[1]);
	ft_write(fd2, &res, (*mass)[1]);
	g_byte_pos += (*mass)[1];
	if ((*token)->next)
		(*token) = (*token)->next;
	if ((*token)->type == 1)
		(*mass)[0] = ft_atoi((*token)->value + 1);
	else if ((*token)->type == 3)
		(*mass)[0] = ft_atoi((*token)->value);
	else if ((*token)->type == 2)
		(*mass)[0] = ft_atoi((*token)->value + 1);
	else if ((*token)->type == 5)
		(*mass)[0] = ft_get_label_val((*token)->value + 1, labels) -
	g_byte_pos + 2;
	else if ((*token)->type == 6)
		(*mass)[0] = ft_get_label_val((*token)->value, labels) -
	g_byte_pos + 2;
	else
		ft_death("Bad second argument for and!!!");
	if ((*token)->type == 1)
		(*mass)[1] = 1;
	else
		(*mass)[1] = (*token)->type == 2 || (*token)->type == 5 ? 4 : 2;
}

static void		ft_and_3(t_token **token, t_label **labels, int **mass, int fd2)
{
	char		*res;

	res = ft_hex_conv((*mass)[1] + 4, 1);
	ft_write(fd2, &res, 1);
	g_byte_pos++;
	if ((*token)->type == 1)
		(*mass)[0] = ft_atoi((*token)->value + 1);
	else if ((*token)->type == 3)
		(*mass)[0] = ft_atoi((*token)->value);
	else if ((*token)->type == 2)
		(*mass)[0] = ft_atoi((*token)->value + 1);
	else if ((*token)->type == 5)
		(*mass)[0] = ft_get_label_val((*token)->value + 1, labels) -
	g_byte_pos + 2;
	else if ((*token)->type == 6)
		(*mass)[0] = ft_get_label_val((*token)->value, labels) -
	g_byte_pos + 2;
	else
		ft_death("Bad first argument for and!!!");
	if ((*token)->type == 1)
		(*mass)[1] = 1;
	else if ((*token)->type == 2 || (*token)->type == 5)
		(*mass)[1] = 4;
	else
		(*mass)[1] = 2;
}

static void		ft_and_2(t_token **token, int **mass, int fd2)
{
	char		*res;

	res = ft_hex_conv(6, 1);
	ft_write(fd2, &res, 1);
	g_byte_pos++;
	if ((*token)->next)
		(*token) = (*token)->next;
	if ((*token)->type == 1)
		(*mass)[1] += 64;
	else if ((*token)->type == 2 || (*token)->type == 5)
		(*mass)[1] += 128;
	else
		(*mass)[1] += 192;
	if ((*token)->next->type == 1)
		(*mass)[1] += 16;
	else if ((*token)->next->type == 2 || (*token)->next->type == 5)
		(*mass)[1] += 32;
	else
		(*mass)[1] += 48;
}

void			ft_and(t_token **token, t_label **labels, int fd2)
{
	char		*res;
	int			*mass;

	mass = (int *)ft_memalloc(sizeof(int) * 2);
	ft_and_2(token, &mass, fd2);
	ft_and_3(token, labels, &mass, fd2);
	ft_and_4(token, labels, &mass, fd2);
	res = ft_hex_conv(mass[0], mass[1]);
	ft_write(fd2, &res, mass[1]);
	g_byte_pos += mass[1];
	if ((*token)->next)
		(*token) = (*token)->next;
	if ((*token)->type != 1)
		ft_death("Bad third argument for and!!!");
	mass[0] = ft_atoi((*token)->value + 1);
	if (mass[0] > 99 || mass[0] < 0)
		ft_death("Bad register!!!");
	res = ft_hex_conv(mass[0], 1);
	ft_write(fd2, &res, 1);
	g_byte_pos++;
	free(mass);
}
