/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:12:35 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/06/28 17:14:37 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static void	if_return_code_var()
{
	
}

void	replace_var_redir(t_parser *p, t_data *data)
{
	int		var_len;
	char	*var_name;
	char	*var_value;
	char	*new_str;
	char	flag;

	flag = 0;
	var_len = 0;
	if (p->str[p->i + 1] != '?')
	{
		while (p->str[p->i + 1 + var_len] && (ft_isalnum(p->str[p->i + 1 + \
	var_len]) || p->str[p->i + 1 + var_len] == '_'))
			var_len++;
		var_name = ft_substr(p->str, p->i + 1, var_len);
		var_value = find_variable(var_name, data);
		free(var_name);
	}
	else
	{
		var_value = ft_itoa(data->rcode);
		flag = 1;
		var_len++;
	}
	if (var_value)
	{
		new_str = ft_calloc((p->i + ft_strlen(var_value) + (ft_strlen(p->str) \
	- p->i - var_len)), sizeof(p->str));
		ft_memcpy(new_str, p->str, p->i);
		ft_memcpy(new_str + p->i, var_value, ft_strlen(var_value));
		ft_memcpy(new_str + p->i + ft_strlen(var_value), p->str + p->i + \
	var_len + 1, ft_strlen(p->str + p->i + var_len));
		free(p->str);
		p->str = new_str;
		p->i = p->i + ft_strlen(var_value);
		if (flag)
			free(var_value);
	}
	else
	{
		new_str = ft_calloc((ft_strlen(p->str) - (var_len + 1)), \
	sizeof(p->str));
		ft_memcpy(new_str, p->str, p->i);
		ft_memcpy(new_str + p->i, p->str + p->i + var_len + 1, ft_strlen \
	(p->str + p-> i + var_len));
		free(p->str);
		p->str = new_str;
	}
}