/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 00:39:57 by avallie           #+#    #+#             */
/*   Updated: 2020/10/21 00:39:59 by avallie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*get_env_ptr(t_list *env, char *str)
{
	while (env)
	{
		if (!(ft_strncmp(env->content, str, ft_strlen(env->content) + 1)))
			return (env);
		env = env->next;
	}
	return (0x0);
}

static int		ft_change_env_value(t_data *data,
				char *content, char *value, int vis)
{
	t_list *tmp;

	if (!(tmp = get_env_ptr(data->env, content)))
		return (0);
	free(content);
	if (vis)
	{
		free(tmp->value);
		tmp->value = value;
		tmp->visible = vis;
		return (1);
	}
	tmp && tmp->value ? tmp->visible = 1 : 0;
	return (1);
}

static void		ft_add_elem_env_p2(t_data *data, char *content, int *i, int j)
{
	char *value;

	value = 0x0;
	if (data->v_cmd->arr_cmd[*i][j] == '=')
	{
		!(value = ft_strdup(""))
		? ft_error("malloc return NULL", 13) : 0;
		j++;
	}
	while (data->v_cmd->arr_cmd[*i][j])
		value = char_join(value, data->v_cmd->arr_cmd[*i][j++]);
	if (value)
		ft_change_env_value(data, content, value, 1);
	else
		ft_change_env_value(data, content, 0x0, 0);
}

static void		ft_add_elem_env_p1(t_data *data, char *content, int *i, int j)
{
	char *value;

	value = 0x0;
	if (data->v_cmd->arr_cmd[*i][j] == '=')
	{
		!(value = ft_strdup(""))
		? ft_error("malloc return NULL", 13) : 0;
		j++;
	}
	while (data->v_cmd->arr_cmd[*i][j])
		value = char_join(value, data->v_cmd->arr_cmd[*i][j++]);
	if (value)
	{
		if (!ft_change_env_value(data, content, value, 1))
			ft_lstadd_back(&data->env, ft_lstnew(content, value, 1));
	}
	else
	{
		if (!ft_change_env_value(data, content, value, 1))
			ft_lstadd_back(&data->env, ft_lstnew(content, 0x0, 0));
	}
}

void			ft_add_elem_env(t_data *data, int i)
{
	char	*content;
	int		j;
	int		ex;

	ex = 0;
	while (data->v_cmd->arr_cmd[i])
	{
		if (is_valid_var(data->v_cmd->arr_cmd[i], "minishell: export: `"))
		{
			j = 0;
			!(content = ft_calloc(1, sizeof(char)))
			? ft_error("malloc return NULL", 13) : 0;
			while (data->v_cmd->arr_cmd[i][j]
			&& data->v_cmd->arr_cmd[i][j] != '=')
				content = char_join(content, data->v_cmd->arr_cmd[i][j++]);
			if (!get_env_value_ptr(data->env, content))
				ft_add_elem_env_p1(data, content, &i, j);
			else
				ft_add_elem_env_p2(data, content, &i, j);
		}
		else
			ex = 1;
		i++;
	}
	g_code = ex ? g_code : ex;
}
