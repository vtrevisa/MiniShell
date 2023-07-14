/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 01:12:41 by romachad          #+#    #+#             */
/*   Updated: 2023/07/14 20:14:20 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

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
	if (ft_strncmp(str, "exit", ft_strlen(str)) == 0)
		return (7);
	return (0);
}

int	builtin_exec_main(t_data *data)
{
	if (data->builtin == 1)
		return (echo_n(data->full_cmd[0] + 1));
	if (data->builtin == 2)
		return (change_directory(data->full_cmd[0], data->envp));
	if (data->builtin == 3)
		return (pwd());
	if (data->builtin == 4)
		return (if_bt4(data, 1, NULL));
	if (data->builtin == 5)
		return (if_bt5(data, 1, NULL));
	if (data->builtin == 6)
		return (if_bt6(data, 1));
	if (data->builtin == 7)
		exit_shell(data);
	return (0);
}

int	builtin_exec_pipe(t_pipe *args, t_data *data)
{
	if (args->builtin == 1)
		return (echo_n(data->full_cmd[args->cmd_n] + 1));
	if (args->builtin == 2)
		return (change_directory(data->full_cmd[args->cmd_n], data->envp));
	if (args->builtin == 3)
		return (pwd());
	if (args->builtin == 4)
		return (if_bt4(data, 2, args));
	if (args->builtin == 5)
		return (if_bt5(data, 2, args));
	if (args->builtin == 6)
		return (if_bt6(data, 2));
	if (args->builtin == 7)
		exit_shell(data);
	return (0);
}
