/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 22:54:48 by romachad          #+#    #+#             */
/*   Updated: 2023/04/23 03:09:08 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"
//////// POSSIVELMENTE SEPARA EM UTILS OU ALGO SIMILAR////
void	free_args(t_pipe *args)
{
	free(args->pid);
	free(args->pipes);
}

void	close_pipes(t_pipe *args)
{
	int	i;

	i = -1;
	while (++i < (args->qtd_cmd - 1) * 2)
		close(args->pipes[i]);
}

//////// FIM DO POSSIVELMENTE SEPARA EM UTILS OU ALGO SIMILAR////

//////// SEPARAR EM CHILD ////

static int	child_exec(t_pipe *args, t_data *data)
{
	execve(args->fpath, args->cmd_args, data->envp);
	free(args->fpath);
	free_char_array(args->cmd_args);
}

int	child_prog(t_pipe *args, t_data *data)
{
	args->cmd_args = treat_str(args->argv[args->cmd_n]);
	args->fpath = path_search(data->envp, args->cmd_args[0]);
	if (args->fpath == NULL)
	{
		dup2(STDERR_FILENO, STDOUT_FILENO);
		printf("minishell: %s not found\n", args->cmd_args[0]);
		free_char_array(args->cmd_args);
		return (127);
	}
	return (child_exec(args, data));
}
//////// FIM SEPARAR EM CHILD ////

static int	call_fork(t_pipe *args, t_data *data)
{
	args->pid[args->cmd_n] = fork();
	//colar um if de caso de falha do fork?
	if (args->pid[args->cmd_n] == 0)
	{
		args->pid[args->cmd_n] = child_prog(args, data);
		free_args(args);
		printf("\ndeu falha no child?\n");
		exit(1); // caso de falha do child...
	}
	if (args->pid[args->cmd_n] > 0)
		return (0);
	else
		return (-1); //caso de falha
}

static int	main_fork(t_pipe *args, t_data *data)
{
	int	i;

	args->flag = 0;
	call_fork(args, data); //Adicionar seguranca??
	args->cmd_n++;
	//if (args->qtd_cmd > 2)
	//	pipe_to_pipe(args, data);
	//else if (args->qtd_cmd == 2)
	//{
	//	args->flag = 1;
	//	call_fork(args, data->envp); //Adicionar seguranca??
	//}
	close_pipes(args);
	i = -1;
	while (++i < args->cmd_n)
		waitpid(args->pid[i], NULL, 0);
	free_args(args);
}

void	parser(t_data *data)
{
	t_pipe args;

	args.argv = ft_split(data->line, '|');
	args.qtd_cmd = 0;
	while (args.argv[args.qtd_cmd])
		args.qtd_cmd++;
	args.pipes = malloc((args.qtd_cmd * 2) * sizeof(args.qtd_cmd));
	if (args.pipes == NULL)
		error_exit("Fail pipes malloc");
	args.pid = malloc(args.qtd_cmd * sizeof(args.qtd_cmd));
	if (args.pid == NULL)
		error_exit("Fail pid malloc");
	args.cmd_n = 0;
	args.pipe_i = 0;
	main_fork(&args, data);

	/*int i;
	for (i=0; args.argv[i];i++)
		printf("This is the cmd %d: %s\n", i, args.argv[i]);*/
	free_char_array(args.argv);	
}
