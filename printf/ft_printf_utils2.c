#include "ft_printf.h"

int	ft_print_ptr(void *p)
{
	if (!p)
		return (ft_print_str("(nil)"));
	return (ft_print_str("0x") + ft_print_hex((unsigned long)p, 0));
}
