
#include "../Include/minishell.h"

///////// Funcoes do comando UNSET /////////
static int	check_unset_str(const char *str)
{
	if (!str || !*str)
		return (1);
	if (!ft_isalpha(*str) && *str != '_')
		return (1);
	str++;
	while (ft_isalnum(*str) || *str == '_')
		str++;
	if (*str == '=')
		return (1);
	return (0);
}

char	**unset(char **envpl, const char *str, t_data *data)
{
	int	count;
	int	i_to_remove;
	char	**copy;

	i_to_remove = -1;
	count = -1;
	if (check_unset_str(str))
	{
		data->rcode = 1;
		printf("unset: `%s': not a valid identifier\n", str);
	}
	//printf("Start UNSET!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	while (envpl[++count])
	{
		//printf("currentl envpl[%i] is: %s\n",count, envpl[count]);
		//printf("str e strlen: %s e %i\n",str, strlen(str));
		if(ft_strncmp(envpl[count], str, strlen(str)) == 0)
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
	ft_memset(copy, 0, count * sizeof(envpl[0]));
	if (copy == NULL)
		error_exit("unset env malloc");
	if (count == 1)
		copy[0] = NULL;
	else
	{
		ft_memcpy(copy, envpl, i_to_remove * sizeof(envpl[0]));
		ft_memcpy(copy + i_to_remove, envpl + i_to_remove + 1, (count - i_to_remove - 1) * sizeof(envpl[0]));
	}
	free(envpl[i_to_remove]);
	free(envpl);
	return (copy);
}

char	**prep_unset(char **envpl, const char **str, t_data *data)
{
	int	i;

	i = -1;
	while (str[++i])
		envpl = unset(envpl, str[i], data);
	return (envpl);
}
///////// FIM das funcoes do comando UNSET /////////
