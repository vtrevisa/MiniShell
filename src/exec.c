/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:35:06 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/04/17 22:22:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

char	**getcmd(t_data *data, char **args)
{
	char	**cmd;
	int		index;
	int		index2;

	index = 0;
	index2 = 0;
	cmd = malloc (sizeof (char *) * 3);
	while (args[index] != NULL)
	{
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
	if (data->cmd)
		execve(data->cmd_path, data->line_splitted, data->envp);
	return (0);
}

int	execute(t_data *data, char **args)
{
	int	pid;
	int	situation;

	situation = 1;
	data->pipes = 0;
	data->cmd = getcmd(data, args);
	if (data->count_pipe)
	{	
	}
	else
	{	
		pid = fork();
		if (pid == 0)
			child(data);
	}
}
