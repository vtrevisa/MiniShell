/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 00:02:46 by vtrevisa          #+#    #+#             */
/*   Updated: 2022/06/20 00:02:51 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_if_normal(int n, int fd)
{
	if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	if (n >= 10)
	{
		ft_if_normal(n / 10, fd);
		n %= 10;
	}
	if (n < 10)
	{
		ft_putchar_fd(n + 48, fd);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n > -2147483647)
	{
		ft_if_normal(n, fd);
	}
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
	}
}
