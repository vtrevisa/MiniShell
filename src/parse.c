/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 21:33:39 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/02/27 21:48:33 by vtrevisa         ###   ########.fr       */
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

int	count_cmd_len(char *line)
{
	int index;
	
	index = -1;
	while (line[++index] != 0 && line[index] != ' ')
		index++;
	return (index);
}

void	get_cmd(t_data *data)
{
	
}

void	parser(t_data *data)
{
    count
	data->cmd = malloc (sizeof (char *) * )
}