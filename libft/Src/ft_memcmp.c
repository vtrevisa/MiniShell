/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitor <vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 01:13:09 by vtrevisa          #+#    #+#             */
/*   Updated: 2022/06/26 15:22:20 by vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			position;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	position = 0;
	while (position < n)
	{
		if (n == 0)
			return (0);
		if (str1[position] != str2[position])
			return (str1[position] - str2[position]);
		position++;
	}
	return (0);
}
