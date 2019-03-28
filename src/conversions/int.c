#include "ft_printf.h"
#include "int_utils.h"
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>

static long long conv_arg(t_conv *conv, va_list ap)
{
	if (ft_strchr(conv->len, 'z'))
		return ((ssize_t)va_arg(ap, ssize_t));
	if (ft_strchr(conv->len, 'j'))
		return ((intmax_t)va_arg(ap, intmax_t));
	if (ft_strequ(conv->len, "hh"))
		return ((char)va_arg(ap, int));
	if (ft_strequ(conv->len, "h"))
		return ((short)va_arg(ap, int));
	if (ft_strequ(conv->len, "l"))
		return ((long)va_arg(ap, long));
	if (ft_strequ(conv->len, "ll"))
		return (va_arg(ap, long long));
	return ((int)va_arg(ap, int));
}

static int build_num(t_conv *conv)
{
	precision(conv);
	leader(conv);
	return (ft_strlen(conv->str));
}

static void build_conv(t_conv *conv)
{
	char	*copy;
	int		len;

	copy = ft_strdup(conv->str);
	len = build_num(conv);
	if (len < conv->width && ft_strchr(conv->flags, '0') && !ft_strchr(conv->flags, '-'))
	{
		conv->precision = conv->width - len + ft_strlen(copy);
		build_num(conv, &copy);
		free_swap(str, copy);
	}
	else
		free(copy);
	width(conv);
}

int conv_int(t_conv *conv, va_list ap)
{
	conv->str = ft_lltoa(conv_arg(conv, ap));
	build_conv(conv);
	return (print(conv->str));
}