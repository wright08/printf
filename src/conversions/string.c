#include "ft_printf.h"

static char* conv_arg(va_list ap)
{
	return (va_arg(ap, char *));
}

static void build_conv(t_fmt *fmt, char **str)
{
	width(fmt, str);
}

int		conv_string(t_fmt *fmt, va_list ap)
{
	char	*ret;

	ret = conv_arg(ap);
	build_conv(fmt, &ret);
	return (print(ret));
}