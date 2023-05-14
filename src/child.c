/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 22:49:22 by romachad          #+#    #+#             */
/*   Updated: 2023/05/14 06:53:47 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

static int	child_start(t_pipe *args, t_data *data)
{
	int	fd;
	if (data->cmd_redir[args->cmd_n][1])
	{
		fd = open(data->cmd_redir[args->cmd_n][1] + 1, O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (data->cmd_redir[args->cmd_n][0])
	{
		if (data->cmd_redir[args->cmd_n][0][0] == '0')
			fd = open(data->cmd_redir[args->cmd_n][0] + 1, O_WRONLY);
		else
			fd = open(data->cmd_redir[args->cmd_n][0] + 1, O_WRONLY | O_APPEND);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}

	//if (args->qtd_cmd > 1) //Por essa regiao sera necessario verificar se ha infile...
	if (data->qtd_cmd > 1) //Por essa regiao sera necessario verificar se ha infile...
	{
		dup2(args->pipes[1], STDOUT_FILENO);
		close_pipes(args, data); //Deveria estar fora do if??
	}
	if (args->builtin == 0)
	{
		//execve(args->fpath, args->cmd_args, data->envp);
		execve(args->fpath, data->full_cmd[args->cmd_n], data->envp);
		free(args->fpath);
	}
	else
		builtin_exec_pipe(args, data);
	//free_char_array(args->cmd_args);
	
	/*free_char_array(data->envp);
	//free_char_array(data->full_cmd[args->cmd_n]); //--> Trocar para liberar todo o data->full_cmd!!
	int i;
	for (i=0; data->full_cmd[i]; i++)
		free_char_array(data->full_cmd[i]);
	free(data->full_cmd[i]);*/
	if (args->builtin == 0)
		return (errno);
	else
		return (0); //ajustar para mandar o return code do builtin;
}

static int	child_middle(t_pipe *args, t_data *data)
{
	dup2(args->pipes[args->pipe_i], STDIN_FILENO);
	dup2(args->pipes[args->pipe_i + 3], STDOUT_FILENO);
	//close_pipes(args);
	close_pipes(args, data);
	//execve(args->fpath, args->cmd_args, data->envp);
	execve(args->fpath, data->full_cmd[args->cmd_n], data->envp);
	free(args->fpath);
	//free_char_array(args->cmd_args);
	
	/*free_char_array(data->envp);
	//free_char_array(data->full_cmd[args->cmd_n]); //--> Trocar para liberar todo o data->full_cmd!!
	int i;
	for (i=0; data->full_cmd[i]; i++)
		free_char_array(data->full_cmd[i]);
	free(data->full_cmd[i]);*/
	
	return (errno);
}

static int	child_end(t_pipe *args, t_data *data)
{
	int	fd;

	dup2(args->pipes[args->pipe_i], STDIN_FILENO); //verificar se ha outfile...
	//close_pipes(args);
	close_pipes(args, data);
	if (data->cmd_redir[args->cmd_n][0])
	{
		if (data->cmd_redir[args->cmd_n][0][0] == '0')
			fd = open(data->cmd_redir[args->cmd_n][0] + 1, O_WRONLY);
		else
			fd = open(data->cmd_redir[args->cmd_n][0] + 1, O_WRONLY | O_APPEND);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	execve(args->fpath, data->full_cmd[args->cmd_n], data->envp);
	free(args->fpath);
	//free_char_array(args->cmd_args);
	
	/*free_char_array(data->envp);
	//free_char_array(data->full_cmd[args->cmd_n]); //--> Trocar para liberar todo o data->full_cmd!!
	int i;
	for (i=0; data->full_cmd[i]; i++)
		free_char_array(data->full_cmd[i]);
	free(data->full_cmd[i]);*/

	return (errno);
}

static int	child_exec(t_pipe *args, t_data *data)
{
	if (args->flag == 0)
		return (child_start(args, data));
	if (args->flag == 2)
		return (child_middle(args, data));
	else
		return (child_end(args, data));
}

int	child_prog(t_pipe *args, t_data *data)
{
	//args->cmd_args = treat_str(args->argv[args->cmd_n]); -->Str ja tratada no parser
	//args->builtin = builtin_checker(args->cmd_args[0]);
	args->builtin = builtin_checker(data->full_cmd[args->cmd_n][0]);
	if (args->builtin == 0)
	{
		//args->fpath = path_search(data->envp, args->cmd_args[0]);
		args->fpath = path_search(data->envp, data->full_cmd[args->cmd_n][0]);
		if (args->fpath == NULL)
		{
			dup2(STDERR_FILENO, STDOUT_FILENO);
			//printf("minishell: %s not found\n", args->cmd_args[0]);//Mudar para stderr?
			printf("minishell: %s not found\n", data->full_cmd[args->cmd_n][0]);//Mudar para stderr?
			//free_char_array(args->cmd_args);
			/*free_char_array(data->full_cmd[args->cmd_n]); //--> Trocar para liberar todo o data->full_cmd!!
			free_char_array(data->envp);
			int i;
			for (i=0; data->full_cmd[i]; i++)
				free_char_array(data->full_cmd[i]);
			free(data->full_cmd[i]);*/
			return (127);
		}
	}
	//else
	//	printf("BUILTIN Identificado!\n");
	return (child_exec(args, data));
}
