/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 21:26:41 by avallie           #+#    #+#             */
/*   Updated: 2020/10/20 21:27:06 by avallie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_pipe_pipe_v2(t_data *data)
{
	close(data->fd2[0]);
	if (data->new_fd_n == -1 && (data->v_cmd->prev && data->v_cmd->prev->is_ok))
	{
		dup2(data->fd1[0], 0);
		if (check_prev_pipe_red(data->v_cmd))
			close(data->fd1[0]);
	}
	else if (data->new_fd_n != -1)
		dup2(data->new_fd_n, 0);
	if (data->new_fd_f == -1)
		dup2(data->fd2[1], 1);
	else
		dup2(data->new_fd_f, 1);
	if (data->v_cmd->prev && !data->v_cmd->prev->is_ok)
	{
		pipe(data->fd1);
		write(data->fd1[1], "", 0);
		dup2(data->fd1[0], 0);
		close(data->fd1[1]);
	}
	ft_exec_cmd(data);
	exit(g_code);
}

void		ft_pipe_pipe(t_data *data)
{
	pid_t	pid;
	int		status;

	pipe(data->fd2);
	pid = fork();
	if (pid == 0)
		ft_pipe_pipe_v2(data);
	else if (pid < 0)
		ft_error(strerror(errno), 15);
	if (data->v_cmd->prev && data->v_cmd->is_ok)
		close(data->fd1[0]);
	close(data->fd2[1]);
	if (data->new_fd_f != -1)
		close(data->new_fd_f);
	if (data->new_fd_n != -1)
		close(data->new_fd_n);
	wait(&status);
	g_code = status;
}

void		ft_write_pipe(t_data *data, int status)
{
	pid_t	pid;

	pipe(data->fd1);
	pid = fork();
	if (pid == 0)
	{
		close(data->fd1[0]);
		if (data->new_fd_f == -1)
			dup2(data->fd1[1], 1);
		else
			dup2(data->new_fd_f, 1);
		if (data->new_fd_n != -1)
			dup2(data->new_fd_n, 0);
		ft_exec_cmd(data);
		exit(g_code);
	}
	else if (pid < 0)
		ft_error(strerror(errno), 15);
	close(data->fd1[1]);
	if (data->new_fd_f != -1)
		close(data->new_fd_f);
	if (data->new_fd_n != -1)
		close(data->new_fd_n);
	wait(&status);
	g_code = status;
}

static void	ft_pipe_write_v2(t_data *data)
{
	if (data->new_fd_n == -1 && (data->v_cmd->prev && data->v_cmd->prev->is_ok))
	{
		dup2(data->fd1[0], 0);
		if (check_prev_pipe_red(data->v_cmd))
			close(data->fd1[0]);
	}
	else if (data->new_fd_n != -1)
	{
		dup2(data->new_fd_n, 0);
	}
	if (data->new_fd_f != -1)
		dup2(data->new_fd_f, 1);
	if (data->v_cmd->prev && !data->v_cmd->prev->is_ok)
	{
		pipe(data->fd1);
		write(data->fd1[1], "", 0);
		dup2(data->fd1[0], 0);
		close(data->fd1[1]);
	}
	ft_exec_cmd(data);
	exit(g_code);
}

void		ft_pipe_write(t_data *data)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		ft_pipe_write_v2(data);
	else if (pid < 0)
		ft_error(strerror(errno), 15);
	if (data->v_cmd->prev && data->v_cmd->prev->is_ok)
		close(data->fd1[0]);
	if (data->new_fd_f != -1)
		close(data->new_fd_f);
	if (data->new_fd_n != -1)
		close(data->new_fd_n);
	wait(&status);
	g_code = status;
}
