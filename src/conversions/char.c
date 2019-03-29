#include "ft_printf.h"
#include <stdlib.h>

static int	arg(va_list ap)
{
	return ((unsigned char)va_arg(ap, int));
}

static int needs_zero_pad(t_conv *conv)
{
	return (has(conv->flags, "0") && !has(conv->flags, "-"));
}

int			conv_char(t_conv *conv, va_list ap)
{
	char *fix;
	char pad;

	if (conv->width > 1)
	{
		fix = ft_strnew(conv->width - 1);
		pad = needs_zero_pad(conv) ? '0' : ' ';
		ft_memset(fix, pad, conv->width - 1);
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