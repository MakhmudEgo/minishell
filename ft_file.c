/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 18:31:46 by mizola            #+#    #+#             */
/*   Updated: 2020/10/20 18:31:47 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_creat_file(char *file)
{
	int fd;

	if ((fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)
	{
		g_code = 258;
		return (0);
	}
	return (fd);
}

int		fd_creat_or_add_file(char *file)
{
	int fd;

	if ((fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0666)) == -1)
	{
		g_code = 258;
		return (0);
	}
	return (fd);
}

int		fd_open_file(char *file)
{
	int fd;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (-1);
	return (fd);
}

int		ft_check_next_file(t_red *lst)
{
	t_red	*tmp;
	int		fd;

	tmp = lst;
	if (tmp && tmp->next)
	{
		tmp = tmp->next;
		if ((fd = open(tmp->file, O_RDONLY)) == -1)
			return (0);
		close(fd);
		return (1);
	}
	return (0);
}
