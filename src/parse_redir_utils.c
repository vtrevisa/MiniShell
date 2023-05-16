/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 22:37:26 by romachad          #+#    #+#             */
/*   Updated: 2023/05/16 03:59:32 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

static char	*trim_redir(t_parser *p)
{
	char	*new_str;
	
	new_str = ft_calloc((ft_strlen(p->str) - 2), sizeof(p->str));
	if (p->i > 0)
		ft_memcpy(new_str, p->str, p->i);
	ft_memcpy(new_str + p->i, p->str + p->i + 1, p->j - (p->i +1));
	ft_memcpy(new_str + p->i + (p->j - (p->i + 1)), p->str + p->j + 1, ft_strlen(p->str) - p->j);
	free(p->str);
	p->i = p->j - 2;
	return (new_str);
}

void	trim_quote_redir(t_parser *p)
{
	char	flag;
	int	bkp;

	flag = 0;
	bkp = p->i;
	p->i = -1;
	while (p->str[++p->i])
	{
		if (p->str[p->i] == '"' || p->str[p->i] == '\'')
		{
			p->j = p->i + 1;
			flag = p->str[p->i];
			while(p->str[p->j] && p->str[p->j] != flag)
				p->j++;
			if (p->str[p->j] == flag)
				p->str = trim_redir(p);
		}
	}
	p->i = bkp;
}

void	replace_var_redir(t_parser *p, t_data *data)
{
	int	var_len;
	char	*var_name;
	char	*var_value;
	char	*new_str;

	var_len = 0;
	while (p->str[p->i + 1 + var_len] && (ft_isalnum(p->str[p->i + 1 + var_len]) || p->str[p->i + 1 + var_len] == '_'))
		var_len++;
	var_name = ft_substr(p->str, p->i + 1, var_len);
	var_value = find_variable(var_name, data);
	free(var_name);
	if (var_value)
	{
		new_str = ft_calloc((p->i + ft_strlen(var_value) + (ft_strlen(p->str) - p->i - var_len)), sizeof(p->str));
		ft_memcpy(new_str, p->str, p->i);
		ft_memcpy(new_str + p->i, var_value, ft_strlen(var_value));
		ft_memcpy(new_str + p->i + ft_strlen(var_value), p->str + p->i + var_len + 1, ft_strlen(p->str + p->i + var_len));
		free(p->str);
		p->str = new_str;
		p->i = p->i + ft_strlen(var_value);
	}
	else
	{
		new_str = ft_calloc((ft_strlen(p->str) - (var_len + 1)), sizeof(p->str));
		ft_memcpy(new_str, p->str, p->i);
		ft_memcpy(new_str + p->i, p->str + p->i + var_len + 1, ft_strlen(p->str + p-> i + var_len));
		free(p->str);
		p->str = new_str;
	}
}

void	parse_var_redir(t_data *data, t_parser *p)
{
	int	flag;
	int	bkp;
	//t_parser	p;

	flag = 0;
	//p.str = parser->str;
	bkp = p->i;
	p->i = - 1;
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

/*void	parse_var_heredoc(char *str)
{
	int	flag;
	int	bkp;
	//t_parser	p;

	flag = 0;
	//p.str = parser->str;
	bkp = p->i;
	p->i = - 1;
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
}*/
