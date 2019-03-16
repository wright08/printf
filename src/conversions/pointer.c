#include "ft_printf.h"
#include <stdarg.h>

int     conv_pointer(t_fmt *fmt, va_list ap)
{
    ft_memset(fmt->flags, '#', 6);
    ft_memset(fmt->len, 'l', 2);
    fmt->conv = 'x';
    return (conv_uint(fmt, ap));
}