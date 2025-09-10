/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 15:09:23 by luxu              #+#    #+#             */
/*   Updated: 2025/09/10 13:41:51 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

/**
 *弧度转换公式：fov_rad = cam->fov * M_PI / 180.0;
 *视平面高度：viewport.height = 2.0 * tan(fov_rad / 2.0);
 *视平面宽度：viewport.width = viewport.aspect_ratio * viewport.height;
 *摄像机后方向量：basis.w = normalize(cam->orient);
 *水平基向量：basis.u = normalize(cross((0, 1, 0), w));
 *垂直基向量：basis.v = cross(w, u);
 *横向向量：horizontal = u * viewport.width;
 *纵向向量：vertical = v * viewport.height;
 *视平面左下角坐标：
 *lower_left_corner = cam->pos - horizontal/2 - vertical/2 - w * focal_length;
 *归一化像素坐标：u_ratio = x / (image_width - 1);
 *v_ratio = y / (image_height - 1);
 *像素在视平面上的实际坐标：
 *pixel_pos = lower_left_corner + horizontal * u_ratio + vertical * v_ratio;
 *光线方向：direction = normalize(pixel_pos - cam->pos);
 */
static void	init_viewport_and_basis(t_camera *cam, t_image img, \
		t_viewport *vp, t_basis *basis)
{
	double	fov_rad;

	vp->aspect_ratio = (double)img.width / (double)img.height;
	fov_rad = cam->fov * M_PI / 180.0;
	vp->height = 2.0 * tan(fov_rad / 2.0);
	vp->width = vp->aspect_ratio * vp->height;
	vp->focal_length = 1.0;
	basis->w = vec3_normalize(vec3_scale(cam->orient, -1));
	basis->u = vec3_normalize(vec3_cross((t_vec3){0, 1, 0}, basis->w));
	basis->v = vec3_cross(basis->w, basis->u);
}

static void	compute_lower_left_corner(t_camera *cam, t_viewport vp, \
		t_basis basis, t_vec3 *ll_corner)
{
	t_vec3	horizontal;
	t_vec3	vertical;

	horizontal = vec3_scale(basis.u, vp.width);
	vertical = vec3_scale(basis.v, vp.height);
	*ll_corner = vec3_sub(vec3_sub(vec3_sub(cam->pos, vec3_scale
					(horizontal, 0.5)), vec3_scale
				(vertical, 0.5)), vec3_scale(basis.w, vp.focal_length));
}

t_ray	generate_ray(t_camera *cam, t_point2 pixel, t_image img)
{
	t_ray		ray;
	t_viewport	vp;
	t_vec3		ll_corner;
	t_basis		basis;
	t_uv		uv;

	ft_memset(&vp, 0, sizeof(t_viewport));
	ft_memset(&ray, 0, sizeof(t_ray));
	ft_memset(&basis, 0, sizeof(t_basis));
	init_viewport_and_basis(cam, img, &vp, &basis);
	compute_lower_left_corner(cam, vp, basis, &ll_corner);
	uv.u = (double)pixel.x / (img.width - 1);
	uv.v = (double)pixel.y / (img.height - 1);
	ray.origin = cam->pos;
	ray.direction = vec3_normalize(vec3_sub
			(pixel_pos_from_offset(ll_corner, compute_view_offset
					(basis, vp, uv)), cam->pos));
	return (ray);
}

static void	init_hitcheck(t_hitcheck *hc)
{
	if (!hc)
		return ;
	ft_memset(hc, 0, sizeof(t_hitcheck));
	hc->closest.t = INFINITY;
}

t_color	trace_ray(t_ray ray, t_scene *scene)
{
	t_object	*obj;
	t_hitcheck	hc;

	init_hitcheck(&hc);
	obj = scene->objs;
	while (obj)
	{
		check_hit_obj(obj, ray, &hc);
		obj = obj->next;
	}
	if (hc.hit)
		return (compute_lighting(scene, &hc.closest));
	return (create_color(0, 0, 0));
}
