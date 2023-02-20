/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printhex_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitor <vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 19:28:04 by vitor             #+#    #+#             */
/*   Updated: 2022/08/18 13:37:18 by vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/libft.h"

static char	hexabase(int num, int flag)
{
	char	*base;

	if (flag != 0)
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	return (base[num]);
}

static int	hexlen(unsigned long int lli)
{
	int	result;

	result = 0;
	while (lli >= 16)
	{
		lli = lli / 16;
		result++;
	}
	if (lli < 16)
		result++;
	return (result);
}

static void	*makestr(unsigned long int lli, int position, int flag)
{
	char	*str;

	str = malloc (position + 2);
	str[position + 1] = 0;
	while (lli >= 16)
	{
		str[position--] = hexabase(lli % 16, flag);
		lli /= 16;
	}
	str[position--] = hexabase(lli, flag);
	return (str);
}

static char	*htoa(unsigned long int lli, int flag)
{	
	char	*str;
	int		dig;

	dig = hexlen(lli);
	str = makestr(lli, dig - 1, flag);
	return (str);
}

void	printhex_fd(unsigned long int lli, int fd, int flag)
{	
	char	*str;

	ft_putstr_fd ("0x", 1);
	str = htoa(lli, flag);
	ft_putstr_fd (str, fd);
	free (str);
}
