#include "ft_printf.h"

static char* conv_arg(va_list ap)
{
	return (va_arg(ap, char *));
}

static void build_conv(t_fmt *fmt, char **str)
{
	int len;

	len = ft_strlen(*str);
	if (len > fmt->precision)
		(*str)[fmt->precision] = '\0';
	if (len < fmt->width && ft_strchr(fmt->flags, '0') && !ft_strchr(fmt->flags, '-'))
		zero(fmt->width - len, str);
	width(fmt, str);
}

int		conv_string(t_fmt *fmt, va_list ap)
{
	char	*ret;
	char	*arg;

	arg = conv_arg(ap);
	if (!arg)
		ret = ft_strdup("(null)");
	else
		ret = ft_strdup(arg);
	build_conv(fmt, &ret);
	return (print(ret));
}