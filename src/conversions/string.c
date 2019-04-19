#include "ft_printf.h"

static char* arg(va_list ap)
{
	return (va_arg(ap, char *));
}

static void build_conv(t_conv *conv)
{
	if (!conv->str)
		conv->str = ft_strdup("(null)");
	else
		conv->str = ft_strdup(conv->str);
	conv->len = ft_strlen(conv->str);
	if (conv->precision >= 0 && conv->len > conv->precision)
	{
		conv->str[conv->precision] = '\0';
		conv->len = conv->precision;
	}
	width(conv);
}

int		conv_str(t_conv *conv, va_list ap)
{
	conv->str = arg(ap);
	build_conv(conv);
	return (print(conv));
}