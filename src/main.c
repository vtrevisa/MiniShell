/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:03:52 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/04/17 22:35:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	show_display(void)
{
	int		fd;
	char	*line;

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
		if (ft_strnstr("exit", data->line, 4) != 0 && data->line != NULL)
		{
			free(data->line);
			return (EXIT_CODE);
		}
		else
			lexer(data);
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
	t_data	data;

	show_display();
	init_data(&data, envp);
	prompt_loop(&data);
	free (data.user);
	free_all (data.paths);
	return (0);
}
