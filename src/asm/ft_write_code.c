/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_code.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbakhari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 06:18:32 by kbakhari          #+#    #+#             */
/*   Updated: 2019/05/11 06:18:33 by kbakhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

void			ft_write_code2(int fd2, t_label **labels, t_token **token)
{
	if (ft_strequ((*token)->value, "aff"))
		ft_aff(token, fd2);
	else if (ft_strequ((*token)->value, "add"))
		ft_add(token, fd2);
	else if (ft_strequ((*token)->value, "sub"))
		ft_sub(token, fd2);
	else if (ft_strequ((*token)->value, "and"))
		ft_and(token, labels, fd2);
	else if (ft_strequ((*token)->value, "or"))
		ft_or(token, labels, fd2);
	else if (ft_strequ((*token)->value, "xor"))
		ft_xor(token, labels, fd2);
	else if (ft_strequ((*token)->value, "zjmp"))
		ft_zjmp(token, labels, fd2);
	else if (ft_strequ((*token)->value, "ldi"))
		ft_ldi(token, labels, fd2);
	else if (ft_strequ((*token)->value, "sti"))
		ft_sti(token, labels, fd2);
	else if (ft_strequ((*token)->value, "fork"))
		ft_fork(token, labels, fd2);
	else if (ft_strequ((*token)->value, "lfork"))
		ft_lfork(token, labels, fd2);
}

void			ft_write_code(int fd2, t_label **labels, t_token **tokens)
{
	t_token		*token;

	token = *tokens;
	while (token->next)
	{
		if (token->type == 0)
		{
			if (ft_strequ(token->value, "live"))
				ft_live(&token, labels, fd2);
			else if (ft_strequ(token->value, "ld"))
				ft_ld(&token, labels, fd2);
			else if (ft_strequ(token->value, "st"))
				ft_st(&token, labels, fd2);
			else if (ft_strequ(token->value, "lld"))
				ft_lld(&token, labels, fd2);
			else if (ft_strequ(token->value, "lldi"))
				ft_lldi(&token, labels, fd2);
			else
				ft_write_code2(fd2, labels, &token);
		}
		else if (token->type != 4)
			ft_death("Bad arguments!!!");
		token = token->next;
	}
}
