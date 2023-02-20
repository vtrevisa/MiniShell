/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitor <vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 01:14:32 by vtrevisa          #+#    #+#             */
/*   Updated: 2022/06/26 14:51:05 by vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		s1_len;
	int		s2_len;
	char	*str1;
	int		all_len;

	if (!s1 || !s2)
		return (0);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	all_len = s2_len + s1_len + 1;
	str1 = ft_calloc(1, all_len);
	if (!str1)
		return (NULL);
	ft_strlcat(str1, s1, s1_len + 1);
	ft_strlcat(str1, s2, all_len + 1);
	return (str1);
}
