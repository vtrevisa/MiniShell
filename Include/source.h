/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:21:06 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/07/14 20:26:48 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOURCE_H
# define SOURCE_H
/*TEST APAGAR*/
void	show_data(t_data *data);
/*--------BUILTINS---------*/
/*BUILTIN CHECKER UTILS*/
int		if_bt4(t_data *data, int flag, t_pipe *args);
int		if_bt5(t_data *data, int flag, t_pipe *args);
int		if_bt6(t_data *data, int flag);
/*BUILTIN CHECKER*/
int		builtin_exec_main(t_data *data);
int		builtin_checker(char *str);
int		builtin_exec_pipe(t_pipe *args, t_data *data);
/*CHANGE DIR*/
int		change_directory(char **paths, char **envp);
/*ECHO*/
int		echo_n(char **text);
/*ENV*/
void	env(char **envp);
/*EXIT_ERROR_CODES*/
int		illegal_number(void);
int		too_many_args(void);
int		big_number(char *str);
/*EXIT*/
void	exit_shell(t_data *data);
void	exit_child(t_data *data, int code);
/*EXPORT UTILS*/
void	export_empty(char **envp);
/*EXPORT*/
char	**export(char **envp, char **str, t_data *data);
/*PWD*/
int		pwd(void);
/*UNSET*/
char	**unset(char **envpl, const char *str, t_data *data);
char	**prep_unset(char **envpl, const char **str, t_data *data);

/*--------EXEC---------*/
/*CHECK PERM*/
int		check_perm_cmd(t_pipe *args, t_data *data);
/*CHILD UTILS*/
int		if_cmdredir_childstart_case1(int *fd, t_data *data, t_pipe *args);
int		if_cmdredir_childstart_case2(int *fd, t_data *data, t_pipe *args);
int		if_cmdredir_childmiddle_case1(int *fd, t_data *data, t_pipe *args);
int		if_cmdredir_childend_case1(int *fd, t_data *data, t_pipe *args);
int		fd_error(t_data *data, t_pipe *args);
/*CHILD UTILS 2*/
int		if_cmd_redir(t_data *data, t_pipe *args, int *fd);
void	call_exec(t_data *data, t_pipe *args);
/*CHILD*/
int		child_prog(t_pipe *args, t_data *data);
/*PATH SEARCH*/
char	*path_search(char *envp[], const char *cmd, t_data *data);
/*PIPE INPUT UTILS*/
void	free_args(t_pipe *args);
void	close_pipes(t_pipe *args, t_data *data);
int		create_pipes(t_pipe *args, t_data *data);
/*PIPE INPUT*/
void	piper(t_data *data);

/*--------PARSER-LEXER---------*/
/*ARGS STR TREATMENT*/
char	**treat_str(char *str);
/*PARSE REDIR UTILS*/
void	trim_quote_redir(t_parser *p);
void	parse_var_redir(t_data *data, t_parser *parser);
char	*parse_var_heredoc(char *str, t_data *data);
/*PARSE REDIR UTILS 2*/
char	**remove_redir(char **parsed, t_parser *p, char *redir_type);
void	create_redir_str(char **parsed, t_parser *p, t_data *data, \
	char *redir_type);
int		check_outfile(char *outfile, char mode);
int		check_infile(char *infile);
/*PARSER REDIR*/
char	**parse_redir(char **parsed, t_data *data, int index);
/*PARSER UTILS*/
char	*trim(char *str, t_data *data, t_parser *p);
void	trim_quote(char *str, t_data *data, t_parser *p);
char	**split_pipes(char *str);
char	*find_variable(char *var, t_data *data);
/*PARSER UTILS 2*/
int		check_close_dq(char *str);
void	parse_quote(char *str, t_data *data, int index, t_parser *p);
/*PARSER*/
void	parser(char *str, t_data *data);
/*REPLACE VAR REDIR*/
void	replace_var_redir(t_parser *p, t_data *data);
/*REPLACE VAR*/
void	replace_var(t_parser *p, t_data *data);

/*----SYSTEM-----*/
/*HERE DOC*/
char	*here_doc(char *str);
/*--INIT--*/
void	init_data(t_data *data, char **envp);
/*MAIN_UTILS*/
int		if_data_cmd_redir0(t_data *data, int *fd, int flag);
int		if_data_cmd_redir1(t_data *data, int *fd, int flag);
void	free_full_cmd(t_data *data);
void	if_ctrl_c1(t_data *data);
/*MAIN UTILS 2*/
void	show_display(void);
void	free_all(char **str);
void	free_char_array(char **array);
void	error_exit(char *str);
/*READ LINE*/
void	print_user_dir(t_data *data);
void	read_line(t_data *data);
/*SIGNALS*/
void	sigint_handler(int sig);

#endif
