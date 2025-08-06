#include "../../includes/miniRT.h"


/**
 *返回两个向量的叉积结果（即垂直于这两个向量的向量）
 */
t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	t_vec3	res;
	
	res.x = a.y * b.z - a.z * b.y;
	res.y = a.z * b.x - a.x * b.z;
	res.z = a.x * b.y - a.y * b.x;
	return (res);
}

double	vec3_length(t_vec3 v)
{
	double	len;
	
	len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	return (len);
}
