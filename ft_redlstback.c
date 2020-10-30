/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redlstback.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 16:57:14 by mizola            #+#    #+#             */
/*   Updated: 2020/10/03 16:57:15 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redlstback(t_red **lst, t_red *new)
{
	t_red *tmp;
	t_red *prev;

	tmp = *lst;
	if (!tmp && lst)
	{
		*lst = new;
	}
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
