/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 20:04:15 by mizola            #+#    #+#             */
/*   Updated: 2020/10/10 20:04:16 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	putstr_err(char *s)
{
	ft_putendl_fd("exit", 2);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(s, 2);
	ft_putendl_fd(": numeric argument required", 2);
	g_code = 255;
}

static int	check_valid(char *arr)
{
	int i;

	i = -1;
	while (arr && arr[++i])
	{
		if ((!ft_isdigit(arr[0]) && (arr[0] != '-' || arr[0] != '+'))
		|| !ft_isdigit(arr[i]))
		{
			putstr_err(arr);
			return (0);
		}
	}
	return (1);
}

void		ft_exit(t_data *data)
{
	int n;
	int i;
	int valid;
	int exit_code;

	n = 1;
	valid = 0;
	exit_code = 0;
	i = ft_arrstrlen_null((const char **)data->v_cmd->arr_cmd);
	if (data->v_cmd->arr_cmd &&
	(n = check_valid(data->v_cmd->arr_cmd[1])) && i == 2)
		exit_code = (int)ft_atoi_shell(data->v_cmd->arr_cmd[1], &valid);
	else if (n && i > 2)
	{
		ft_putendl_fd("exit", 2);
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return ;
	}
	n ? ft_putendl_fd("exit", 1) : 0;
	valid ? putstr_err(data->v_cmd->arr_cmd[0]) : 0;
	g_code = exit_code ? exit_code : g_code;
	exit(exit_code && exit_code % 256 == 0 ? 1 : g_code);
}
