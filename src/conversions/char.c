#include "ft_printf.h"
#include <stdlib.h>

static int	conv_arg(va_list ap)
{
	return ((unsigned char)va_arg(ap, int));
}

int			conv_char(t_conv *conv, va_list ap)
{
	char *fix;
	char pad;

	if (conv->width > 1)
	{
		pad = (ft_strchr(conv->flags, '0') && !ft_strchr(conv->flags, '-')) ? '0' : ' ';
		ft_memset((fix = ft_strnew(conv->width - 1)), pad, conv->width - 1);
		if (ft_strchr(conv->flags, '-'))
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
		return (conv->width);
	}
	ft_putchar(conv_arg(ap));
	return (1);
}