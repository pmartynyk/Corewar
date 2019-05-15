/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_labels.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbakhari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 01:44:22 by kbakhari          #+#    #+#             */
/*   Updated: 2019/05/11 01:44:22 by kbakhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

void			ft_check_label(char *str)
{
	int			i;
	int			y;
	char		*chars;
	int			match;

	i = -1;
	chars = ft_strdup(LABEL_CHARS);
	while (str[++i])
	{
		match = 0;
		y = -1;
		while (chars[++y])
			if (str[i] == chars[y])
				match = 1;
		if (match == 0)
			ft_death("Invalid LABEL name!");
	}
	ft_strdel(&chars);
}

static void		ft_add_label_2(t_token **this, t_label **cur, char **str,
								int *i)
{
	int			y;

	while ((*cur)->next)
		(*cur) = (*cur)->next;
	(*cur)->next = ft_memalloc(sizeof(t_label));
	while ((*this)->next)
		(*this) = (*this)->next;
	(*this)->next = ft_memalloc(sizeof(t_token));
	while ((*str)[++(*i)] == ' ' || (*str)[(*i)] == '\t')
		;
	y = (*i);
	while ((*str)[++(*i)] != LABEL_CHAR)
		;
	(*cur)->name = ft_strsub((*str), y, (*i) - y);
}

void			ft_add_label(char *str, t_label **labels, t_token **tokens,
								int i)
{
	t_label		*cur;
	t_token		*this;
	char		*tmp;

	cur = *labels;
	this = *tokens;
	ft_add_label_2(&this, &cur, &str, &i);
	cur->position = g_byte_pos;
	this->type = LABEL;
	this->value = cur->name;
	ft_check_label(cur->name);
	if (str[++i])
	{
		tmp = ft_strsub(str, i, (int)ft_strlen(str) - i);
		if (ft_check_empty(tmp))
			ft_define_tokens(tmp, tokens, labels);
		ft_strdel(&tmp);
	}
}
