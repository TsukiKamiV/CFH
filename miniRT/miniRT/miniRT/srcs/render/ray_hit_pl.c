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
	if (fabs(denom) > 1e-6)//这是科学计数法，表示 1 \times 10^{-6}，即：0.000001 （由于浮点数运算可能不会精确等于 0（而是一个非常接近 0 的小数））是“避免除以0的技巧”
	{
		//p010 = 平面上的点 - 光线的起点;
		//计算结果是一个方向向量，也就是：从光线起点指向平面的一点。
		p010 = vec3_sub(pl->point, ray.origin);
		//📌 目的：计算射线与平面交点的参数 t
		//•	p010 = pl->point - ray.origin 表示从光线起点到平面上任意一点的向量。
		t = vec3_dot(p010, pl->normal) / denom;
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
