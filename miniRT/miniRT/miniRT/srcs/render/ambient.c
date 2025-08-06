#include "../../includes/miniRT.h"


/**
 *@brief ambient （环境光）是对场景中所有可见物体颜色的一个基础“整体亮度”贡献，它不受光源方向、阴影等影响
 *渲染的最终颜色 = 物体颜色 x 环境光颜色 x 环境光强度
 *
 */

t_color	compute_ambient(t_color obj_color, t_scene *scene)
{
	t_color	res;
	
	res.r = obj_color.r * scene->amb->ratio * (scene->amb->color.r / 255.0);
	res.g = obj_color.g * scene->amb->ratio * (scene->amb->color.g / 255.0);
	res.b = obj_color.b * scene->amb->ratio * (scene->amb->color.b / 255.0);
	if (res.r > 255)
		res.r = 255;
	if (res.g > 255)
		res.g = 255;
	if (res.b > 255)
		res.b = 255;
	return (res);
}
