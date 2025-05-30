#include "../../includes/miniRT.h"

int	parse_ambient(char **tokens, t_scene *scene)
{
	scene->amb = malloc(sizeof(t_ambient));
	if (!scene->amb)
	{
		ft_putstr_fd("Error\nAmbient allocation failed.\n", 2);
		return (1);
	}
	if (ft_count_size(tokens) != 3)
	{
		ft_putstr_fd("Error\nInvalid ambient parameter.\n", 2);
		return (1);
	}
	scene->amb->ratio = strtod(tokens[1], NULL);
	return (0);
}
