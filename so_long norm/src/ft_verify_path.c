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
	while (tab_copy[i])
	{
		j = 0;
		while (tab_copy[i][j])
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

void  flood_fill(char **tab, t_position size, t_position begin)
{
	t_position p;
	
	tab[begin.y][begin.x] = 'F';
	if (begin.y > 0 && (tab[begin.y - 1][begin.x] == '0' || tab[begin.y - 1][begin.x] == 'C' || tab[begin.y - 1][begin.x] == 'E'))
	{
		p.x = begin.x;
		p.y = begin.y - 1;
		flood_fill(tab, size, p);
	}
	if ((begin.y < (size.y - 1)) && (tab[begin.y + 1][begin.x] == '0' || tab[begin.y + 1] [begin.x] == 'C' || tab[begin.y + 1][begin.x] == 'E'))
	{
		p.x = begin.x;
		p.y = begin.y + 1;
		flood_fill(tab, size, p);
	}
	if ((begin.x < (size.x - 1)) && (tab[begin.y][begin.x + 1] == '0' || tab[begin.y][begin.x + 1] == 'C' || tab[begin.y][begin.x + 1] == 'E'))
	{
		p.x = begin.x + 1;
		p.y = begin.y;
		flood_fill(tab, size, p);
	}
	if (begin.x > 0 && (tab[begin.y][begin.x - 1] == '0' || tab[begin.y][begin.x - 1] == 'C' || tab[begin.y][begin.x - 1] == 'E'))
	{
		p.x = begin.x - 1;
		p.y = begin.y;
		flood_fill(tab, size, p);
	}
}
