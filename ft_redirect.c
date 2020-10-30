/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 18:30:58 by mizola            #+#    #+#             */
/*   Updated: 2020/10/20 18:30:59 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_new_file_red_p2(t_red **tmp_red, int fd)
{
	if (!(fd = fd_creat_or_add_file((*tmp_red)->file)))
		return (0);
	close(fd);
	if (ft_check_next_red(*tmp_red) == 2 && (!ft_check_red_two(tmp_red)))
		return (0);
	return (1);
}

static int	ft_new_file_red_p1(t_red **tmp_red, int fd)
{
	if ((*tmp_red)->red == 1)
	{
		if (!(fd = ft_creat_file((*tmp_red)->file)))
			return (0);
		close(fd);
		if (ft_check_next_red(*tmp_red) == 2 && (!ft_check_red_two(tmp_red)))
			return (0);
		else if (ft_check_next_red(*tmp_red) == -1)
			return (1);
	}
	else if ((*tmp_red)->red == 2)
	{
		if ((ft_open_next_two(tmp_red, 0)) == -1)
			return (0);
	}
	else if ((*tmp_red)->red == 3)
	{
		return (ft_new_file_red_p2(tmp_red, fd));
	}
	return (2);
}

int			ft_new_file_red(t_ident *ident, t_data *data)
{
	int		fd;
	t_red	*tmp_red;

	while (ident)
	{
		tmp_red = ident->red;
		while (tmp_red)
		{
			ft_valid_str(data, &ident->red->file);
			if (tmp_red->red == 1 || tmp_red->red == 2 || tmp_red->red == 3)
			{
				if ((fd = ft_new_file_red_p1(&tmp_red, fd)) != 2)
					break ;
			}
			else if (tmp_red->red == 4)
			{
				if (!(fd = fd_creat_or_add_file(tmp_red->file)))
					return (0);
				close(fd);
			}
			tmp_red = tmp_red->next;
		}
		ident = ident->next;
	}
	return (1);
}
