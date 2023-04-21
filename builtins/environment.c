
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//UTILS
void	free_char_array(char **array)
{
	int	i;
	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}

void	error_exit(char *str)
{
	perror(str);
	exit (1);
}
//END OF UTILS

///////// Funcoes do comando UNSET /////////
char	**unset(char **envpl, const char *str)
{
	int	count;
	int	i_to_remove;
	char	**copy;

	i_to_remove = -1;
	count = -1;
	//printf("Start UNSET!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	while (envpl[++count])
	{
		//printf("currentl envpl[%i] is: %s\n",count, envpl[count]);
		//printf("str e strlen: %s e %i\n",str, strlen(str));
		if(strncmp(envpl[count], str, strlen(str)) == 0)
		{
			//printf("strncmp foi igual a zero!\n");
			//printf("Temos envpl[%i] = %s\n", count, envpl[count]);
			//printf("str e strlen sao: %s e %i\n", str, strlen(str));
			if (envpl[count][strlen(str)] == '=')
			{
				i_to_remove = count;
			}
		}
	}
	//printf("i_to_remove = %i\n", i_to_remove);
	if (i_to_remove == -1)
		return (envpl);
	copy = (char **)malloc((count) * sizeof(envpl[0]));
	memset(copy, 0, count * sizeof(envpl[0]));
	if (copy == NULL)
		error_exit("unset env malloc");
	if (count == 1)
		copy[0] = NULL;
	else
	{
		memcpy(copy, envpl, i_to_remove * sizeof(envpl[0]));
		memcpy(copy + i_to_remove, envpl + i_to_remove + 1, (count - i_to_remove - 1) * sizeof(envpl[0]));
	}
	free(envpl[i_to_remove]);
	free(envpl);
	return (copy);
}

char	**prep_unset(char **envpl, const char **str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		envpl = unset(envpl, str[i]);
	}
	return (envpl);
}
///////// FIM das funcoes do comando UNSET /////////


///////// Funcoes do comando EXPORT /////////
// REPLACE MEMCPY WITH FT_MEMCPY!
char	**add_new_var(char **envpl, char *str)
{
	int	count;
	char	**copy;

	count = 0;
	while (envpl[count])
		count++;
	copy = (char **)malloc((count + 2) * sizeof(envpl[0]));
	if (copy == NULL)
		error_exit("new env malloc");
	memcpy(copy, envpl, count * sizeof(envpl[0]));
	copy[count] = strdup(str);
	copy[count + 1] = NULL;
	free(envpl);
	return (copy);
}

// REPLACE ISALPHA AND ISALNUM WITH 42 LIBFT!!!
int	check_export_str(const char *str)
{
	if (!str || !*str)
		return (1);
	if (!isalpha(*str) && *str != '_')
		return (1);
	str++;
	while (isalnum(*str) || *str == '_')
		str++;
	if (!*str)
		return (2);
	if (*str != '=')
		return (1);
	return (0);
}

int	check_exists(char **envpl, char *str)
{
	int	i;
	int	eq;

	eq = 0;
	while (str[eq] != '=' && str[eq] )
		eq++;
	if (!str[eq])
		return (0);
	i = - 1;
	while (envpl[++i])
	{
		//printf("\nOK lets check if exists!\n");
		//printf("envpl[%i] = %s\nstr = %s\neq is: %i\n", i, envpl[i], str, eq);
		if (strncmp(envpl[i], str, eq) == 0)
			return (eq);
		//printf("If we are still here then NOPE, no MATCH! FTS\n");
	}
	return (0);
}

char	**export(char **envpl, char **str)
{
	int	result;
	int	i;
	int	valid;
	char	*replace;

	result = 0;
	i = -1;
	while (str[++i])
	{
		valid = check_export_str(str[i]);
		//if (check_export_str(str[i]) == 1)
		if (valid == 1)
		{
			//Ajustar no tstruct pra deixar o return code como 1!
			result = 1;
			printf("export: `%s': not a valid identifier\n", str[i]);//transformar esse output em STDERR!!
		}
		else if (valid == 0)
		{
			//If ja existir:
				//chama funcao de unset!
			valid = check_exists(envpl, str[i]);
			if (valid > 0)
			{
				//printf("REPETIDO ENCONTRADO VER ACAO!!!!!!!\n");
				//printf("valid is: %i\n",valid);
				//printf("str[%i] = %s\n",i, str[i]);
				replace = calloc(valid , str[i][0]);
				strncpy(replace, str[i], valid);
				//printf("This is the replace str and size: %s size: %i\n", replace,strlen(replace));
				envpl = unset(envpl, replace);
				free(replace);
			}
			envpl = add_new_var(envpl, str[i]);
		}
	}
	return (envpl);
	/* Isso foi feito pois parecia que o export adicionava de tras pra frente;
	   Mas na real, nao parece ter logica na forma que eh feito...
	while (--i >= 0)
	{
		if (check_export_str(str[i]) == 0)
			//se já existir:
				//chamar funcao de unset!
			envpl = add_new_var(envpl, str[i]);
	}
	return (envpl);*/
}
///////// FIM das funcoes do comando EXPORT /////////

// FUNCTION THAT NEEDS TO BE CALLED AT THE START OF MINISHELL
// REPLACE STRDUP WITH FT_STRDUP!
char	**copy_env_var(char **envp)
{
	int	count;
	int	i;
	char	**copy;

	copy = envp -1;
	count = 0;
	while (*++copy != NULL)
		count++;
	copy = (char **)malloc((count + 1) * sizeof(envp[0]));
	if (copy == NULL)
		error_exit("env malloc");
	i = -1;
	while (++i < count)
	{
		copy[i] = strdup(envp[i]);
		if (copy[i] == NULL)
			error_exit("env strdup");
	}
	copy[count] = NULL;
	return (copy);
}

//ENV BUILTIN!
void	env(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		printf("%s\n", envp[i]);
}

int	main(int argc, char *argv[], char *envp[])
{
	char *myenv[] = {
        "variable1=value",
        "variable2=value",
        "VaRiAbLe3=value",
        NULL
    };
	char **env_copy;

	//env_copy = copy_env_var(envp);
	env_copy = copy_env_var(myenv);

	env(env_copy);


	printf("\nNow lets add: TXT=FTS\n");
	//env_copy = add_new_var(env_copy, "TXT=FTS");
	//env_copy = add_new_var(env_copy, "FTS=WHO/CARES?");
	env_copy = export(env_copy, (char *[]){"TXT=FTS", "1var=nope", "_var2=value", "variable", "*asd=algo muito legal", "var2=", "", NULL});

	printf("\nenv list:\n");
	env(env_copy);

	int i = 0;

	while (env_copy[i])
		i++;
	printf("\ntotal number of elements: %i\n",i);


	printf("\n\nLets play! Removing TXT!\n");
	env_copy = prep_unset(env_copy, (const char *[]){"variable1=", "var2", "_var", "variable1","VaRiAbLe3", "variable2", "_var2", NULL});
	env_copy = unset(env_copy, "TXT");
	//env_copy = unset(env_copy, "variable1");
	//env_copy = unset(env_copy, "variable2");
	//env_copy = unset(env_copy, "var2");
	//env_copy = unset(env_copy, "_var2");
	//env_copy = unset(env_copy, "VaRiAbLe3");
	//env_copy = unset(env_copy, "TXT");
	env(env_copy);
	i = 0;


	for (i =0; env_copy[i]; i++)
		;
	printf("\ntotal number of elements: %i\n",i);

	printf("\nRecreating!This are the env now:\n");
	env_copy = export(env_copy, (char *[]){"TXT=FTS", "var=nope", "_var2=value", "var1=hope", "var3=algo muito legal", "var4=dope", "var5=pope", NULL});
	env(env_copy);

	printf ("\n\n\nadding new values for var, var1 var4 and var5\n");
	env_copy = export(env_copy, (char *[]){"var5=roma", "var=toma", "var4=soma", "var1=poma", NULL});
	env(env_copy);


	printf("\n\nMorri?\n");
	free_char_array(env_copy);
	return 0;

	/*const char *test_cases[] = {
        "1variable=value",
        "_variable=value",
        "VaRiAbLe_123=value",
        "variable",
	"*asdad =\'algo muito legal\'",
	"var2="
        "",
        NULL
    };

    for (const char **test = test_cases; *test != NULL; test++) {
        if (check_export_str(*test) == 0) {
            printf("OK: %s\n", *test);
        } else {
            printf("Not OK: %s\n", *test);
        }
    }

    return 0;*/
}
