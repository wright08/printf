#include "ft_printf.h"
#include <stdlib.h>
#include <stdarg.h>

static unsigned long long arg(t_conv *conv, va_list ap)
{
    if (ft_strchr(conv->len_mod, 'z'))
        return ((size_t)va_arg(ap, size_t));
    if (ft_strchr(conv->len_mod, 'j'))
        return ((uintmax_t)va_arg(ap, uintmax_t));
    if (ft_strequ(conv->len_mod, "l"))
        return (va_arg(ap, unsigned long));
    if (ft_strequ(conv->len_mod, "ll"))
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
    else if (!*conv->str || conv->type == 10)
        return ;
    else if (conv->type == 16)
        fix = ft_strjoin("0x", conv->str);
    else
        fix = ft_strjoin("0X", conv->str);
    free_swap(conv, fix);
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
        free_swap(conv, copy);
		build_num(conv);
    }
	else
		free(copy);
    width(conv);
}

int     conv_uint(t_conv *conv, va_list ap)
{
    if (conv->type == 'o')
		conv->type = 8;
    else if (conv->type == 'u')
		conv->type = 10;
    else if (conv->type == 'x')
		conv->type = 16;
    else
        conv->type = 17;
    conv->str = ft_ulltoa_base(arg(conv, ap), conv->type);
    build_conv(conv);
    return (print(conv));
}