/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandrosh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 03:56:18 by oandrosh          #+#    #+#             */
/*   Updated: 2019/05/15 07:36:21 by kbakhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

char	*is_carr(t_vmka *all, char *carr_field)
{
	t_carr	*tmp;
	int		i;

	i = 0;
	tmp = all->carr;
	while (i < MEM_SIZE)
	{
		carr_field[i] = 0;
		i++;
	}
	while (tmp)
	{
		carr_field[tmp->poss_carr] = tmp->carr_color;
		tmp = tmp->next;
	}
	return (carr_field);
}

void	fill_field(t_vmka *all, WINDOW **field, int i)
{
	int		id;
	int		id_carr;
	char	carr_field[MEM_SIZE + 1];

	is_carr(all, carr_field);
	while (++i < MEM_SIZE)
	{
		id = all->field[i].id_bot;
		if ((id_carr = carr_field[i]) != 0)
		{
			wattron((*field), COLOR_PAIR(id_carr + 4));
			wprintw((*field), "%02x", all->field[i].place);
			wattroff((*field), COLOR_PAIR(id_carr + 4));
			wprintw((*field), " ");
		}
		else
		{
			wattron((*field), COLOR_PAIR(id));
			wprintw((*field), "%02x ", all->field[i].place);
			wattroff((*field), COLOR_PAIR(id));
		}
	}
}

void	set_colors(void)
{
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(5, COLOR_BLACK, COLOR_RED);
	init_pair(6, COLOR_BLACK, COLOR_BLUE);
	init_pair(7, COLOR_BLACK, COLOR_GREEN);
	init_pair(8, COLOR_BLACK, COLOR_YELLOW);
}

void	fill_winner(t_vmka *all)
{
	WINDOW	*win;
	int		x;
	int		y;

	getmaxyx(stdscr, y, x);
	if (y > 72)
	{
		win = newwin(7, 100, 72, 60);
		wattron(win, COLOR_PAIR(all->bot[all->last_alive - 1]->id_bot));
		wattron(win, A_BOLD);
		wprintw(win, "\t¶¶```¶¶`¶¶¶¶¶¶``¶¶``¶¶``¶¶``¶¶``¶¶¶¶¶```¶¶¶¶¶\n");
		wprintw(win, "\t¶¶```¶¶```¶¶````¶¶¶`¶¶``¶¶¶`¶¶``¶¶``````¶¶``¶¶\n");
		wprintw(win, "\t¶¶`¶`¶¶```¶¶````¶¶`¶¶¶``¶¶`¶¶¶``¶¶¶¶````¶¶¶¶¶\n");
		wprintw(win, "\t¶¶¶¶¶¶¶```¶¶````¶¶``¶¶``¶¶``¶¶``¶¶``````¶¶``¶¶\n");
		wprintw(win, "\t`¶¶`¶¶``¶¶¶¶¶¶``¶¶``¶¶``¶¶``¶¶``¶¶¶¶¶```¶¶``¶¶\n");
		wprintw(win, "\n\t\t%s", all->bot[all->last_alive - 1]->name);
		wattroff(win, A_BOLD);
		wattroff(win, COLOR_PAIR(all->bot[all->last_alive - 1]->id_bot));
		refresh();
		wrefresh(win);
	}
	while (getch() != 27)
		;
}

void	visual(t_vmka **all)
{
	WINDOW	*field;
	WINDOW	*info;
	int		x;
	int		y;

	initscr();
	curs_set(0);
	field = newwin(64, 192, 7, 1);
	info = newwin(60, 30, 7, 196);
	start_color();
	nodelay(stdscr, TRUE);
	noecho();
	set_colors();
	getmaxyx(stdscr, y, x);
	fill_header(x);
	fill_field(*all, &field, -1);
	if (x > 196 && y > 7)
		fill_info(*all, &info, -1);
	refresh();
	wrefresh(field);
	timeout((*all)->speed);
	config(all, 0);
}
