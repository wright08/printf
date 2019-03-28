#include "ft_printf.h"

static char* arg(va_list ap)
{
	return (va_arg(ap, char *));
}

static void build_conv(t_conv *conv)
{
	int len;

	len = ft_strlen(conv->str);
	if (len > conv->precision)
		conv->str[conv->precision] = '\0';
	if (len < conv->width && ft_strchr(conv->flags, '0') && !ft_strchr(conv->flags, '-'))
		zero(conv, conv->width - len);
	width(conv);
}

int		conv_str(t_conv *conv, va_list ap)
{
	conv->str = arg(ap);
	if (!conv->str)
		conv->str = ft_strdup("(null)");
	else
		conv->str = ft_strdup(conv->str);
	build_conv(conv);
	return (print(conv));
}