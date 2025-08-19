#include "../../includes/miniRT.h"

/**
 *@brief Lambert模型：
 *一个物体表面所反射出的光的强度，取决于该表面法线方向与光线方向的夹角
 */
t_color	compute_diffuse(t_scene *scene, t_hit *hit)
{
	t_color	res;
	t_vec3	light_dir;
	double	dot_nl;

	light_dir = vec3_normalize(vec3_sub(scene->light->pos, hit->point));
	dot_nl = vec3_dot(hit->normal, light_dir);
	if (dot_nl <= 0)
		return (create_color(0, 0, 0));
	if (is_in_shadow(scene, hit->point, light_dir))
		return (create_color(0, 0, 0));
	res.r = hit->color.r * (scene->light->color.r / 255.0) * (scene->light->ratio * dot_nl);
	res.g = hit->color.g * (scene->light->color.g / 255.0) * (scene->light->ratio * dot_nl);
	res.b = hit->color.b * (scene->light->color.b / 255.0) * (scene->light->ratio * dot_nl);
	res.r = fmin(res.r, 255);
	res.g = fmin(res.g, 255);
	res.b = fmin(res.b, 255);
	return (res);
}

static bool	hit_shadow_object(t_ray ray, t_object *obj, t_hit *tmp_hit, double light_dist)
{
	if (obj->type == PLANE)
	{
		if(hit_plane(ray, (t_plane *)obj->element, tmp_hit))
			if (tmp_hit->t > 0 && tmp_hit->t < light_dist)
				return (true);
	}
	else if (obj->type == SPHERE)
	{
		if (hit_sphere(ray, (t_sphere *)obj->element, tmp_hit))
			if (tmp_hit->t > 0 && tmp_hit->t < light_dist)
				return (true);
	}
	else if (obj->type == CYLINDER)
	{
		if (hit_cylinder(ray, (t_cylinder *)obj->element, tmp_hit))
			if (tmp_hit->t > 0 && tmp_hit->t < light_dist)
				return (true);
	}
	return (false);
}

bool	is_in_shadow(t_scene *scene, t_vec3 p, t_vec3 light_dir)
{
	t_ray		shadow_ray;
	t_vec3		origin;
	t_object	*obj;
	t_hit		tmp_hit;
	double		light_dist;
	
	origin = vec3_add(p, vec3_scale(light_dir, EPSILON));
	shadow_ray.origin = origin;
	shadow_ray.direction = light_dir;
	light_dist = vec3_length(vec3_sub(scene->light->pos, p));
	obj = scene->objs;
	while(obj)
	{
		tmp_hit.t = INFINITY;
		if (hit_shadow_object(shadow_ray, obj, &tmp_hit, light_dist))
			return (true);
		obj = obj->next;
	}
	return (false);
}
/**
 *@brief 判断当前点是否被其他物体挡住了光源，如果是，就不计算漫反射光照
 *从命中点p出发，朝light_dir发射一条shadow_ray
 *检查是否有物体与这条光线相交
 *如果有，返回true，否则false
 */
//bool	is_in_shadow(t_scene *scene, t_vec3 p, t_vec3 light_dir)
//{
//	t_vec3		origin;
//	t_ray		shadow_ray;
//	t_object	*objs;
//	t_hit		tmp_hit;
//	double		light_dist;
//	//bool		hit_on;
//
//	//让shadow_ray的起点稍稍偏移，防止自己挡住自己
//	origin = vec3_add(p, vec3_scale(light_dir, EPSILON));
//	shadow_ray.origin = origin;
//	shadow_ray.direction = light_dir;
//	objs = scene->objs;
//
//	//hit_on = false;
//	light_dist = vec3_length(vec3_sub(scene->light->pos, p));
//	while (objs)
//	{
//		tmp_hit.t = INFINITY;
//		if (objs->type == PLANE)
//		{
//			if (hit_plane(shadow_ray, (t_plane *)objs->element, &tmp_hit))
//			{
//				if (tmp_hit.t > 0 && tmp_hit.t < light_dist)
//					return (true);
//			}
//		}
//		else if (objs->type == SPHERE)
//		{
//			if (hit_sphere(shadow_ray, (t_sphere *) objs->element, &tmp_hit))
//			{
//				if (tmp_hit.t > 0 && tmp_hit.t < light_dist)
//					return (true);
//			}
//		}
//		else if (objs->type == CYLINDER)
//		{
//			if (hit_cylinder(shadow_ray, (t_cylinder *) objs->element, &tmp_hit))
//			{
//				if (tmp_hit.t > 0 && tmp_hit.t < light_dist)
//					return (true);
//			}
//		}
//		objs = objs->next;
//
//	}
//	return (false);
//}
