/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:19:13 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/05/11 05:12:32 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

char	**copy_double_str(char **envp)
{
	int	count;
	int	i;
	char	**copy;

	copy = envp - 1;
	count = 0;
	while (*++copy != NULL)
		count++;
	copy = (char **)malloc((count + 1) * sizeof(envp[0]));
	if (copy == NULL)
		error_exit("env malloc");
	i = -1;
	while (++i < count)
	{
		copy[i] = ft_strdup(envp[i]);
		if (copy[i] == NULL)
			error_exit("env strdup");
	}
	copy[count] = NULL;
	return (copy);
}

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
	//data->envp = envp; Removido pq o envp sera copiado!
	data->envp = copy_double_str(envp);
	data->count_cmd = 0;
	data->fd_in = 0;
	data->fd_out = 0;
	data->count_pipe = 0;
}
