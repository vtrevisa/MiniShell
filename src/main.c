/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:03:52 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/05/07 02:56:25 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	show_display(void)
{
	int	fd;
	char *line;

	fd = open ("./src/display", O_RDONLY);
	while (fd != -1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		ft_printf("%s", line);
		free(line);
	}
	return (fd);
}

void	free_all(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

int	prompt_loop(t_data *data)
{
	int		status;

	status = 0;
	while (1)
	{
		printf("> ");
		read_line(data);
		if (data->linetyped == 1)
		{
			if (ft_strnstr("exit", data->line, 4) != 0)
			{
				free(data->line);
				free(data->cmd);
				free_all(data->envp);
				return (EXIT_CODE);
			}
			//1- Remover espacos do inicio;
			//2- Fazer tratamento das aspas e Variaveis $ --> Mover o 3 para esse ponto?
			//data->cmd_split = split_pipes(data->line);
			parser(data->line, data);
			free_char_array(data->cmd_split);
			int i;
			if (data->full_cmd)
			{
				for (i=0; data->full_cmd[i]; i++)
				{
					int j;
					for (j=0; data->full_cmd[i][j]; j++)
						printf("str[%d][%d] = %s\n",i,j,data->full_cmd[i][j]);
				}
			}
			for (i = 0; data->full_cmd[i]; i++)
				free_char_array(data->full_cmd[i]);
			free(data->full_cmd);
			/*if (data->cmd_split)
			{
				int i;
				for (i=0; data->cmd_split[i];i++)
					printf("str[%d] = %s\n", i, data->cmd_split[i]);
				free_char_array(data->cmd_split);
			}*/
			//3- Verificar se ha pipes (em locais que devem ser considerados)
			//4.1 -> Caso nao, (checar > e < )ver se e bultins se for executar senao ir pro piper
			//4.2 -> Caso sim, ir pro piper
		
			//Paso 3:
			/*if (is_there_pipes(data->line) == 0)
			{
				//4.1
				data->cmd_split = ft_split(data->line, ' ');
				//If iniciar com > ou <: fazer um cmd_split+1;
				data->builtin = builtin_checker(data->cmd_split[0]);
				if (data->builtin)
				{
					builtin_exec_main(data);
				}
				else
					piper(data);
				free_char_array(data->cmd_split);
				//int i;
				//free(data->cmd_split[i]);
				//free(data->cmd_split);
			}
			else
			{
				//4.2
				piper(data);
			}*/

			/*if (ft_strnstr("exit", data->line, 4) != 0)
			{
				free(data->line);
				free(data->cmd);
				free_all(data->envp);
				return (EXIT_CODE);
			}
			else if(ft_strnstr("cd", data->line, 2) != 0)
			{
				printf("CHANGE DIR HERE!\n");
				data->cmd = treat_str(data->line);
				change_directory(data->cmd[1], data->envp);
				free(data->cmd);
			}
			else
				piper(data);
				//ft_printf(">%s\n", data->line); //teste*/
			free(data->line);

		}
		/* write(1, "ok\n", 3); */
		//lexer(data);
		/* status = execute(data); */
		else
			printf("");
	}
}

int	main(int argc, char **argv, char **envp)
{	
	// Load config files, if any.
	t_data	data;
	
	show_display();
	init_data(&data, envp);
	// Run command loop.
	prompt_loop(&data);

	// Perform any shutdown/cleanup.
	free (data.user);
	free_all (data.paths);

	return (0);
}
