/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:12:35 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/07/14 20:20:04 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static void	if_return_code_var(t_var *var, t_parser *p, t_data *data)
{
	while (p->str[p->i + 1 + var->len] && (ft_isalnum(p->str[p->i + 1 + \
	var->len]) || p->str[p->i + 1 + var->len] == '_'))
		var->len++;
	var->name = ft_substr(p->str, p->i + 1, var->len);
	var->value = find_variable(var->name, data);
	free(var->name);
}

static void	if_var_value(t_var *var, t_parser *p, char flag)
{
	var->n_str = ft_calloc((p->i + ft_strlen(var->value) + (ft_strlen(p->str) \
		- p->i - var->len)), sizeof(p->str));
	ft_memcpy(var->n_str, p->str, p->i);
	ft_memcpy(var->n_str + p->i, var->value, ft_strlen(var->value));
	ft_memcpy(var->n_str + p->i + ft_strlen(var->value), p->str + p->i + \
		var->len + 1, ft_strlen(p->str + p->i + var->len));
	free(p->str);
	p->str = var->n_str;
	p->i = p->i + ft_strlen(var->value);
	if (flag)
		free(var->value);
}

void	replace_var_redir(t_parser *p, t_data *data)
{
	t_var	var;
	char	flag;

	flag = 0;
	var.len = 0;
	if (p->str[p->i + 1] != '?')
		if_return_code_var(&var, p, data);
	else
	{
		var.value = ft_itoa(data->rcode);
		flag = 1;
		var.len++;
	}
	if (var.value)
		if_var_value(&var, p, flag);
	else
	{
		var.n_str = ft_calloc((ft_strlen(p->str) - (var.len + 1)), \
	sizeof(p->str));
		ft_memcpy(var.n_str, p->str, p->i);
		ft_memcpy(var.n_str + p->i, p->str + p->i + var.len + 1, ft_strlen \
	(p->str + p-> i + var.len));
		free(p->str);
		p->str = var.n_str;
	}
}
