#include "ft_printf.h"
#include <stdlib.h>
#include <unistd.h>

int needs_zero_pad(t_conv *conv)
{
	return (conv->len < conv->width &&
			has(conv->flags, "0") && !has(conv->flags, "-"));
}

//Precision zero
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
	}
}
void	precision(t_conv *conv)
{
	if (conv->precision == 0 && *conv->str == '0')
		*conv->str = '\0';
	zero(conv);
}

void	width(t_conv *conv)
{
	char	*fix;
	int		diff;
	int		len;

	len = ft_strlen(conv->str);
	diff = conv->width - len;
	if (diff > 0)
	{
		fix = ft_strnew(conv->width);
		if (ft_strchr(conv->flags, '-'))
		{
			ft_strcat(fix, conv->str);
			ft_memset(fix + len, ' ', diff);
		}
		else
		{
			ft_memset(fix, ' ', diff);
			ft_strcat(fix, conv->str);
		}
		free_swap(conv, fix);
	}
}

int		print(t_conv *conv)
{
	int len;

	len = ft_putstr(conv->str);
	free(conv->str);
	return (len);
}