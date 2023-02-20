/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 01:15:21 by vtrevisa          #+#    #+#             */
/*   Updated: 2022/06/14 00:17:59 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			position;
	unsigned char	*r1;
	unsigned char	*r2;

	r1 = (unsigned char *)s1;
	r2 = (unsigned char *)s2;
	position = 0;
	if (n == 0)
		return (0);
	while ((position + 1) < n && r1[position] != '\0' && \
	r1[position] == r2[position])
		position++;
	return ((unsigned char)r1[position] - (unsigned char)r2[position]);
}
