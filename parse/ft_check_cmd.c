/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 21:39:14 by mizola            #+#    #+#             */
/*   Updated: 2020/10/18 21:39:15 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int		ft_check_cmd(const char *s)
{
	if (ft_strncmp(s, "echo", ft_strlen(s) + 1)
	&& ft_strncmp(s, "cd", ft_strlen(s) + 1)
	&& ft_strncmp(s, "pwd", ft_strlen(s) + 1)
	&& ft_strncmp(s, "export", ft_strlen(s) + 1)
	&& ft_strncmp(s, "unset", ft_strlen(s) + 1)
	&& ft_strncmp(s, "env", ft_strlen(s) + 1)
	&& ft_strncmp(s, "exit", ft_strlen(s) + 1))
		return (0);
	return (1);
}

int		ft_check_only_parents(const char *s, t_data *data)
{
	if (ft_strncmp(s, "cd", ft_strlen(s) + 1)
		&& ft_strncmp(s, "export", ft_strlen(s) + 1)
		&& ft_strncmp(s, "unset", ft_strlen(s) + 1)
		&& ft_strncmp(s, "exit", ft_strlen(s) + 1))
		return (0);
	if (!ft_strncmp(data->v_cmd->cmd, "export",
	ft_strlen(data->v_cmd->cmd)) && !data->v_cmd->arr_cmd[1])
		return (0);
	return (1);
}
