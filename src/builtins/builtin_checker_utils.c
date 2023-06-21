/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_checker_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 01:12:41 by romachad          #+#    #+#             */
/*   Updated: 2023/06/21 09:57:56 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	if_bt4(t_data *data, int flag, t_pipe *args)
{
	if (flag == 1)
	{
		data->rcode = 0;
		data->envp = export(data->envp, data->full_cmd[0] + 1, data);
		return (data->rcode);
	}
	else
	{
		data->rcode = 0;
		data->envp = export(data->envp, data->full_cmd[args->cmd_n] + 1, data);
		return (data->rcode);
	}
}

int	if_bt5(t_data *data, int flag, t_pipe *args)
{
	if (flag == 1)
	{
		data->rcode = 0;
		data->envp = prep_unset(data->envp, (const char **) \
	data->full_cmd[0] + 1, data);
		return (data->rcode);
	}
	else
	{
		data->rcode = 0;
		data->envp = prep_unset(data->envp, (const char **) \
	data->full_cmd[args->cmd_n] + 1, data);
		return (data->rcode);
	}
}

int	if_bt6(t_data *data, int flag, t_pipe *args)
{
	if (flag == 1)
	{
		data->rcode = 0;
		env(data->envp);
		return (data->rcode);
	}
	else
	{
		data->rcode = 0;
		env(data->envp);
		return (data->rcode);
	}
}
