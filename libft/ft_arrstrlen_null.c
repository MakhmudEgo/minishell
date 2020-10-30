/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrstrlen_null.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 21:49:32 by mizola            #+#    #+#             */
/*   Updated: 2020/10/10 21:49:33 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_arrstrlen_null(const char **arrstr)
{
	int i;

	i = 0;
	while (arrstr && arrstr[i])
		i++;
	return (i);
}
