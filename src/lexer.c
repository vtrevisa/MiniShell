/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:21:05 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/03/17 14:16:18 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	tolkenizer(t_data *data)
{
	int	index;
	int	max_index;
	//GOTTA THINK ABAOUT ISSPACE AND NEW LINE (TYPED ONLYSPACE AND ENTER = SEGFAULT)
	max_index = count_splitted(data);
	data->lexed_class = malloc(sizeof (int) * max_index);
	ft_bzero(data->lexed_class, max_index);
	index = 0;
	while (index <= max_index)
	{
		if(iscmd(data, data->line_splitted[index]))
		{
			data->lexed_class[index] = 1;
			ft_printf("%s: is a cmd: %d\n", data->line_splitted[index], data->lexed_class[index]);
		}
		else if (isarg(data, data->line_splitted[index]))
		{
			data->lexed_class[index] = 2;
			ft_printf("%s: is arg: %d\n", data->line_splitted[index], data->lexed_class[index]);
		}
		else
		{
			data->lexed_class[index] = issimble(data, data->line_splitted[index]);
			if (data->lexed_class[index] == 3)
				ft_printf("%s: is a var: %d\n", data->line_splitted[index], data->lexed_class[index]);
			else if (data->lexed_class[index] == 4 || data->lexed_class[index] == 5)
				ft_printf("%s: is a redir out: %d\n", data->line_splitted[index], data->lexed_class[index]);
			else if (data->lexed_class[index] == 6 || data->lexed_class[index] == 7)
				ft_printf("%s: is a redir in: %d\n", data->line_splitted[index], data->lexed_class[index]);
			else if (data->lexed_class[index] == 8)
				ft_printf("%s: is a pipe: %d\n", data->line_splitted[index], data->lexed_class[index]);
			else
			{
				if ((data->lexed_class[index - 1] >= 4 && data->lexed_class[index - 1] <= 7) && index > 0)
					{
						data->lexed_class[index] = 9;
						ft_printf("%s: is a filename: %d\n", data->line_splitted[index], data->lexed_class[index]);
					}
				else
					ft_printf("%s: not a cmd nor arg: %d\n", data->line_splitted[index], data->lexed_class[index]);

			}
		}
		index++;
	}
}

void	lexer(t_data *data)
{
	//lexing string
	data->line_splitted = ft_split(space_to_nonprint(data->line), -1);
	tolkenizer(data);
	openfiles(data);
}
