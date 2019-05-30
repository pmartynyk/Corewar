/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkremen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 11:58:42 by vkremen           #+#    #+#             */
/*   Updated: 2019/05/09 01:24:52 by oandrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

static void		usage(void)
{
	ft_printf(" Usage: \033[0;31m[-dump nbr_cycles]\033[0m \033[0;32m");
	ft_printf("[[-n number] champion1.cor]\033[0m \033[0;33m[-v]\033[0m ");
	ft_printf("\033[0;34m[-dump64 nbr_cycles]\033[0m\n");
	ft_printf("\t\033[0;31m-dump \t\t-- At the end of nbr_cycles of\n");
	ft_printf("\t \t\texecutions, dump the memory on the standard output\n");
	ft_printf("\t \t\tin the hexadecimal format with 32 octets per line\n");
	ft_printf("\t \t\tand quit the game!\033[0m\n");
	ft_printf("\t\033[0;32m-n number \t-- Sets the number of the ");
	ft_printf("next player!\033[0m\n");
	ft_printf("\t\033[0;33m-v \t\t-- Run visualizer!\033[0m\n");
	ft_printf("\t\033[0;34m-dump64 \t-- At the end of nbr_cycles of\n");
	ft_printf("\t \t\texecutions, dump the memory on the standard output\n");
	ft_printf("\t \t\tin the hexadecimal format with 64 octets per line\n");
	ft_printf("\t \t\tand quit the game!\033[0m\n");
	exit(0);
}

static int		music(void)
{
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
		return (0);
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
		return (0);
	g_wave = Mix_LoadWAV(WAV_PATH);
	if (g_wave == NULL)
		return (0);
	g_music = Mix_LoadMUS(WAV_PATH);
	if (g_music == NULL)
		return (0);
	if (Mix_PlayChannel(-1, g_wave, 0) == -1)
		return (0);
	if (Mix_PlayMusic(g_music, -1) == -1)
		return (0);
	return (1);
}

static void		introducing(t_vmka **vmka, int id)
{
	if (!(*vmka)->visual)
	{
		ft_printf("Introducing contestants...\n");
		while (++id < (*vmka)->nbr_players)
		{
			ft_printf("* Player %d, weighing %d bytes, \"%s\" ",
				id + 1, (*vmka)->bot[id]->code_size,
				(*vmka)->bot[id]->name);
			ft_printf("(\"%s\") !\n", (*vmka)->bot[id]->comment);
		}
	}
}

int				main(int argc, char **argv)
{
	t_vmka		*vmka;

	if (!music())
		return (0);
	if (argc < 2 || !ft_strcmp(argv[1], "--help"))
		usage();
	g_id_players = (int *)ft_memalloc(sizeof(int) * 4);
	g_count_bot = -1;
	init_vm(&vmka, -1);
	parsing_argv_params(argc, argv, &vmka, 0);
	init_field(&vmka, -1, -1);
	init_carriages(&vmka, -1);
	introducing(&vmka, -1);
	vmka->last_alive = vmka->nbr_players;
	start_fight(&vmka);
	endwin();
	Mix_FreeChunk(g_wave);
	Mix_FreeMusic(g_music);
	Mix_CloseAudio();
}
