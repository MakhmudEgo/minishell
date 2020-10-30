/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_valid_arr_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 21:46:46 by mizola            #+#    #+#             */
/*   Updated: 2020/10/21 21:46:47 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	ft_valid_arr_str(char **str, t_data *data)
{
	int i;

	i = 0;
	while (str && str[i])
	{
		str[i] = ft_strtrim_free(str[i], " ");
		ft_valid_str(data, &str[i]);
		i++;
	}
}
