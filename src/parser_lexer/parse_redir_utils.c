/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 22:37:26 by romachad          #+#    #+#             */
/*   Updated: 2023/07/13 04:24:09 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static char	*trim_redir(t_parser *p)
{
	char	*new_str;

	new_str = ft_calloc((ft_strlen(p->str) - 2), sizeof(p->str));
	if (p->i > 0)
		ft_memcpy(new_str, p->str, p->i);
	ft_memcpy(new_str + p->i, p->str + p->i + 1, p->j - (p->i +1));
	ft_memcpy(new_str + p->i + (p->j - (p->i + 1)), p->str + p->j + 1, \
		ft_strlen(p->str) - p->j);
	free(p->str);
	p->i = p->j - 2;
	return (new_str);
}

void	trim_quote_redir(t_parser *p)
{
	char	flag;
	int		bkp;

	flag = 0;
	bkp = p->i;
	p->i = -1;
	while (p->str[++p->i])
	{
		if (p->str[p->i] == '"' || p->str[p->i] == '\'')
		{
			p->j = p->i + 1;
			flag = p->str[p->i];
			while (p->str[p->j] && p->str[p->j] != flag)
				p->j++;
			if (p->str[p->j] == flag)
				p->str = trim_redir(p);
		}
	}
	p->i = bkp;
}

void	parse_var_redir(t_data *data, t_parser *p)
{
	int	flag;
	int	bkp;

	flag = 0;
	bkp = p->i;
	p->i = -1;
	while (p->str[++p->i])
	{
		if (p->str[p->i] == '"')
			flag = check_close_dq(p->str + p->i);
		if (p->str[p->i] == '\'' && p->str[p->i + 1] && flag == 0)
		{
			p->j = p->i + 1;
			while (p->str[p->j] && p->str[p->j] != '\'')
				p->j++;
			if (p->str[p->j] == '\'')
				p->i = p->j;
		}
		if (p->str[p->i] == '$')
		{
			replace_var_redir(p, data);
			flag = 0;
		}
	}
	p->i = bkp;
}

char	*parse_var_heredoc(char *str, t_data *data)
{
	t_parser	p;

	p.str = str;
	p.i = -1;
	if (p.str == NULL)
		return (p.str);
	while (p.str[++p.i])
	{
		if (p.str[p.i] == '$')
			replace_var_redir(&p, data);
	}
	return (p.str);
}
