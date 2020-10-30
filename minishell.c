/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 09:16:53 by mizola            #+#    #+#             */
/*   Updated: 2020/10/01 09:16:54 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sh_loop(t_data *data)
{
	while (1)
	{
		write(1, "minishell->", 11);
		if (!get_next_line(&g_buf))
		{
			write(1, " exit\n", 6);
			exit(0);
		}
		if (g_buf)
		{
			!(data->is_valid_str = ft_strtrim_free(ft_strdup(g_buf), " "))
			? ft_error("malloc return NULL", 13) : 0;
			ft_parse(data, g_buf);
		}
		data->v_cmd ? ft_free_xxx(data->v_cmd) : 0;
		free(data->is_valid_str);
		free(g_buf);
		g_buf = 0x0;
		ft_data_init(data);
		signal(SIGINT, ft_sig);
		signal(SIGQUIT, ft_sig);
		signal(SIGTERM, ft_sig);
	}
}

void	ft_sig(int sig)
{
	if (sig == SIGQUIT)
	{
		write(1, "\b\b  \b\b", 6);
	}
	else if (sig == SIGINT)
	{
		write(1, "\b\b  \b\b", 6);
		g_buf[0] = '\0';
		write(1, "\nminishell->", 13);
		g_code = 1;
	}
}

int		main(int ac, char **av, char **env)
{
	t_data data;

	if (ac && av)
	{
	}
	g_buf = 0x0;
	data.env = 0x0;
	g_code = 0x0;
	signal(SIGINT, ft_sig);
	signal(SIGQUIT, ft_sig);
	signal(SIGTERM, ft_sig);
	cp_env_lst(&data.env, (const char**)env, 0, 0);
	ft_data_init(&data);
	ft_sh_loop(&data);
	return (0);
}
