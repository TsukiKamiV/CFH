#include "../../includes/miniRT.h"

int	error_msg(const char *msg, int ret)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd((char *)msg, 2);
	ft_putstr_fd("\n", 1);
	return (ret);
}
