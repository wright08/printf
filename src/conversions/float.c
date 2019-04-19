#include "ft_printf.h"
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>

static long double arg(t_conv *conv, va_list ap)
{
    if (has(conv->len_mod, "L"))
        return (va_arg(ap, long double));
    return (va_arg(ap, double));
}

long double ft_round(long double n, int precision)
{
	long double reckoning;
	int			i;

	if (fpclassify(n) != FP_NORMAL)
		return (n);
	reckoning = .5;
	i = -1;
	while (++i < precision)
		reckoning /= 10;
	return (n < 0 ? n - reckoning : n + reckoning);
}

static void	leader(t_conv *conv, char *lead)
{
	ft_bzero(lead, 2);
	if (conv->neg)
		;
	else if (has(conv->flags, "+"))
		*lead = '+';
	else if (has(conv->flags, " "))
		*lead = ' ';
}

void	fractional(t_conv *conv, long double n)
{
	char	*fix;
	int		i;
	char	digit;

	if (has(conv->flags, "#") || conv->precision != 0)
	{
		fix = ft_strnew(conv->len + 1 + conv->precision);
		ft_memmove(fix, conv->str, conv->len++);
		ft_strcat(fix, ".");
		n -= (long long)n;
		n *= 10;
		i = -1;
		while (++i < conv->precision)
		{
			digit = (long long)n % 10;
			fix[conv->len + i] = digit + '0';
			n = (n - digit) * 10;
		}
		free_swap(conv, fix);
		conv->len += conv->precision;
	}
}

static void build_conv(t_conv *conv, long double n)
{
	char	lead[2];

	ft_bzero(lead, 2);
	if (signbit(n) && fpclassify(n) != FP_NAN)
	{
		conv->neg = 1;
		n = -n;
		if (*conv->str != '-')
			free_swap(conv, ft_strjoin("-", conv->str));
	}
	conv->len = ft_strlen(conv->str);
	if (fpclassify(n) == FP_NORMAL || fpclassify(n) == FP_ZERO)
	{
		leader(conv, lead);
		fractional(conv, n);
	}
	if (fpclassify(n) == FP_INFINITE)
		leader(conv, lead);
	if (conv->len < conv->width && has(conv->flags, "0") && !has(conv->flags, "-"))
	{
		conv->precision = conv->width - (!!*lead || conv->neg);
		zero(conv);
	}
	free_swap(conv, ft_strjoin(lead, conv->str));
	conv->len += !!*lead;
	width(conv);
}

int     conv_float(t_conv *conv, va_list ap)
{
	long double n;
	int			class;

	if (conv->precision == -1)
		conv->precision = 6;
	n = ft_round(arg(conv, ap), conv->precision);
	class = fpclassify(n);
	if (class == FP_NAN || class == FP_INFINITE)
	{
		if (class == FP_NAN)
			conv->str = ft_strdup((conv->type == 'f' ? "nan" : "NAN"));
		else
			conv->str = ft_strdup((conv->type == 'f' ? "inf" : "INF"));
		if (ft_strchr(conv->flags, '0'))
			*ft_strchr(conv->flags, '0') = 1;
	}
	else
		conv->str = ft_lltoa(n);
	build_conv(conv, n);
    return (print(conv));
}