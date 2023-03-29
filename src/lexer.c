/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:21:05 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/03/29 11:32:05 by vtrevisa         ###   ########.fr       */
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
			data->count_cmd++;
			ft_printf("%s: is a cmd: %d[%d]\n", data->line_splitted[index], data->lexed_class[index], index);//teste
		}
		else if (isarg(data, data->line_splitted[index]))
		{
			data->lexed_class[index] = 2;
			ft_printf("%s: is arg: %d\n", data->line_splitted[index], data->lexed_class[index]);//teste
		}
		else
		{
			data->lexed_class[index] = issimble(data, data->line_splitted[index]);
			if (data->lexed_class[index] == 3)
				ft_printf("%s: is a var: %d\n", data->line_splitted[index], data->lexed_class[index]); //teste
			else if (data->lexed_class[index] == 4 || data->lexed_class[index] == 5)
				ft_printf("%s: is a redir out: %d\n", data->line_splitted[index], data->lexed_class[index]);//teste
			else if (data->lexed_class[index] == 6 || data->lexed_class[index] == 7)
				ft_printf("%s: is a redir in: %d\n", data->line_splitted[index], data->lexed_class[index]);//teste
			else
			{
				if ((data->lexed_class[index - 1] >= 4 && data->lexed_class[index - 1] <= 7) && index > 0)
					{
						data->lexed_class[index] = 9;
						ft_printf("%s: is a filename: %d\n", data->line_splitted[index], data->lexed_class[index]);//teste
					}
				else
					ft_printf("%s: not a cmd nor arg: %d\n", data->line_splitted[index], data->lexed_class[index]);//teste

			}
		}
		index++;
	}
}

void	count_pipe(t_data *data)
{
	int	index;

	index = 0;
/* 	write(1, "ok\n", 3); */
	while (data->line[index])
	{
		if (data->line[index] == '|')
			data->count_pipe++;
		index++;
	}
/* 	write(1, "ok\n", 3); */
}

void	lexer(t_data *data)
{
	char	**args;
	int		index;
	
	index = 0;
	count_pipe(data);
	args = ft_split(data->line, '|');
	while (args[index])
	{
		data->line_splitted = ft_split(space_to_nonprint(args[index]), -1);
		/* ft_printf("LEXER: Line_splitted[0]: %s | Line_splitted[1]: %s\n", data->line_splitted[0], data->line_splitted[1]); */
		tolkenizer(data);
		/* write(1, "ok\n", 3); */
		openfiles(data);
		/* write(1, "ok\n", 3); */
		execute(data, args);
		index++;
	}
}
