#include "ft_printf.h"

static char* conv_arg(va_list ap)
{
	return (va_arg(ap, char *));
}

int		conv_string(t_fmt *fmt, va_list ap)
{
	return (print(fmt, conv_arg(ap)));
}