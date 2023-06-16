
#include "../../Include/minishell.h"

void	error_exit(char *str)
{
	perror(str);
	exit (1);
}
