#include "ft_printf.h"
#include <stdlib.h>

void leader(t_conv *conv)
{
    char	*leader;

	leader = NULL;
	if (has(conv->flags, "+"))
		leader = "+";
	else if (has(conv->flags, " "))
		leader = " ";
    if (*conv->str == '-' || !leader)
        return ;
	conv->len++;
    free_swap(conv, ft_strjoin(leader, conv->str));
}