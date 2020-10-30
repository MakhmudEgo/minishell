/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_identlstback.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 16:50:39 by mizola            #+#    #+#             */
/*   Updated: 2020/10/03 16:50:40 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_identlstback(t_ident **lst, t_ident *new)
{
	t_ident *tmp;
	t_ident *prev;

	tmp = *lst;
	if (!tmp && lst)
		*lst = new;
	else if (lst && new)
	{
		if (!tmp->next)
			prev = tmp;
		while (tmp->next != NULL)
		{
			prev = tmp;
			tmp = tmp->next;
			tmp->prev = prev;
			prev = tmp;
		}
		new->prev = prev;
		tmp->next = new;
		new->next = NULL;
	}
}
