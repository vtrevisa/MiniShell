/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 04:04:24 by romachad          #+#    #+#             */
/*   Updated: 2023/07/06 13:29:19 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static int check_arg2(t_data *data)
{
	int				i;
	long long int	code;

	i = 0;
	while(data->full_cmd[0][1][i] == '+')
		i++;
	if (data->full_cmd[0][1][i] == '-')
		code = Illegal_number(data);
	else if(is_all_num(data->full_cmd[0][1] + i))
	{
		if (ft_strncmp(data->full_cmd[0][1], "2147483647", 11) > 0 && \
	ft_strlen(data->full_cmd[0][1]) > 9)
			code = Illegal_number(data);
		else
			code = ft_atoli(data->full_cmd[0][1] + i);
	}
	else if(is_all_alph(data->full_cmd[0][1] + i))
	{
		code = Illegal_number(data);
	}
	return (code);
}

static int	handle_exit_code(t_data *data)
{
	int	code;

	code = 0;
	if(data->full_cmd[0][2])
	{
		ft_printf_fd(2, " too many arguments");
		exit(1);
	}
	code = check_arg2(data);
/* 	ft_printf("$?: %d\n", code % 256); */
	return(code % 256);
}

void	exit_shell(t_data *data)
{
	int	exit_code;

	exit_code = 0;
	if (data->full_cmd[0][1])
		exit_code = handle_exit_code(data);
	if (data->linetyped == 1)
	{
		free_full_cmd(data);
		free(data->cmd_redir);
		free(data->full_cmd);
		free(data->line);
	}
	free(data->user);
	free(data->cmd);
	free_char_array(data->envp);
	free_char_array(data->paths);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit(exit_code);
}

void	exit_child(t_data *data, int code)
{
	if (data->linetyped == 1)
	{
		free_full_cmd(data);
		free(data->cmd_redir);
		free(data->full_cmd);
		free(data->line);
	}
	free(data->user);
	free(data->cmd);
	free_char_array(data->paths);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit(code);
}
