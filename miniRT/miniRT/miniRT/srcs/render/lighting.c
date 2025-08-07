#include "../../includes/miniRT.h"

//t_color	compute_lighting(t_scene *scene, t_hit *hit)
//{
//t_color	color;
//
//	color = compute_ambient(hit->color, scene);
//return (color);
//}


t_color	compute_lighting(t_scene *scene, t_hit *hit)
{
	t_color	ambient;
	t_color	diffuse;
	t_color	final;
	
	ambient = compute_ambient(hit->color, scene);
	diffuse = compute_diffuse(scene, hit);
	
	final.r = fmin(ambient.r + diffuse.r, 255);
	final.g = fmin(ambient.g + diffuse.g, 255);
	final.b = fmin(ambient.b + diffuse.b, 255);
	return (final);
}
