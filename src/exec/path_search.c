/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 02:55:31 by romachad          #+#    #+#             */
/*   Updated: 2023/06/29 03:21:26 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static char	*exec_val(char **paths, char *cmd)
{
	char	*tmppath;
	int		i;
	int		x_flag;

	i = -1;
	while (paths[++i])
	{
		tmppath = ft_strjoin(paths[i], cmd);
		x_flag = access(tmppath, X_OK);
		if (x_flag == 0)
			break ;
		free(tmppath);
	}
	free(cmd);
	if (x_flag == 0)
		return (tmppath);
	else
		return (NULL);
}

static int	path_to_exec(const char *cmd)
{
	//if (cmd[0] == '.' && cmd[1] == '/')
	//	return (1);
	//else if (ft_strchr(cmd, '/'))
	if (ft_strchr(cmd, '/'))
		return (1);
	else
		return (0);
}

char	*path_search(char *envp[], const char *cmd)
{
	char	*path;
	char	*tmppath;
	char	**paths;
	int		i;

	if (path_to_exec(cmd) == 0)
	{
		printf("access nok\n");
		i = -1;
		while (envp[++i])
			if (!(ft_strncmp(envp[i], "PATH=", 5)))
				break ;
		if (envp[i])
		{
			path = ft_strdup(envp[i] + 5);
			//tmppath = ft_strdup(envp[i]);
			//path = ft_strjoin(tmppath, ":./");
			//free(tmppath);
		}
		else
			return (NULL);
			//path = ft_strdup(":./");
		paths = ft_split(path, ':');
		printf("this is paths[0]: %s\n", paths[0]);
		free(path);
		path = exec_val(paths, ft_strjoin("/", cmd));
		free_char_array(paths);
		return (path);
	}
	else
	{
		printf("cmd: %s\n", cmd);
		if (access(cmd, F_OK) != -1)
		{
			printf("ret do if\n");
			return (ft_strdup(cmd));
		}
		else
		{
			printf("ret do else\n");
			return (NULL);
		}
	}
}
