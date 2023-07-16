/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:21:06 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/07/16 04:07:19 by romachad         ###   ########.fr       */
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
	//char	*tmp;
	//char	**line_splitted;
	//int		file_fds_index;
	//int		*file_fds;
	//int		count_cmd;
	//int		count_pipe;
	//char	*cmd_path;
	//int		*lexed_class;
	//char	**paths;
	//char	**cmd;
	//char	*user;
	char	**envp;
	//int		fd[2]; --> sera?
	//int		fd_in;
	//int		fd_out;
	//int		pipes;
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
	//int		saved_stderr;
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
