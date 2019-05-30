/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbakhari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 16:07:14 by kbakhari          #+#    #+#             */
/*   Updated: 2019/05/06 16:07:15 by kbakhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

void		ft_write(int fd, char **str, int size)
{
	if (write(fd, *str, size) < 0)
		ft_death("Write error!");
	ft_strdel(str);
}

void		ft_put_magic(int fd2, int flag)
{
	int		magic;
	int		i;
	char	*res;

	res = ft_strnew(4);
	i = 4;
	magic = flag == 0 ? COREWAR_EXEC_MAGIC : g_code_size;
	while (--i >= 0)
	{
		res[i] = magic % 256;
		magic /= 256;
	}
	ft_write(fd2, &res, 4);
}

void		ft_put_null(int fd2)
{
	int		zero;
	char	*res;
	int		i;

	zero = 0;
	i = 4;
	res = ft_strnew(4);
	while (--i >= 0)
		res[i] = 0;
	ft_write(fd2, &res, 4);
}

void		ft_write_name(int fd2, char *str, int flag)
{
	int		i;
	char	*res;

	res = ft_strnew(flag == 1 ? PROG_NAME_LENGTH : COMMENT_LENGTH);
	i = 0;
	while (str[i])
	{
		if (g_kostil != 3)
			res[i] = g_kostil == flag ? 0 : str[i];
		else
			res[i] = 0;
		i++;
	}
	if (i > (flag == 1 ? PROG_NAME_LENGTH : COMMENT_LENGTH))
		ft_death(flag == 1 ? "Champ name too big" : "Comment too big");
	while (++i <= (flag == 1 ? PROG_NAME_LENGTH : COMMENT_LENGTH))
		res[i] = 0;
	ft_write(fd2, &res, (flag == 1 ? PROG_NAME_LENGTH : COMMENT_LENGTH));
}
