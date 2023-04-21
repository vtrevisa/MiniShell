
#include "../Include/minishell.h"

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
		printf("%s\n", cwd);
	else
	{
		perror("getcwd error");
		//free(cwd);
		return (1);
	}
	//free(cwd);
	return (0);
}
