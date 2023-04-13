/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:38:39 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/04/13 17:52:46 by vtrevisa         ###   ########.fr       */
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
		if (str[index] == '\'' || str[index] == '\"')
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

int	openfiles(t_data *data)
{
	int	index;
	int	fd;

	index = -1;
	fd = 0;
	data->file_fds = malloc (sizeof (int) * data->file_fds_index);
	while (data->line_splitted[++index])
	{
		if (data->lexed_class[index] == 4 || data->lexed_class[index] == 5)
		{
			data->file_fds[fd++] = open (data->line_splitted[index + 1], O_CREAT, S_IRWXU);
			data->fd_out = data->file_fds[fd];
		}
		if (data->lexed_class[index] == 6 || data->lexed_class[index] == 7)
		{
			data->file_fds[fd++] = open (data->line_splitted[index + 1], O_CREAT, S_IRWXU);
			data->fd_in = data->file_fds[fd];
		}
	}
}

char	*remove_space(t_data *data)
{
	int		index;
	char	*str;
	int		size;
	
	
	index = 0;
	size = ft_strlen(data->line);
	while (data->line[index] == ' ')
		index++;
	str = malloc (sizeof (ft_strlen(data->line + index)));
/* 	write(1, "ok\n", 3); */
	ft_strlcpy(str, data->line + index, size);
	/* write(1, "ok\n", 3); */
	return (str);
}