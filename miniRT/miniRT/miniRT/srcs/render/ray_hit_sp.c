#include "../../includes/miniRT.h"

static void	compute_quadratic(t_ray ray, t_sphere *sp, t_quad *q)
{
	t_vec3	oc;
	oc = vec3_sub(ray.origin, sp->center);
	q->a = vec3_dot(ray.direction, ray.direction);
	q->b = 2.0 * vec3_dot(oc, ray.direction);
	q->c = vec3_dot(oc, oc) - (sp->radius * sp->radius);
	q->discriminant = (q->b * q->b) - (4 * q->a * q->c);
}
//void	compute_quad_from_vecs(t_vec3 d, t_vec3 oc_p, t_quad *q)
//{
//	q->a = vec3_dot(d, d);
//	q->b = 2 * vec3_dot(d, oc_p);
//	q->c = vec3_dot(oc_p, oc_p);
//	q->discriminant = q->b * q->b - 4 * q->a * q->c;
//}

bool	select_root(t_quad q, double *t)
{
	double	root;
	
	if (q.discriminant < 0)
		return (false);
	root = (-q.b - sqrt(q.discriminant)) / (2.0 * q.a);
	if (root < EPSILON)
	{
		root = (-q.b + sqrt(q.discriminant)) / (2.0 * q.a);
		if (root < EPSILON)
			return (false);
	}
	*t = root;
	return (true);
}

bool	hit_sphere(t_ray ray, t_sphere *sphere, t_hit *rec)
{
	t_quad	q;
	t_vec3	point;
	t_vec3	normal;
	double	t;
	
	compute_quadratic(ray, sphere, &q);
	if (!select_root(q, &t))
		return (false);
	point = ray_at(ray, t);
	normal = vec3_normalize(vec3_sub(point, sphere->center));
	rec->t = t;
	rec->point = point;
	rec->normal = normal;
	rec->color = sphere->color;
	return (true);
}
