#include "ft_printf.h"
#include "int_utils.h"
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>

static long long conv_arg(t_fmt *fmt, va_list ap)
{
	if (ft_strchr(fmt->len, 'z'))
		return ((ssize_t)va_arg(ap, ssize_t));
	if (ft_strchr(fmt->len, 'j'))
		return ((intmax_t)va_arg(ap, intmax_t));
	if (ft_strequ(fmt->len, "hh"))
		return ((char)va_arg(ap, int));
	if (ft_strequ(fmt->len, "h"))
		return ((short)va_arg(ap, int));
	if (ft_strequ(fmt->len, "l"))
		return ((long)va_arg(ap, long));
	if (ft_strequ(fmt->len, "ll"))
		return (va_arg(ap, long long));
	return ((int)va_arg(ap, int));
}

static int build_num(t_fmt *fmt, char **str)
{
	precision(fmt, str);
	leader(fmt, str);
	return (ft_strlen(*str));
}

static void build_conv(t_fmt *fmt, char **str)
{
	char *copy;
	int len;

	copy = ft_strdup(*str);
	len = build_num(fmt, str);
	if (len < fmt->width && ft_strchr(fmt->flags, '0') && !ft_strchr(fmt->flags, '-'))
	{
		fmt->precision = fmt->width - len + ft_strlen(copy);
		build_num(fmt, &copy);
		free_swap(str, copy);
	}
	else
		free(copy);
	width(fmt, str);
}

int conv_int(t_fmt *fmt, va_list ap)
{
	char *ret;

	ret = ft_lltoa(conv_arg(fmt, ap));
	build_conv(fmt, &ret);
	return (print(ret));
}