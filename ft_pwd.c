/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 09:16:41 by mizola            #+#    #+#             */
/*   Updated: 2020/10/01 09:16:41 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_data *data)
{
	char *dir;

	dir = 0x0;
	!(dir = getcwd(dir, 1)) ? ft_error(strerror(errno), 13) : 0;
	ft_putendl_fd(dir, data->st_fd_f);
	free(dir);
	g_code = 0;
}
