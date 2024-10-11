#include "../includes/so_long.h"

t_position	ft_calculate_map_size(char **tab)
{
	t_position	size;
	
	size.y = (int)ft_strlen(*tab);
	size.x = 0;
	while (tab[size.x])
		size.x++;
	return (size);
}

int	ft_is_valid_item(char c)
{
	return (c == 'E' || c == 'P' || c == 'C' || c == '0' || c == '1');
}

//void	ft_check_item_count(t_item_count)
