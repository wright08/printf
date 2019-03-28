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

void	precision(t_conv *conv)
{
	int		diff;
	int		neg;

	if (conv->precision == 0 && *conv->str == '0')
		*conv->str = '\0';
	neg = (*conv->str == '-');
	diff = conv->precision - (ft_strlen(conv->str) - neg);
	if (diff > 0)
	{
		zero(diff + neg, &conv->str);
		if (neg)
			*conv->str = '-';
	}
}

void	width(t_conv *conv)
{
	char	*fix;
	int		diff;
	int		len;

	len = ft_strlen(*conv->str);
	diff = conv->width - len;
	if (diff > 0)
	{
		fix = ft_strnew(conv->width);
		if (ft_strchr(conv->flags, '-'))
		{
			ft_strcat(fix, *conv->str);
			ft_memset(fix + len, ' ', diff);
		}
		else
		{
			ft_memset(fix, ' ', diff);
			ft_strcat(fix, *conv->str);
		}
		free_swap(conv->str, fix);
	}
}

int		print(t_conv *conv)
{
	int len;

	len = ft_putstr(conv->str);
	free(conv->str);
	return (len);
}