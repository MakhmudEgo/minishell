/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_pipe_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 21:30:47 by avallie           #+#    #+#             */
/*   Updated: 2020/10/20 21:30:48 by avallie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_prev_pipe_red(t_ident *ident)
{
	t_ident *tmp;

	tmp = ident;
	if (tmp && tmp->prev)
	{
		tmp = tmp->prev;
		while (tmp->red)
		{
			if (tmp->red->red == 1 || tmp->red->red == 3)
				return (1);
			tmp->red = tmp->red->prev;
		}
	}
	return (0);
}
