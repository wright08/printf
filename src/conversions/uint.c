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

static void alternate(t_conv *conv)
{
    char    *fix;

    if (!ft_strchr(conv->flags, '#') || (*conv->str == '0' && conv->precision < 0))
        return ;
    if (conv->type == 8)
        fix = ft_strjoin("0", conv->str);
    else if (!**str || conv->type == 10)
        return ;
    else if (conv->type == 16)
        fix = ft_strjoin("0x", conv->str);
    else
        fix = ft_strjoin("0X", conv->str);
    free_swap(&conv->str, fix);
}

static int build_num(t_conv *conv)
{
    precision(conv);
    alternate(conv);
    return (ft_strlen(conv->str));
}

static void build_conv(t_conv *conv)
{
    char    *copy;
    int     len;

    copy = ft_strdup(conv->str);
	len = build_num(conv);
	if (len < conv->width && ft_strchr(conv->flags, '0') && !ft_strchr(conv->flags, '-'))
	{
		conv->precision = conv->width - len + ft_strlen(copy);
		build_num(conv, &copy);
        free_swap(&conv->str, copy);
    }
	else
		free(copy);
    width(conv);
}

int     conv_uint(t_conv *conv, va_list ap)
{
    int base;

    if (conv->type == 'o')
        base = 8;
    else if (conv->type == 'u')
        base = 10;
    else if (conv->type == 'x')
        base = 16;
    else
        base = 17;
    ret = ft_ulltoa_base(conv_arg(conv->fmt, ap), base);
    build_conv(conv);
    return (print(conv->str));
}