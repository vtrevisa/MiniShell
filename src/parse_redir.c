/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 04:46:03 by romachad          #+#    #+#             */
/*   Updated: 2023/05/12 03:41:48 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

char	**remove_redir(char **parsed, t_parser *p, char *redir_type)
{
	int	count;
	char	**copy;

	if (ft_strlen(redir_type) == ft_strlen(parsed[p->i]) && parsed[p->i + 1])
	{
		p->i++;
		parsed = remove_redir(parsed, p, redir_type);
	}
	count = 0;
	while (parsed[count])
		count++;
	copy = (char **) malloc(count * sizeof(parsed[0]));
	ft_memset(copy, 0, count * sizeof(parsed[0]));
	ft_memcpy(copy, parsed, p->i * sizeof(parsed[0]));
	ft_memcpy(copy + p->i, parsed + p->i + 1, (count - p->i - 1) * sizeof(parsed[0]));
	free(parsed[p->i]);
	free(parsed);
	p->i--;
	return (copy);
}


char	**parse_redir(char **parsed)
{
	t_parser	p;
	//char	**parsed;

	//parsed = copy_double_str(str);
	p.i = -1;
	p.j = 0;
	while (parsed[++p.i])
	{
		if (ft_strncmp(parsed[p.i], ">>", 2) == 0)
			//append_change_output()
			printf("append output redir\n");
		else if (ft_strncmp(parsed[p.i], ">", 1) == 0)
			parsed = remove_redir(parsed, &p, ">");
			//printf("output redir\n");
		else if (ft_strncmp(parsed[p.i], "<<", 2) == 0)
			printf("here-doc\n");
		else if (ft_strncmp(parsed[p.i], "<", 1) == 0)
			printf("input file");
		p.j++;
	}
	return (parsed);
}
