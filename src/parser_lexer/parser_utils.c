/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 15:44:35 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/06/28 16:17:48 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

char	*trim(char *str, t_data *data, t_parser *p)
{
	char	*new_str;

	if (ft_strlen(str) - 2 == 0)
	{
		new_str = ft_calloc(1, sizeof(str));
	}
	else
	{
		new_str = ft_calloc((ft_strlen(str) - 2), sizeof(str));
		if (p->i > 0)
			ft_memcpy(new_str, str, p->i);
		ft_memcpy(new_str + p->i, str + p->i + 1, p->j - (p->i + 1));
		ft_memcpy(new_str + p->i + (p->j - (p->i + 1)), str + p->j + 1, ft_strlen(str) - p->j);
		p->i = p->j - 2;
	}
	free(str);
	data->full_cmd[p->index][p->index2] = new_str;
	return (new_str);
}

char	**remove_empty(char **str,int i_to_remove, t_parser *p)
{
	int	count;
	char	**copy;

	count = 0;
	while(str[count])
		count++;
	copy = (char **)ft_calloc(count, sizeof(str[0]));
	if (copy == NULL)
		error_exit("Fail realoc remove empty var");
	if (count == 1)
		copy[0] = NULL;
	else
	{
		ft_memcpy(copy, str, i_to_remove * sizeof(str[0]));
		ft_memcpy(copy + i_to_remove, str + i_to_remove + 1, (count - i_to_remove - 1) * sizeof(str[0]));
	}
	free(str[i_to_remove]);
	free(str);
	return (copy);
}

void	trim_quote(char *str, t_data *data, t_parser *p)
{
	char	flag;

	flag = 0;
	p->i = -1;
	while (str[++p->i])
	{
		if (str[p->i] == -1 && str[p->i + 1] == 0)
		{
			data->full_cmd[p->index] = remove_empty(data->full_cmd[p->index], p->index2, p);
			p->index2--;
			break ;
		}
		if (str[p->i] == '"' || str[p->i] == '\'')
		{
			p->j = p->i + 1;
			flag = str[p->i];
			while (str[p->j] && str[p->j] != flag)
				p->j++;
			if (str[p->j] == flag)
				str = trim(str, data, p);
		}
	}
}

char	**split_pipes(char *str)
{
	int		i;
	int		j;
	char	flag;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			flag = str[i];
			j = i + 1;
			while (str[j] && str[j] != flag)
				j++;
			if (str[j] == flag)
				i = j;
		}
		if (str[i] == '|')
			str[i] = 17;
	}
	return (ft_split(str, 17));
}

char	*find_variable(char *var, t_data *data)
{
	int	i;

	i = -1;
	while (data->envp[++i])
	{
		if (ft_strncmp(data->envp[i], var, ft_strlen(var)) == 0 && \
	data->envp[i][ft_strlen(var)] == '=')
			return (data->envp[i] + ft_strlen(var) + 1);
	}
	return (NULL);
}
