#include "../../includes/miniRT.h"

/**
 *@brief 给定一条射线 ray 和参数 t，返回这条射线从起点出发沿着方向走 t 单位后的位置向量（即交点的位置）。
 */
t_vec3	ray_at(t_ray ray, double t)
{
	return (vec3_add(ray.origin, vec3_scale(ray.direction, t)));
}

bool	is_closer_hit(t_hit *tmp, t_hit *closest)
{
	if (tmp->t < closest->t)
	{
		*closest = *tmp;
		return (true);
	}
	return (false);
}

void	check_hit_obj(t_object *obj, t_ray ray, t_hit *tmp, t_hit *closest, bool *hit)
{
	bool	res;
	
	res = false;
	if (obj->type == PLANE)
		res = hit_plane(ray, (t_plane *)obj->element, tmp);
	else if (obj->type == SPHERE)
		res = hit_sphere(ray, (t_sphere *)obj->element, tmp);
	else if(obj->type == CYLINDER)
		res = hit_cylinder(ray, (t_cylinder *)obj->element, tmp);
	if (res && is_closer_hit(tmp, closest))
		*hit = true;
}
