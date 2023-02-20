#include "../Libft/Include/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/stat.h>
#include <readline/readline.h>
#include <readline/history.h>


int	main(void)
{
	int	fd;
	char *line;

	fd = 1;
	fd = open ("./src/display", O_RDONLY);
	while (fd != -1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		ft_printf("%s", line);
		free(line);
	}
	line = readline("$ ");
	ft_printf("%s\n", line);
	return (0);
}