/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 17:25:25 by avallie           #+#    #+#             */
/*   Updated: 2020/10/24 17:25:26 by avallie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_exec_launch(char *args, char *err, int code)
{
	struct stat		buf;

	stat(args, &buf);
	if (buf.st_mode & S_IFREG)
	{
		if (!(buf.st_mode & S_IXUSR))
		{
			ft_puterr(args, err, code);
			return (0);
		}
	}
	else if (S_ISDIR(buf.st_mode))
	{
		ft_puterr(args, ": is a directory", 126);
		return (0);
	}
	else if (args[0] == '/' && (!(buf.st_mode & S_IFREG)))
	{
		ft_puterr(args, ": No such file or directory", 127);
		return (0);
	}
	return (1);
}

int		check_exec_str(char *str, char *err, int code)
{
	struct stat	buf;

	stat(str, &buf);
	if (!(buf.st_mode & S_IFREG))
	{
		ft_puterr(str, err, code);
		return (0);
	}
	return (1);
}

int		check_red_file(char *str, char *err, int code)
{
	struct stat	buf;

	if ((stat(str, &buf)))
	{
		ft_puterr(str, ": No such file or directory", 1);
		return (0);
	}
	if (buf.st_mode & S_IFREG)
	{
		if (!(buf.st_mode & S_IRUSR))
		{
			ft_puterr(str, err, code);
			return (0);
		}
		if (!(buf.st_mode & S_IWUSR))
		{
			ft_puterr(str, err, code);
			return (0);
		}
	}
	return (1);
}
