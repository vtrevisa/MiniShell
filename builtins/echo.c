/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 17:54:54 by romachad          #+#    #+#             */
/*   Updated: 2023/03/19 18:33:14 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

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

int	main(int argc, char **argv)
{
	int	retcode;

	if (argc > 1)
	{
		retcode = echo_n(argv + 1);
	}
	else
	{
		return (1);
	}
	return (retcode);
}
