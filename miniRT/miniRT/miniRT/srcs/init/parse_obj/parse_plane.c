#include "../../../includes/miniRT.h"

static int	split_plane_tokens(char **tokens, char ***pos, char ***normal, char ***color)
{
	*pos = NULL;
	*normal = NULL;
	*color = NULL;
	*pos = ft_split(tokens[1], ',');
	*normal = ft_split(tokens[2], ',');
	*color = ft_split(tokens[3], ',');
	if (!(*pos) || !(*normal) || !(*color))
	{
		free_multiple_tab(4, *pos, *normal, *color, tokens);
		return (error_msg("invalid plane vector formatting.", 1));
	}
	if (ft_count_size(*pos) != 3 || ft_count_size(*normal) != 3 || ft_count_size(*color) != 3)
	{
		free_multiple_tab(4, *pos, *normal, *color, tokens);
		return (error_msg("invalid plane parameter size.", 1));
	}
	return (0);
}

static void	assign_plane_point_normal(t_plane *pl, char **pos, char **normal)
{
	pl->point.x = atof(pos[0]);
	pl->point.y = atof(pos[1]);
	pl->point.z = atof(pos[2]);
	pl->normal.x = atof(normal[0]);
	pl->normal.y = atof(normal[1]);
	pl->normal.z = atof(normal[2]);
}

static int	fill_plane(t_scene *scene, char **tokens, t_plane *pl, t_params *ls)
{
	char	**pos;
	char	**normal;
	char	**color;
	
	pos = NULL;
	normal = NULL;
	color = NULL;
	if (split_plane_tokens(tokens, &pos, &normal, &color))
		exit_with_lines(scene, ls, NULL, EXIT_ERROR_PARAM);
	//return (1);
	assign_plane_point_normal(pl, pos, normal);
	if (normal_is_unit(pl->normal))
	{
		free_multiple_tab(4, pos, normal, color, tokens);
		free (pl);
		exit_with_lines(scene, ls, "Error: plane normal must be normalized.\n", EXIT_ERROR_PARAM);
		//close_program(scene, "Error: plane normal must be normalized.\n", EXIT_ERROR_PARAM);
		//return (error_msg("plane normal must be normalized.", 1));
	}
	if (validate_assign_rgb(&pl->color, color))
	{
		free_multiple_tab(4, pos, normal, color, tokens);
		free (pl);
		exit_with_lines(scene, ls, NULL, EXIT_ERROR_PARAM);
		//close_program(scene, NULL, EXIT_ERROR_PARAM);
		//return (1);
	}
	free_multiple_tab(3, pos, normal, color);
	return (0);
}

int	parse_plane(char **tokens, t_scene *scene, t_params *ls)
{
	t_plane		*pl;
	t_object	*obj;
	
	if (ft_count_size(tokens) != 4)
	{
		free_tab(tokens);
		exit_with_lines(scene, ls, "Error: invalid plane parameter number.\n", EXIT_ERROR_PARAM);
	}
	pl = malloc(sizeof(t_plane));
	if (!pl)
	{
		free_tab(tokens);
		exit_with_lines(scene, ls, "Error: allocation failed for t_plane.\n", EXIT_ERROR_MALLOC);
	}
	fill_plane(scene, tokens, pl, ls);
	obj = malloc(sizeof(t_object));
	if (!obj)
	{
		free(pl);
		exit_with_lines(scene, ls, "Error: allocation failed for t_object.\n", EXIT_ERROR_MALLOC);
	}
	obj->type = PLANE;
	obj->element = pl;
	obj->next = NULL;
	add_object(scene, obj);
	return (1);
}
