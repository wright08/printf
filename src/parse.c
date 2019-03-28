#include "ft_printf.h"

static void get_flags(t_conv *conv, const char **format)
{
	while (ft_strchr("#0- +", **format))
	{
		if (ft_strlen(conv->flags) < 6 && !ft_strchr(conv->flags, **format))
			ft_strncat(conv->flags, *format, 1);
		(*format)++;
	}
}

static void get_width(t_conv *conv, const char **format)
{
	if (ft_isdigit(**format))
		conv->width = ft_atoi(*format);
	while (ft_isdigit(**format))
		(*format)++;
}

static void get_precision(t_conv *conv, const char **format)
{
	conv->precision = -1;
	if (**format == '.')
	{
		(*format)++;
		if (!ft_isdigit(**format))
			conv->precision = 0;
		else
			conv->precision = ft_atoi(*format);
	}
	while (**format == '-' || ft_isdigit(**format))
		(*format)++;
}

static void get_len(t_conv *conv, const char **format)
{
	while (ft_strchr("lhjz", **format))
	{
		if (ft_strlen(conv->len) < 2)
			ft_strncat(conv->len, *format, 1);
		(*format)++;
	}
}

void	parse_fmt(t_conv *conv, const char **format)
{
	get_flags(conv, format);
	get_width(conv, format);
	get_precision(conv, format);
	get_len(conv, format);
}