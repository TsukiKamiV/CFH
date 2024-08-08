#include "../includes/so_long.h"

int	ft_verify_map(int argc, char *argv[])
{
	size_t	argv_len;

	if (argc > 2)
	{
		ft_printf("Too many arguments");
		return (0);
	}
	if (argc < 2)
	{
		ft_printf("Please load a map");
		return (0);
	}
	argv_len = ft_strlen(argv[1]);
	if (!ft_strnstr(&argv[1][argv_len - 4], ".ber", 4))
	{
		ft_printf("The map should be a .ber file");
		return (0);
	}
	return (1);
}
