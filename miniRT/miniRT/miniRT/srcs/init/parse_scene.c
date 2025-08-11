#include "../../includes/miniRT.h"

/**
 *ambient环境光参数：
 * A <ratio> <R.G.B>
 * ratio取值范围：0.0 ～ 1.0
 * rgb范围 0 ～ 255 （含）
 */

int	parse_ambient(char **tokens, t_scene *scene)
{
	char	**rgb;
	int		i;
	
	scene->amb = malloc(sizeof(t_ambient));
	if (!scene->amb)
		return (error_msg("memory allocation failed.", 1));
	if (ft_count_size(tokens) != 3)
	{
		free(scene->amb);
		return (error_msg("invalid ambient parameter.", 1));
	}
	scene->amb->ratio = strtod(tokens[1], NULL);
	rgb = ft_split(tokens[2], ',');
	if (!rgb || ft_count_size(rgb) != 3)
	{
		free(scene->amb);
		return (error_msg("invalid ambient color format.", 1));
	}
	i = 0;
	while (i < 3)
	{
		if (ft_atoi(rgb[i]) < 0 || ft_atoi(rgb[i]) > 255)
		{
			free(scene->amb);
			return (error_msg("ambient color component out of range.", 1));
		}
		i++;
	}
	scene->amb->color.r = ft_atoi(rgb[0]);
	scene->amb->color.g = ft_atoi(rgb[1]);
	scene->amb->color.b = ft_atoi(rgb[2]);
	free_tab(rgb);
	return (0);
}

/**
 * Camera参数
 * C ([x, y, z] [xn, yn, zn] fov)
 *    位置            朝向       视角
 * 位置取值范围：任意实数
 * 朝向取值范围： -1.0 ～ 1.0 （必须是单位向量）
 * 视角：0 ～ 180（度）
 */

static int	validate_camera_tokens(char **tokens)
{
	if (ft_count_size(tokens) != 4)
		return (error_msg("invalid camera parameter count.", 1));
	return (0);
}

static int	parse_cam_pos_orientation(t_scene *scene, char **tokens, char ***pos, char ***orient)
{
	*pos = ft_split(tokens[1], ',');
	*orient = ft_split(tokens[2], ',');
	if (!(*pos) || !(*orient) || ft_count_size(*pos) != 3 || ft_count_size(*orient) != 3)
	{
		if (*pos)
			free_tab(*pos);
		if (*orient)
			free_tab(*orient);
		return (error_msg("invalid camera parameter.", 1));
	}
	scene->cam->pos.x = atof((*pos)[0]);
	scene->cam->pos.y = atof((*pos)[1]);
	scene->cam->pos.z = atof((*pos)[2]);
	scene->cam->orient.x = atof((*orient)[0]);
	scene->cam->orient.y = atof((*orient)[1]);
	scene->cam->orient.z = atof((*orient)[2]);
	return (0);
}

int	parse_camera(char **tokens, t_scene *scene)
{
	char	**pos;
	char	**orient;
	double	len;
	
	if (ft_count_size(tokens) != 4)
		return (error_msg("invalid camera parameter count.", 1));
	scene->cam = malloc(sizeof(t_camera));
	if (!scene->cam)
		return (error_msg("memory allocation failed", 1));
	if (parse_cam_pos_orientation(scene, tokens, &pos, &orient))
		return (1);
	//pos = ft_split(tokens[1], ',');
	//orient = ft_split(tokens[2], ',');
	//if (!pos || !orient || ft_count_size(pos) != 3 || ft_count_size(orient) != //3)
	//{
	//	if (pos)
	//		free_tab(pos);
	//	if (orient)
	//		free_tab(orient);
	//	return (error_msg("invalid camera parameter.", 1));
	//}
	//scene->cam->pos.x = atof(pos[0]);
	//scene->cam->pos.y = atof(pos[1]);
	//scene->cam->pos.z = atof(pos[2]);
	//scene->cam->orient.x = atof(orient[0]);
	//scene->cam->orient.y = atof(orient[1]);
	//scene->cam->orient.z = atof(orient[2]);
	
	//len = sqrt(scene->cam->orient.x * scene->cam->orient.x + \
			   scene->cam->orient.y * scene->cam->orient.y + \
			   scene->cam->orient.z * scene->cam->orient.z);
	len = vec3_length(scene->cam->orient);
	if (len < 0.99 || len > 1.01)
	{
		free_tab(pos);
		free_tab(orient);
		return (error_msg("camera orientation must be normalized.", 1));
	}
	scene->cam->fov = atof(tokens[3]);
	if (scene->cam->fov < 0.0 || scene->cam->fov > 180.0)
	{
		free_tab(pos);
		free_tab(orient);
		return (error_msg("camera FOV out of range", 1));
	}
	free_tab(pos);
	free_tab(orient);
	return (0);
}

static int	parse_light_pos_color(char **tokens, char ***pos, char ***rgb)
{
	int	ok;
	
	ok = 1;
	*pos = NULL;
	*rgb = NULL;
	*pos = ft_split(tokens[1], ',');
	*rgb = ft_split(tokens[3], ',');
	if (!(*pos) || !(*rgb))
		ok = 0;
	if (ok && (ft_count_size(*pos) != 3 || ft_count_size(*rgb) != 3))
		ok = 0;
	if (!ok)
	{
		free_multiple_tab(2, *pos, *rgb);
		return (error_msg("invalid light parameter.", 1));
	}
	return (0);
}

static void	assign_light_pos(t_light *light, char **pos)
{
	light->pos.x = atof(pos[0]);
	light->pos.y = atof(pos[1]);
	light->pos.z = atof(pos[2]);
}

static int	validate_light_ratio(char *s, double *out_ratio)
{
	double	val;
	
	val = strtod(s, NULL);
	if (val < 0.0 || val > 1.0)
		return (error_msg("light ratio out of range.", 1));
	*out_ratio = val;
	return (0);
}

int	parse_light(char **tokens, t_scene *scene)
{
	char	**pos;
	char	**rgb;
	//int		i;
	double	ratio;
	
	if (ft_count_size(tokens) != 4)
		return (error_msg("invalid light parameter.", 1));
	scene->light = malloc(sizeof(t_light));
	if (!scene->light)
		return (error_msg("light allocation failed.", 1));
	if (parse_light_pos_color(tokens, &pos, &rgb))
	{
		free(scene->light);
		scene->light = NULL;
		return (1);
	}
	assign_light_pos(scene->light, pos);
	//pos = ft_split(tokens[1], ',');
	//rgb = ft_split(tokens[3], ',');
	//if (!pos || !rgb || ft_count_size(pos) != 3 || ft_count_size(rgb) != 3)
	//{
	//	//if (pos)
	//	//	free_tab(pos);
	//	//if (rgb)
	//	//	free_tab(rgb);
	//	free_multiple_tab(2, pos, rgb);
	//	return (error_msg("invalid light parameter.", 1));
	//}
	//scene->light->pos.x = atof(pos[0]);
	//scene->light->pos.y = atof(pos[1]);
	//scene->light->pos.z = atof(pos[2]);
	if (validate_light_ratio(tokens[2], &ratio))
	{
		free_multiple_tab(2, pos, rgb);
		free(scene->light);
		scene->light = NULL;
		return (1);
	}
	//ratio = strtod(tokens[2], NULL);
	//if (ratio < 0.0 || ratio > 1.0)
	//{
	//	free_tab(pos);
	//	free_tab(rgb);
	//	return (error_msg("light ratio out of range.", 1));
	//}
	scene->light->ratio = ratio;
	if (validate_assign_rgb(&scene->light->color, rgb))
	{
		free_multiple_tab(2, pos, rgb);
		free(scene->light);
		scene->light = NULL;
		return (1);
	}
	//i = 0;
	//while (i < 3)
	//{
	//	if (ft_atoi(rgb[i]) < 0 || ft_atoi(rgb[i]) > 255)
	//	{
	//		free_tab(pos);
	//		free_tab(rgb);
	//		return (error_msg("light color component out of range.", 1));
	//	}
	//	i++;
	//}
	//scene->light->color.r = ft_atoi(rgb[0]);
	//scene->light->color.g = ft_atoi(rgb[1]);
	//scene->light->color.b = ft_atoi(rgb[2]);
	//free_tab(pos);
	//free_tab(rgb);
	free_multiple_tab(2, pos, rgb);
	return (0);
}
