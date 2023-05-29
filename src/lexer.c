/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:21:05 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/05/29 14:41:02 by vtrevisa         ###   ########.fr       */
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
			{
				write(1, "2\n", 2);
				data->lexed_class[index] = 2;
			}
		else
		{
			write(1, "9\n", 2);
			data->lexed_class[index] = issimble(data, \
				data->line_splitted[index]);
			if (data->lexed_class[index] == 3)
			{
				write(1, "3\n", 2);
			}
			else if (data->lexed_class[index] == 4 || \
				data->lexed_class[index] == 5)
			{
				write(1, "4\n", 2);
			}
			else if (data->lexed_class[index] == 6 || \
				data->lexed_class[index] == 7)
			{
				write(1, "5\n", 2);
			}
			else
			{
				write(1, "6\n", 2);
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
	int		index2;

	index2 = 0;
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
			while (data->line_splitted[index2] != NULL)
			{
				if (*data->line_splitted[index2] == '$')
				{
					data->line_splitted[index2] = unveil_vars(data->envp, data->line_splitted[index2]);
				}
				index2++;
			}
			tolkenizer(data);
			openfiles(data);
			execute(data, args);
			index++;
		}
	}
	free (data->lexed_class);//
}
