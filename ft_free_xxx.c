/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_xxx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 03:31:18 by mizola            #+#    #+#             */
/*   Updated: 2020/10/21 03:31:19 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_red(t_red *red)
{
	t_red *tmp;

	if (red->prev)
	{
		while (red->prev)
			red = red->prev;
	}
	while (red)
	{
		free(red->file);
		free(red->red_str);
		tmp = red;
		red = red->next;
		free(tmp);
	}
}

void	ft_free_xxx(t_ident *v_cmd)
{
	t_ident *tmp;

	while (v_cmd)
	{
		free(v_cmd->cmd);
		ft_free_arrstr(v_cmd->cmd_arr);
		ft_free_arrstr(v_cmd->arr_cmd);
		ft_free_arrstr(v_cmd->wr_arr);
		ft_free_arrstr(v_cmd->dirs);
		v_cmd->red ? ft_free_red(v_cmd->red) : 0;
		tmp = v_cmd;
		v_cmd = v_cmd->prev;
		free(tmp);
	}
}
