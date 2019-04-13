#include "ft_printf.h"
#include <stdarg.h>
#include <stdlib.h>

static float arg(t_conv *conv, va_list ap)
{
    if (has(conv->len_mod, "l"))
        return (va_arg(ap, double));
    if (has(conv->len_mod, "L"))
        return (va_arg(ap, long double));
    return (va_arg(ap, double));
}

void    print_bits(long bits, size_t n)
{
    char    *str;
    size_t  i;

    if (!n || n > 32)
        return ;
    str = ft_strnew(n);
    i = 0;
    while (i < n)
	{
        str[i] = bits & (1 << (n - i - 1)) ? '1' : '0';
		i++;
	}
    ft_putstr(str);
    free(str);
}

char    *ft_ftoa(float n)
{
    int     *bits;
    int     sign;
    unsigned char    exponent;
    long    significand;

    bits = (int *)&n;
    print_bits(*bits, 32);
    sign = (*bits & 1 << 31);
    exponent = (t_byte)(bits + 1);
    significand = *bits & 0x7FFFFF;

	return ("");
}

int     conv_float(t_conv *conv, va_list ap)
{
    float f = arg(conv, ap);
    conv->str = ft_ftoa(f);
    return (0);
}