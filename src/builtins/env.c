/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 09:51:51 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/06/21 09:51:55 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	env(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		ft_printf("%s\n", envp[i]);
}
