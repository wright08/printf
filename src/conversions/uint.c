#include "ft_printf.h"
#include <stdarg.h>

static unsigned long long conv_arg(t_fmt *fmt, va_list ap)
{
    if (ft_strequ(fmt->len, "l"))
        return (va_arg(ap, unsigned long));
    else if (ft_streque(fmt->len, "ll"))
        return (va_arg(ap, unsigned long long));
    return (va_arg(ap, unsigned int));
}

static void alternate(t_fmt *fmt, char **str)
{
    char *fix;
    char *scan;

    if (!ft_strchr(fmt->flags, '#') || (**str == '0' && fmt->precision < 0))
        return ;
    if (fmt->conv == 8)
        fix = ft_strjoin("0", *str);
    else if (fmt->conv == 10)
        fix = ft_strdup(*str);
    else if (fmt->conv == 16)
        fix = ft_strjoin("0x", *str);
    else if (fmt->conv == 17)
        fix = ft_strjoin("0X", *str);
    free(*str);
    *str = fix;
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
    precision(fmt, &ret);
    group(fmt, &ret);
    alternate(fmt, &ret);
    width(fmt, &ret);
    len = print(fmt, ret);
    free(ret);
    return (len);
}

// build number string:
    // precision
    // group flag
    // alternate form
    // if not wide enough, rerun with bigger precision
// 