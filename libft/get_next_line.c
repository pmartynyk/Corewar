/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkremen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 18:44:42 by vkremen           #+#    #+#             */
/*   Updated: 2018/11/12 15:52:45 by vkremen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char			*ft_stock_the_new_line(char *str)
{
	int			i;
	int			len;
	char		*new;

	i = 0;
	len = 0;
	while (str[len++])
		;
	if (!(new = (char *)malloc(sizeof(*new) * len + 1)))
		return (NULL);
	while (i < len && str[i] != '\n')
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

static char		*ft_clean_new(char *str)
{
	char		*new;
	int			i;

	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	if ((str[i] && !str[i + 1]) || !str[i])
	{
		ft_strdel(&str);
		return (NULL);
	}
	new = ft_strdup(str + i + 1);
	ft_strdel(&str);
	return (new);
}

static int		other_func(char **new, char ***line)
{
	**line = ft_stock_the_new_line(*new);
	*new = ft_clean_new(*new);
	return (1);
}

static void		ft_check_nl(char *new)
{
	static char		c;

	if (c == '\n')
		g_gnl = 1;
	else if (c != '\t' && c != ' ')
		g_gnl = 0;
	c = new[ft_strlen(new) - 1];
}

int				get_next_line(const int fd, char **line)
{
	char		buff[BUFF_SIZE + 1];
	int			ret;
	static char	*new;

	if (!new)
		new = ft_strnew(1);
	if (BUFF_SIZE < 0 || !line || fd < 0)
		return (-1);
	while (!(ft_strchr(new, '\n')))
	{
		ret = read(fd, buff, BUFF_SIZE);
		if (ret == -1)
			return (-1);
		buff[ret] = '\0';
		new = ft_strjoin(new, buff);
		ft_check_nl(new);
		if (ret == 0 && *new == '\0')
			return (0);
		if (ret == 0)
			break ;
	}
	return (other_func(&new, &line));
}
