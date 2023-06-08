/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:58:59 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/06/08 16:59:00 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	echo_n(char **text)
{
	int	i;

	i = 0;
	if (ft_strncmp(text[0], "-n", 3) == 0) // && ft_strlen())
		i = 1;
	while (text[i])
	{
		ft_printf("%s", text[i]);
		i++;
		if (text[i])
			ft_printf(" ");
	}
	if (ft_strncmp(text[0], "-n", 3) != 0) // && ft_strlen())
		ft_printf("\n");
	return (0);
}
