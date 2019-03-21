#include "ft_printf.h"
#include <stdlib.h>
#include <stdarg.h>

static unsigned long long conv_arg(t_fmt *fmt, va_list ap)
{
    if (ft_strchr(fmt->len, 'z'))
        return ((size_t)va_arg(ap, size_t));
    if (ft_strchr(fmt->len, 'j'))
        return ((uintmax_t)va_arg(ap, uintmax_t));
    if (ft_strequ(fmt->len, "l"))
        return (va_arg(ap, unsigned long));
    if (ft_strequ(fmt->len, "ll"))
        return (va_arg(ap, unsigned long long));
    return (va_arg(ap, unsigned int));
}

static void alternate(t_fmt *fmt, char **str)
{
    char    *fix;

    if (!ft_strchr(fmt->flags, '#') || (**str == '0' && fmt->precision < 0))
        return ;
    if (fmt->conv == 8)
        fix = ft_strjoin("0", *str);
    else if (!**str || fmt->conv == 10)
        return ;
    else if (fmt->conv == 16)
        fix = ft_strjoin("0x", *str);
    else
        fix = ft_strjoin("0X", *str);
    free(*str);
    *str = fix;
}

static void build_num(t_fmt *fmt, char **str)
{
    precision(fmt, str);
    alternate(fmt, str);
}

static void build_conv(t_fmt *fmt, char **str)
{
    char    *copy;
    int     len;

    copy = ft_strdup(*str);
	build_num(fmt, str);
    len = (int)ft_strlen(*str);
	if (len < fmt->width && ft_strchr(fmt->flags, '0') && !ft_strchr(fmt->flags, '-'))
	{
		fmt->precision = fmt->width - len + ft_strlen(copy);
		build_num(fmt, &copy);
        free(*str);
        *str = copy;
    }
	else
		free(copy);
    width(fmt, str);
}

int     conv_uint(t_fmt *fmt, va_list ap)
{
    char    *ret;

    if (fmt->conv == 'o')
        fmt->conv = 8;
    else if (fmt->conv == 'u')
        fmt->conv = 10;
    else if (fmt->conv == 'x')
        fmt->conv = 16;
    else if (fmt->conv == 'X')
        fmt->conv = 17;
    ret = ft_ulltoa_base(conv_arg(fmt, ap), fmt->conv);
    build_conv(fmt, &ret);
    return (print(ret));
}