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
 *视平面左下角坐标：lower_left_corner = cam->pos - horizontal/2 - vertical/2 - w * focal_length;
 *归一化像素坐标：u_ratio = x / (image_width - 1);
 *v_ratio = y / (image_height - 1);
 *像素在视平面上的实际坐标：pixel_pos = lower_left_corner + horizontal * u_ratio + vertical * v_ratio;
 *光线方向：direction = normalize(pixel_pos - cam->pos);
 */

static void	init_viewport_and_basis(t_camera *cam, t_image img, t_viewport *vp, t_basis *basis)
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

static void	compute_lower_left_corner(t_camera *cam, t_viewport vp, t_basis basis, t_vec3 *ll_corner)
{
	t_vec3	horizontal;
	t_vec3	vertical;
	
	horizontal = vec3_scale(basis.u, vp.width);
	vertical = vec3_scale(basis.v, vp.height);
	*ll_corner = vec3_sub(vec3_sub(vec3_sub(cam->pos, vec3_scale(horizontal, 0.5)), vec3_scale(vertical, 0.5)), vec3_scale(basis.w, vp.focal_length));
}

static t_vec3	compute_pixel_pos(t_vec3 ll_corner, t_basis basis, t_viewport vp, t_point2 pixel, t_image img)
{
	double	u_ratio;
	double	v_ratio;
	t_vec3	horizontal;
	t_vec3	vertical;
	t_vec3	pos;
	
	u_ratio = (double)pixel.x / (img.width - 1);
	v_ratio = (double)pixel.y / (img.height - 1);
	horizontal = vec3_scale(basis.u, vp.width);
	vertical = vec3_scale(basis.v, vp.height);
	pos = vec3_add(vec3_add(ll_corner, vec3_scale(horizontal, u_ratio)), vec3_scale(vertical, v_ratio));
	return (pos);
}

t_ray	generate_ray(t_camera *cam, t_point2 pixel, t_image img)
{
	t_ray		ray;
	t_viewport	vp;
	t_vec3		ll_corner;
	t_basis		basis;
	t_vec3		pixel_pos;
	
	ft_memset(&vp, 0, sizeof(t_viewport));
	ft_memset(&ray, 0, sizeof(t_ray));
	ft_memset(&basis, 0, sizeof(t_basis));
	init_viewport_and_basis(cam, img, &vp, &basis);
	compute_lower_left_corner(cam, vp, basis, &ll_corner);
	pixel_pos = compute_pixel_pos(ll_corner, basis, vp, pixel, img);
	ray.origin = cam->pos;
	ray.direction = vec3_normalize(vec3_sub(pixel_pos, cam->pos));
	return (ray);
}

t_color	trace_ray(t_ray ray, t_scene *scene, t_point2 pixel)
{
	t_object	*obj;
	t_hit		closest;
	t_hit		tmp;
	bool		hit;
	
	(void)pixel;
	ft_memset(&closest, 0, sizeof(t_hit));
	ft_memset(&tmp, 0, sizeof(t_hit));
	closest.t = INFINITY;
	hit = false;
	obj = scene->objs;
	while (obj)
	{
		check_hit_obj(obj, ray, &tmp, &closest, &hit);
		obj = obj->next;
	}
	if (hit)
		return (compute_lighting(scene, &closest));
	return (create_color(0, 0, 0));
}

//t_ray	generate_ray(t_camera *cam, t_point2 pixel, t_image img)
//{
//	t_ray		ray;
//	t_viewport	viewport;
//	t_basis		basis;
//	t_vec3		horizontal;
//	t_vec3		vertical;
//	t_vec3		lower_left_corner;
//	t_vec3		pixel_pos;
//	double		u_ratio;
//	double		v_ratio;
//	double		fov_rad;
//
//	ft_memset(&ray, 0, sizeof(t_ray));
//	ft_memset(&viewport, 0, sizeof(t_viewport));
//	ft_memset(&basis, 0, sizeof(t_basis));
//
//	// 步骤1：计算画面比例和视平面尺寸
//	viewport.aspect_ratio = (double)img.width / (double)img.height;
//	fov_rad = cam->fov * M_PI / 180.0;
//	viewport.height = 2.0 * tan(fov_rad / 2.0);
//	viewport.width = viewport.aspect_ratio * viewport.height;
//	viewport.focal_length = 1.0;
//
//	// 步骤2：构建摄像机坐标系
//	basis.w = vec3_normalize(vec3_scale(cam->orient, -1));
//	basis.u = vec3_normalize(vec3_cross((t_vec3){0, 1, 0}, basis.w));
//	basis.v = vec3_cross(basis.w, basis.u);
//	// 步骤3：计算视平面左下角坐标
//	horizontal = vec3_scale(basis.u, viewport.width);
//	vertical = vec3_scale(basis.v, viewport.height);
//	lower_left_corner = vec3_sub(vec3_sub(vec3_sub(cam->pos, vec3_scale(horizontal, 0.5)), vec3_scale(vertical, 0.5)), vec3_scale(basis.w, viewport.focal_length));
//	// 步骤4：归一化像素坐标，用于定位像素在视平面上的位置
//	u_ratio = (double)pixel.x / (img.width - 1);
//	v_ratio = (double)pixel.y / (img.height - 1);
//	pixel_pos = vec3_add(vec3_add(lower_left_corner, vec3_scale(horizontal, u_ratio)), vec3_scale(vertical, v_ratio));
//
//	// 步骤5：生成 ray 的 origin 和 direction
//	ray.origin = cam->pos;
//	ray.direction = vec3_normalize(vec3_sub(pixel_pos, cam->pos));
//	return (ray);
//}

/**
 *@brief 接收一条光线 ray 和一个完整的场景 scene，判断这条光线是否与任何物体（目前仅支持平面）相交，并返回交点处的颜色（或背景色）。
 */
//t_color	trace_ray(t_ray ray, t_scene *scene, t_point2 pixel)
//{
//	t_object	*obj;
//	t_hit		closest_hit;
//	t_hit		tmp_hit;
//	bool		hit_something;
//
//	ft_memset(&closest_hit, 0, sizeof(t_hit));
//	ft_memset(&tmp_hit, 0, sizeof(t_hit));
//	closest_hit.t = INFINITY;
//	obj = scene->objs;
//	hit_something = false;
//	while (obj)
//	{
//		if (obj->type == PLANE)
//		{
//			if (hit_plane(ray, (t_plane *)obj->element, &tmp_hit))
//			{
//				if (tmp_hit.t < closest_hit.t)
//				{
//					closest_hit = tmp_hit;
//					hit_something = true;
//				}
//			}
//		}
//		else if (obj->type == SPHERE)
//		{
//			if (hit_sphere(ray, (t_sphere *) obj->element, &tmp_hit))
//			{
//				if (tmp_hit.t < closest_hit.t)
//				{
//					closest_hit = tmp_hit;
//					hit_something = true;
//				}
//			}
//		}
//		else if (obj->type == CYLINDER)
//		{
//			if (hit_cylinder(ray, (t_cylinder *) obj->element, &tmp_hit))
//			{
//				if (tmp_hit.t < closest_hit.t)
//				{
//					closest_hit = tmp_hit;
//					hit_something = true;
//				}
//			}
//		}
//		obj = obj->next;
//	}
//	if (hit_something)
//	{
//		t_color	lit_color = compute_lighting(scene, &closest_hit);
//		return (create_color(lit_color.r, lit_color.g, lit_color.b));
//	}
//		//return (create_color(closest_hit.color.r, closest_hit.color.g, closest_hit.color.b));
//	else
//		return (create_color(0, 0, 0));
//}

