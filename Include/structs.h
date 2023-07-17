/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:21:06 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/07/16 23:41:02 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include "./minishell.h"

/*Struct for PARSER*/
typedef struct s_parser
{
	int		i;
	int		j;
	int		index;
	int		index2;
	int		redir_type;
	char	*str;
}	t_parser;

/*General struct (GLOBAL)*/
typedef struct s_data
{
	char	*line;
	char	linetyped;
	char	**envp;
	char	**cmd_split;
	char	***full_cmd;
	int		flag_fullcmd;
	int		builtin;
	int		rcode;
	int		ctrl_c;
	int		here_doc;
	int		is_here_doc;
	char	***cmd_redir;
	int		redir_error;
	int		qtd_cmd;
	int		saved_stdin;
	int		saved_stdout;
	int		*pid;
}	t_data;

extern t_data	g_var;

/*Struct to deal with pipes*/
typedef struct t_pipe
{
	char	**argv;
	char	**cmd_args;
	char	*fpath;
	int		*pid;
	int		*pipes;
	int		builtin;
	int		flag;
	int		qtd_cmd;
	int		cmd_n;
	int		pipe_i;
}	t_pipe;

/*Struct for variable substitution*/
typedef struct s_var
{
	int		len;
	char	*name;
	char	*value;
	char	*n_str;
}	t_var;

#endif
