/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbakhari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 20:17:56 by kbakhari          #+#    #+#             */
/*   Updated: 2019/05/12 20:17:57 by kbakhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

void			ft_aff(t_token **token, int fd2)
{
	char	*res;
	char	*tmp;
	int		n;

	res = ft_hex_conv(16, 1);
	ft_write(fd2, &res, 1);
	g_byte_pos++;
	if ((*token)->next)
		(*token) = (*token)->next;
	g_byte_pos++;
	tmp = ft_hex_conv(64, 1);
	ft_write(fd2, &tmp, 1);
	g_byte_pos++;
	if ((*token)->type != 1)
		ft_death("Bad argument for aff!!!");
	n = ft_atoi((*token)->value + 1);
	if (n > 99 || n < 0)
		ft_death("Bad register!!!");
	res = ft_hex_conv(n, 1);
	ft_write(fd2, &res, 1);
	g_byte_pos++;
}
