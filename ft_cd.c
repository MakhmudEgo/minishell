/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 09:16:32 by mizola            #+#    #+#             */
/*   Updated: 2020/10/01 09:16:33 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			cd_home(t_data *data)
{
	char	*dir;
	char	*err;
	t_list	*tmp;

	tmp = data->env;
	dir = get_env_value_ptr(tmp, "HOME");
	if (chdir(dir) != 0)
	{
		err = strerror(errno);
		ft_putendl_fd(err, 2);
		g_code = 1;
		return (0);
	}
	return (1);
}

int			cd_oldpwd(t_data *data)
{
	char	*dir;
	char	*err;
	t_list	*tmp;

	tmp = data->env;
	dir = get_env_value_ptr(tmp, "OLDPWD");
	ft_putendl_fd(dir, 1);
	if (chdir(dir) != 0)
	{
		err = strerror(errno);
		ft_putendl_fd(err, 2);
		g_code = 1;
		return (0);
	}
	return (1);
}

int			cd_dir(t_data *data)
{
	char	*err;

	if (chdir(data->v_cmd->cmd_arr[0]) != 0)
	{
		err = strerror(errno);
		ft_putendl_fd(err, 2);
		g_code = 1;
		return (0);
	}
	return (1);
}

static void	ft_cd_v1(t_data *data)
{
	t_list	*tmp;
	char	*dir;

	tmp = data->env;
	dir = 0x0;
	!(dir = getcwd(dir, 1)) ? ft_error(strerror(errno), 13) : 0;
	while (tmp)
	{
		if (!(ft_strncmp(tmp->content, "PWD", 4)))
		{
			if (!get_env_content_ptr(data->env, "OLDPWD"))
				ft_lstadd_back(&data->env,
			ft_lstnew(ft_strdup("OLDPWD"), ft_strdup(tmp->value), 3));
			init_oldpwd(data->env, "OLDPWD", tmp->value);
			tmp->value = dir;
			break ;
		}
		tmp = tmp->next;
	}
	g_code = 0;
}

void		ft_cd(t_data *data)
{
	char	*dir;
	t_list	*tmp;

	dir = 0x0;
	tmp = data->env;
	if (!get_env_value_ptr(tmp, "PWD"))
		!(dir = getcwd(dir, 1)) ? ft_error(strerror(errno), 13) :
		ft_lstadd_back(&data->env, ft_lstnew(ft_strdup("PWD"), dir, 3));
	if (!data->v_cmd->cmd_arr)
	{
		if (!(cd_home(data)))
			return ;
	}
	else if (data->v_cmd->cmd_arr
	&& data->v_cmd->cmd_arr[0][0] == '-' && data->v_cmd->cmd_arr[0][1] == '\0')
	{
		if (!(cd_oldpwd(data)))
			return ;
	}
	else
	{
		if (!(cd_dir(data)))
			return ;
	}
	ft_cd_v1(data);
}
