#include "ft_printf.h"
#include <stdlib.h>

static int	conv_arg(va_list ap)
{
	return ((unsigned char)va_arg(ap, int));
}

int			conv_char(t_fmt *fmt, va_list ap)
{
	char *fix;
	char pad;

	if (fmt->width > 1)
	{
		pad = (ft_strchr(fmt->flags, '0') && !ft_strchr(fmt->flags, '-')) ? '0' : ' ';
		ft_memset((fix = ft_strnew(fmt->width - 1)), pad, fmt->width - 1);
		if (ft_strchr(fmt->flags, '-'))
		{
			ft_putchar(conv_arg(ap));
			ft_putstr(fix);
		}
		else
		{
			ft_putstr(fix);
			ft_putchar(conv_arg(ap));
		}
		free(fix);
		return (fmt->width);
	}
	ft_putchar(conv_arg(ap));
	return (1);
}