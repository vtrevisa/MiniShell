/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:03:52 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/06/08 17:48:56 by vtrevisa         ###   ########.fr       */
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

void	command_exec(t_data *data)
{
	int	fd;

	data->qtd_cmd = 0;
	while (data->full_cmd[data->qtd_cmd])
		data->qtd_cmd++;
	if (data->qtd_cmd == 1)
	{
		data->builtin = builtin_checker(data->full_cmd[0][0]);
		if (data->builtin)
		{
			if (data->cmd_redir[0][0])
			{
				data->saved_stdout = dup(STDOUT_FILENO);
				if (data->cmd_redir[0][0][0] == '0')
					fd = open(data->cmd_redir[0][0] + 1, O_WRONLY);
				else
					fd = open(data->cmd_redir[0][0] + 1, O_WRONLY | O_APPEND);
				dup2(fd, STDOUT_FILENO);
				close(fd);
			}
			if (data->cmd_redir[0][1])
			{
				data->saved_stdin = dup(STDIN_FILENO);
				if (data->cmd_redir[0][1][0] == '0')
					fd = open(data->cmd_redir[0][1] + 1, O_RDONLY);
				dup2(fd, STDIN_FILENO);
				close(fd);
			}
			//ft_printf("ESTOU INDO PRO BUILTIN EXEC MAIN\n");
			data->rcode = builtin_exec_main(data);
			//ft_printf("SAI DO BUILTIN EXEC MAIN!\n");
			if (data->cmd_redir[0][0])
			{
				dup2(data->saved_stdout, STDOUT_FILENO);
				close(data->saved_stdout);
			}
			if (data->cmd_redir[0][1])
			{
				dup2(data->saved_stdin, STDIN_FILENO);
				close(data->saved_stdin);
			}
		}
		else
			piper(data);
	}
	else
		piper(data);
}

int	prompt_loop(t_data *data)
{
	int		status;
	int		i;
	int		j;

	status = 0;
	while (1)
	{
		ft_printf("> ");
		read_line(data);
		if (data->linetyped == 1)
		{
			/*if (ft_strnstr("exit", data->line, 4) != 0)
			{
				free(data->line);
				free(data->cmd);
				free_all(data->envp);
				return (EXIT_CODE);
			}*/
			data->redir_error = 0;
			parser(data->line, data);
			free_char_array(data->cmd_split);
			/* Just to show the commands sperately 
			int i;
			if (data->full_cmd)
			{
				for (i=0; data->full_cmd[i]; i++)
				{
					int j;
					for (j=0; data->full_cmd[i][j]; j++)
						ft_printf("str[%d][%d] = %s\n",i,j,data->full_cmd[i][j]);
					ft_printf("REDIRECTIONS:\n");
					for (j=0; j < 2; j++)
						ft_printf("arg[%d][%d] = %s\n",i,j,data->cmd_redir[i][j]);
				}
			}*/
			if (data->redir_error == 0 && data->ctrl_c == 0)
			{
				command_exec(data);
			}
			else if (data->ctrl_c == 1)
			{
				data->ctrl_c = 0;
				dup2(data->saved_stdin, STDIN_FILENO);
				close(data->saved_stdin);
				//STDIN_FILENO = dup(data->saved_stdin);
			}
			for (i = 0; data->full_cmd[i]; i++)
			{
				free_char_array(data->full_cmd[i]);
				for (j = 0; j < 2; j++)
					free(data->cmd_redir[i][j]);
				free(data->cmd_redir[i]);
			}
			free(data->cmd_redir);
			free(data->full_cmd);
			free(data->line);
		}
		/* write(1, "ok\n", 3); */
		//lexer(data);
		/* status = execute(data); */
		else
			ft_printf("");
	}
}

t_data	g_global_var;

int	main(int argc, char **argv, char **envp)
{	
	// Load config files, if any.
	//t_data	data;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	show_display();
	//init_data(&data, envp);
	init_data(&g_global_var, envp);
	// Run command loop.
	//prompt_loop(&data);
	prompt_loop(&g_global_var);
	// Perform any shutdown/cleanup.
	//free (data.user);
	//free_all (data.paths);
	free (g_global_var.user);
	free_all (g_global_var.paths);
	return (0);
}
