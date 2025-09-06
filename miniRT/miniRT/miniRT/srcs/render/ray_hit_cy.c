#include "../../includes/miniRT.h"



static t_vec3	get_cap_center(t_cylinder *cy, int is_top)
{
	if (is_top)
		return (vec3_add(cy->centre, vec3_scale(cy->axis, cy->height / 2)));
	return (vec3_sub(cy->centre, vec3_scale(cy->axis, cy->height / 2)));
}

static bool	hit_cap(t_ray ray, t_cylinder *cy, t_vec3 center, t_hit *hit)
{
	t_vec3	to_cap;
	t_vec3	p;
	t_vec3	diff;
	double	t;
	double	r2;
	
	r2 = cy->radius * cy->radius;
	if (fabs(vec3_dot(ray.direction, cy->axis)) < EPSILON)
		return (false);
	to_cap = vec3_sub(center, ray.origin);
	t = vec3_dot(to_cap, cy->axis) / vec3_dot(ray.direction, cy->axis);
	if (t < EPSILON || t > hit->t)
		return (false);
	p = ray_at(ray, t);
	diff = vec3_sub(p, center);
	if (vec3_dot(diff, diff) > r2)
		return (false);
	hit->t = t;
	hit->point = p;
	hit->normal = vec3_normalize(vec3_sub(center, cy->centre));
	hit->color = cy->color;
	return (true);
}

bool	hit_cylinder_cap(t_ray ray, t_cylinder *cy, t_hit *hit)
{
	t_vec3	center;
	int		i;
	bool	hit_any;
	
	hit_any = false;
	i = 0;
	while (i < 2)
	{
		center = get_cap_center(cy, i == 0);
		if (hit_cap(ray, cy, center, hit))
			hit_any = true;
		i++;
	}
	return (hit_any);
}

bool	hit_cylinder(t_ray ray, t_cylinder *cy, t_hit *hit)
{
	t_hit	tmp;
	bool	hit_any;
	
	hit_any = false;
	tmp.t = INFINITY;
	if (hit_cylinder_body(ray, cy, &tmp))
		hit_any = true;
	if (hit_cylinder_cap(ray, cy, &tmp))
		hit_any = true;
	if (hit_any)
	{
		*hit = tmp;
		hit->obj = (void *)cy;
		return (true);
	}
	return (false);
}
