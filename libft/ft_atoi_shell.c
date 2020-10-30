/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 21:37:35 by mizola            #+#    #+#             */
/*   Updated: 2020/10/12 21:37:36 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void			get_str_without_signs(const char *str,
					int *k, unsigned int *index)
{
	while ((str[*index] == ' ' || str[*index] == '\t'
	|| str[*index] == '\v' || str[*index] == '\f'
	|| str[*index] == '\r' || str[*index] == '\n')
	&& str[*index])
	{
		*index += 1;
	}
	if (str[*index] == '-' || str[*index] == '+')
	{
		if (str[*index] == '-')
			*k = -1;
		*index += 1;
	}
	while (str[*index] == '0' && str[*index])
		*index += 1;
}

unsigned long long	ft_atoi_shell(const char *str, int *valid)
{
	unsigned int		index;
	unsigned long long	number;
	int					k;
	long long			tmp;

	k = 1;
	index = 0;
	number = 0;
	get_str_without_signs(str, &k, &index);
	while (str[index] <= '9' && str[index] >= '0')
	{
		number = (number * 10) + (str[index] - '0');
		tmp = number;
		if ((number > 9223372036854775807) &&
		((tmp * (-1)) != (-9223372036854775807 - 1) || k > 0))
		{
			*valid = 1;
			return (0);
		}
		index++;
	}
	return (number);
}
