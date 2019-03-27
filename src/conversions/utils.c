#include "ft_printf.h"
#include <stdlib.h>
#include <unistd.h>

//The hard problem you're having right now of propogating the negative
//could be solved by having a t_conv struct that keeps track of its sign.

void	zero(int diff, char **str)
{
	char 	*fix;
	int		len;

	len = ft_strlen(*str);
	fix = ft_strnew(len + diff);
	ft_memset(fix, '0', diff);
	ft_strcat(fix, *str);
	free_swap(str, fix);
}

void	precision(t_fmt *fmt, char **str)
{
	int		diff;
	int		neg;

	if (fmt->precision == 0 && **str == '0')
		**str = '\0';
	neg = (**str == '-');
	diff = fmt->precision - (ft_strlen(*str) - neg);
	if (diff > 0)
	{
		zero(diff + neg, str);
		if (neg)
			**str = '-';
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
		free_swap(str, fix);
	}
}

int		print(char *str)
{
	int len;

	len = ft_putstr(str);
	free(str);
	return (len);
}