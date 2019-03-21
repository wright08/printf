#include "ft_printf.h"
#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>
void	precision(t_fmt *fmt, char **str)
{
	char	*fix;
	int		diff;
	int		neg;

	if (fmt->precision == 0 && **str == '0')
		**str = '\0';
	neg = (**str == '-');
	diff = fmt->precision - (ft_strlen(*str) - neg);
	if (diff > 0)
	{
		fix = ft_strnew(fmt->precision + neg);
		ft_memset(fix + neg, '0', diff);
		if (neg)
			*fix = '-';
		ft_strcat(fix, *str + neg);
		free(*str);
		*str = fix;
	}
}

void	width(t_fmt *fmt, char **str)
{
	char	*fix;
	int		diff;
	int		len;

	len = ft_strlen(*str);
	diff = fmt->width - len;
	if (diff > 0)
	{
		fix = ft_strnew(fmt->width);
		if (ft_strchr(fmt->flags, '-'))
		{
			ft_strcat(fix, *str);
			ft_memset(fix + len, ' ', diff);
		}
		else
		{
			ft_memset(fix, ' ', diff);
			ft_strcat(fix, *str);
		}
		free(*str);
		*str = fix;
	}
}

int		print(char *str)
{
	int len;

	len = ft_strlen(str);
	write(1, str, len);
	free(str);
	return (len);
}