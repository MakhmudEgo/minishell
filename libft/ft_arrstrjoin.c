/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrstrjoin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 21:39:51 by mizola            #+#    #+#             */
/*   Updated: 2020/10/10 21:41:31 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_arrstrjoin(char **arrstr1, char **arrstr2)
{
	char	**res;
	int		i;
	int		n;

	i = 0;
	n = 0;
	if (!(res = malloc(sizeof(char **) *
	(ft_arrstrlen_null((const char **)arrstr1)
	+ ft_arrstrlen_null((const char **)arrstr2) + 1))))
		return (NULL);
	while (arrstr1 && arrstr1[i])
	{
		!(res[i] = ft_strdup(arrstr1[i]))
		? ft_error("malloc return NULL", 13) : 0;
		i++;
	}
	while (arrstr2 && arrstr2[n])
		!(res[i++] = ft_strdup(arrstr2[n++]))
		? ft_error("malloc return NULL", 13) : 0;
	res[i] = 0x0;
	ft_free_arrstr(arrstr1);
	return (res);
}

char	**ft_arrstrjoin_free(char **arrstr1, char **arrstr2)
{
	char	**res;
	int		i;
	int		n;

	i = 0;
	n = 0;
	if (!(res = malloc(sizeof(char **) *
	(ft_arrstrlen_null((const char **)arrstr1)
	+ ft_arrstrlen_null((const char **)arrstr2) + 1))))
		return (NULL);
	while (arrstr1 && arrstr1[i])
	{
		!(res[i] = ft_strdup(arrstr1[i]))
		? ft_error("malloc return NULL", 13) : 0;
		i++;
	}
	while (arrstr2 && arrstr2[n])
		!(res[i++] = ft_strdup(arrstr2[n++]))
		? ft_error("malloc return NULL", 13) : 0;
	res[i] = 0x0;
	ft_free_arrstr(arrstr1);
	ft_free_arrstr(arrstr2);
	return (res);
}
