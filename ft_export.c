/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 17:46:14 by mizola            #+#    #+#             */
/*   Updated: 2020/10/04 17:46:15 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		sort_exp(char **env)
{
	int		len;
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	len = ft_arrstrlen((const char **)env);
	while (i < len - 1)
	{
		j = 0;
		while (j < len - 1)
		{
			if (ft_strncmp(env[j], env[j + 1], ft_strlen(env[j])) > 0)
			{
				tmp = env[j + 1];
				env[j + 1] = env[j];
				env[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

int			is_valid_var(char *s, char *err)
{
	int i;

	i = 0;
	if (!s[0])
	{
		ft_putstr_fd(err, 2);
		ft_putstr_fd(s, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		g_code = 1;
		return (0);
	}
	while (s && s[i] && (s[i] != '=' || s[0] == '='))
	{
		if (s[0] == '=' || ft_isdigit(s[0])
		|| (!ft_isalnum(s[i]) && s[i] != 95))
		{
			ft_putstr_fd(err, 2);
			ft_putstr_fd(s, 2);
			ft_putendl_fd("': not a valid identifier", 2);
			g_code = 1;
			return (0);
		}
		i++;
	}
	return (1);
}

static void	ft_export_print(char *exp)
{
	int j;

	j = 0;
	write(1, "declare -x ", 11);
	while (exp[j] != '=' && exp[j] != '\0')
		write(1, &exp[j++], 1);
	if (exp[j] == '=')
	{
		j++;
		write(1, "=\"", 2);
		while (exp[j] != '\0')
			write(1, &exp[j++], 1);
		write(1, "\"", 1);
	}
	write(1, "\n", 1);
}

void		ft_export(t_data *data)
{
	char	**exp;
	int		i;

	if (data->v_cmd->arr_cmd)
		ft_valid_arr_str(data->v_cmd->arr_cmd, data);
	exp = env_cp(data->env);
	sort_exp(exp);
	i = 0;
	if (!data->v_cmd->arr_cmd[1])
	{
		while (exp[i])
			ft_export_print(exp[i++]);
		g_code = 0;
	}
	else
		ft_add_elem_env(data, 1);
	ft_free_arrstr(exp);
}
