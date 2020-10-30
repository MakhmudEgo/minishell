/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 18:12:03 by avallie           #+#    #+#             */
/*   Updated: 2020/10/20 18:12:04 by avallie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*char_join(char *str, char c)
{
	int		i;
	char	*res;

	i = 0;
	res = NULL;
	!(res = (char *)malloc(ft_strlen_null(str) + 2))
	? ft_error("malloc return NULL", 13) : 0;
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i++] = c;
	res[i] = '\0';
	free(str);
	str = NULL;
	return (res);
}

int		get_next_line(char **line)
{
	int		b;
	char	buf_gnl;

	buf_gnl = 0x0;
	!(*line = (char *)malloc(1))
	? ft_error("malloc return NULL", 13) : 0;
	**line = '\0';
	while ((b = read(0, &buf_gnl, 1)) > 0
	|| ((buf_gnl != '\0') && b == 0))
	{
		if ((buf_gnl != '\0') && b == 0)
			continue;
		if (buf_gnl == '\n')
			return (1);
		*line = char_join(*line, buf_gnl);
	}
	return (0);
}
