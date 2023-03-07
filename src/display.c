/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:03:52 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/03/06 21:10:07 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

char	*userfinder(char *envp[])
{
	int	index;

	index = 0;
	while (!ft_strnstr(envp[index], "HOME=", 5))
		index++;
	return (envp[index] + 5);
}

void	print_user_dir(char **envp)
{
	char cwd[1024];
	char *cwp;
	int index;

	index = 0;
	getcwd(cwd, sizeof(cwd));
	cwp = ft_strdup(userfinder(envp));
	while (cwd[index] == cwp[index])
		index++;
	ft_printf("~%s", cwd + index);
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

//char	*read_line(char **envp, t_data data)
void	*read_line(char **envp, t_data *data)
{
	//char *line;

	data->linetyped = 0;
	print_user_dir(envp); //errors with the history, it erases the userdir
	data->line = readline("$ ");
	if (ft_strlen(data->line))
	{
		add_history(data->line);
		data->linetyped = 1;
		//return ;
	}
	else
		free(data->line);
		//return ;
}

int	show_display_prompt(t_data *data, char **envp)
{
	if (show_display() == -1)
		return (-1);
	while (1)
	{
		read_line(envp, data);
		//data->line = ft_strdup(read_line(envp));
		if (data->linetyped == 1)
		{
			if (ft_strnstr("exit", data->line, 4) != 0)
				return (EXIT_CODE);
			else
				ft_printf(">%s\n", data->line); //teste
			free(data->line);
		}	
		else
			printf("");
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data data;
	show_display_prompt(&data, envp);
	/* parser(&data); */
	//execute
	
	return (0);
}
