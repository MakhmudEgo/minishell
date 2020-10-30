/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_back_n.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 18:53:24 by mizola            #+#    #+#             */
/*   Updated: 2020/10/19 18:53:25 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static char	**ft_arr_cp(char **free_arr, char **arr)
{
	int		i;
	char	**res;

	if (!free_arr || !arr)
		return (0x0);
	i = 0;
	!(res = malloc(sizeof(char **) * (ft_arrstrlen((const char **)arr) + 1)))
	? ft_error("malloc return NULL", 13) : 0;
	while (arr[i])
	{
		!(res[i] = ft_strdup(arr[i]))
		? ft_error("malloc return NULL", 13) : 0;
		i++;
	}
	res[i] = 0x0;
	ft_free_arrstr(free_arr);
	return (res);
}

void		ft_skip_back_n(char **arr, t_data *data)
{
	int		i;
	char	*tmp;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			tmp = arr[i];
			if (tmp[0] == '-' && tmp[1] != '\0'
				&& tmp[1] == 'n'
				&& tmp[2] == '\0')
				data->v_cmd->flag = 1;
			else
				break ;
			i++;
		}
		data->v_cmd->cmd_arr = ft_arr_cp(arr, &arr[i]);
	}
}
