/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitor <vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 19:19:00 by vitor             #+#    #+#             */
/*   Updated: 2022/08/18 13:54:41 by vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/libft.h"

int	countdigit(int n)
{
	long int	nb;
	int			result;

	nb = n;
	result = 0;
	if (n < 0)
	{
		nb *= -1;
		result++;
	}
	while (nb >= 10)
	{
		nb = nb / 10;
		result++;
	}
	if (nb < 10)
		result++;
	return (result);
}

int	countudigit(unsigned int n)
{
	unsigned int	nb;
	int				result;

	nb = n;
	result = 0;
	while (nb >= 10)
	{
		nb = nb / 10;
		result++;
	}
	if (nb < 10)
		result++;
	return (result);
}

void	ft_putunbr_fd(unsigned int n, int fd)
{
	if (n >= 10)
	{
		ft_putunbr_fd(n / 10, fd);
		n %= 10;
	}
	if (n < 10)
	{
		ft_putchar_fd(n + 48, fd);
	}
}
