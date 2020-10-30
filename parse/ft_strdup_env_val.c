/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_env_val.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 21:45:50 by mizola            #+#    #+#             */
/*   Updated: 2020/10/18 21:45:51 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	*ft_strdup_env_val(char *dol, t_list *data)
{
	char *res;

	res = 0x0;
	while (data)
	{
		if (!ft_strncmp(dol, data->content, ft_strlen(dol) + 1))
		{
			if (data->value)
				!(res = ft_strdup(data->value))
				? ft_error("malloc return NULL", 13) : 0;
			break ;
		}
		data = data->next;
	}
	free(dol);
	return (res);
}
