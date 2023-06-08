/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitor <vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 18:09:09 by vitor             #+#    #+#             */
/*   Updated: 2022/08/18 13:40:11 by vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/libft.h"

static char	*get_line(char *buf)
{
	char	*ret;
	int		ln;

	ln = 0;
	if (!*buf)
		return (NULL);
	if (*buf)
	{
		while (buf[ln] && buf[ln] != '\n')
			ln++;
		ret = malloc (ln + 2);
		if (!ret)
			return (0);
		ln = -1;
		while (buf[++ln] && buf[ln] != '\n')
			ret[ln] = buf[ln];
		if (buf[ln] == '\n')
		{
			ret[ln] = buf[ln];
			ln++;
		}
		ret[ln] = 0;
		return (ret);
	}
	return (0);
}

static char	*get_buf(int fd, char *buf)
{
	int		err;
	char	*temp;

	err = 1;
	temp = malloc (BUFFER_SIZE + 1);
	if (!temp)
		return (NULL);
	while (ft_strchr(buf, '\n') == 0 && err)
	{
		err = read (fd, temp, BUFFER_SIZE);
		if (err < 0)
		{	
			free (temp);
			return (NULL);
		}
		temp[err] = 0;
		buf = ft_strjoin(buf, temp);
	}
	free (temp);
	return (buf);
}

static char	*get_rest(char *buf)
{
	int		nln;
	int		pos;
	char	*ret;

	nln = 0;
	pos = 0;
	while (buf[nln] && buf[nln] != '\n')
		nln++;
	if (!buf[nln])
	{
		free (buf);
		return (NULL);
	}
	ret = malloc (ft_strlen(buf) - nln + 1);
	if (!ret)
		return (0);
	nln++;
	while (buf[nln])
		ret[pos++] = buf[nln++];
	ret[pos] = 0;
	free (buf);
	return (ret);
}

char	*get_next_line(int fd)
{
	char		*ret;
	static char	*buf[MAX_FD_SIZE];

	if (fd < 0 || fd > MAX_FD_SIZE || BUFFER_SIZE <= 0)
		return (0);
	buf[fd] = get_buf(fd, buf[fd]);
	if (!buf[fd])
		return (0);
	ret = get_line(buf[fd]);
	buf[fd] = get_rest(buf[fd]);
	return (ret);
}
