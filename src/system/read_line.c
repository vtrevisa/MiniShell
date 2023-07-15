/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:09:55 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/07/15 22:01:32 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static char	*create_prompt(void)
{
	char	*name;
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX) != NULL)
		name = ft_strjoin(cwd, " $ ");
	else
		name = ft_strdup(" $ ");
	return (name);
}

void	read_line(t_data *data)
{
	char	*prompt;

	prompt = create_prompt();
	data->linetyped = 0;
	data->line = readline(prompt);
	free(prompt);
	while ((data->line != NULL))
	{
		if (ft_strlen(data->line))
		{
			add_history(data->line);
			data->linetyped = 1;
			break ;
		}
		else
			free(data->line);
		prompt = create_prompt();
		data->line = readline(prompt);
		free(prompt);
	}
	if (!data->line)
		exit_shell(data);
}
