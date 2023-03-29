/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:35:06 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/03/29 18:19:45 by vtrevisa         ###   ########.fr       */
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
	if (data->cmd)
		execve(data->cmd_path, data->line_splitted, data->envp);
	return (0);
}

int	execute (t_data *data, char **args)
{
	int	pid;
	int	situation;

	situation = 1;
	data->pipes = 0;
	data->cmd = getcmd(data, args);
	/* ft_printf("EXECUTE: cmd_path: %s | cmd: %s | arg: %s\n", data->cmd_path, data->line_splitted[0], data->line_splitted[1]); */
	if (data->count_pipe)
	{
		child_1(data);
		data->pipes++;
		while (data->pipes < data->count_pipe) // THIS THING IST HERE
		{
			child_2(data);
			data->pipes++;
		}
		child_3(data);
		data->pipes++;
	}
	else
	{	
		pid = fork();
		if (pid == 0)
		child(data);
	}
}