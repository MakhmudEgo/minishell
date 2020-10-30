/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 21:41:33 by mizola            #+#    #+#             */
/*   Updated: 2020/10/18 21:41:35 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSE_H
# define MINISHELL_PARSE_H

# include "../minishell.h"

typedef struct s_data	t_data;
typedef struct s_list	t_list;
typedef struct s_ident	t_ident;
typedef struct			s_varsftvalidstr
{
	char				*res;
	int					q2;
	int					q;
	char				*s;
	int					n;
	int					i;
}						t_v;

void					ft_skip_space(int *i, const char *cmd);
int						ft_get_len_str_cmd(const char *str, int i, int space);
int						ft_check_cmd(const char *s);
int						ft_is_red(const char *cmd, int *i);
char					*ft_strdup_env_val(char *dol, t_list *data);
int						ft_is_valid_cmd(const char *cmd, int i, int q, int q2);
void					ft_valid_str(t_data *data, char **str);
void					ft_get_red_val_init(t_ident *new_i,
						int *i, int *n, char *cmd);
void					ft_skip_back_n(char **s, t_data *data);
int						ft_check_only_parents(const char *s, t_data *data);
void					ft_valid_arr_str(char **str, t_data *data);

#endif
