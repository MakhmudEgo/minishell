/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 09:16:35 by mizola            #+#    #+#             */
/*   Updated: 2020/10/01 09:16:36 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_env(t_data *data)
{
	t_list *tmp;

	tmp = data->env;
	while (tmp)
	{
		if (tmp->visible && tmp->visible != 3)
		{
			ft_putstr_fd(tmp->content, 1);
			write(1, "=", 1);
			ft_putstr_fd(tmp->value, 1);
			write(1, "\n", 1);
		}
		tmp = tmp->next;
	}
	g_code = 0;
	return (0);
}
