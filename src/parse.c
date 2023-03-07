/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:21:05 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/03/07 18:40:35 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

char	*space_to_nonprint(char *str)
{
	int	index;
	int	flag;

	flag = 1;
	index = 0;
	while (str[index])
	{
		if (str[index] == '\'')
			flag *= -1;
		if (str[index] == ' ' && flag == 1)
			str[index] = -1;
		index++;
	}
	return (str);
}

int	count_splitted(t_data *data)
{
	int	index;
	int	splits;
	
	index = 0;
	splits = 0;
	while (data->line[index])
	{
		if (data->line[index] == -1)
			splits++;
		index++;
	}
	return (splits);
}

int	test_cmd(t_data *data, char *line_splitted)
{
	char	*tmp;
	char	*cmd;
	int		index;
	
	index = -1;
	while (data->paths[++index])
	{
		tmp = ft_strjoin(data->paths[index], "/");
		cmd = ft_strjoin(tmp, line_splitted);
		if (access(cmd, X_OK) == 0)
		{
			free (tmp);
			free(cmd);
			return (1);
		}
		free (cmd);
		free (tmp);
	}
	return (0);
}

void	tolkenizer(t_data *data)
{
	int	index;

	index = count_splitted(data);
	while (index >= 0)
	{
		if(test_cmd(data, data->line_splitted[index]))
		{
			data->parsed_class[index] == 1;
			ft_printf("%s: is a cmd\n", data->line_splitted[index]);
		}
		else
			ft_printf("%s: not a cmd\n", data->line_splitted[index]);
		//else if (/*isarg*/)
		//	data->parsed_class[index] == 2;
		//else if (/*issimble*/)
	//		data->parsed_class[index] == 3;
		index--;
	}
}

void	parser(t_data *data)
{
	//lexing string
	data->line_splitted = ft_split(space_to_nonprint(data->line), -1);
	//tolkenizing string
	tolkenizer(data);
	//parsing tring
}