/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 09:50:10 by mizola            #+#    #+#             */
/*   Updated: 2020/10/07 09:50:11 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char			*str;
	unsigned int	len;
	unsigned int	i;
	unsigned int	n;

	len = ft_strlen_null(s1) + ft_strlen_null(s2) + 1;
	i = 0;
	n = 0;
	str = (char*)malloc(len);
	if (str == NULL)
		return (NULL);
	while (s1 && s1[n] != '\0')
		str[i++] = s1[n++];
	n = 0;
	while (s2 && s2[n] != '\0')
		str[i++] = s2[n++];
	str[i] = '\0';
	free(s1);
	free(s2);
	s1 = 0x0;
	s2 = 0x0;
	return (str);
}
