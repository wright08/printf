#include "ft_printf.h"
#include <stdarg.h>
#include <unistd.h>

#include <stdio.h>
int		convert(const char **format, va_list ap)
{
	int				i;
	t_fmt			*fmt;
	const int		table_len = 7;
	const t_able	table[] = {	{"u", &conv_uint}, {"c", &conv_char}, {"s", &conv_string}, {"p", &conv_pointer},
								{"di", &conv_int}, {"ouxX", &conv_uint}, {"%", &conv_mod}};

	fmt = parse_fmt(format);
	while (**format)
	{
		fmt->conv = *(*format)++;
		i = table_len;
		while (i--)
			if (ft_strchr(table[i].keys, fmt->conv))
				return (table[i].func(fmt, ap));
	}
	return (table[0].func(fmt, ap));
}

int		next_section(const char **format, va_list ap)
{
	int offset;

	offset = -1;
	while ((*format)[++offset])
	{
		if ((*format)[offset] == '%')
		{
			write(1, *format, offset);
			*format += offset + 1;
			return (offset + convert(format, ap));
		}
	}
	if (offset)
	{
		write(1, *format, offset);
		*format += offset;
	}
	return (offset);
}

int		ft_printf(const char *format, ...)
{
	va_list	ap;
	int		len;

	va_start(ap, format);
	len = 0;
	while (*format)
		len += next_section(&format, ap);
	va_end(ap);
	return (len);
}