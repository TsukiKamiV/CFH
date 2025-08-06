#include "../../includes/miniRT.h"

t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	t_vec3	res;
	
	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return (res);
}

t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	t_vec3	res;
	
	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
	return (res);
}

t_vec3	vec3_scale(t_vec3 a, double s)
{
	t_vec3	res;
	
	res.x = a.x * s;
	res.y = a.y * s;
	res.z = a.z * s;
	return (res);
}

t_vec3	vec3_normalize(t_vec3 v)
{
	t_vec3	res;
	double	len;

	len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (len == 0)
	{
		res.x = 0;
		res.y = 0;
		res.z = 0;
	}
	else
	{
		res.x = v.x / len;
		res.y = v.y / len;
		res.z = v.z / len;
	}
	return (res);
}

/**
 * @brief 点积
 * 本质是“你站在向量b的方向上，a向这个方向“推进了多少”，即a在b上的投影长度
 *
 * 作用1:判断两个向量的夹角关系
 * if ret > 0 => 夹角 < 90°
 * if ret == 0 => 互相垂直
 * if ret < 0 => 夹角 > 90°
 *
 *作用2: 计算向量a在b方向上的投影长度
 */
double	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
