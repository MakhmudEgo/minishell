/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 09:16:56 by mizola            #+#    #+#             */
/*   Updated: 2020/10/01 09:16:57 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "parse/parse.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <sys/wait.h>
# include <dirent.h>
# include <errno.h>
# include <signal.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>

typedef struct dirent	t_dir;

typedef struct			s_redirect
{
	int					red;
	char				*file;
	char				*red_str;
	struct s_redirect	*prev;
	struct s_redirect	*next;
}						t_red;

typedef struct			s_ident
{
	char				*cmd;
	int					flag;
	char				**cmd_arr;
	t_red				*red;
	int					p;
	char				**arr_cmd;
	char				**wr_arr;
	struct s_ident		*prev;
	struct s_ident		*next;
	char				**dirs;
	int					is_cmd;
	int					is_ok;
}						t_ident;

typedef struct			s_data
{
	t_ident				*v_cmd;
	t_list				*env;
	char				*cmd;
	int					fd1[2];
	int					fd2[2];
	int					st_fd_f;
	int					new_fd_n;
	int					new_fd_f;
	char				*is_valid_str;
}						t_data;

char					*g_buf;
int						g_code;

void					ft_pwd(t_data *data);
void					ft_cd(t_data *data);
int						ft_env(t_data *data);
int						lsh_launch(char **args, t_data *data);
void					ft_parse(t_data *data, char *cmd);
void					ft_ident_init(t_ident *data);
void					ft_red_init(t_red *data);
void					ft_identlstback(t_ident **lst, t_ident *new);
void					ft_redlstback(t_red **lst, t_red *new);
void					ft_export(t_data *data);
char					**env_cp(t_list *env);
void					ft_echo(t_data *data);
void					ft_red_array(t_ident *v_cmd);
int						ft_check_next_file(t_red *lst);
int						ft_check_next_red(t_red *lst);
void					ft_wr_array(t_data *data, int fd);
void					ft_dir(t_data *data, char **cmd, int i);
int						check_prev_pipe(t_data *data);
void					ft_bash_cmd(t_data *data);
void					ft_data_init(t_data *data);
void					ft_exit(t_data *data);
void					ft_unset(t_data *data);
void					cp_env_lst(t_list **lst,
						const char **env, int p, int o);
int						ft_red_new(t_data *data, int i);
void					ft_sig(int sig);
int						ft_new_file_red(t_ident *ident, t_data *data);
int						get_next_line(char **line);
char					*char_join(char *str, char c);
char					*get_env_value_ptr(t_list *env, char *str);
char					**ft_split_quote(char const *s);
int						is_valid_var(char *s, char *err);
int						ft_creat_file(char *file);
int						fd_creat_or_add_file(char *file);
int						fd_open_file(char *file);
int						ft_check_red_two(t_red **red);
int						ft_open_next_two(t_red **red, int check);
void					ft_pipe_write(t_data *data);
void					ft_pipe_pipe(t_data *data);
void					ft_write_pipe(t_data *data, int status);
void					ft_exec_cmd(t_data *data);
int						check_prev_pipe_red(t_ident *ident);
void					init_oldpwd(t_list *env, char *str, char *val);
void					ft_puterr(char *s1, char *s2, int err);
void					ft_add_elem_env(t_data *data, int i);
void					ft_free_xxx(t_ident *v_cmd);
void					dirs_init(t_data *data);
void					quotes(const char *s, int i, int *quote, int *quote2);
int						check_exec_launch(char *args, char *err, int code);
int						check_exec_str(char *str, char *err, int code);
void					check_reg(char **cmd, t_data *data);
int						check_red_file(char *str, char *err, int code);
char					*get_env_content_ptr(t_list *env, char *str);

#endif
