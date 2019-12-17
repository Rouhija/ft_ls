#include "ft_printf.h"
#include "libft.h"
#include "get_next_line.h"

int		main(void)
{
	ft_printf("Long string {red} now red {blue} then blue {normal} %s\n", "the end.");
	ft_printf("binary %08b\n", 10);
	ft_printf("size_t %ju\n", 10234234);
	ft_printf("intmax %zd\n", 10234234);
	return (0);
}
