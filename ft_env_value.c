/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 23:41:54 by avallie           #+#    #+#             */
/*   Updated: 2020/10/20 23:41:56 by avallie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value_ptr(t_list *env, char *str)
{
	t_list	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!(ft_strncmp(tmp->content, str, ft_strlen(tmp->content) + 1)))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (0x0);
}

char	*get_env_content_ptr(t_list *env, char *str)
{
	t_list	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!(ft_strncmp(tmp->content, str, ft_strlen(tmp->content) + 1)))
			return (tmp->content);
		tmp = tmp->next;
	}
	return (0x0);
}

void	init_oldpwd(t_list *env, char *str, char *val)
{
	int	i;

	i = ft_strlen(str) + 1;
	while (env)
	{
		if (!(ft_strncmp(env->content, str, i)))
		{
			env->value ? free(env->value) : 0;
			env->value = val;
			break ;
		}
		env = env->next;
	}
}
