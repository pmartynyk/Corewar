/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utility.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbakhari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 13:37:19 by kbakhari          #+#    #+#             */
/*   Updated: 2019/05/06 13:37:20 by kbakhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

char		*ft_get_filename(char *name)
{
	char	*result;
	int		endlen;
	int		namelen;

	if (!ft_strrchr(name, '.') ||
		!ft_strequ(ft_strrchr(name, '.'), ".s"))
		ft_death("Bad file!");
	endlen = (int)ft_strlen(ft_strrchr(name, '.'));
	namelen = (int)ft_strlen(name) - endlen;
	if (ft_strcmp(ft_strrchr(name, '.'), ".s"))
		ft_death("Bad file");
	result = ft_strsub(name, 0, namelen);
	result = ft_strjoin(result, ".cor");
	return (result);
}

int			ft_is_label(char *line)
{
	int		i;
	char	*tmp;

	i = -1;
	while (line[++i])
	{
		if (line[i] == LABEL_CHAR)
		{
			tmp = ft_strsub(line, 0, i);
			if (i == 0 || !ft_check_empty(tmp))
				ft_death("Label char? There?");
			ft_strdel(&tmp);
			if (line[i - 1] && line[i - 1] != '%' && line[i - 1] != ',' &&
				line[i - 1] != ' ')
				return (1);
		}
	}
	return (0);
}

int			ft_check_empty(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == COMMENT_CHAR || line[i] == ALT_COMMENT_CHAR)
			return (0);
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (1);
		i++;
	}
	return (0);
}

void		ft_death(char *str)
{
	int		len;
	int		i;

	i = -1;
	len = (int)ft_strlen(str);
	ft_printf("\033[0;31m/");
	while (++i < len + 5)
		ft_printf("-");
	ft_printf("\\\n");
	ft_printf("| %s%s\n", str, "    |");
	i = -1;
	ft_printf("\\");
	while (++i < len + 5)
		ft_printf("-");
	ft_printf("/\n\033[0m");
	exit(0);
}
