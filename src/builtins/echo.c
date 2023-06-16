
#include "../../Include/minishell.h"

int	echo_n(char **text)
{
	int	i;

	i = 0;
	if (ft_strncmp(text[0], "-n", 3) == 0) // && ft_strlen())
		i = 1;
	while (text[i])
	{
		ft_printf("%s", text[i]);
		i++;
		if (text[i])
			ft_printf(" ");
	}
	if (ft_strncmp(text[0], "-n", 3) != 0) // && ft_strlen())
		ft_printf("\n");
	return (0);
}
