/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:03:52 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/03/29 18:15:09 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	show_display(void)
{
	int	fd;
	char *line;

	fd = open ("./src/display", O_RDONLY);
	while (fd != -1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		ft_printf("%s", line);
		free(line);
	}
	return (fd);
}

int	prompt_loop(t_data *data)
{
	int		status;

	status = 0;
	while (1)
	{
		ft_printf("> ");
		data->line = read_line(data);
		if (ft_strnstr("exit", data->line, 4) != 0)
			{
				free(data->line);
				return (EXIT_CODE);
			}
			else
				ft_printf(">%s\n", data->line); //teste
		/* write(1, "ok\n", 3); */
		lexer(data);
		/* status = execute(data); */
		free (data->line);
	}
}

void	free_all(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

int	main(int argc, char **argv, char **envp)
{	
	// Load config files, if any.
	t_data	data;
	
	show_display();
	init_data(&data, envp);
	// Run command loop.
	prompt_loop(&data);

	// Perform any shutdown/cleanup.
	free (data.user);
	free_all (data.paths);

	return (0);
}