/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 09:52:00 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/06/21 09:52:42 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	pwd(void)
{
	//char	*cwd;
	char	cwd[PATH_MAX];


	/*cwd = malloc(PATH_MAX * sizeof(cwd));
	if (cwd == NULL)
	{
		perror("pwd malloc error");
		return (1);
	}*/
	if (getcwd(cwd, PATH_MAX) != NULL)
		ft_printf("%s\n", cwd);
	else
	{
		perror("getcwd error");
		//free(cwd);
		return (1);
	}
	//free(cwd);
	return (0);
}
