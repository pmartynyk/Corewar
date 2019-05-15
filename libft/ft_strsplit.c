/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkremen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 16:53:40 by vkremen           #+#    #+#             */
/*   Updated: 2018/10/31 17:40:05 by vkremen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_count(char const *s, char c)
{
	int i;

	i = 0;
	while (*s == c)
	{
		s++;
	}
	while (*s)
	{
		i++;
		while (*s != c && *s)
			s++;
		while (*s == c)
			s++;
	}
	return (i);
}

static int	new_word_len(char const *s, char c)
{
	int i;

	i = 0;
	if (s == NULL)
		return (0);
	while (*s != c && *s)
	{
		i++;
		s++;
	}
	return (i);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**list;
	int		w_count;

	if (s == NULL)
	{
		list = malloc(sizeof(char *));
		list[0] = NULL;
		return (list);
	}
	list = (char **)malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (list == NULL)
		return (NULL);
	w_count = 0;
	while (*s == c)
		s++;
	while (*s)
	{
		list[w_count++] = ft_strsub(s, 0, new_word_len(s, c));
		while (*s != c && *s)
			s++;
		while (*s == c)
			s++;
	}
	list[w_count] = NULL;
	return (list);
}
