/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 10:00:20 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/07/11 17:16:59 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	export_empty(char **envp)
{
	int	i;
	int	j;

	i = -1;
	while (envp[++i])
	{
		ft_printf("declare -x ");
		j = -1;
		while (envp[i][++j] != '=')
			ft_putchar_fd(envp[i][j], STDOUT_FILENO);
		ft_putchar_fd(envp[i][j], STDOUT_FILENO);
		ft_putchar_fd('"', STDOUT_FILENO);
		while (envp[i][++j])
			ft_putchar_fd(envp[i][j], STDOUT_FILENO);
		ft_putstr_fd("\"\n", STDOUT_FILENO);
	}
}

