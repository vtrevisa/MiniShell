/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 22:49:22 by romachad          #+#    #+#             */
/*   Updated: 2023/04/25 03:48:03 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

static int	child_start(t_pipe *args, t_data *data)
{
	if (args->qtd_cmd > 1) //Por essa regiao sera necessario verificar se ha infile...
	{
		dup2(args->pipes[1], STDOUT_FILENO);
		close_pipes(args); //Deveria estar fora do if??
	}
	execve(args->fpath, args->cmd_args, data->envp);
	free(args->fpath);
	free_char_array(args->cmd_args);
	return (errno);
}

static int	child_middle(t_pipe *args, t_data *data)
{
	dup2(args->pipes[args->pipe_i], STDIN_FILENO);
	dup2(args->pipes[args->pipe_i + 3], STDOUT_FILENO);
	close_pipes(args);
	execve(args->fpath, args->cmd_args, data->envp);
	free(args->fpath);
	free_char_array(args->cmd_args);
	return (errno);
}

static int	child_end(t_pipe *args, t_data *data)
{
	dup2(args->pipes[args->pipe_i], STDIN_FILENO); //verificar se ha outfile...
	close_pipes(args);
	execve(args->fpath, args->cmd_args, data->envp);
	free(args->fpath);
	free_char_array(args->cmd_args);
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
	args->cmd_args = treat_str(args->argv[args->cmd_n]);
	args->fpath = path_search(data->envp, args->cmd_args[0]);
	if (args->fpath == NULL)
	{
		dup2(STDERR_FILENO, STDOUT_FILENO);
		printf("minishell: %s not found\n", args->cmd_args[0]);//Mudar para stderr?
		free_char_array(args->cmd_args);
		return (127);
	}
	return (child_exec(args, data));
}
