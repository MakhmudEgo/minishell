/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 09:40:16 by mizola            #+#    #+#             */
/*   Updated: 2020/10/09 09:40:17 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_puterr(char *s1, char *s2, int err)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(s1, 2);
	ft_putendl_fd(s2, 2);
	g_code = err;
}

static void	ft_dir_p2(t_data *data, char **cmd)
{
	if (ft_strncmp(*cmd, "/", 1))
	{
		if (ft_strncmp(*cmd, "./", 2))
		{
			data->v_cmd->is_cmd = 1;
			if (!ft_strncmp(*cmd, ".", 2))
				ft_puterr(*cmd, ": filename argument required", 2);
			else if (!ft_strncmp(*cmd, "..", 3))
				ft_puterr(*cmd, ": command not found", 127);
			else
				ft_puterr(*cmd, ": command not found", 127);
		}
		else
		{
			if (ft_strncmp(*cmd, "./", 3))
				!check_exec_str(&data->v_cmd->cmd[2],
				": No such file or directory", 127)
				? (data->v_cmd->is_cmd = 1) : 0;
			else if ((!ft_strncmp(*cmd, ".", 2)) && (data->v_cmd->is_cmd = 1))
				ft_puterr(*cmd, ": filename argument required", 2);
			else if (!(ft_strncmp(*cmd, "..", 3)) && (data->v_cmd->is_cmd = 1))
				ft_puterr(*cmd, ": command not found", 127);
		}
	}
}

void		check_reg(char **cmd, t_data *data)
{
	int		i;
	char	*tmp;
	char	*tmp_cmd;

	tmp_cmd = ft_strdup(*cmd);
	i = 0;
	tmp = *cmd;
	while (tmp && tmp[i])
	{
		tmp[i] = (char)ft_tolower(tmp[i]);
		i++;
	}
	if (!(strncmp(tmp, "cd", ft_strlen(tmp) + 1))
	&& ((strncmp(tmp_cmd, tmp, ft_strlen(tmp_cmd)))))
		data->v_cmd->is_cmd = 1;
	if (!(strncmp(tmp, "exit", ft_strlen(tmp) + 1)) ||
	(!(ft_strncmp(tmp, "export", ft_strlen(tmp) + 1)))
	|| (!(ft_strncmp(tmp, "unset", ft_strlen(tmp) + 1))))
	{
		free(tmp);
		*cmd = tmp_cmd;
	}
	else
		free(tmp_cmd);
}

void		ft_dir(t_data *data, char **cmd, int i)
{
	t_dir	*dir_el;
	DIR		*dir;
	char	*tmp;

	dirs_init(data);
	while (data->v_cmd->dirs && data->v_cmd->dirs[++i])
		if ((dir = opendir(data->v_cmd->dirs[i])))
		{
			while ((dir_el = readdir(dir)))
				if ((!ft_strncmp(*cmd, dir_el->d_name,
					ft_strlen(dir_el->d_name) + 1))
					&& ft_strncmp(*cmd, ".", 2) && ft_strncmp(*cmd, "..", 3))
				{
					tmp = *cmd;
					*cmd = ft_strjoin("/", *cmd);
					free(tmp);
					tmp = *cmd;
					*cmd = ft_strjoin(data->v_cmd->dirs[i], *cmd);
					free(tmp);
					(i = closedir(dir)) ? exit(32) : 0;
					return ;
				}
			(closedir(dir)) ? exit(32) : 0;
		}
	ft_dir_p2(data, cmd);
}
