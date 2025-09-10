/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hit_pl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:47:47 by luxu              #+#    #+#             */
/*   Updated: 2025/09/10 13:48:40 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

/**
 *@brief 用于判断一个射线是否与一个平面相交
 *denom 是平面法向量与射线方向的点积。如果为 0，说明射线与平面平行，不可能相交；
 *p0l0 是从光线起点指向平面上一点的向量
 *t 是相交距离；
 •	如果 t > 0，说明交点在摄像机前方；
 •	如果 t < 0，说明交点在摄像机后面，不可见。
 * 第一处点积：denom = vec3_dot(pl->normal, ray.direction);
 * 📌 目的：判断射线是否与平面平行
 */
int	hit_plane(t_ray ray, t_plane *pl, t_hit *hit)
{
	double	denom;
	t_vec3	p010;
	double	t;

	denom = vec3_dot(pl->normal, ray.direction);
	if (fabs(denom) > 1e-6)
	{
		p010 = vec3_sub(pl->point, ray.origin);
		t = vec3_dot(p010, pl->normal) / denom;
		if (t >= 0)
		{
			hit->t = t;
			hit->point = vec3_add(ray.origin, vec3_scale
					(ray.direction, t));
			hit->normal = vec3_normalize(pl->normal);
			hit->color = pl->color;
			return (1);
		}
	}
	return (0);
}
