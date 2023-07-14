/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 02:55:31 by romachad          #+#    #+#             */
/*   Updated: 2023/07/14 20:15:23 by vtrevisa         ###   ########.fr       */
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
	if (ft_strchr(cmd, '/'))
		return (1);
	else
		return (0);
}

static char	*if_path_to_exec_true(char *envp[], char **path, char ***paths, \
	const char *cmd)
{
	int	i;

	i = -1;
	while (envp[++i])
		if (!(ft_strncmp(envp[i], "PATH=", 5)))
			break ;
	if (envp[i])
		*path = ft_strdup(envp[i] + 5);
	else
		return (NULL);
	*paths = ft_split(*path, ':');
	free(*path);
	*path = exec_val(*paths, ft_strjoin("/", cmd));
	free_char_array(*paths);
	return (*path);
}

char	*path_search(char *envp[], const char *cmd, t_data *data)
{
	char	*path;
	char	**paths;
	char	*str;

	if (path_to_exec(cmd) == 0)
		return (if_path_to_exec_true(envp, &path, &paths, cmd));
	else
	{
		if (access(cmd, F_OK) != -1)
			return (ft_strdup(cmd));
		else
		{
			str = ft_strjoin("minishell: ", cmd);
			perror(str);
			free(str);
			data->rcode = 127;
			return (NULL);
		}
	}
}
