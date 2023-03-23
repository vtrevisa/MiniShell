/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:19:13 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/03/21 16:46:33 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

char	*pathfinder(char *envp[])
{
	int	index;

	index = 0;
	while (!ft_strnstr(envp[index], "PATH=", 5))
		index++;
	return (envp[index] + 5);
}

char	*userfinder(char *envp[])
{
	int	index;

	index = 0;
	while (!ft_strnstr(envp[index], "HOME=", 5))
		index++;
	return (envp[index] + 5);
}

void	init_data(t_data *data, char **envp)
{
	data->paths = ft_split(pathfinder(envp), ':');
	data->user = ft_strdup(userfinder(envp));
	data->file_fds_index = 0;
	data->cmd = malloc (sizeof (char *) * 3);
	data->envp = envp;
	data->count_cmd = 0;
	data->fd_in = 0;
	data->fd_out = 0;
	data->count_pipe = 0;
}