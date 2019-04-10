#include "ft_printf.h"
#include <stdarg.h>

static float arg(t_conv *conv, va_list ap)
{
    if (has(conv->len_mod, "l"))
        return (va_arg(ap, double));
    if (has(conv->len_mod, "L"))
        return (va_arg(ap, long double));
    return (va_arg(ap, float));
}

char    *ft_ftoa(float n)
{
    unsigned bits;
    int     sign;
    char    exponent;
    long    significand;

    ft_memmove(&bits, &n, sizeof(float));
    sign = (bits & 1 << 31);
    exponent = (t_byte)(&bits + 1);
    significand = bits & 0x7777;

	return ("");
}

int     conv_float(t_conv *conv, va_list ap)
{
    conv->str = ft_ftoa(arg(conv, ap));
    return (0);
}