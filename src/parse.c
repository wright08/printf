#include "ft_printf.h"

static void get_flags(t_fmt *fmt, const char **format)
{
	while (ft_strchr("#0- +'", **format))
	{
		if (ft_strlen(fmt->flags) == 6 || ft_strchr(fmt->flags, **format))
			continue;
		ft_strncat(fmt->flags, *format, 1);
		(*format)++;
	}
}

static void get_width(t_fmt *fmt, const char **format)
{
	if (ft_isdigit(**format))
		fmt->width = ft_atoi(*format);
	while (ft_isdigit(**format))
		(*format)++;
}

static void get_precision(t_fmt *fmt, const char **format)
{
	fmt->precision = -1;
	if (**format == '.')
	{
		(*format)++;
		if (!ft_isdigit(**format))
			fmt->precision = 0;
		else
			fmt->precision = ft_atoi(*format);
	}
	while (**format == '-' || ft_isdigit(**format))
		(*format)++;
}

static void get_len(t_fmt *fmt, const char **format)
{
	while (ft_strchr("lh", **format))
	{
		if (ft_strlen(fmt->len) == 2)
		{
			(*format)++;
			continue ;
		}
		ft_strncat(fmt->len, *format, 1);
		(*format)++;
	}
}

t_fmt *parse_fmt(const char **format)
{
	t_fmt *fmt;

	fmt = ft_memalloc(sizeof(t_fmt));
	get_flags(fmt, format);
	get_width(fmt, format);
	get_precision(fmt, format);
	get_len(fmt, format);
	fmt->conv = (*format)++;
	return (fmt);
}