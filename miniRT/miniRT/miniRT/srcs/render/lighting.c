#include "../../includes/miniRT.h"

t_color	compute_lighting(t_scene *scene, t_hit *hit)
{
	t_color	color;
	
	color = compute_ambient(hit->color, scene);
	return (color);
}
