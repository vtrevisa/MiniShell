/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 01:13:55 by vtrevisa          #+#    #+#             */
/*   Updated: 2022/06/12 02:40:31 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	position;

	position = 0;
	while (s[position])
	{	
		if (s[position] == (unsigned char)c)
			return ((char *)s + position);
		position++;
	}
	if (s[position] == c)
		return ((char *)s + position);
	return (NULL);
}
