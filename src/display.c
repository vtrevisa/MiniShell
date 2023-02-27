/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:03:52 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/02/27 19:50:32 by vtrevisa         ###   ########.fr       */
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
		ft_printf("%s\n", line);//teste
		return (line);
	}
	else
		return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	char *line;
	
	if (show_display() == -1)
		return (-1);
	while (1)
	{
		line = ft_strdup(read_line(envp));
		if (ft_strlen(line) != 0)
		{
			
		}		
	}
	return (0);
}