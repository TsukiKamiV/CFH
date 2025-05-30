#include "../../includes/miniRT.h"

t_color	parse_color(char *str)
{
	t_color	color;
	char	**rgb;
	
	rgb = ft_split(str, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
	{
		ft_putstr_fd("Error\nInvalid RGB setting.", 1);
		return ((t_color){0, 0, 0});
	}
	color.r = ft_atoi(rgb[0]);
	color.g = ft_atoi(rgb[1]);
	color.b = ft_atoi(rgb[2]);
	free_tab(rgb);
	return (color);
}

void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	add_object(t_scene *scene, t_object *new)
{
	t_object	*current;
	
	if (!scene->objs)
	{
		scene->objs = new;
		return ;
	}
	current = scene->objs;
	while (current->next)
		current = current->next;
	current->next = new;
}
