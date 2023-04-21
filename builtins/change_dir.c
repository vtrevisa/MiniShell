/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 18:35:21 by romachad          #+#    #+#             */
/*   Updated: 2023/03/20 22:57:49 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

//REPLACE STRNCMP AND STRDUP for FT_STRNCMP and FT_STRDUP
static char	*home_search(char *envp[])
{
	int	i;
	char	*tmppath;

	i = -1;
	while (envp[++i])
		if (!(strncmp(envp[i], "HOME=", 5)))
			break ;
	if (envp[i])
	{
		tmppath = strdup(envp[i] + (5 * sizeof(envp[i][0])));
		printf("tmppath: %s\n", tmppath);
		return (tmppath);
	}
	else
		return (NULL);
}

int	change_directory(char *path, char **envp)
{
	char	cwd[PATH_MAX];
	char	flag;

	flag = 0;
	if (path == NULL)
	{
		path = home_search(envp);
		if (path)
			flag = 1;
	}
	//printf("Current directory: %s\n", cwd);*/
	if (chdir(path) == -1)
	{
		perror("chdir");
		//free(cwd);
		if (flag)
			free(path);
		return (1);
	}
	//printf("Changed to directory: %s\n", cwd);
	if (flag)
		free(path);
	return (0);
}

int main(int argc, char *argv[], char *envp[])
{
	int	result;

	if (argc > 2)
	{
		fprintf(stderr, "Usage: %s <path>\n", argv[0]);
		return 1;
	}
	result = change_directory(argv[1], envp);
	return (result);
}
