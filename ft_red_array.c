/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_red_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 20:14:38 by mizola            #+#    #+#             */
/*   Updated: 2020/10/20 20:14:39 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_size_red_arr(t_red *red)
{
	t_red	*tmp;
	int		i;

	tmp = red;
	i = 0;
	while (tmp)
	{
		if (ft_check_next_red(red) == 1 || ft_check_next_red(red) == 3)
			i++;
		else if (ft_check_next_red(red) == 2)
		{
			if (!ft_check_next_file(red))
				return (i);
			i++;
		}
		tmp = tmp->next;
	}
	return (i);
}

void	ft_red_array(t_ident *v_cmd)
{
	int		i;
	t_red	*tmp;
	int		len_tmp;

	len_tmp = ft_size_red_arr(v_cmd->red);
	tmp = v_cmd->red;
	!(v_cmd->wr_arr = malloc(sizeof(char **) * (len_tmp + 2)))
	? ft_error("malloc return NULL", 13) : 0;
	i = 0;
	while (tmp && i < len_tmp + 1)
	{
		if (tmp->red_str)
		{
			!(v_cmd->wr_arr[i] = ft_strdup(tmp->red_str))
			? ft_error("malloc return NULL", 13) : 0;
			i++;
		}
		tmp = tmp->next;
	}
	v_cmd->wr_arr[i] = 0x0;
}

void	ft_wr_array(t_data *data, int fd)
{
	int	i;

	i = 1;
	while (data->v_cmd->arr_cmd[i])
	{
		ft_putstr_fd(data->v_cmd->arr_cmd[i], fd);
		i++;
		if (data->v_cmd->arr_cmd[i] && data->v_cmd->arr_cmd[i][0] != '\0')
			ft_putchar_fd(' ', fd);
	}
	if (!data->v_cmd->flag)
		ft_putchar_fd('\n', fd);
}
