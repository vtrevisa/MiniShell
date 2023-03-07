/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:03:52 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/03/07 17:57:04 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

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
	char	*line;
	char	**args;
	int		status;

	status = 1;
	while (status)
	{
		ft_printf("> ");
		line = read_line(data);
		if (ft_strnstr("exit", line, 4) != 0)
			{
				free(line);
				return (EXIT_CODE);
			}
			else
				ft_printf(">%s\n", line); //teste
		/* args = split_line(line); */
		/* status = execute(args); */
		free (line);
		/* free (args); */
	}
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