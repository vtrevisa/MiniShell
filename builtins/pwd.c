/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 18:49:55 by romachad          #+#    #+#             */
/*   Updated: 2023/03/20 22:39:44 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h> //getcwd();
#include <stdlib.h> //malloc
#include <limits.h> //PATH_MAX

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

int	main(void)
{
	printf("Path max: %d\n", PATH_MAX);
	return (pwd());
}
