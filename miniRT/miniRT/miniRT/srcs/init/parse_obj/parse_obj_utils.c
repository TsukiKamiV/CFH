#include "../../../includes/miniRT.h"

int	validate_cy_dims_and_color(t_cylinder *cy, char **tokens, char **color)
{
	int	err1;
	int	err2;
	
	err1 = assign_cy_dims(cy, tokens);
	err2 = validate_assign_rgb(&cy->color, color);
	if (err1 || err2)
		return (1);
	return (0);
}

void	cy_exit(t_scene *scene, t_params *ls, char **tokens, t_cylinder *cy)
{
	free_tab(tokens);
	free (cy);
	exit_with_lines(scene, ls, NULL, ERR_PARAM);
}
