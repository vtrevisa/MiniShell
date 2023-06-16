/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:09:55 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/06/16 17:51:30 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	print_user_dir(t_data *data)
{
	char cwd[1024];
	int index;

	index = 0;
	getcwd(cwd, sizeof(cwd));
	while (cwd[index] == data->user[index] && cwd[index])
		index++;
	if (index >= ft_strlen(cwd))
		ft_printf("~");
	else
		ft_printf("~%s", cwd + index);
}

//char	*read_line(t_data *data)
void	*read_line(t_data *data)
{
	//char *line;
	
	data->linetyped = 0;
	print_user_dir(data); //errors with the history, it erases the userdir
	while ((data->line = readline("$ ")) != NULL)
	{
		if (*data->line == '\0')
		{
			print_user_dir(data); //errors with the history, it erases the userdir
		}
		if (ft_strlen(data->line))
		{
			add_history(data->line);
			data->linetyped = 1;
			break ;
		}
		else
			free(data->line);
	}
	if (!data->line)
		exit_shell(data);
	//else
	//	free(data->line);
		//return (NULL);
}
