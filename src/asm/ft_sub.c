/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbakhari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 10:58:03 by kbakhari          #+#    #+#             */
/*   Updated: 2019/05/11 10:58:10 by kbakhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

void			ft_sub(t_token **token, int fd2)
{
	char	*res;
	int		n;
	int		i;

	i = -1;
	res = ft_hex_conv(5, 1);
	ft_write(fd2, &res, 1);
	g_byte_pos++;
	res = ft_hex_conv(84, 1);
	ft_write(fd2, &res, 1);
	g_byte_pos++;
	while (++i < 3)
	{
		if ((*token)->next)
			(*token) = (*token)->next;
		if ((*token)->type != 1)
			ft_death("Bad argument for sub!!!");
		n = ft_atoi((*token)->value + 1);
		if (n > 99 || n < 0)
			ft_death("Bad register!!!");
		res = ft_hex_conv(n, 1);
		ft_write(fd2, &res, 1);
		g_byte_pos++;
	}
}
