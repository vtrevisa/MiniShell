/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:21:05 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/05/08 16:56:17 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	tolkenizer(t_data *data)
{
	int	index;
	int	max_index;

	max_index = count_splitted(data);
	data->lexed_class = malloc(sizeof (int) * max_index);
	ft_bzero(data->lexed_class, max_index);
	index = 0;
	while (index <= max_index)
	{
		if (iscmd(data, data->line_splitted[index]))
		{
			data->lexed_class[index] = 1;
			data->count_cmd++;
		}
		else if (isarg(data, data->line_splitted[index]))
			data->lexed_class[index] = 2;
		else
		{
			data->lexed_class[index] = issimble(data, \
	data->line_splitted[index]);
			if (data->lexed_class[index] == 3)
			{
			}
			else if (data->lexed_class[index] == 4 || \
	data->lexed_class[index] == 5)
			{
			}
			else if (data->lexed_class[index] == 6 || \
	data->lexed_class[index] == 7)
			{
			}
			else
			{
				if ((data->lexed_class[index - 1] >= 4 \
	&& data->lexed_class[index - 1] <= 7) && index > 0)
					data->lexed_class[index] = 9;
			}
		}
		index++;
	}
}
//THIS FUNCTION IS OPEN FOR CHANGES THEREFORE IT HA MORE THAN 25 LINES

void	count_pipe(t_data *data)
{
	int	index;

	index = 0;
	while (data->line[index])
	{
		if (data->line[index] == '|')
			data->count_pipe++;
		index++;
	}
}

void	lexer(t_data *data)
{
	char	**args;
	int		index;

	if (data->line == NULL)
		return ;
	if (data->line[0] == ' ')
		data->line = remove_space(data);
	if (data->line != NULL)
	{
		index = 0;
		count_pipe(data);
		args = ft_split(data->line, '|');
		while (args[index])
		{
			data->line_splitted = \
	ft_split(space_to_nonprint(args[index]), -1);
			tolkenizer(data);
			openfiles(data);
			execute(data, args);
			index++;
		}
	}
}
