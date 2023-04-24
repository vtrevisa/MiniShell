/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 22:54:48 by romachad          #+#    #+#             */
/*   Updated: 2023/04/24 01:48:28 by romachad         ###   ########.fr       */
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

int	create_pipes(t_pipe *args)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (++i < args->qtd_cmd -1)
	{
		if (pipe(&args->pipes[j]) == -1)
			return (-1);
		j += 2;
	}
	return (0);
}


//////// FIM DO POSSIVELMENTE SEPARA EM UTILS OU ALGO SIMILAR////

static int	call_fork(t_pipe *args, t_data *data)
{
	args->pid[args->cmd_n] = fork();
	//colar um if de caso de falha do fork?
	if (args->pid[args->cmd_n] == 0)
	{
		args->pid[args->cmd_n] = child_prog(args, data);
		free_args(args);
		printf("\ndeu falha no child?\n");
		free_char_array(data->envp);// Realmente necessario?
		exit(args->pid[args->cmd_n]); // caso de falha do child... 
	}
	if (args->pid[args->cmd_n] > 0)
		return (0);
	else
		return (-1); //caso de falha
}

static void	pipe_to_pipe(t_pipe *args, t_data *data)
{
	int	retv;
	int	i;

	args->flag = 2;
	i = -1;
	while (++i < args->qtd_cmd - 2)
	{
		//free(args->cmd_str);
		//args->cmd_str = ft_strdup(args->argv[args->cmd_n]);
		retv = call_fork(args, data);
		if (retv < 0)
		{
			free_args(args);
			exit(255);
		}
		args->cmd_n++;
		args->pipe_i += 2;
	}
}

static int	main_fork(t_pipe *args, t_data *data)
{
	int	i;

	args->flag = 0;
	call_fork(args, data); //Adicionar seguranca??
	args->cmd_n++;
	if (args->qtd_cmd > 2)
		pipe_to_pipe(args, data);
	if (args->qtd_cmd > 1)
	{
		//if (!(args->qtd_cmd > 2))
		//	args->pipe_i += 2;
		args->flag = 1;
		call_fork(args, data); //Adicionar seguranca??
	}
	close_pipes(args);
	i = -1;
	while (++i < args->cmd_n)
		waitpid(args->pid[i], NULL, 0);
	free_args(args);
	return (0);
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
	if (create_pipes(&args) == -1)
	{
		printf("ERROR! Failed to create pipes!\n");
		free(args.pipes);
		exit (130);
	}
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
