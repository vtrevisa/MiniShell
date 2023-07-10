/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 22:33:51 by romachad          #+#    #+#             */
/*   Updated: 2023/07/10 14:03:08 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static void	if_str_slash(char *str, t_data *data, t_parser *parse, int flag)
{
	parse->j = parse->i + 1;
	while (parse->str[parse->j] && parse->str[parse->j] != '\'')
		parse->j++;
	if (parse->str[parse->j] == '\'')
		parse->i = parse->j;
}

static void	parse_var(char *str, t_data *data, t_parser *parse)
{
	int	flag;

	flag = 0;
	parse->str = str;
	parse->i = -1;
	while (parse->str[++parse->i])
	{
		if (parse->str[parse->i] == '"')
			flag = check_close_dq(parse->str + parse->i);
		if (parse->str[parse->i] == '\'' && \
	parse->str[parse->i + 1] && flag == 0)
			if_str_slash(str, data, parse, flag);
		parse->j = 0;
		if (parse->str[parse->i] == '$' && \
	(ft_isalnum(parse->str[parse->i + 1]) || \
	parse->str[parse->i + 1] == '_' || parse->str[parse->i + 1] == '?'))
		{
			replace_var(parse, data);
			flag = 0;
		}
	}
}

static void	while_cmd_split(char *str, t_data *data, t_parser *parser)
{
	parse_quote(data->cmd_split[parser->index], data, parser->index, parser);
	data->cmd_redir[parser->index] = (char **) ft_calloc(2, sizeof(char **));
	data->full_cmd[parser->index] = parse_redir(data->full_cmd \
		[parser->index], data, parser->index);
	parser->index2 = -1;
	while (data->full_cmd[parser->index][++parser->index2])
	{
		parse_var(data->full_cmd[parser->index][parser->index2], \
	data, parser);
		trim_quote(data->full_cmd[parser->index][parser->index2], \
	data, parser);
	}
}

void	parser(char *str, t_data *data)
{
	int			i;
	int			j;
	t_parser	parser;

	i = 0;
	data->cmd_split = split_pipes(str);
	while (data->cmd_split[i])
		i++;
	data->full_cmd = (char ***) ft_calloc(i + 1, sizeof(char ***));
	data->flag_fullcmd = 1;
	data->cmd_redir = (char ***) ft_calloc(i, sizeof(char ***));
	parser.index = -1;
	while (data->cmd_split[++parser.index])
		while_cmd_split(str, data, &parser);
}
