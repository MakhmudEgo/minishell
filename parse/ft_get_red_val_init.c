/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_red_val_init.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 22:39:30 by mizola            #+#    #+#             */
/*   Updated: 2020/10/18 22:39:31 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	ft_get_red_val_init(t_ident *new_i, int *i, int *n, char *cmd)
{
	t_red *new;

	while ((*n = ft_is_red(cmd, i)))
	{
		ft_skip_space(i, cmd);
		!(new = malloc(sizeof(t_red))) ? ft_error("malloc return NULL", 13) : 0;
		ft_red_init(new);
		new->red = *n;
		*n = *i;
		*n = ft_get_len_str_cmd(cmd, *i, 1);
		!(new->file = ft_substr(cmd, *i, *n))
		? ft_error("malloc return NULL", 13) : 0;
		*i += *n;
		ft_skip_space(i, cmd);
		*n = ft_get_len_str_cmd(cmd, *i, 0);
		if (new_i->cmd && *n)
		{
			!(new->red_str = ft_substr(cmd, *i, *n))
			? ft_error("malloc return NULL", 13) : 0;
			*i += *n;
			ft_skip_space(i, cmd);
		}
		ft_redlstback(&new_i->red, new);
	}
}
