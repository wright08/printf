#include "ft_printf.h"
#include <stdarg.h>
#include <unistd.h>

int		convert(const char **format, va_list ap)
{
	t_fmt			*fmt;
	int				i;
	const t_able	table[] = {	{"c", conv_char}, {"s", conv_string}, {"p", conv_pointer},
								{"di", conv_int}, {"ouxX", conv_uint}};

	i = sizeof(table) / sizeof(t_able);
	while (i--)
	{
		if (ft_strchr(table[i].keys, **format))
			return (table[i].func(format, ap));
	}
	return (0);
}

int		next_section(const char **format, va_list ap)
{
	int offset;

	offset = -1;
	while (*format[++offset])
	{
		if (*format[offset] == '%')
		{
			write(1, *format, offset);
			(*format) += offset + 1;
			return (offset + convert(format, ap));
		}
	}
	if (offset)
	{
		write(1, *format, offset);
		(*format) += offset;
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

// While String
//  print everything up to the next mod
//  print conversion


//  a
// 01234567
// 10