
#include "../Include/minishell.h"

static char	*home_search(char *envp[])
{
	int	i;
	char	*tmppath;

	i = -1;
	while (envp[++i])
		if (!(ft_strncmp(envp[i], "HOME=", 5)))
			break ;
	if (envp[i])
	{
		tmppath = ft_strdup(envp[i] + (5 * sizeof(envp[i][0])));
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

//  IMPORTANTE COLOCAR NO SHELL O ERRO SE HOUVER MAIS DE UM ARGUMENTO!!!!

/*int main(int argc, char *argv[], char *envp[])
{
	int	result;

	if (argc > 2)
	{
		fprintf(stderr, "Usage: %s <path>\n", argv[0]);
		return 1;
	}
	result = change_directory(argv[1], envp);
	return (result);
}*/
