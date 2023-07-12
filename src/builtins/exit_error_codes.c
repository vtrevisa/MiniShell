/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error_codes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 13:13:27 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/07/12 16:16:28 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	illegal_number(void)
{
	ft_printf_fd(2, "exit: numeric argument required\n");
	return (2);
}

int	too_many_args(void)
{
	ft_printf_fd(2, " too many arguments");
	return (1);
}

int	big_number(char *str)
{
	int	ret;

	ret = ft_strncmp(str, "9223372036854775807", 21);
	if (ret == 0)
		return (255);
	else if (ret > 0)
		return (illegal_number());
	ret = ft_strncmp(str, "-9223372036854775808", 21);
	if (ret <= 0)
		return (ret *= -1);
	if (ret > 0)
		return (illegal_number());
	return (2);
}
