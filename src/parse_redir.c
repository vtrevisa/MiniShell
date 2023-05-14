/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 04:46:03 by romachad          #+#    #+#             */
/*   Updated: 2023/05/14 04:30:00 by romachad         ###   ########.fr       */
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

void	outfile(char **parsed, t_parser *p, t_data *data, char *redir_type)
{
	p->str = parsed[p->i];
	if (ft_strlen(redir_type) == ft_strlen(parsed[p->i]))
		p->str = parsed[p->i + 1];
	else
		p->str = parsed[p->i] + ft_strlen(redir_type);
	p->str = ft_strdup(p->str);
	parse_var_redir(data, p);
	trim_quote_redir(p);
	if (!data->cmd_redir[p->index][p->index2])
		data->cmd_redir[p->index][p->index2] = (char *) ft_calloc(ft_strlen(p->str) + 2, sizeof(p->str));
	else
	{
		free(data->cmd_redir[p->index][p->index2]);
		data->cmd_redir[p->index][p->index2] = (char *) ft_calloc(ft_strlen(p->str) + 2, sizeof(p->str));
	}
	if (p->redir_type == 0)
		data->cmd_redir[p->index][p->index2][0] = '0';
	else
		data->cmd_redir[p->index][p->index2][0] = '1';
	ft_strlcat(data->cmd_redir[p->index][p->index2], p->str, ft_strlen(p->str) + 2);
	free(p->str);
}

/*int	check_outfile(char *outfile, char mode)
{
	char	*str;
	int		fd;

	if (mode)
	{

	}
}*/

char	**parse_redir(char **parsed, t_data *data, int index)
{
	t_parser	p;

	p.index = index;
	p.i = -1;
	p.j = 0;
	while (parsed[++p.i])
	{
		if (ft_strncmp(parsed[p.i], ">>", 2) == 0)
			//append_change_output()
			printf("append output redir\n");
		else if (ft_strncmp(parsed[p.i], ">", 1) == 0)
		{
			p.redir_type = 0;
			p.index2= 0;
			outfile(parsed, &p, data, ">");
			parsed = remove_redir(parsed, &p, ">");
		}
		else if (ft_strncmp(parsed[p.i], "<<", 2) == 0)
			printf("here-doc\n");
		else if (ft_strncmp(parsed[p.i], "<", 1) == 0)
			printf("input file");
	}
	return (parsed);
}
