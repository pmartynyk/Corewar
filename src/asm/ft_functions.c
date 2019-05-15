/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbakhari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 16:45:28 by kbakhari          #+#    #+#             */
/*   Updated: 2019/05/06 16:45:30 by kbakhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

static int	ft_get_name2(char *line, int i, int flag)
{
	while (line[++i] != '.')
		if (line[i] != ' ' && line[i] != '\t')
			ft_death("Error in name/comment");
	if (flag == 1 && (line[i + 1] != 'n' || line[i + 2] != 'a' ||
		line[i + 3] != 'm' || line[i + 4] != 'e'))
		ft_death("Error in name");
	if (flag == 2 && (line[i + 1] != 'c' || line[i + 2] != 'o' ||
		line[i + 3] != 'm' || line[i + 4] != 'm' || line[i + 5] != 'e' ||
		line[i + 6] != 'n' || line[i + 7] != 't'))
		ft_death("Error in comment");
	i += flag == 1 ? 5 : 8;
	while (line[++i] != '"')
		if (line[i] != ' ' && line[i] != '\t')
			ft_death("Error in name/comment");
	return (i);
}

static void	ft_get_name3(char **name, char *line, int **i, int fd)
{
	char	*tmp;

	if (!(*name))
	{
		(*name) = ft_strsub(line, (*i)[0], (*i)[0] - (*i)[1]);
		(*name) = ft_strjoin((*name), "\n");
	}
	else
	{
		tmp = ft_strsub(line, (*i)[1], (*i)[0] - (*i)[1]);
		(*name) = ft_strjoin((*name), tmp);
		ft_strdel(&tmp);
		(*name) = ft_strjoin((*name), "\n");
	}
	(*i)[1] = 0;
	(*i)[0] = -1;
	get_next_line(fd, &line);
}

char		*ft_get_name(int fd, char *line, int flag)
{
	int		*mass;
	char	*name;
	char	*tmp;

	mass = (int*)ft_memalloc(sizeof(int) * 2);
	mass[0] = ft_get_name2(line, -1, flag);
	mass[1] = mass[0] + 1;
	name = NULL;
	while (line[++mass[0]] != '"')
		if (!line[mass[0]])
		{
			ft_get_name3(&name, line, &mass, fd);
			ft_strdel(&line);
		}
	if (!name)
		name = ft_strsub(line, mass[1], mass[0] - mass[1]);
	else
	{
		tmp = ft_strsub(line, mass[1], mass[0] - mass[1]);
		name = ft_strjoin(name, tmp);
		ft_strdel(&tmp);
	}
	free(mass);
	ft_strdel(&line);
	return (name);
}

static void	ft_get_name_comment2(char *line, char ***res, int *flag, int fd)
{
	if (ft_strstr(line, ".name"))
	{
		if ((*res)[0])
			ft_death("Dublicate name");
		(*flag)++;
		(*res)[0] = ft_get_name(fd, line, 1);
	}
	else if (ft_strstr(line, ".comment") && !(*res)[1])
	{
		if ((*res)[1])
			ft_death("Dublicate comment");
		(*flag)++;
		(*res)[1] = ft_get_name(fd, line, 2);
	}
}

char		**ft_get_name_comment(int fd)
{
	char	*line;
	int		i;
	int		flag;
	char	**res;

	i = 0;
	flag = 0;
	res = (char**)ft_memalloc(sizeof(char*) * 3);
	while (i < 2)
	{
		get_next_line(fd, &line);
		while (!ft_check_empty(line))
		{
			ft_strdel(&line);
			get_next_line(fd, &line);
		}
		ft_get_name_comment2(line, &res, &flag, fd);
		i++;
	}
	if (flag != 2)
		ft_death("No name/comment!");
	res[2] = "\0";
	return (res);
}
