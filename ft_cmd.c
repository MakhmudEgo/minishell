/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 21:07:54 by mizola            #+#    #+#             */
/*   Updated: 2020/10/14 21:07:55 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_exec_cmd(t_data *data)
{
	if (data->v_cmd->cmd &&
	!ft_strncmp(data->v_cmd->cmd, "pwd", ft_strlen("pwd") + 1))
		ft_pwd(data);
	else if (data->v_cmd->cmd &&
	!ft_strncmp(data->v_cmd->cmd, "export", ft_strlen("export") + 1))
		ft_export(data);
	else if (data->v_cmd->cmd &&
	!ft_strncmp(data->v_cmd->cmd, "echo", ft_strlen("echo") + 1))
		ft_echo(data);
	else if (data->v_cmd->cmd &&
	!ft_strncmp(data->v_cmd->cmd, "env", ft_strlen("env") + 1))
		ft_env(data);
	else if (data->v_cmd->cmd &&
	!ft_strncmp(data->v_cmd->cmd, "unset", ft_strlen("unset") + 1))
		ft_unset(data);
	else if (data->v_cmd->cmd &&
	!ft_strncmp(data->v_cmd->cmd, "exit", ft_strlen("exit") + 1))
		ft_exit(data);
	else if (data->v_cmd->cmd &&
	!ft_strncmp(data->v_cmd->cmd, "cd", ft_strlen("cd") + 1))
		ft_cd(data);
	else
		lsh_launch(data->v_cmd->arr_cmd, data);
}

void		ft_print_file_red(t_data *data)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (data->new_fd_n != -1)
			dup2(data->new_fd_n, 0);
		if (data->new_fd_f != -1)
			dup2(data->new_fd_f, 1);
		ft_exec_cmd(data);
		exit(g_code);
	}
	if (data->new_fd_n != -1)
		close(data->new_fd_n);
	if (data->new_fd_f != -1)
		close(data->new_fd_f);
	wait(&status);
	g_code = status;
}

static void	ft_bash_cmd_v1(t_data *data)
{
	data->v_cmd->arr_cmd = ft_arrstrjoin(ft_split_quote(data->v_cmd->cmd), 0x0);
	!data->v_cmd->arr_cmd ? ft_error("malloc return NULL", 13) : 0;
	data->v_cmd->cmd ? ft_valid_str(data, &data->v_cmd->cmd) : 0;
	check_reg(&data->v_cmd->cmd, data);
	!ft_check_cmd(data->v_cmd->cmd) ? ft_dir(data, &data->v_cmd->cmd, -1) : 0;
	data->v_cmd->red ? ft_red_array(data->v_cmd) : 0;
	data->v_cmd->wr_arr ? ft_valid_arr_str(data->v_cmd->wr_arr, data) : 0;
	data->v_cmd->arr_cmd ? ft_valid_arr_str(data->v_cmd->arr_cmd, data) : 0;
	data->v_cmd->cmd_arr ? ft_valid_arr_str(data->v_cmd->cmd_arr, data) : 0;
	!ft_strncmp(data->v_cmd->cmd, "echo", ft_strlen(data->v_cmd->cmd) + 1)
	? ft_skip_back_n(data->v_cmd->cmd_arr, data) : 0;
	data->v_cmd->arr_cmd = ft_arrstrjoin(data->v_cmd->arr_cmd,
	data->v_cmd->cmd_arr);
	!data->v_cmd->arr_cmd ? ft_error("malloc return NULL", 13) : 0;
	data->v_cmd->arr_cmd = ft_arrstrjoin(data->v_cmd->arr_cmd,
	data->v_cmd->wr_arr);
	!data->v_cmd->arr_cmd ? ft_error("malloc return NULL", 13) : 0;
	data->new_fd_f = -1;
	data->new_fd_n = -1;
}

static void	ft_bash_cmd_v2(t_data *data)
{
	if (data->v_cmd->p)
	{
		if (check_prev_pipe(data))
		{
			ft_pipe_pipe(data);
			data->fd1[0] = data->fd2[0];
			data->fd1[1] = data->fd2[1];
		}
		else
			ft_write_pipe(data, 0);
	}
	else
	{
		if (check_prev_pipe(data))
			ft_pipe_write(data);
		else
		{
			if ((data->new_fd_n == -1 && data->new_fd_f == -1)
			|| (ft_check_only_parents(data->v_cmd->cmd, data)))
				ft_exec_cmd(data);
			else if ((data->new_fd_n != -1 || data->new_fd_f != -1))
				ft_print_file_red(data);
		}
	}
}

void		ft_bash_cmd(t_data *data)
{
	while (data->v_cmd && data->v_cmd->cmd)
	{
		ft_bash_cmd_v1(data);
		if (!data->v_cmd->is_cmd)
		{
			if (ft_red_new(data, 0))
				ft_bash_cmd_v2(data);
			else
				data->v_cmd->is_ok = 0;
		}
		if (!data->v_cmd->next)
			return ;
		data->v_cmd = data->v_cmd->next;
	}
}
