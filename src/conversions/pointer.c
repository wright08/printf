#include "ft_printf.h"
#include <stdarg.h>

int     conv_ptr(t_conv *conv, va_list ap)
{
    conv->str = ft_ulltoa_base(va_arg(ap, long), 16);
    free_swap(conv, ft_strjoin("0x", conv->str), STR);
    conv->len = ft_strlen(conv->str);
    width(conv);
    return (print(conv));
}