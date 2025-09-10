/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hit_cy_annex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:43:10 by luxu              #+#    #+#             */
/*   Updated: 2025/09/10 13:47:22 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static void	cylinder_prepare_vectors(t_ray ray, t_cylinder *cy, \
		t_vec3 *oc, t_vec3 *d)
{
	*oc = vec3_sub(ray.origin, cy->centre);
	*d = vec3_sub(ray.direction, vec3_scale
			(cy->axis, vec3_dot(ray.direction, cy->axis)));
}

static t_vec3	cylinder_compute_projection(t_vec3 oc, t_vec3 axis)
{
	return (vec3_sub(oc, vec3_scale(axis, vec3_dot(oc, axis))));
}

static bool	cylinder_solve_quadratic(t_vec3 d, t_vec3 oc_p,
		double radius, double *t)
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	root;

	a = vec3_dot(d, d);
	b = 2 * vec3_dot(d, oc_p);
	c = vec3_dot(oc_p, oc_p) - radius * radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (false);
	root = (-b - sqrt(discriminant)) / (2.0 * a);
	if (root < EPSILON)
	{
		root = (-b + sqrt(discriminant)) / (2.0 * a);
		if (root < EPSILON)
			return (false);
	}
	*t = root;
	return (true);
}

static bool	cylinder_check_height(t_ray ray, t_cylinder *cy,
		double t, t_hit *hit)
{
	t_vec3	h;
	double	height_proj;

	hit->point = ray_at(ray, t);
	h = vec3_sub(hit->point, cy->centre);
	height_proj = vec3_dot(h, cy->axis);
	if (height_proj < -cy->height / 2.0 || height_proj > cy->height / 2.0)
		return (false);
	return (true);
}

bool	hit_cylinder_body(t_ray ray, t_cylinder *cy, t_hit *hit)
{
	t_vec3	oc;
	t_vec3	d;
	t_vec3	oc_p;
	t_vec3	projection;
	double	t;

	cylinder_prepare_vectors(ray, cy, &oc, &d);
	oc_p = cylinder_compute_projection(oc, cy->axis);
	if (!cylinder_solve_quadratic(d, oc_p, cy->radius, &t))
		return (false);
	if (!cylinder_check_height(ray, cy, t, hit))
		return (false);
	hit->t = t;
	hit->color = cy->color;
	hit->point = ray_at(ray, t);
	projection = vec3_add(cy->centre, vec3_scale(cy->axis, vec3_dot
				(vec3_sub(hit->point, cy->centre), cy->axis)));
	hit->normal = vec3_normalize(vec3_sub(hit->point, projection));
	return (true);
}
