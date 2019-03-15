#include "ft_printf.h"
#include <stdlib.h>
#include <stdarg.h>

static unsigned long long conv_arg(t_fmt *fmt, va_list ap)
{
    if (ft_strequ(fmt->len, "l"))
        return (va_arg(ap, unsigned long));
    else if (ft_strequ(fmt->len, "ll"))
        return (va_arg(ap, unsigned long long));
    return (va_arg(ap, unsigned int));
}

static void alternate(t_fmt *fmt, char **str)
{
    char *fix;

    if (!ft_strchr(fmt->flags, '#') || (**str == '0' && fmt->precision < 0))
        return ;
    if (fmt->conv == 8)
        fix = ft_strjoin("0", *str);
    else if (fmt->conv == 10)
        fix = ft_strdup(*str);
    else if (fmt->conv == 16)
        fix = ft_strjoin("0x", *str);
    else
        fix = ft_strjoin("0X", *str);
    free(*str);
    *str = fix;
}

static void build_conv(t_fmt *fmt, char **str)
{
    int len;
    char *copy;

    len = (int)ft_strlen(*str);
    copy = ft_strdup(*str);
    precision(fmt, str);
    group(fmt, str);
    alternate(fmt, str);
	if (len < fmt->width && ft_strchr(fmt->flags, '0') && !ft_strchr(fmt->flags, '-'))
	{
		fmt->precision = fmt->width - len;
        precision(fmt, &copy);
        group(fmt, &copy);
        alternate(fmt, &copy);
        free(*str);
        *str = copy;
    }
    else
        free(copy);
    width(fmt, str);
}

int     conv_uint(t_fmt *fmt, va_list ap)
{
    char *ret;
    int len;

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
    len = print(fmt, ret);
    free(ret);
    return (len);
}