#include "ft_printf.h"
#include <stdarg.h>

int     conv_ptr(t_conv *conv, va_list ap)
{
    ft_memset(conv->flags, '#', 6);
    ft_memset(conv->len_mod, 'l', 2);
    conv->type = 'x';
    return (conv_uint(conv, ap));
}