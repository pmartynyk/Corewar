/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandrosh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 03:49:09 by oandrosh          #+#    #+#             */
/*   Updated: 2019/05/11 03:49:11 by oandrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int		last_live(t_carr *all, int id)
{
	while (all)
	{
		if (all->carr_color == id)
			return (all->last_live);
		all = all->next;
	}
	return (0);
}

int		count_live(t_carr *all, int id)
{
	int	count;

	count = 0;
	while (all)
	{
		if (all->carr_color == id)
			count++;
		all = all->next;
	}
	return (count);
}
