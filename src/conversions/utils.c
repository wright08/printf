#include "ft_printf.h"
#include <stdlib.h>
#include <unistd.h>

int needs_zero_pad(t_conv *conv)
{
	return (conv->len < conv->width && conv->precision == -1 &&
			has(conv->flags, "0") && !has(conv->flags, "-"));
}

void	zero(t_conv *conv)
{
	char	*fix;
	int		diff;

	diff = conv->precision - (conv->len - conv->neg);
	if (diff > 0)
	{
		fix = ft_strnew(conv->len + diff + conv->neg);
		if (conv->neg)
			*fix = '-';
		ft_memset(fix + conv->neg, '0', diff);
		ft_strcat(fix, conv->str + conv->neg);
		free_swap(conv, fix);
		conv->len += diff;
	}
}

void	width(t_conv *conv)
{
	char	*fix;
	int		diff;

	diff = conv->width - conv->len;
	if (diff > 0)
	{
		fix = ft_strnew(conv->width);
		if (ft_strchr(conv->flags, '-'))
		{
			ft_strcat(fix, conv->str);
			ft_memset(fix + conv->len, ' ', diff);
		}
		else
		{
			ft_memset(fix, ' ', diff);
			ft_strcat(fix, conv->str);
		}
		free_swap(conv, fix);
		conv->len += diff;
	}
}

int		print(t_conv *conv)
{
	int		printed;

	printed = ft_putstr(conv->str);
	free(conv->str);
	return (printed);
}