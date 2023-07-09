/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 04:46:03 by romachad          #+#    #+#             */
/*   Updated: 2023/07/09 23:39:19 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static char	**if_2more(char **parsed, t_data *data, t_parser *p)
{
	p->redir_type = 1;
	p->index2 = 0;
	create_redir_str(parsed, p, data, ">>");
	/*if (check_outfile(data->cmd_redir[p->index][p->index2] + 1, 1) != 0)
		data->redir_error = 1;*/
	return (remove_redir(parsed, p, ">>"));
}

static char	**if_1more(char **parsed, t_data *data, t_parser *p)
{
	p->redir_type = 0;
	p->index2 = 0;
	create_redir_str(parsed, p, data, ">");
	/*if (check_outfile(data->cmd_redir[p->index][p->index2] + 1, 0) != 0)
		data->redir_error = 1;*/
	return (remove_redir(parsed, p, ">"));
}

static char	**if_2less(char **parsed, t_data *data, t_parser *p)
{
	p->redir_type = 1;
	p->index2 = 1;
	create_redir_str(parsed, p, data, "<<");
	data->cmd_redir[p->index][p->index2] = here_doc(data->cmd_redir \
		[p->index][p->index2]);
	data->cmd_redir[p->index][p->index2] = parse_var_heredoc \
		(data->cmd_redir[p->index][p->index2], data);
	return (remove_redir(parsed, p, "<<"));
}

static char	**if_1less(char **parsed, t_data *data, t_parser *p)
{
	p->redir_type = 0;
	p->index2 = 1;
	create_redir_str(parsed, p, data, "<");
	/*if (check_infile(data->cmd_redir[p->index][p->index2] + 1) != 0)
		data->redir_error = 1;*/
	return (remove_redir(parsed, p, "<"));
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
			parsed = if_2more(parsed, data, &p);
		else if (ft_strncmp(parsed[p.i], ">", 1) == 0)
			parsed = if_1more(parsed, data, &p);
		else if (ft_strncmp(parsed[p.i], "<<", 2) == 0)
			parsed = if_2less(parsed, data, &p);
		else if (ft_strncmp(parsed[p.i], "<", 1) == 0)
			parsed = if_1less(parsed, data, &p);
	}
	return (parsed);
}
