/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error_codes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 13:13:27 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/07/06 13:14:56 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	Illegal_number(t_data *data)
{
	ft_printf_fd(2, "exit: Illegal number: %s\n", data->full_cmd[0][1]);
	return (2);
}