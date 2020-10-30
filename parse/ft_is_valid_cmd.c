/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_valid_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 21:52:36 by mizola            #+#    #+#             */
/*   Updated: 2020/10/18 21:52:37 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	is_valid_cmd_else(const char *cmd, int i)
{
	char c1;
	char c2;

	c1 = cmd[i];
	i++;
	ft_skip_space(&i, cmd);
	if ((cmd[i] == ';' || cmd[i] == '|'))
	{
		c2 = cmd[i];
		ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
		write(2, &cmd[i], 1);
		c1 == c2 && cmd[i] == cmd[i - 1] ? write(2, &cmd[i], 1) : 0;
		write(2, "'\n", 2);
		g_code = 258;
		return (0);
	}
	return (1);
}

int			ft_is_valid_cmd(const char *cmd, int i, int q, int q2)
{
	while (cmd[i])
	{
		cmd[i - 1] != '\\' && cmd[i] == '\'' && q2 % 2 == 0 ? q++ : 0;
		cmd[i - 1] != '\\' && cmd[i] == '\"' && q % 2 == 0 ? q2++ : 0;
		if (cmd[i - 1] != '\\')
		{
			if (cmd[0] == ';' || cmd[0] == '|')
			{
				ft_putstr_fd("minishell: syntax error near "
				"unexpected token '", 2);
				write(2, &cmd[i], 1);
				cmd[0] == cmd[1] ? write(2, &cmd[i], 1) : 0;
				write(2, "'\n", 2);
				g_code = 258;
				return (0);
			}
			else if ((cmd[i] == ';' && q2 % 2 == 0 && q % 2 == 0)
			|| (cmd[i] == '|' && q2 % 2 == 0 && q % 2 == 0))
				if (!is_valid_cmd_else(cmd, i))
					return (0);
		}
		i++;
	}
	return (1);
}
