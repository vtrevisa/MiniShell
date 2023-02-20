/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 01:15:34 by vtrevisa          #+#    #+#             */
/*   Updated: 2022/06/15 23:43:30 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	position;

	position = ft_strlen(s);
	while (position >= 0)
	{
		if (s[position] == (unsigned char) c)
			return ((char *)&s[position]);
		position--;
	}
	if (position < 0)
		return (NULL);
	return ((char *)&s[position]);
}
