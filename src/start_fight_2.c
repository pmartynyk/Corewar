/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_fight_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartyny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 15:43:56 by pmartyny          #+#    #+#             */
/*   Updated: 2019/05/09 10:49:36 by oandrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include <stdio.h>

static void		dump(t_vmka **vmka, int step)
{
	while (++step < MEM_SIZE)
	{
		if (!step)
			ft_printf("0x0000 : ");
		else if (step % (*vmka)->octet_dump == 0)
			ft_printf("0x%04x : ", step);
		ft_printf("%02x ", (*vmka)->field[step].place);
		if ((step + 1) % (*vmka)->octet_dump == 0)
			ft_printf("\n");
	}
	exit(0);
}

static void		check_for_winner(t_vmka **vmka)
{
	if (!(*vmka)->carr)
	{
		if (!(*vmka)->visual)
		{
			ft_printf("Contestant %d, \"%s\", has won !\n",
				(*vmka)->last_alive,
				(*vmka)->bot[(*vmka)->last_alive - 1]->name);
		}
		else
			fill_winner(*vmka);
		endwin();
		exit(0);
	}
}

static void		check_to_del_carr(t_vmka **vmka, t_carr *tmp, t_carr *tmp_prev)
{
	while (tmp)
	{
		if ((*vmka)->cycles - tmp->last_live >= (*vmka)->cycles_to_die)
		{
			if ((*vmka)->carr == tmp)
			{
				(*vmka)->carr = tmp->next;
				free(tmp);
				tmp = (*vmka)->carr;
			}
			else
			{
				tmp_prev->next = tmp->next;
				free(tmp);
				tmp = tmp_prev->next;
			}
		}
		else
		{
			tmp_prev = tmp;
			tmp = tmp->next;
		}
	}
}

static void		start_fight_2_1(int checks, int *cycles_to_dies, t_vmka **vmka)
{
	if (checks != 0 && !(checks %= MAX_CHECKS))
		if ((*cycles_to_dies) == (*vmka)->cycles_to_die &&
			(*vmka)->cycles_to_die > 0)
		{
			(*vmka)->cycles_to_die -= CYCLE_DELTA;
			(*cycles_to_dies) = (*vmka)->cycles_to_die;
		}
}

void			start_fight_2(t_vmka **vmka)
{
	static int	cycles_to_dies;
	static int	checks;
	static int	cycles;

	cycles++;
	cycles_to_dies = !cycles_to_dies ? (*vmka)->cycles_to_die : cycles_to_dies;
	if (cycles % (*vmka)->cycles_to_die == 0 || (*vmka)->cycles_to_die <= 0)
	{
		checks++;
		check_to_del_carr(vmka, (*vmka)->carr, NULL);
		if ((*vmka)->lives >= NBR_LIVE)
		{
			(*vmka)->cycles_to_die -= CYCLE_DELTA;
			cycles_to_dies = (*vmka)->cycles_to_die;
			checks = 0;
		}
		start_fight_2_1(checks, &cycles_to_dies, vmka);
		cycles = 0;
		(*vmka)->lives = 0;
		check_for_winner(vmka);
	}
	(*vmka)->cycles == (*vmka)->dump_cycles ? dump(vmka, -1) : 0;
	if ((*vmka)->visual)
		visual(vmka);
	(*vmka)->cycles++;
}
