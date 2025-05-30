#include "../../includes/miniRT.h"



int	parse_plane(char **tokens, t_scene *scene)
{
	t_object	*obj;
	t_plane		*pl;
	char		**pos;
	char		**normal;
	char		**color;
	
	if (!tokens[1] || !tokens[2] || !tokens[3])
	{
		ft_putstr_fd("Error.\nInvalid plane format.", 2);
		return (0);
	}
	pl = malloc(sizeof(t_plane));
	if (!pl)
	{
		ft_putstr_fd("Error.\nMalloc failed when creating plane.", 2);
		return (0);
	}
	pos = ft_split(tokens[1], ',');
	normal = ft_split(tokens[2], ',');
	color = ft_split(tokens[3], ',');
	
	if (!pos || !normal || !color)
	{
		ft_putstr_fd("Error.\nInvalid plane vector formatting.\n", 2);
		if (pos)
			free_tab(pos);
		if (normal)
			free_tab(normal);
		if (color)
			free_tab(color);
		free(pl);
		return (0);
	}
	
	pl->point.x = atof(pos[0]);
	pl->point.y = atof(pos[1]);
	pl->point.z = atof(pos[2]);
	
	pl->normal.x = atof(normal[0]);
	pl->normal.y = atof(normal[1]);
	pl->normal.z = atof(normal[2]);
	
	pl->color.r = ft_atoi(color[0]);
	pl->color.g = ft_atoi(color[1]);
	pl->color.b = ft_atoi(color[2]);
	
	free_tab(pos);
	free_tab(normal);
	free_tab(color);
	
	
	obj = malloc(sizeof(t_object));
	if (!obj)
	{
		ft_putstr_fd("Error.\nMalloc failed for t_object.\n", 2);
		free(pl);
		return (0);
	}
	obj->type = PLANE;
	obj->element = pl;
	obj->next = NULL;
	add_object(scene, obj);
	return (1);
}
