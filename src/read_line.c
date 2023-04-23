/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:09:55 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/04/22 22:52:17 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	print_user_dir(t_data *data)
{
	char cwd[1024];
	int index;

	index = 0;
	getcwd(cwd, sizeof(cwd));
	while (cwd[index] == data->user[index])
		index++;
	ft_printf("~%s", cwd + index);
}

//char	*read_line(t_data *data)
void	*read_line(t_data *data)
{
	//char *line;
	
	data->linetyped = 0;
	print_user_dir(data); //errors with the history, it erases the userdir
	data->line = readline("$ ");
	if (ft_strlen(data->line))
	{
		add_history(data->line);
		data->linetyped = 1;
		//return (line);
	}
	else
		free(data->line);
		//return (NULL);
}
