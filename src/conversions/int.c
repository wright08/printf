#include "ft_printf.h"
#include "int_utils.h"
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>

static long long arg(t_conv *conv, va_list ap)
{
	if (has(conv->len_mod, "z"))
		return ((ssize_t)va_arg(ap, ssize_t));
	if (has(conv->len_mod, "j"))
		return ((intmax_t)va_arg(ap, intmax_t));
	if (ft_strequ(conv->len_mod, "hh"))
		return ((char)va_arg(ap, int));
	if (ft_strequ(conv->len_mod, "h"))
		return ((short)va_arg(ap, int));
	if (ft_strequ(conv->len_mod, "l"))
		return (va_arg(ap, long));
	if (ft_strequ(conv->len_mod, "ll"))
		return (va_arg(ap, long long));
	return (va_arg(ap, int));
}

static void build_num(t_conv *conv)
{
	conv->len = ft_strlen(conv->str);
	conv->neg = (*conv->str == '-');
	if (conv->precision == 0 && *conv->str == '0')
	{
		*conv->str = '\0';
		conv->len = 0;
	}
	zero(conv);
}

static void build_conv(t_conv *conv)
{
	char	*copy;
	char	lead[2];

	copy = ft_strdup(conv->str);
	build_num(conv);
	leader(conv, lead);
	if (needs_zero_pad(conv))
	{
		conv->precision = conv->width - (!!*lead || conv->neg);
		zero(conv);
	}
	else
		free(copy);
	free_swap(conv, ft_strjoin(lead, conv->str));
	conv->len += !!*lead;
	width(conv);
}

int conv_int(t_conv *conv, va_list ap)
{
	conv->str = ft_lltoa(arg(conv, ap));
	build_conv(conv);
	return (print(conv));
}