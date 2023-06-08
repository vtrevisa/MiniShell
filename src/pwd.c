/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:52:11 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/06/08 18:04:37 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	pwd(void)
{
	char	cwd[PATH_MAX];
	//char	*cwd;
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
