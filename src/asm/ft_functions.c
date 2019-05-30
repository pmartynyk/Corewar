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
	i += flag == 1 ? 4 : 7;
	while (line[++i] != '"')
		if (line[i] != ' ' && line[i] != '\t')
			ft_death("Error in name/comment");
	return (i);
}

static void	ft_get_name3(char **name, char **line, int **i, int fd)
{
	char	*tmp;

	if ((*name) == NULL && (*i)[0] != (*i)[1])
	{
		(*name) = ft_strsub((*line), (*i)[1], (*i)[0] - (*i)[1]);
		(*name) = ft_strjoin((*name), "\n");
	}
	else if ((*i)[0] != (*i)[1])
	{
		tmp = ft_strsub((*line), (*i)[1], (*i)[0] - (*i)[1]);
		(*name) = ft_strjoin((*name), tmp);
		ft_strdel(&tmp);
		(*name) = ft_strjoin((*name), "\n");
	}
	(*i)[1] = 0;
	(*i)[0] = -1;
	ft_strdel(line);
	if (get_next_line(fd, line) <= 0)
		ft_death("Bad name/comment!!!");
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
			ft_get_name3(&name, &line, &mass, fd);
	if (ft_check_empty(line + mass[0] + 1))
		ft_death("Bad symbols after name/comment!");
	if (!name && mass[1] != mass[0])
		name = ft_strsub(line, mass[1], mass[0] - mass[1]);
	else if (mass[1] != mass[0])
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
		if (!(*res)[0])
		{
			ft_strdel(&(*res)[0]);
			g_kostil = g_kostil == 2 ? 3 : 1;
			(*res)[0] = ft_strdup("Hello!");
		}
	}
	else if (ft_strstr(line, ".comment") && !(*res)[1])
	{
		(*res)[1] ? ft_death("Dublicate comment") : 0;
		(*flag)++;
		(*res)[1] = ft_get_name(fd, line, 2);
		if (!(*res)[1])
		{
			ft_strdel(&(*res)[1]);
			g_kostil = g_kostil == 1 ? 3 : 2;
			(*res)[1] = ft_strdup("Hello!");
		}
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
			if (get_next_line(fd, &line) <= 0)
				ft_death("Bad file!");
		}
		ft_get_name_comment2(line, &res, &flag, fd);
		i++;
	}
	if (flag != 2)
		ft_death("No name/comment!");
	res[2] = "\0";
	return (res);
}
