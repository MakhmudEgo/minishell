/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 20:02:55 by mizola            #+#    #+#             */
/*   Updated: 2020/10/10 20:02:56 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	lst_deleate(t_list **lst, char *content)
{
	t_list	*tmp;
	void	*tmp_save;
	void	*tmp_next;

	tmp = *lst;
	tmp_save = tmp;
	tmp_next = 0x0;
	while (tmp)
	{
		if (!ft_strncmp(content, tmp->content, ft_strlen(content) + 1))
			break ;
		tmp_save = tmp;
		tmp = tmp->next;
	}
	if (tmp)
	{
		free(tmp->content);
		free(tmp->value);
		tmp_next = tmp->next;
		free(tmp);
		tmp = tmp_save;
		tmp->next = tmp_next;
	}
}

void		ft_unset(t_data *data)
{
	int i;
	int ex;

	i = 0;
	ex = 0;
	if (data->v_cmd->arr_cmd)
		ft_valid_arr_str(data->v_cmd->arr_cmd, data);
	while (data->v_cmd->cmd_arr && data->v_cmd->arr_cmd[i])
	{
		if (is_valid_var(data->v_cmd->arr_cmd[i], "minishell: unset: `"))
			lst_deleate(&data->env, data->v_cmd->arr_cmd[i]);
		else
			ex = 1;
		i++;
	}
	g_code = ex ? g_code : ex;
}
