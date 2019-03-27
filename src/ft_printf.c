#include "ft_printf.h"
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>

#define TABLE_LEN 6

#include <stdio.h>
void	free_swap(char **str, char *fix)
{
	free(*str);
	*str = fix;
}

int		convert(const char **format, va_list ap)
{
	int				i;
	t_conv			conv;
	const t_able	table[] = {	{"c", &conv_char}, {"s", &conv_string}, {"p", &conv_pointer},
								{"di", &conv_int}, {"ouxX", &conv_uint}, {"%", &conv_mod}};

	parse_fmt(&conv.fmt, format);
	while (**format)
	{
		conv.fmt.type = *(*format)++;
		i = TABLE_LEN;
		while (i--)
		{
			if (ft_strchr(table[i].keys, conv.fmt.type))
			{
				i = table[i].func(conv.fmt, ap);
				free(conv.fmt);
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