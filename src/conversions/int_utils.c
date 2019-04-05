#include "ft_printf.h"
#include <stdlib.h>

void	leader(t_conv *conv, char *lead)
{
	ft_bzero(lead, 2);
	if (conv->neg)
		;
	else if (has(conv->flags, "+"))
		*lead = '+';
	else if (has(conv->flags, " "))
		*lead = ' ';
}