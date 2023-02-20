/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 01:14:04 by vtrevisa          #+#    #+#             */
/*   Updated: 2022/06/14 01:11:14 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dst;
	size_t	s_len;

	s_len = ft_strlen(s) + 1;
	dst = malloc(s_len);
	if (!dst)
		return (NULL);
	ft_strlcpy (dst, s, s_len);
	return (dst);
}
