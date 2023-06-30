/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 15:44:35 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/06/30 16:40:13 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	check_close_dq(char *str)
{
	int	i;

	i = 0;
	while (str[++i])
	{
		if (str[i] == '"')
			return (1);
	}
	return (0);
}

void	parse_quote(char *str, t_data *data, int index, t_parser *p)
{
	p->i = -1;
	p->str = str;
	while (p->str[++p->i])
	{
		if (p->str[p->i] == ' ')
			p->str[p->i] = 17;
		else if (p->str[p->i] == '\'')
		{
			p->j = p->i + 1;
			while (p->str[p->j] && p->str[p->j] != '\'')
				p->j++;
			if (p->str[p->j] == '\'')
				p->i = p->j;
		}
		else if (p->str[p->i] == '"')
		{
			p->j = p->i + 1;
			while (p->str[p->j] && p->str[p->j] != '"')
				p->j++;
			if (p->str[p->j] == '"')
				p->i = p->j;
		}
	}
	data->full_cmd[index] = ft_split(p->str, 17);
}
