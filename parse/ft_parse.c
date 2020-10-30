/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 12:31:18 by mizola            #+#    #+#             */
/*   Updated: 2020/10/01 12:31:19 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	ft_if_first_red(t_data *data, char *cmd, int *i, int *n)
{
	t_ident	*new_i;
	char	*tmp;

	!(new_i = malloc(sizeof(t_ident))) ? ft_error("malloc return NULL", 13) : 0;
	ft_ident_init(new_i);
	ft_get_red_val_init(new_i, i, n, cmd);
	*n = ft_get_len_str_cmd(cmd, *i, 1);
	*n != 0 ? new_i->cmd = ft_substr(cmd, *i, *n) : 0;
	*n != 0 && !new_i->cmd ? ft_error("malloc return NULL", 13) : 0;
	*i += *n;
	*n = ft_get_len_str_cmd(cmd, *i, 0);
	!(tmp = ft_substr(cmd, *i, *n)) && n != 0
	? ft_error("malloc return NULL", 13) : 0;
	new_i->cmd_arr = ft_split_quote(tmp);
	free(tmp);
	*i += *n;
	ft_skip_space(i, cmd);
	ft_get_red_val_init(new_i, i, n, cmd);
	new_i->p = (cmd[*i] == '|') ? 1 : 0;
	ft_identlstback(&data->v_cmd, new_i);
}

static void	ft_get_val_for_new_i(t_data *data, char *cmd, int *i, int *n)
{
	t_ident	*new_i;
	char	*tmp;

	!(new_i = malloc(sizeof(t_ident))) ? ft_error("malloc return NULL", 13) : 0;
	ft_ident_init(new_i);
	new_i->cmd = data->cmd;
	ft_skip_space(i, cmd);
	if ((*n = ft_get_len_str_cmd(cmd, *i, 0)))
	{
		!(tmp = ft_substr(cmd, *i, *n))
		? ft_error("malloc return NULL", 13) : 0;
		new_i->cmd_arr = ft_split_quote(tmp);
		free(tmp);
		*i += *n;
	}
	ft_skip_space(i, cmd);
	ft_get_red_val_init(new_i, i, n, cmd);
	new_i->p = (cmd[*i] == '|') ? 1 : 0;
	ft_identlstback(&data->v_cmd, new_i);
}

int			check_valid_red(t_data *data)
{
	t_ident		*tmp;
	t_red		*tmp_red;

	tmp = data->v_cmd;
	while (tmp)
	{
		tmp_red = tmp->red;
		while (tmp_red)
		{
			if (!tmp_red->file || (tmp_red->file && !ft_strlen(tmp_red->file)))
			{
				g_code = 258;
				ft_putendl_fd("syntax error near unexpected token `newline'",
				2);
				return (0);
			}
			tmp_red = tmp_red->next;
		}
		tmp = tmp->next;
	}
	return (1);
}

void		ft_parse(t_data *data, char *cmd)
{
	int		n;
	int		i;

	i = 0;
	if (!ft_is_valid_cmd(data->is_valid_str, 0, 2, 2))
		return ;
	while (cmd[i] != '\0')
	{
		n = ft_get_len_str_cmd(cmd, i, 1);
		data->cmd = n != 0 ? ft_substr(cmd, i, n) : 0x0;
		n != 0 && !data->cmd ? ft_error("malloc return NULL", 13) : 0;
		i += n;
		if (!n && (cmd[i] == '>' || cmd[i] == '<'))
			ft_if_first_red(data, cmd, &i, &n);
		else if (data->cmd)
			ft_get_val_for_new_i(data, cmd, &i, &n);
		cmd[i] == '\0' ? i : i++;
		ft_skip_space(&i, cmd);
	}
	if (check_valid_red(data))
	{
		data->v_cmd ? ft_new_file_red(data->v_cmd, data) : 0;
		ft_bash_cmd(data);
	}
}
