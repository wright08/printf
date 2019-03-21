#include "ft_printf.h"
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>

#define TABLE_LEN 6

#include <stdio.h>
int		convert(const char **format, va_list ap)
{
	int				i;
	t_fmt			*fmt;
	const t_able	table[] = {	{"c", &conv_char}, {"s", &conv_string}, {"p", &conv_pointer},
								{"di", &conv_int}, {"ouxX", &conv_uint}, {"%", &conv_mod}};

	fmt = parse_fmt(format);
	while (**format)
	{
		fmt->conv = *(*format)++;
		i = TABLE_LEN;
		while (i--)
		{
			if (ft_strchr(table[i].keys, fmt->conv))
			{
				i = table[i].func(fmt, ap);
				free(fmt);
				return (i);
			}
		}
	}
	free(fmt);
	return (0);
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