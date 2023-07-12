/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 16:22:28 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/07/12 16:15:15 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static void	return_code_var(t_parser *p, t_data *data, t_var *v)
{
	if (ft_isdigit(p->str[p->i + 1]))
		v->len = 1;
	else
	{
		while (p->str[p->i + 1 + v->len] && (ft_isalnum(p->str \
	[p->i + 1 + v->len]) || p->str[p->i + 1 + v->len] == '_'))
			v->len++;
	}
	v->name = ft_substr(p->str, p->i + 1, v->len);
	v->value = find_variable(v->name, data);
	free(v->name);
}

static void	if_value(t_parser *p, t_data *data, t_var *v, int flag)
{
	v->n_str = ft_calloc((p->i + ft_strlen(v->value) + (ft_strlen(p->str) \
		- p->i - v->len)), sizeof(p->str));
	ft_memcpy(v->n_str, p->str, p->i);
	ft_memcpy(v->n_str + p->i, v->value, ft_strlen(v->value));
	ft_memcpy(v->n_str + p->i + ft_strlen(v->value), p->str + p->i + \
		v->len + 1, ft_strlen(p->str + p->i + v->len));
	free(data->full_cmd[p->index][p->index2]);
	data->full_cmd[p->index][p->index2] = v->n_str;
	p->str = v->n_str;
	p->i = p->i + ft_strlen(v->value) - 1;
	if (flag)
		free(v->value);
}

static void	if_no_value(t_parser *p, t_data *data, t_var *v)
{
	if (ft_strlen(p->str) - (v->len + 1) == 0)
	{
		v->n_str = ft_calloc(2, sizeof(p->str));
		v->n_str[0] = -1;
		free(data->full_cmd[p->index][p->index2]);
		data->full_cmd[p->index][p->index2] = v->n_str;
		p->str = v->n_str;
	}
	else
	{
		v->n_str = ft_calloc((ft_strlen(p->str) - \
	(v->len + 1)), sizeof(p->str));
		ft_memcpy(v->n_str, p->str, p->i);
		ft_memcpy(v->n_str + p->i, p->str + p->i + v->len + \
	1, ft_strlen(p->str + p->i + v->len));
		free(data->full_cmd[p->index][p->index2]);
		data->full_cmd[p->index][p->index2] = v->n_str;
		p->str = v->n_str;
		p->i--;
	}
}

void	replace_var(t_parser *p, t_data *data)
{
	t_var	v;
	char	flag;

	flag = 0;
	v.len = 0;
	if (p->str[p->i +1] != '?')
		return_code_var(p, data, &v);
	else
	{
		v.value = ft_itoa(data->rcode);
		flag = 1;
		v.len++;
	}
	if (v.value)
		if_value(p, data, &v, flag);
	else
		if_no_value(p, data, &v);
}
