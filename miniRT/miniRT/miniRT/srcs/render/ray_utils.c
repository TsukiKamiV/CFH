#include "../../includes/miniRT.h"

/**
 *@brief 给定一条射线 ray 和参数 t，返回这条射线从起点出发沿着方向走 t 单位后的位置向量（即交点的位置）。
 */
t_vec3	ray_at(t_ray ray, double t)
{
	return (vec3_add(ray.origin, vec3_scale(ray.direction, t)));
}
