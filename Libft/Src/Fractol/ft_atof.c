#include "libft.h"

double	ft_atof(const char *str)
{
	double	ret;
	int		p_vir;
	int		i;
	int		temp;

	ret = 0.0;
	p_vir = 0;
	i = 0;
	while ((temp = str[i]) != '\0' && ft_isdigit(str[i++]))
		ret = ret * 10 + (temp - 48);
	if (temp == '.')
		{
			while ((temp = str[i]) != 0 && ft_isdigit(str[i++]))
			{
				ret = ret * 10 + (temp - 48);
				p_vir++;
			}
		}
	while (p_vir > 0)
	{
		ret /= 10;
		p_vir--;
	}
	return (ret);
}