/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_ptr_mod.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwright <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 06:10:21 by rwright           #+#    #+#             */
/*   Updated: 2019/04/19 06:10:22 by rwright          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>
#include <stdlib.h>

static char	*arg(va_list ap)
{
	return (va_arg(ap, char *));
}

static void	build_conv(t_conv *conv)
{
	if (!conv->str)
		conv->str = ft_strdup("(null)");
	else
		conv->str = ft_strdup(conv->str);
	conv->len = ft_strlen(conv->str);
	if (conv->precision >= 0 && conv->len > conv->precision)
	{
		conv->str[conv->precision] = '\0';
		conv->len = conv->precision;
	}
	width(conv);
}

int			conv_str(t_conv *conv, va_list ap)
{
	conv->str = arg(ap);
	build_conv(conv);
	return (print(conv));
}

int			conv_mod(t_conv *conv, va_list ap)
{
	(void)ap;
	conv->str = ft_strdup("%");
	conv->len = 1;
	if (has(conv->flags, "0") && !has(conv->flags, "-") &&
		conv->width > conv->len)
		zero(conv, conv->width - conv->len);
	width(conv);
	return (print(conv));
}

int			conv_ptr(t_conv *conv, va_list ap)
{
	conv->str = ft_ulltoa_base(va_arg(ap, long), 16);
	free_swap(conv, ft_strjoin("0x", conv->str), STR);
	conv->len = ft_strlen(conv->str);
	width(conv);
	return (print(conv));
}
