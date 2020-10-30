/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 18:15:58 by avallie           #+#    #+#             */
/*   Updated: 2020/10/20 18:15:59 by avallie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**env_cp(t_list *env)
{
	char	**res;
	int		i;

	i = ft_lstsize(env);
	!(res = malloc(sizeof(char **) * (i + 1)))
	? ft_error("malloc return NULL", 13) : (i = 0);
	while (env)
	{
		if (env->value && env->visible != 3)
		{
			!(res[i] = ft_strjoin(env->content, "="))
			? ft_error("malloc return NULL", 13) : 0;
			!(res[i] = ft_strjoin_free(res[i], ft_strdup(env->value)))
			? ft_error("malloc return NULL", 13) : 0;
		}
		else if (env->visible != 3)
			!(res[i] = ft_strdup(env->content))
			? ft_error("malloc return NULL", 13) : 0;
		env->visible != 3 ? i++ : 0;
		env = env->next;
	}
	res[i] = NULL;
	return (res);
}

static void	get_cont_val(const char *env, char **cont, char **val, int *vis)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (env[i] == '=')
		{
			!(*cont = ft_substr(env, 0, i))
			? ft_error("malloc return NULL", 13) : 0;
			if (env[i + 1] == '\0')
			{
				*val = 0x0;
				*vis = 0x0;
			}
			else
			{
				!(*val = ft_strdup(&env[i + 1]))
				? ft_error("malloc return NULL", 13) : 0;
				*vis = 1;
			}
			break ;
		}
		i++;
	}
}

char		*ft_getcwd(void)
{
	char	*dir;

	dir = 0x0;
	!(dir = getcwd(dir, 1)) ? ft_error(strerror(errno), 13) : 0;
	return (dir);
}

void		cp_env_lst(t_list **lst, const char **env, int p, int o)
{
	int		vis;
	char	*cont;
	char	*val;

	val = 0x0;
	cont = 0x0;
	while (env && *env && !(vis = 0))
	{
		get_cont_val(*env, &cont, &val, &vis);
		if (!ft_strncmp(cont, "OLDPWD", ft_strlen(cont) + 1) && (o = 1))
		{
			free(val);
			ft_lstadd_back(lst, ft_lstnew(cont, 0x0, 0));
		}
		else if (!ft_strncmp(cont, "PWD", ft_strlen(cont) + 1) && (p = 1))
		{
			free(val);
			ft_lstadd_back(lst, ft_lstnew(cont, ft_getcwd(), 1));
		}
		else
			ft_lstadd_back(lst, ft_lstnew(cont, val, vis));
		env++;
	}
	!p ? ft_lstadd_back(lst, ft_lstnew(ft_strdup("PWD"), ft_getcwd(), 1)) : 0;
	!o ? ft_lstadd_back(lst, ft_lstnew(ft_strdup("OLDPWD"), 0x0, 0)) : 0;
}
