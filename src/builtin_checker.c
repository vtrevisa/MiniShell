/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 01:12:41 by romachad          #+#    #+#             */
/*   Updated: 2023/05/14 23:40:34 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	builtin_checker(char *str)
{
	if (ft_strncmp(str, "echo", ft_strlen(str)) == 0)
		return (1);
	if (ft_strncmp(str, "cd", ft_strlen(str)) == 0)
		return (2);
	if (ft_strncmp(str, "pwd", ft_strlen(str)) == 0)
		return (3);
	if (ft_strncmp(str, "export", ft_strlen(str)) == 0)
		return (4);
	if (ft_strncmp(str, "unset", ft_strlen(str)) == 0)
		return (5);
	if (ft_strncmp(str, "env", ft_strlen(str)) == 0)
		return (6);
	//if (ft_strncmp(str, "exit", ft_strlen(str)) == 0)
	//	return (1);
	return (0);
}

int	builtin_exec_main(t_data *data)
{
	if (data->builtin == 1)
		return (echo_n(data->full_cmd[0] + 1));
	if (data->builtin == 2)
		return (change_directory(data->full_cmd[0][1], data->envp));
	if (data->builtin == 3)
		return (pwd());
	if (data->builtin == 4)
	{
		data->envp = export(data->envp, data->full_cmd[0] + 1);
		return (0); //alterar para retornar o returncode!
	}
	if (data->builtin == 5)
	{
		data->envp = prep_unset(data->envp, (const char **) data->full_cmd[0] + 1);
		return (0); //alterar para retornar o returncode!
	}
	if (data->builtin == 6)
	{
		env(data->envp);
		return (0);
	}
	return (0);
}

int	builtin_exec_pipe(t_pipe *args, t_data *data)
{
	if (args->builtin == 1)
		return (echo_n(args->cmd_args + 1));
	if (args->builtin == 2)
		return (change_directory(args->cmd_args[1], data->envp));
	if (args->builtin == 3)
		return (pwd());
	if (args->builtin == 4)
	{
		data->envp = export(data->envp, args->cmd_args + 1);
		return (0); //alterar para retornar o returncode!
	}
	if (args->builtin == 5)
	{
		//args->cmd_args++;
		data->envp = prep_unset(data->envp, (const char **) args->cmd_args + 1);
		return (0); //alterar para retornar o returncode!
	}
	if (args->builtin == 6)
	{
		env(data->envp);
		return (0);
	}
	return (0);
}

int	is_there_pipes(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '|')
			return (1);
	return (0);
}
