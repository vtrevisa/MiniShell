/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 04:04:24 by romachad          #+#    #+#             */
/*   Updated: 2023/06/08 17:39:54 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	exit_shell(t_data *data)
{
	free(data->line);
	free(data->cmd);
	free_char_array(data->envp);
	free(data->user);
	free_char_array(data->paths);
	exit(0);
}
