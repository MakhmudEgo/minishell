/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_valid_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 22:03:58 by mizola            #+#    #+#             */
/*   Updated: 2020/10/18 22:03:59 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	ft_valid_str_p1(t_v *v)
{
	v->s[v->n] == '\'' && v->q2 % 2 == 0 ? v->q++ && ++v->i && ++v->n : 0;
	v->s[v->n] == '\"' && v->q % 2 == 0 ? v->q2++ && ++v->i && ++v->n : 0;
	if (v->q % 2 == 0 && v->q2 % 2 == 0)
	{
		ft_skip_space(&v->n, v->s);
		v->n > v->i ? --v->n && (v->i = v->n) : 0;
	}
	while (v->s && v->s[v->n] != '\0')
	{
		if ((v->s[v->n] == '\'' && v->q2 % 2 == 0)
			|| (v->s[v->n] == '\"' && v->q % 2 == 0)
			|| (v->s[v->n] == '$' && v->s[v->n + 1] != '/' && v->q % 2 == 0)
			|| (v->s[0] == '~' && (v->s[1] == '\0' || v->s[1] == ' ')
			&& v->q2 % 2 == 0 && v->q % 2 == 0) ||
			(v->s[v->n - 1] == ' ' && v->s[v->n] == '~' && v->s[v->n + 1] == ' '
			&& v->q2 % 2 == 0 && v->q % 2 == 0)
			|| (v->s[v->n] == '\\' && v->q % 2 == 0)
			|| (v->s[v->n] == ' ' && v->s[v->n + 1] == ' '
			&& v->q % 2 == 0 && v->q2 % 2 == 0))
			break ;
		(v->n)++;
	}
}

static void	ft_valid_str_p2(t_v *v, t_data *data)
{
	if (v->n != v->i)
		!(v->res = ft_strjoin_free(v->res, ft_substr(v->s, v->i, v->n - v->i)))
		? ft_error("malloc return NULL", 13) : 0;
	if (v->s[v->n] == '\\' && v->q % 2 == 0)
	{
		if (v->q2 % 2 == 0 || (v->q2 % 2 != 0 && (v->s[v->n + 1] == '$'
		|| v->s[v->n + 1] == '\"' || v->s[v->n + 1] == '\\')))
		{
			++v->n;
			v->res = ft_strjoin_free(v->res, ft_substr(v->s, v->n++, 1));
			!v->res ? ft_error("malloc return NULL", 13) : 0;
		}
		else
		{
			v->res = ft_strjoin_free(v->res, ft_substr(v->s, v->n, 2));
			!v->res ? ft_error("malloc return NULL", 13) : 0;
			v->n += 2;
		}
	}
	if (v->s[v->n] == '~' && ++v->n)
		!(v->res = ft_strjoin_free(v->res,
		ft_strdup_env_val(ft_strdup("HOME"), data->env)))
		? ft_error("malloc return NULL", 13) : 0;
}

static void	ft_valid_str_p3(t_v *v, t_data *data)
{
	if (v->s[v->n] == '$' && v->s[v->n + 1] == '?' && (v->n += 2))
		!(v->res = ft_strjoin_free(v->res, ft_itoa(g_code)))
		? ft_error("malloc return NULL", 13) : 0;
	else if (v->s[v->n] == '$')
	{
		v->i = ++v->n;
		while (v->s[v->i])
		{
			if ((ft_isdigit(v->s[v->n])
			|| (!ft_isalnum(v->s[v->i]) && v->s[v->i] != 95)))
				break ;
			v->i++;
		}
		if (v->i != v->n)
			!(v->res = ft_strjoin_free(v->res,
		ft_strdup_env_val(ft_substr(v->s, v->n, v->i - v->n), data->env)))
		? ft_error("malloc return NULL", 13) : 0;
		v->n = ft_isdigit(v->s[v->n]) ? ++v->i : v->i;
	}
}

void		ft_valid_str(t_data *data,
			char **str)
{
	t_v v;

	v.res = 0x0;
	v.q2 = 2;
	v.q = 2;
	v.s = *str;
	v.i = 0;
	v.n = 0;
	if (*str)
	{
		v.res = strdup("");
		while (v.s[v.i])
		{
			ft_valid_str_p1(&v);
			ft_valid_str_p2(&v, data);
			ft_valid_str_p3(&v, data);
			v.i = v.n;
		}
	}
	v.res ? free(*str) : 0;
	*str = v.res ? v.res : *str;
}
