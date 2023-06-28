/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 22:33:51 by romachad          #+#    #+#             */
/*   Updated: 2023/06/28 04:25:44 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

/*void	normal_st(t_parser *p, char *str)
{
	int	i;

	i = p.i;
	//while (str[p.i] != ' ' && str[p.i] != '\f' && str[p.i] != '\r' && str[p.i] != '\t' && str[p.i] != '\v')
	//	p.i++;
	while (str[p.i])
	{

		p.i++;
	}

}

char	**parser(char *str)
{
	t_parser	parse;

	parse.full_cmd = (char **)malloc(1 * sizeof(parse.full_cmd));
	parse.full_cmd[0] = NULL;
	parse.pipe_i = 0;
	while (str == ' ' || str == '\f' || str == '\r' || str == '\t' || str == '\v')
		str++;
	parse.st = NORMAL;
	parse.i = -1;
	while (str[++parse.i])
	{
		if (parse.st == NORMAL)
			normal_func;
		else if (parse.st == ESPACE)
			espace_func;
		else if (parse.st == SINGLE_QUOTE)
			sq_func;
		else if (parse.st == DOUBLE_QUOTE)
			dq_func;
		else if (parse.st == VARIABLE)
			var_func;
		else if (parse.st == VARIABLE_IN_DQ)
			var_dq_func;
	}
}*/


/*Split pipes if not in quotes*/
char	**split_pipes(char *str)
{
	int	i;
	int	j;
	char	flag;
	
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			flag = str[i];
			j = i + 1;
			while(str[j] && str[j] != flag)
				j++;
			if (str[j] == flag)
				i = j;
		}
		if (str[i] == '|')
			str[i] = 17;
	}
	return (ft_split(str, 17));
}

char	*find_variable(char *var, t_data *data)//-> Move this to parser_utils.c
{
	int	i;

	i = -1;
	while (data->envp[++i])
	{
		if (ft_strncmp(data->envp[i], var, ft_strlen(var)) == 0 && data->envp[i][ft_strlen(var)] == '=')
			return (data->envp[i] + ft_strlen(var) + 1);
	}
	return (NULL);
}

void	replace_var(t_parser *p, t_data *data)
{
	int	var_len;
	char	*var_name;
	char	*var_value;
	char	*new_str;
	char	flag;

	flag = 0;
	var_len =0;
	//printf("p->str[p->i + 1] = %c", p->str[p->i+1]);
	if (p->str[p->i +1] != '?')
	{
		if (ft_isdigit(p->str[p->i + 1]))
		{
			var_len = 1;
		}
		else
		{
			while (p->str[p->i + 1 + var_len] && (ft_isalnum(p->str[p->i + 1 + var_len]) || p->str[p->i + 1 + var_len] == '_'))
				var_len++;
		}
		var_name = ft_substr(p->str, p->i + 1, var_len);
		var_value = find_variable(var_name, data);
		free(var_name);
	}
	else
	{
		//printf("ENTREI NO SUB DO $? !!\n");
		var_value = ft_itoa(data->rcode);
		flag = 1;
		var_len++;
	}
	if (var_value)
	{
		new_str = ft_calloc((p->i + ft_strlen(var_value) + (ft_strlen(p->str) - p->i - var_len)), sizeof(p->str));
		ft_memcpy(new_str, p->str, p->i);
		ft_memcpy(new_str + p->i, var_value, ft_strlen(var_value));
		ft_memcpy(new_str + p->i + ft_strlen(var_value), p->str + p->i + var_len + 1, ft_strlen(p->str + p->i + var_len));
		//free(data->cmd_split[index]);
		free(data->full_cmd[p->index][p->index2]);
		//data->cmd_split[index] = new_str;
		data->full_cmd[p->index][p->index2] = new_str;
		p->str = new_str;
		p->i = p->i + ft_strlen(var_value) - 1;
		if (flag)
			free(var_value);
	}
	else
	{
		if (ft_strlen(p->str) - (var_len + 1) == 0)
		{
			new_str = ft_calloc(2 , sizeof(p->str));
			new_str[0] = -1;
			free(data->full_cmd[p->index][p->index2]);
			data->full_cmd[p->index][p->index2] = new_str;
			p->str = new_str;
		}
		else
		{
		//ft_printf("str eh: %s\n",p->str);
			new_str = ft_calloc((ft_strlen(p->str) - (var_len + 1)), sizeof(p->str));
			ft_memcpy(new_str, p->str, p->i);
			ft_memcpy(new_str + p->i, p->str + p->i + var_len + 1, ft_strlen(p->str + p->i + var_len));
			//free(data->cmd_split[index]);
			free(data->full_cmd[p->index][p->index2]);
			//data->cmd_split[index] = new_str;
			data->full_cmd[p->index][p->index2] = new_str;
			p->str = new_str;
			p->i--;
		}
	}
}

int	check_close_dq(char *str)//-> Move this to parser_utils.c and add in header
{
	int	i;

	i= 0;
	while (str[++i])
	{
		if (str[i] == '"')
			return (1);
	}
	return (0);
}

/*Split Arguments based on space, however no splitting spaces that are in quotes*/
void	parse_quote(char *str, t_data *data, int index, t_parser *p) 
{
	p->i = -1;
	p->str = str;
	while (p->str[++p->i])
	{
		if (p->str[p->i] == ' ')
			p->str[p->i] = 17;
		else if (p->str[p->i] == '\'')
		{
			p->j = p->i + 1;
			while (p->str[p->j] && p->str[p->j] != '\'')
				p->j++;
			if (p->str[p->j] == '\'')
				p->i = p->j;
		}
		else if (p->str[p->i] == '"')
		{
			p->j = p->i + 1;
			while (p->str[p->j] && p->str[p->j] != '"')
				p->j++;
			if (p->str[p->j] == '"')
				p->i = p->j;
		}
	}
	data->full_cmd[index] = ft_split(p->str, 17);
}

void	parse_var(char *str, t_data *data, t_parser *parse)
{
	int	flag;

	flag = 0;
	parse->str = str;
	parse->i = -1;
	while (parse->str[++parse->i])
	{
		if (parse->str[parse->i] == '"')
			flag = check_close_dq(parse->str + parse->i);
		if (parse->str[parse->i] == '\'' && parse->str[parse->i + 1] && flag == 0)
		{
			parse->j = parse->i + 1;
			while (parse->str[parse->j] && parse->str[parse->j] != '\'')
				parse->j++;
			if (parse->str[parse->j] == '\'')
				parse->i = parse->j;
			//flag = 0;
		}
		parse->j = 0;
		if (parse->str[parse->i] == '$' && (ft_isalnum(parse->str[parse->i + 1]) || \
	parse->str[parse->i + 1] == '_' || parse->str[parse->i + 1] == '?'))
		{
			replace_var(parse, data);
			flag = 0;
			//ft_printf("current str: %s\ni: %d\n",parse->str,parse->i);
		}
	}
}

char	*trim(char *str, t_data *data, t_parser *p)
{
	char	*new_str;

	if (ft_strlen(str) - 2 == 0)
	{
		new_str = ft_calloc(1, sizeof(str));
	}
	else
	{
		new_str = ft_calloc((ft_strlen(str) - 2), sizeof(str));
		if (p->i > 0)
			ft_memcpy(new_str, str, p->i);
		ft_memcpy(new_str + p->i, str + p->i + 1, p->j - (p->i + 1));
		ft_memcpy(new_str + p->i + (p->j - (p->i + 1)), str + p->j + 1, ft_strlen(str) - p->j);
		p->i = p->j - 2;
	}
	free(str);
	data->full_cmd[p->index][p->index2] = new_str;
	return (new_str);
}

char	**remove_empty(char **str,int i_to_remove, t_parser *p)
{
	int	count;
	char	**copy;

	count = 0;
	while(str[count])
		count++;
	copy = (char **)ft_calloc(count, sizeof(str[0]));
	if (copy == NULL)
		error_exit("Fail realoc remove empty var");
	if (count == 1)
		copy[0] = NULL;
	else
	{
		ft_memcpy(copy, str, i_to_remove * sizeof(str[0]));
		ft_memcpy(copy + i_to_remove, str + i_to_remove + 1, (count - i_to_remove - 1) * sizeof(str[0]));
	}
	free(str[i_to_remove]);
	free(str);
	return (copy);
}

void	trim_quote(char *str, t_data *data, t_parser *p)
{
	char	flag;

	flag = 0;
	p->i = -1;
	while (str[++p->i])
	{
		if (str[p->i] == -1 && str[p->i + 1] == 0) //--> Remove str da lista pq eh variavel vazia
		{
			data->full_cmd[p->index] = remove_empty(data->full_cmd[p->index], p->index2, p);
			p->index2--;
			break ;
			//function to remove
		}
		if (str[p->i] == '"' || str[p->i] == '\'')
		{
			/*if (str[p->i + 1] == -1)
				str[p->i +1] = ' '; TALVEZ NAO FACA SENTIDO*/ 
			p->j = p->i + 1;
			flag = str[p->i];
			while (str[p->j] && str[p->j] != flag)
				p->j++;
			if (str[p->j] == flag)
				str = trim(str, data, p);
		}
	}
}

void	parser(char *str, t_data *data)
{
	int	i;
	int	j;
	t_parser	parser;

	i = 0;
	data->cmd_split = split_pipes(str);
	while (data->cmd_split[i])
		i++;
	data->full_cmd = (char ***) ft_calloc(i+1, sizeof(char ***));
	data->cmd_redir = (char ***) ft_calloc(i, sizeof(char ***));
	parser.index = -1;
	while (data->cmd_split[++parser.index])
	{
		parse_quote(data->cmd_split[parser.index], data, parser.index, &parser);
		data->cmd_redir[parser.index] = (char **) ft_calloc(2, sizeof(char **));//-->Implementation in progress
		data->full_cmd[parser.index] = parse_redir(data->full_cmd[parser.index], data, parser.index); //-->Implementation in progres
		//j = -1;
		parser.index2 = -1;
		while (data->full_cmd[parser.index][++parser.index2])
		{
			parse_var(data->full_cmd[parser.index][parser.index2], data, &parser);
			trim_quote(data->full_cmd[parser.index][parser.index2], data, &parser);
			/*ft_printf("loop %i temos:\n",parser.index2);
			int k;
			for (k =0; data->full_cmd[parser.index][k]; k++)
				ft_printf("data->full_cmd[%i][%i] = %s\n", parser.index, k, data->full_cmd[parser.index][k]);
			ft_printf("FIM de rodada\n");*/
		}
	}
	//return (split_pipes(str));
}
