/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 20:04:23 by mizola            #+#    #+#             */
/*   Updated: 2020/10/20 20:04:24 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_next_red(t_red *lst)
{
	t_red *tmp;

	tmp = lst;
	if (tmp && tmp->next)
	{
		tmp = tmp->next;
		if (tmp->red == 1)
			return (1);
		else if (tmp->red == 2)
			return (2);
		else if (tmp->red == 3)
			return (3);
		else if (tmp->red == 4)
			return (4);
	}
	return (-1);
}

int	ft_check_red_two(t_red **red)
{
	int		fd;
	t_red	*tmp;

	tmp = *red;
	tmp = tmp->next;
	while (tmp && tmp->red == 2)
	{
		if ((fd = fd_open_file(tmp->file)) == -1)
		{
			*red = tmp;
			return (0);
		}
		close(fd);
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
	if (tmp->prev)
		*red = tmp->prev;
	return (1);
}

int	ft_open_next_two(t_red **red, int check)
{
	int		fd;
	t_red	*tmp;

	tmp = *red;
	while (tmp && tmp->red == 2)
	{
		if (check && (!check_red_file(tmp->file, ": Permission denied", 1)))
			return (-1);
		if ((fd = fd_open_file(tmp->file)) == -1)
		{
			*red = tmp;
			return (-1);
		}
		if (tmp->next && ft_check_next_red(tmp) == 2)
			close(fd);
		else
		{
			*red = tmp;
			return (fd);
		}
		tmp = tmp->next;
	}
	return (fd);
}
