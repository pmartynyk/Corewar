/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbakhari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 13:31:28 by kbakhari          #+#    #+#             */
/*   Updated: 2019/05/06 13:31:29 by kbakhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

void			ft_writer(char *filename, char **namecom, t_label **labels,
							t_token **tokens)
{
	int			fd2;

	if (g_gnl == 0)
		ft_death("No newline!!!");
	ft_validate_tokens(tokens);
	ft_validate_register(tokens);
	ft_validate_args(tokens);
	fd2 = open(filename, O_RDWR | O_TRUNC | O_CREAT, 0666);
	if (fd2 < 0)
		ft_death("Bad file!");
	ft_put_magic(fd2, 0);
	ft_write_name(fd2, namecom[0], 1);
	ft_put_null(fd2);
	ft_put_magic(fd2, 1);
	ft_write_name(fd2, namecom[1], 2);
	ft_put_null(fd2);
	g_byte_pos = 0;
	ft_write_code(fd2, labels, tokens);
}

void			ft_starter(t_label **labels, t_token **tokens, char *str)
{
	char		*filename;
	int			fd;
	char		**namecom;

	fd = open(str, O_RDONLY);
	if (fd < 0)
		ft_death("Bad file!");
	filename = ft_get_filename(str);
	namecom = ft_get_name_comment(fd);
	ft_get_tokens(fd, tokens, labels);
	if ((*tokens)->value == NULL)
		ft_death("No tokens!");
	ft_check_tokens(tokens);
	ft_get_size(tokens, labels);
	ft_writer(filename, namecom, labels, tokens);
	free(filename);
	ft_free_mass(namecom, -1);
}

int				main(int ac, char **av)
{
	t_token		*tokens;
	t_label		*labels;

	if (ac != 2)
		ft_death("USAGE: ./asm (filename)");
	g_kostil = 0;
	tokens = (t_token*)ft_memalloc(sizeof(t_token));
	labels = (t_label*)ft_memalloc(sizeof(t_label));
	ft_starter(&labels, &tokens, av[ac - 1]);
	return (0);
}
