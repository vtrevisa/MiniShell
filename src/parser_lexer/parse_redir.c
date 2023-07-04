/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 04:46:03 by romachad          #+#    #+#             */
/*   Updated: 2023/07/04 04:05:09 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static char	**if_2more(char **parsed, t_data *data, t_parser *p)
{
	p->redir_type = 1;
	p->index2 = 0;
	create_redir_str(parsed, p, data, ">>");
	if (check_outfile(data->cmd_redir[p->index][p->index2] + 1, 1) != 0)
		data->redir_error = 1;
	return (remove_redir(parsed, p, ">>"));
}

//static void	if_1more(char **parsed, t_data *data, t_parser *p)
static char	**if_1more(char **parsed, t_data *data, t_parser *p)
{
	p->redir_type = 0;
	p->index2 = 0;
	//ft_printf("Entrando no create_redir!\n");
	create_redir_str(parsed, p, data, ">");
	//ft_printf("OK!\nBora pro checkoutfile!\n");
	if (check_outfile(data->cmd_redir[p->index][p->index2] + 1, 0) != 0)
		data->redir_error = 1;
	ft_printf("OK!\nVamos pro remove_redir!\n");
	parsed = remove_redir(parsed, p, ">");
	ft_printf("vamos ver o que voltou do remove_redir!!!\n\n");
	for (int i = 0; parsed[i]; i++)
		ft_printf("parsed[%d] = %s\n", i, parsed[i]);
	ft_printf("break point\n");
	getchar();
	return (parsed);
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
	if (check_infile(data->cmd_redir[p->index][p->index2] + 1) != 0)
		data->redir_error = 1;
	return (remove_redir(parsed, p, "<"));
	//parsed = remove_redir(parsed, p, "<");
}

char	**parse_redir(char **parsed, t_data *data, int index)
{
	t_parser	p;

	p.index = index;
	p.i = -1;
	p.j = 0;
	ft_printf("Vou entrar no while do parse_radir. p.i = %i\n",p.i);
	while (parsed[++p.i])
	{
		ft_printf("Inicio loop, p.i = %i\n", p.i);
		if (ft_strncmp(parsed[p.i], ">>", 2) == 0)
			parsed = if_2more(parsed, data, &p);
		else if (ft_strncmp(parsed[p.i], ">", 1) == 0)
			parsed = if_1more(parsed, data, &p);
		else if (ft_strncmp(parsed[p.i], "<<", 2) == 0)
			parsed = if_2less(parsed, data, &p);
		else if (ft_strncmp(parsed[p.i], "<", 1) == 0)
			parsed = if_1less(parsed, data, &p);
		ft_printf("FIM loop, p.i = %i\n", p.i);
		for (int i = 0; parsed[i]; i++)
			ft_printf("parsed[%d] temos: %s\n", i, parsed[i]);
		getchar();
	}
	return (parsed);
}
