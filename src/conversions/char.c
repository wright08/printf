#include "ft_printf.h"
#include <stdlib.h>

static int	arg(va_list ap)
{
	return ((unsigned char)va_arg(ap, int));
}

int			conv_char(t_conv *conv, va_list ap)
{
	char *fix;
	char pad;

	if (conv->width > 1)
	{
		pad = (has(conv->flags, "0") && !has(conv->flags, "-")) ? '0' : ' ';
		ft_memset((fix = ft_strnew(conv->width - 1)), pad, conv->width - 1);
		if (has(conv->flags, "-"))
		{
			ft_putchar(arg(ap));
			ft_putstr(fix);
		}
		else
		{
			ft_putstr(fix);
			ft_putchar(arg(ap));
		}
		free(fix);
		return (conv->width);
	}
	ft_putchar(arg(ap));
	return (1);
}