#include "ft_printf.h"

static char* conv_arg(va_list ap)
{
	return (va_arg(ap, char *));
}

static void build_conv(t_fmt *fmt, char **str)
{
	if (ft_strlen(*str) > (size_t)fmt->precision)
		(*str)[fmt->precision] = '\0';
	width(fmt, str);
}

int		conv_string(t_fmt *fmt, va_list ap)
{
	char	*ret;
	char	*arg;

	arg = conv_arg(ap);
	if (!arg)
	{
		ret = ft_strnew(6);
		ft_strcat(ret, "(null)");
	}
	else
		ret = ft_strdup(arg);
	build_conv(fmt, &ret);
	return (print(ret));
}