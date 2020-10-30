/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_red_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 13:48:28 by mizola            #+#    #+#             */
/*   Updated: 2020/10/25 13:48:29 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_red_new_p1(t_data *data)
{
	if (!(check_red_file(data->v_cmd->red->file, ": Permission denied", 1)))
		return (0);
	if (!(data->new_fd_f = ft_creat_file(data->v_cmd->red->file)))
		return (0);
	if (ft_check_next_red(data->v_cmd->red) == 1
		|| ft_check_next_red(data->v_cmd->red) == 3)
		close(data->new_fd_f);
	else if (ft_check_next_red(data->v_cmd->red) == 2)
	{
		if (!ft_check_red_two(&data->v_cmd->red))
		{
			ft_puterr(data->v_cmd->red->file, ": No such file or directory", 1);
			close(data->new_fd_f);
			data->new_fd_f = -1;
			return (0);
		}
	}
	else if (ft_check_next_red(data->v_cmd->red) == -1)
		return (1);
	return (2);
}

static int	ft_red_new_p2(t_data *data)
{
	if (!(check_red_file(data->v_cmd->red->file, ": Permission denied", 1)))
		return (0);
	if (!(data->new_fd_f = fd_creat_or_add_file(data->v_cmd->red->file)))
		return (0);
	if (ft_check_next_red(data->v_cmd->red) == 1
		|| ft_check_next_red(data->v_cmd->red) == 3)
		close(data->new_fd_f);
	else if (ft_check_next_red(data->v_cmd->red) == 2)
	{
		if (!ft_check_red_two(&data->v_cmd->red))
		{
			ft_puterr(data->v_cmd->red->file, ": No such file or directory", 1);
			close(data->new_fd_f);
			data->new_fd_f = -1;
			return (0);
		}
	}
	else if (ft_check_next_red(data->v_cmd->red) == -1)
		return (1);
	return (2);
}

static int	ft_red_new_p3(t_data *data)
{
	if (data->new_fd_n != -1)
		close(data->new_fd_n);
	if (!(check_red_file(data->v_cmd->red->file,
	": Permission denied", 1)))
		return (0);
	data->new_fd_n = fd_open_file(data->v_cmd->red->file);
	return (1);
}

int			ft_red_new(t_data *data, int i)
{
	while (data->v_cmd->red)
	{
		if (data->v_cmd->red->red == 1)
		{
			if ((i = ft_red_new_p1(data)) != 2)
				return (i);
		}
		else if (data->v_cmd->red->red == 2)
		{
			if ((data->new_fd_n = ft_open_next_two(&data->v_cmd->red, 1)) == -1)
				return (0);
		}
		else if (data->v_cmd->red->red == 3)
		{
			if ((i = ft_red_new_p2(data)) != 2)
				return (i);
		}
		else if (data->v_cmd->red->red == 4)
			if (!ft_red_new_p3(data))
				return (0);
		if (!data->v_cmd->red->next)
			break ;
		data->v_cmd->red = data->v_cmd->red->next;
	}
	return (1);
}
