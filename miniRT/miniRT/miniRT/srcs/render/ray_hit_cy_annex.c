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
	// 1) 计算 D 在 A 方向上的“系数”：k = D·A
	//double k;
	//k = vec3_dot(ray.direction, cy->axis);
	//
	//// 2) 得到 D 在 A 上的投影向量：proj = k * A
	//t_vec3 proj;
	//proj = vec3_scale(cy->axis, k);
	//
	//// 3) 用 D 减去它在 A 上的投影，得到垂直于 A 的分量：D_perp = D - proj
	//*d = vec3_sub(ray.direction, proj);
}

static t_vec3	cylinder_compute_projection(t_vec3 oc, t_vec3 axis)
{
	return (vec3_sub(oc, vec3_scale(axis, vec3_dot(oc, axis))));
	//k = oc * axis
	//proj = k * axis
	//oc_p = oc - proj
	//
	//即：
	//double	k;
	//t_vec3 proj;
	//
	//k = vec3_dot(oc, axis);
	//proj = vec3_scale(axis, k);
	//return (vec3_sub(oc, proj));
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
	t_vec3	oc;//射线起点到圆柱参考中心的位移 （= O - C）
	t_vec3	d;//射线方向在“径向平面”的分量
	t_vec3	oc_p;//位移在“径向平面”的分量，也就是OC在垂直于圆柱轴线的平面里的投影，忽略了OC在圆柱轴向方向的分量，只保留“OC离轴线有多远”的信息
	t_vec3	projection;//命中点在轴线上的投影点
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
	//t_vec3 hitpoint_to_center;//hit point相对圆柱的中心的向量
	//double	k;//投影系数
	//t_vec3 axis_k;//轴向的缩放向量axis_k = k * axis
	//hitpoint_to_center = vec3_sub(hit->point, cy->centre);
	//k = vec3_dot(hitpoint_to_center, cy->axis);
	//projection = vec3_add(cy->centre, axis_k);
	hit->normal = vec3_normalize(vec3_sub(hit->point, projection));
	return (true);
}
