/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:49:58 by luxu              #+#    #+#             */
/*   Updated: 2025/09/10 13:51:40 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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


void	check_hit_obj(t_object *obj, t_ray ray, t_hitcheck *hc)
{
	bool	res;
	
	res = false;
	if (obj->type == PLANE)
		res = hit_plane(ray, (t_plane *)obj->element, &hc->tmp);
	else if (obj->type == SPHERE)
		res = hit_sphere(ray, (t_sphere *)obj->element, &hc->tmp);
	else if (obj->type == CYLINDER)
		res = hit_cylinder(ray, (t_cylinder *)obj->element, &hc->tmp);
	if (res && is_closer_hit(&hc->tmp, &hc->closest))
		hc->hit = true;
}

//void	check_hit_obj(t_object *obj, t_ray ray,
//		t_hit *tmp, t_hit *closest, bool *hit)
//{
//	bool	res;
//
//	res = false;
//	if (obj->type == PLANE)
//		res = hit_plane(ray, (t_plane *)obj->element, tmp);
//	else if (obj->type == SPHERE)
//		res = hit_sphere(ray, (t_sphere *)obj->element, tmp);
//	else if (obj->type == CYLINDER)
//		res = hit_cylinder(ray, (t_cylinder *)obj->element, tmp);
//	if (res && is_closer_hit(tmp, closest))
//		*hit = true;
//}

/*计算视平面偏移：horizontal * u + vertical * v*/
t_vec3	compute_view_offset(t_basis basis, t_viewport vp, t_uv uv)
{
	t_vec3	h;
	t_vec3	v;
	t_vec3	offset;

	h = vec3_scale(basis.u, vp.width);
	v = vec3_scale(basis.v, vp.height);
	offset = vec3_add(vec3_scale(h, uv.u), vec3_scale(v, uv.v));
	return (offset);
}

/*由左下角 + 偏移 计算像素位置*/
t_vec3	pixel_pos_from_offset(t_vec3 ll_corner, t_vec3 offset)
{
	return (vec3_add(ll_corner, offset));
}
