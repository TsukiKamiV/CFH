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
	t_vec3	p010;//用于存储从光线原点指向平面上一点的方向向量
	double	t;//交点在光线上的参数
	
	denom = vec3_dot(pl->normal, ray.direction);
	//printf("denom = %f\n", denom);
	if (fabs(denom) > 1e-6)//这是科学计数法，表示 1 \times 10^{-6}，即：0.000001 （由于浮点数运算可能不会精确等于 0（而是一个非常接近 0 的小数））是“避免除以0的技巧”
	{
		//p010 = 平面上的点 - 光线的起点;
		//计算结果是一个方向向量，也就是：从光线起点指向平面的一点。
		p010 = vec3_sub(pl->point, ray.origin);
		//📌 目的：计算射线与平面交点的参数 t
		//•	p010 = pl->point - ray.origin 表示从光线起点到平面上任意一点的向量。
		t = vec3_dot(p010, pl->normal) / denom;
		//printf("t = %f\n", t);
		if (t >= 0)
		{
			hit->t = t;
			hit->point = vec3_add(ray.origin, vec3_scale(ray.direction, t));
			hit->normal = vec3_normalize(pl->normal);
			hit->color = pl->color;
			return (1);
		}
	}
	return (0);
}

int	hit_sphere(t_ray ray, t_sphere *sphere, t_hit *hit)
{
	t_vec3	oc;//从球心指向光线起点的向量（是后续计算中用到的中间变量）
	double	a;//方向向量的长度平方（如果ray.direction是单位向量，a = 1)
	double	b;//二元一次方程中一次项的系数
	double	c;//c = |\vec{OC}|^2 - r^2，即光线起点距离球心的平方减去半径平方。c < 0 时，说明光线起点在球体内部。
	double	discriminant;//discriminant = b * b - 4 * a * c; 即delta
	double	t;
	
	oc = vec3_sub(ray.origin, sphere->center);
	a = vec3_dot(ray.direction, ray.direction);
	b = 2.0 * vec3_dot(oc, ray.direction);
	c = vec3_dot(oc, oc) - sphere->radius * sphere->radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (0);
	t = (-b - sqrt(discriminant)) / (2.0 * a);
	//printf("t = %f\n", t);
	if (t < 0)
	{
		t = (-b + sqrt(discriminant)) / (2.0 * a);
		//if (t < 1e-6)
		return (0);
	}
	hit->t = t;
	hit->point = vec3_add(ray.origin, vec3_scale(ray.direction,t));
	hit->normal = vec3_normalize(vec3_sub(hit->point, sphere->center));
	hit->color = sphere->color;
	hit->obj = NULL;
	return (1);
}

/**
 *@brief核心算法概念：光线在圆柱体轴方向的正交投影与轴之间的距离为cy->radius
 */

int	hit_cylinder_body(t_ray ray, t_cylinder *cy, t_hit *hit)
{
	//光线起点到圆柱中心的向量，目的是建立光线与圆柱体之间的位置关系（起点偏移）
	t_vec3	oc;
	//把光线方向ray.direction去掉了沿圆柱轴方向的分量，得到的是光线在圆柱体横截面平面内的投影
	//因为圆柱体是围绕轴“旋转”的，我们要判断光线是否穿过“侧壁”，所以要看光线方向在圆柱体横截面（垂直于轴的平面）上的投影
	t_vec3	d;
	//起点在横截面平面中的位置
	t_vec3	oc_p;
	//
	t_vec3	projection;
	t_vec3	h;
	double	height_proj;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	t;
	
	oc = vec3_sub(ray.origin, cy->centre);
	//printf("oc: (%f, %f, %f)\n", oc.x, oc.y, oc.z);
	d = vec3_sub(ray.direction, vec3_scale(cy->axis, vec3_dot(ray.direction, cy->axis)));
	//printf("d: (%f, %f, %f)\n", d.x, d.y, d.z);
	//把光线起点偏移向量oc去掉了沿轴方向的分量
	oc_p = vec3_sub(oc, vec3_scale(cy->axis, vec3_dot(oc, cy->axis)));
	//printf("oc_p: (%f, %f, %f)\n", oc_p.x, oc_p.y, oc_p.z);
	a = vec3_dot(d, d);
	//printf("a: %f\n", a);
	b = 2 * vec3_dot(d, oc_p);
	//printf("b: %f\n", b);
	c = vec3_dot(oc_p, oc_p) - cy->radius * cy->radius;
	//printf("c: %f\n", c);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (0);
	t = (-b - sqrt(discriminant)) / (2.0 * a);
	if (t < 1e-6)
	{
		t = (-b + sqrt(discriminant)) / (2.0 * a);
		if (t < 1e-6)
			return (0);
	}
	hit->t = t;
	hit->color = cy->color;
	hit->point = ray_at(ray, t);
	h = vec3_sub(hit->point, cy->centre);
	height_proj = vec3_dot(h, cy->axis);
	if (height_proj < -cy->height / 2.0 || height_proj > cy->height / 2.0)
		return (0);
	projection = vec3_add(cy->centre, vec3_scale(cy->axis, vec3_dot(vec3_sub(hit->point, cy->centre), cy->axis)));
	hit->normal = vec3_normalize(vec3_sub(hit->point, projection));
	return (1);
}

int	hit_cylinder_cap(t_ray ray, t_cylinder *cy, t_hit *hit)
{
	t_vec3	cap_centers[2];
	t_vec3	p010;
	t_vec3	intersection;
	t_vec3	to_point;
	double	denom;
	double	t;
	double	radius_squared;
	int 	i;
	
	radius_squared = cy->radius * cy->radius;
	cap_centers[0] = vec3_add(cy->centre, vec3_scale(cy->axis, cy->height / 2.0));//top
	cap_centers[1] = vec3_sub(cy->centre, vec3_scale(cy->axis, cy->height / 2.0));//bottom
	i = 0;
	while (i < 2)
	{
		denom = vec3_dot(cy->axis, ray.direction);
		if (fabs(denom) > 1e-6)
		{
			p010 = vec3_sub(cap_centers[i], ray.origin);
			t = vec3_dot(p010, cy->axis) / denom;
			if(t > 1e-6 && t < hit->t)
			{
				intersection = vec3_add(ray.origin, vec3_scale(ray.direction, t));
				to_point = vec3_sub(intersection, cap_centers[i]);
				if (vec3_dot(to_point, to_point) <= radius_squared)
				{
					hit->t = t;
					hit->point = intersection;
					if (i == 0)
						hit->normal = cy->axis;
					else
						hit->normal = vec3_scale(cy->axis, -1);
					hit->normal = vec3_normalize(hit->normal);
					hit->color = cy->color;
					return (1);
				}
			}
		}
		i++;
	}
	return (0);
}
int	hit_cylinder(t_ray ray, t_cylinder *cy, t_hit *hit)
{
	t_hit	tmp_hit;
	int		hit_anything;
	
	hit_anything = 0;
	tmp_hit.t = INFINITY;
	if (hit_cylinder_body(ray, cy, &tmp_hit))
		hit_anything = 1;
	if (hit_cylinder_cap(ray, cy, &tmp_hit))
		hit_anything = 1;
	if (hit_anything)
	{
		*hit = tmp_hit;
		hit->obj = (void *)cy;
		return (1);
	}
	return (0);
}
