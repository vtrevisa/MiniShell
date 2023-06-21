/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 10:14:04 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/06/21 10:17:51 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static char	*home_search(char *envp[])
{
	int		i;
	char	*tmppath;

	i = -1;
	while (envp[++i])
		if (!(ft_strncmp(envp[i], "HOME=", 5)))
			break ;
	if (envp[i])
	{
		tmppath = ft_strdup(envp[i] + (5 * sizeof(envp[i][0])));
		return (tmppath);
	}
	else
		return (NULL);
}

static int	check_path(char **paths)
{
	if (paths[1])
	{
		if (paths[2])
		{
			ft_printf("cd: too many arguments\n");
			return (1);
		}
	}
	return (0);
}

int	change_directory(char **paths, char **envp)
{
	char	cwd[PATH_MAX];
	char	flag;
	char	*path;

	if (check_path(paths))
		return (1);
	path = paths[1];
	flag = 0;
	if (path == NULL)
	{
		path = home_search(envp);
		if (path)
			flag = 1;
	}
	if (chdir(path) == -1)
	{
		perror("chdir");
		if (flag)
			free(path);
		return (1);
	}
	if (flag)
		free(path);
	return (0);
}
