/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validate_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbakhari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 16:07:48 by kbakhari          #+#    #+#             */
/*   Updated: 2019/05/27 16:07:51 by kbakhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

void	ft_validate_args5(t_token **cur)
{
	if (ft_strequ((*cur)->value, "ldi") ||
		ft_strequ((*cur)->value, "lldi"))
	{
		if ((*cur)->next->type != 2 && (*cur)->next->type != 3 &&
			(*cur)->next->type != 5 && (*cur)->next->type != 6 &&
			(*cur)->next->type != 1 && (*cur)->next->next->type != 2 &&
			(*cur)->next->next->type != 5 && (*cur)->next->next->type != 1)
			ft_death("Wrong arg!");
		if ((*cur)->next->next->next->type != 1)
			ft_death("Wrong arg!");
		(*cur) = (*cur)->next->next->next;
	}
}

void	ft_validate_args4(t_token **cur)
{
	if (ft_strequ((*cur)->value, "sti"))
	{
		if ((*cur)->next->type != 2 && (*cur)->next->type != 3 &&
			(*cur)->next->type != 5 && (*cur)->next->type != 6 &&
			(*cur)->next->type != 1 && (*cur)->next->next->type != 2 &&
			(*cur)->next->next->type != 5 && (*cur)->next->next->type != 1)
			ft_death("Wrong arg!");
		(*cur) = (*cur)->next->next->next;
	}
	else if (ft_strequ((*cur)->value, "aff"))
	{
		if ((*cur)->next->type != 1)
			ft_death("Wrong arg!");
		(*cur) = (*cur)->next;
	}
}

void	ft_validate_args3(t_token **cur)
{
	if (ft_strequ((*cur)->value, "add") || ft_strequ((*cur)->value, "sub"))
	{
		if ((*cur)->next->type != 1 || (*cur)->next->next->type != 1 ||
			(*cur)->next->next->next->type != 1)
			ft_death("Wrong arg!");
		(*cur) = (*cur)->next->next->next;
	}
	else if (ft_strequ((*cur)->value, "and") || ft_strequ((*cur)->value, "or")
		|| ft_strequ((*cur)->value, "xor"))
	{
		if ((*cur)->next->type != 2 && (*cur)->next->type != 3 &&
			(*cur)->next->type != 5 && (*cur)->next->type != 6 &&
			(*cur)->next->type != 1 && (*cur)->next->next->type != 2 &&
			(*cur)->next->next->type != 3 && (*cur)->next->next->type != 5 &&
			(*cur)->next->next->type != 6 && (*cur)->next->next->type != 1)
			ft_death("Wrong arg!");
		if ((*cur)->next->next->next->type != 1)
			ft_death("Wrong arg!");
		(*cur) = (*cur)->next->next->next;
	}
}

void	ft_validate_args2(t_token **cur)
{
	if (ft_strequ((*cur)->value, "live") || ft_strequ((*cur)->value, "zjmp") ||
		ft_strequ((*cur)->value, "fork") || ft_strequ((*cur)->value, "lfork"))
	{
		if ((*cur)->next->type != 2 && (*cur)->next->type != 5)
			ft_death("Wrong arg!");
		(*cur) = (*cur)->next;
	}
	else if (ft_strequ((*cur)->value, "ld") || ft_strequ((*cur)->value, "lld"))
	{
		if ((*cur)->next->type != 2 && (*cur)->next->type != 3 &&
			(*cur)->next->type != 5 && (*cur)->next->type != 6)
			ft_death("Wrong arg!");
		if ((*cur)->next->next->type != 1)
			ft_death("Wrong arg!");
		(*cur) = (*cur)->next->next;
	}
	else if (ft_strequ((*cur)->value, "st"))
	{
		if ((*cur)->next->type != 1)
			ft_death("Wrong arg!");
		if ((*cur)->next->next->type != 1 && (*cur)->next->next->type != 3 &&
			(*cur)->next->next->type != 6)
			ft_death("Wrong arg!");
		(*cur) = (*cur)->next->next;
	}
}

void	ft_validate_args(t_token **tokens)
{
	t_token *cur;

	cur = (*tokens);
	while (cur->next)
	{
		if (cur->type == 0)
		{
			ft_validate_args2(&cur);
			ft_validate_args3(&cur);
			ft_validate_args4(&cur);
			ft_validate_args5(&cur);
		}
		else if (cur->type != 4)
			ft_death("Wrong arguments!");
		cur = cur->next;
	}
}
