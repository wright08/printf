#include "ft_printf.h"
#include <stdarg.h>

static long double conv_arg(t_fmt *fmt, va_list ap)
{
    return (va_arg(ap, double));
}

int     conv_float(t_fmt *fmt, va_list ap);