
#include "../Include/minishell.h"

int	echo_n(char **text)
{
	int	i;

	i = 0;
	while (text[i])
	{
		printf("%s", text[i]);
		i++;
		if (text[i])
			printf(" ");
	}
	return (0);
}
