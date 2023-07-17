/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:19:13 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/07/16 23:39:39 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static char	**copy_double_str(char **envp)
{
	int		count;
	int		i;
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

void	init_data(t_data *data, char **envp)
{
	data->envp = copy_double_str(envp);
	data->ctrl_c = 0;
	data->rcode = 0;
	data->flag_fullcmd = 0;
	data->is_here_doc = 0;
}
