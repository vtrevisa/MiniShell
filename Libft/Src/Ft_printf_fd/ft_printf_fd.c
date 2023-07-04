/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 19:33:25 by vitor             #+#    #+#             */
/*   Updated: 2023/07/04 09:48:16 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/libft.h"

static int	conversions(char c, va_list ap, int fd)
{
	int	ret;

	ret = 0;
	if (c == 'c')
		ret += handlechar (ap, fd);
	else if (c == 's')
		ret += handlestr (ap, fd);
	else if (c == 'p')
		ret += handlepointer (ap, fd, 2);
	else if (c == 'd' || c == 'i')
		ret += handleints(ap, fd);
	else if (c == 'u')
		ret += handleunsigned(ap, fd);
	else if (c == 'x')
		ret += handlehex(ap, fd, 1);
	else if (c == 'X')
		ret += handlehex(ap, fd, 0);
	else if (c == '%')
		ret += write(fd, &c, 1);
	return (ret);
}

int	ft_printf_fd(int fd, const char *str, ...)
{
	va_list	ap;
	int		position;
	int		ret;

	va_start(ap, str);
	position = 0;
	ret = 0;
	while (str[position])
	{
		if (str[position] == '%')
		{
			if (ft_strchr("cspdiuxX%", str[position + 1]))
				ret += conversions(str[++position], ap, fd);
			else
				ret += write (fd, &str[position], 1);
		}
		else
			ret += write(fd, &str[position], 1);
		position++;
	}
	va_end(ap);
	return (ret);
}
