/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_len_str_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 21:35:35 by mizola            #+#    #+#             */
/*   Updated: 2020/10/18 21:35:36 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	quotes(const char *s, int i, int *quote, int *quote2)
{
	if (!(*quote2 % 2 == 0 && *quote % 2 == 0
	&& s[i] == '\'' && s[i - 1] == '\\'))
		(s[i] == '\'') && *quote2 % 2 == 0 ? (*quote)++ : 0;
	(s[i - 1] != '\\' && s[i] == '\"') && *quote % 2 == 0 ? (*quote2)++ : 0;
}

int		ft_get_len_str_cmd(const char *str, int i, int space)
{
	int len;
	int quote;
	int quote2;

	quote = 2;
	quote2 = 2;
	len = 0;
	while (str[i])
	{
		quotes(str, i, &quote, &quote2);
		if (((str[i - 2] == '\\' && str[i - 1] == '\\')
		|| str[i - 1] != '\\') &&
		((str[i] == '|' && quote % 2 == 0 && quote2 % 2 == 0)
		|| (str[i] == ';' && quote % 2 == 0 && quote2 % 2 == 0)
		|| (str[i] == '<' && quote % 2 == 0 && quote2 % 2 == 0)
		|| (str[i] == '>' && quote % 2 == 0 && quote2 % 2 == 0)
		|| (str[i] == ' ' && quote % 2 == 0 && quote2 % 2 == 0 && space)
		|| (str[i] == '\t' && quote % 2 == 0 && quote2 % 2 == 0 && space)))
			break ;
		i++;
		len++;
	}
	return (len);
}
