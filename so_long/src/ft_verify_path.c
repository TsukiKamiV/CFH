#include "../includes/so_long.h"

char	**ft_make_tab_copy(char **tab, t_position *size)
{
	char	**tab_copy;
	int		row_index;
	int		row_counting;
	
	row_counting = 0;
	while (tab[row_counting] != NULL)
		row_counting++;
	tab_copy = malloc(sizeof(char *) * row_counting);
	if (!tab_copy)
		return (NULL);
	row_index = 0;
	while (row_index < row_counting)
	{
		tab_copy[row_index] = ft_strdup(tab[row_index]);
		row_index++;
	}
	size->x = (int)ft_strlen(tab[0]);
	size->y = row_counting;
	return (tab_copy);
}

void	ft_free_tab_copy(char **tab, int row_count)
{
	int	i;
	
	i = 0;
	while (i < row_count)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	find_p(char **tab_copy, t_position size, t_position *begin)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	while (i < size.y)
	{
		j = 0;
		while (j < size.x)
		{
			if (tab_copy[i][j] == 'P')
			{
				begin->y = i;
				begin->x = j;
			}
			j++;
		}
		i++;
	}
}

int	ft_verify_path(char **tab)
{
	int	i;
	int	j;
	t_position	size;
	t_position	begin;
	char	**tab_copy;
	int ret;
	
	tab_copy = ft_make_tab_copy(tab, &size);
	find_p(tab_copy, size, &begin);
	flood_fill(tab_copy, size, begin);
	print_map(tab_copy);
	i = 0;
	ret = 1;
	while (i < size.y)
	{
		j = 0;
		while (j < size.x)
		{
			if (tab_copy[i][j] == 'C' || tab_copy[i][j] == 'E')
				ret = 0;
			j++;
		}
		i++;
	}
	ft_free_tab_copy(tab_copy, size.y);
	return (ret);
}


void	fill(char **tab, t_position size, t_position cur)
{
	if (cur.y < 0 || cur.y >= size.y || cur.x < 0 || cur.x >= size.x)
		return;
	
	// Check if the current cell is '0', 'C', or 'E'
	if (tab[cur.y][cur.x] != '0' && tab[cur.y][cur.x] != 'C' && tab[cur.y][cur.x] != 'E' && tab[cur.y][cur.x] != 'P')
		return;
	
	// Fill the current cell
	tab[cur.y][cur.x] = 'F';
	
	// Recursively fill adjacent cells
	fill(tab, size, (t_position){cur.x - 1, cur.y}); // Left
	fill(tab, size, (t_position){cur.x + 1, cur.y}); // Right
	fill(tab, size, (t_position){cur.x, cur.y - 1}); // Up
	fill(tab, size, (t_position){cur.x, cur.y + 1}); // Down
}

void	flood_fill(char **tab, t_position size, t_position begin)
{
	fill(tab, size, begin);
	ft_printf("\n");
	print_map(tab);
}
