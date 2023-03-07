/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:09:55 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/03/07 17:40:54 by vtrevisa         ###   ########.fr       */
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

char	*read_line(t_data *data)
{
	char *line;
	
	print_user_dir(data); //errors with the history, it erases the userdir
	line = readline("$ ");
	if (ft_strlen(line))
	{
		add_history(line);
		return (line);
	}
	else
		return (NULL);
}