/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:35:06 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/03/29 11:34:12 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

char **getcmd(t_data *data, char **args)
{
	char	**cmd;
	int		index;
	int		index2;
	
	index = 0;
	index2 = 0;
	
	cmd = malloc (sizeof (char *) * 3);
	while(args[index] != NULL)
	{
		/* ft_printf("GETCMD: args[%d]: %s | lexed_class: %d\n", index, args[index], data->lexed_class[index]); */
		if (data->lexed_class[index] == 1 || data->lexed_class[index] == 2)
		{
			cmd[index2] = ft_strdup(args[index]);
			index2++;
		}
		index++;
		
	}
	cmd[index2] = NULL;
	return (cmd);
}

static int	child(t_data *data)
{
	/* if (data->count_pipe)
	{
		
	}	 */
	if (data->cmd)
		execve(data->cmd_path, data->line_splitted, data->envp);
	return (0);
}

int	execute (t_data *data, char **args)
{
	int	pid;
	
	data->cmd = getcmd(data, args);
	/* ft_printf("EXECUTE: cmd_path: %s | cmd: %s | arg: %s\n", data->cmd_path, data->line_splitted[0], data->line_splitted[1]); */
	pid = fork();
	if (pid == 0)
		child(data);
}