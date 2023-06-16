
#include "../../Include/minishell.h"

void	env(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		ft_printf("%s\n", envp[i]);
}
