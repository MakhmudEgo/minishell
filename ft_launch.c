/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 09:16:38 by mizola            #+#    #+#             */
/*   Updated: 2020/10/01 09:16:39 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			status_return(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 2)
			return (130);
		if (WTERMSIG(status) == 3)
			return (131);
		if (WTERMSIG(status) == 15)
			return (143);
	}
	return (WEXITSTATUS(status));
}

int			check_prev_pipe(t_data *data)
{
	t_ident *tmp;

	tmp = data->v_cmd;
	if (tmp->prev)
	{
		tmp = tmp->prev;
		if (tmp->p)
			return (1);
	}
	return (0);
}

static void	launch_v2(pid_t pid, int status)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	pid = waitpid(pid, &status, WUNTRACED);
	if ((g_code = status_return(status)) == 130)
		write(2, "\n", 1);
	if (g_code == 131)
		write(2, "Quit: 3\n", 8);
	if (g_code == 143)
		write(2, "terminated\n", 11);
}

int			lsh_launch(char **args, t_data *data)
{
	int		status;
	pid_t	pid;
	char	**env;

	if (!check_exec_launch(args[0], ": Permission denied", 126))
		return (g_code);
	env = env_cp(data->env);
	status = 0;
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTERM, SIG_DFL);
		if ((status = execve(data->v_cmd->cmd, args, env)) == -1)
			exit(WEXITSTATUS(status));
	}
	else if (pid < 0)
		ft_error(strerror(errno), 15);
	else
		launch_v2(pid, status);
	ft_free_arrstr(env);
	return (g_code);
}
