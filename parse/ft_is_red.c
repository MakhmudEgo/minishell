/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_red.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 21:42:27 by mizola            #+#    #+#             */
/*   Updated: 2020/10/18 21:42:28 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_is_red(const char *cmd, int *i)
{
	if (cmd[*i] == '>' && cmd[*i + 1] != '>')
	{
		*i += 1;
		return (1);
	}
	else if (cmd[*i] == '<' && cmd[*i + 1] != '>')
	{
		*i += 1;
		return (2);
	}
	else if (cmd[*i] == '>' && cmd[*i + 1] == '>')
	{
		*i += 2;
		return (3);
	}
	else if (cmd[*i] == '<' && cmd[*i + 1] == '>')
	{
		*i += 2;
		return (4);
	}
	return (0);
}
