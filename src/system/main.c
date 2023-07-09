/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:03:52 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/07/09 23:34:07 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

t_data	g_var;

static void	show_display(void)
{
	int		fd;
	char	*line;

	fd = open ("./src/system/display", O_RDONLY);
	while (fd != -1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		ft_printf("%s", line);
		free(line);
	}
	close(fd);
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
				if_data_cmd_redir0(data, &fd, 0);
			if (data->cmd_redir[0][1])
				if_data_cmd_redir1(data, &fd, 0);
			data->rcode = builtin_exec_main(data);
			if (data->cmd_redir[0][0])
				if_data_cmd_redir0(data, &fd, 1);
			if (data->cmd_redir[0][1])
				if_data_cmd_redir1(data, &fd, 1);
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

	status = 0;
	while (1)
	{
		read_line(data);
		if (data->linetyped == 1)
		{
			data->redir_error = 0;
			parser(data->line, data);
			free_char_array(data->cmd_split);
			//if (data->redir_error == 0 && data->ctrl_c == 0 && \
			data->full_cmd[0][0])
			if (data->ctrl_c == 0 && data->full_cmd[0][0])
				command_exec(data);
			else if (data->ctrl_c == 1)
				if_ctrl_c1(data);
			free_full_cmd(data);
			free(data->cmd_redir);
			free(data->full_cmd);
			free(data->line);
		}
		else
			ft_printf("");
	}
}

int	main(int argc, char **argv, char **envp)
{	
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	show_display();
	init_data(&g_var, envp);
	prompt_loop(&g_var);
	free (g_var.user);
	free_all (g_var.paths);
	return (0);
}
