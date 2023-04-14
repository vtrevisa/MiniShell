#include <stdio.h>
#include <stdlib.h>

int	main()
{
	char *home;

	home = getenv("HOME");

	if (home != NULL)
		printf("Home is: %s\n", home);
	else
		printf("Home is not set!\n");
	return (0);
}
