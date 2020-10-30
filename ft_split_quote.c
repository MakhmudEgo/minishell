/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 16:05:28 by mizola            #+#    #+#             */
/*   Updated: 2020/10/16 16:05:29 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_am_str(const char *s, int v)
{
	int i;
	int n;
	int q;
	int q2;

	i = 0;
	n = s[0] == '\0' ? 0 : 1;
	q = 2;
	q2 = 2;
	ft_skip_space(&i, s);
	while (s[i])
	{
		quotes(s, i, &q, &q2);
		if (s[i - 1] != '\\' && s[i] == ' ' && q2 % 2 == 0 && q % 2 == 0)
		{
			if (v)
				return (i);
			while (s[i] && s[i] == ' ')
				i++;
			i--;
			n++;
		}
		s[i] != '\0' ? i++ : 0;
	}
	return (v ? i : n);
}

char		**ft_split_quote(char const *s)
{
	char	**res;
	int		i;
	int		n;
	int		j;

	n = 0;
	j = 0;
	if (!s)
		return (0x0);
	i = get_am_str(s, 0) + 1;
	!(res = malloc(sizeof(char**) * i))
	? ft_error("malloc return NULL", 13) : 0;
	res[i - 1] = 0x0;
	while (i)
	{
		if ((i = get_am_str(&s[n], 1)))
		{
			!(res[j++] = ft_substr(s, n, i))
			? ft_error("malloc return NULL", 13) : 0;
			n += i;
			res[j] = 0x0;
			ft_skip_space(&n, s);
		}
	}
	return (res);
}
