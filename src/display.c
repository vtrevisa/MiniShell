/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:03:52 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/02/27 21:25:22 by vtrevisa         ###   ########.fr       */
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

char	*read_line(char **envp)
{
	char *line;

	print_user_dir(envp); //errors with the history, it erases the userdir
	line = readline("$ ");
	if (ft_strlen(line))
	{
		add_history(line);
		return (line);
	}
	else
		return (NULL);
}

void	show_display_prompt(t_data *data, char **envp)
{
	if (show_display() == -1)
		return (-1);
	while (1)
	{
		data->line = ft_strdup(read_line(envp));
		if (ft_strlen(data->line) != 0)
		{
			if (ft_strnstr("exit", data->line, 4) != 0)
				return (EXIT_CODE);
			else
				ft_printf(">%s\n", data->line); //teste
		}		
	}
}

int	test_cmd(t_data *data, char **argvn)
{
	char	*tmp;
	int index;
	
	index = -1;
	while (data->paths[++index])
	{
		tmp = ft_strjoin(data->paths[index], "/");
		data->cmd = ft_strjoin(tmp, argvn[0]);
		if (access(data->cmd, X_OK) == 0)
		{
			free (tmp);
			return (0);
		}
		free (data->cmd);
		free (tmp);
	}
	data->cmd = NULL;
	ft_printf("%s: command not found\n", argvn[0]);
	return (127);
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

void	parser(char *line)
{
	char *cmd;
	
	
}

int	main(int argc, char **argv, char **envp)
{
	t_data data;
	show_display_promt(&data, envp);
	//parse
	//execute
	
	return (0);
}