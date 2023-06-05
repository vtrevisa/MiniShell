/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 04:46:03 by romachad          #+#    #+#             */
/*   Updated: 2023/06/04 21:04:17 by vtrevisa         ###   ########.fr       */
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

void	create_redir_str(char **parsed, t_parser *p, t_data *data, char *redir_type)
{
	p->str = parsed[p->i];
	if (ft_strlen(redir_type) == ft_strlen(parsed[p->i]))
		p->str = parsed[p->i + 1];
	else
		p->str = parsed[p->i] + ft_strlen(redir_type);
	p->str = ft_strdup(p->str);
	if (ft_strncmp(redir_type, "<<", ft_strlen(redir_type)) != 0)
		parse_var_redir(data, p);
	trim_quote_redir(p);
	//ft_printf("data->cmd_redir[%d][%d] = %d\n",p->index,p->index2,data->cmd_redir[p->index][p->index2]);
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

int	check_outfile(char *outfile, char mode)
{
	char	*str;
	int		fd;

	if (mode)
		fd = open(outfile, O_WRONLY | O_APPEND | O_CREAT, 0664);
	else
		fd = open(outfile, O_WRONLY | O_TRUNC | O_CREAT, 0664);
	if (fd == -1)
	{
		str = ft_strjoin("minishell: ", outfile);
		perror(str);
		free(str);
		return (1);
	}
	close(fd);
	return (0);
}

int	check_infile(char *infile)
{
	char	*str;
	int		fd;

	fd = access(infile, R_OK);
	if (fd == -1)
	{
		str = ft_strjoin("minishell: ", infile);
		perror(str);
		free(str);
		return (1);
	}
	return (0);
}

char	**parse_redir(char **parsed, t_data *data, int index)
{
	t_parser	p;

	p.index = index;
	p.i = -1;
	p.j = 0;
	while (parsed[++p.i])
	{
		if (ft_strncmp(parsed[p.i], ">>", 2) == 0)
		{
			p.redir_type = 1;
			p.index2 = 0;
			create_redir_str(parsed, &p, data, ">>");
			if (check_outfile(data->cmd_redir[p.index][p.index2] + 1, 1) != 0)
				data->redir_error = 1;
			parsed = remove_redir(parsed, &p, ">>");
		}
		else if (ft_strncmp(parsed[p.i], ">", 1) == 0)
		{
			p.redir_type = 0;
			p.index2 = 0;
			create_redir_str(parsed, &p, data, ">");
			if (check_outfile(data->cmd_redir[p.index][p.index2] + 1, 0) != 0)
				data->redir_error = 1;
			parsed = remove_redir(parsed, &p, ">");
		}
		else if (ft_strncmp(parsed[p.i], "<<", 2) == 0)
		{
			p.redir_type = 1;
			//ft_printf("here-doc\n");
			p.index2 = 1;
			create_redir_str(parsed, &p, data, "<<");
			data->cmd_redir[p.index][p.index2] = here_doc(data->cmd_redir[p.index][p.index2]);
			data->cmd_redir[p.index][p.index2] = parse_var_heredoc(data->cmd_redir[p.index][p.index2], data);
			parsed = remove_redir(parsed, &p, "<<");
		}
		else if (ft_strncmp(parsed[p.i], "<", 1) == 0)
		{
			p.redir_type = 0;
			p.index2 = 1;
			//ft_printf("input file");
			create_redir_str(parsed, &p, data, "<");
			if (check_infile(data->cmd_redir[p.index][p.index2] + 1) != 0)
				data->redir_error = 1;
			parsed = remove_redir(parsed, &p, "<");
		}
	}
	return (parsed);
}
