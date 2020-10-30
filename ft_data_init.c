/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 12:35:59 by mizola            #+#    #+#             */
/*   Updated: 2020/10/01 12:36:01 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_data_init(t_data *data)
{
	data->v_cmd = 0x0;
	data->cmd = 0x0;
	data->fd1[0] = 0x0;
	data->fd1[1] = 0x0;
	data->fd2[0] = 0x0;
	data->fd2[1] = 0x0;
	data->st_fd_f = 1;
	data->new_fd_n = -1;
	data->new_fd_f = -1;
	data->is_valid_str = 0x0;
}

void	ft_ident_init(t_ident *data)
{
	data->cmd = 0x0;
	data->wr_arr = 0x0;
	data->flag = 0x0;
	data->cmd_arr = 0x0;
	data->red = 0x0;
	data->p = 0x0;
	data->next = 0x0;
	data->prev = 0x0;
	data->arr_cmd = 0x0;
	data->dirs = 0x0;
	data->is_cmd = 0x0;
	data->is_ok = 1;
}

void	ft_red_init(t_red *data)
{
	data->red = 0x0;
	data->file = 0x0;
	data->red_str = 0x0;
	data->next = 0x0;
	data->prev = 0x0;
}

void	dirs_init(t_data *data)
{
	t_list *tmp;

	tmp = data->env;
	while (tmp)
	{
		if (!ft_strncmp("PATH", tmp->content, 5))
		{
			data->v_cmd->dirs = ft_split(tmp->value, ':');
			break ;
		}
		tmp = tmp->next;
	}
}
