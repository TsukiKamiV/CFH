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
	
	scene->amb = malloc(sizeof(t_ambient));
	if (!scene->amb)
		close_program(scene, "Error: memory allocation failed.\n", EXIT_ERROR_MALLOC);
	if (ft_count_size(tokens) != 3)
		close_program(scene, "Error: invalid ambient parameter number.\n", EXIT_ERROR_PARAM);
	scene->amb->ratio = strtod(tokens[1], NULL);
	if (scene->amb->ratio < 0.0 || scene->amb->ratio > 1.0)
		close_program(scene, "Error: ambient ratio out of range.\n", EXIT_ERROR_PARAM);
	rgb = ft_split(tokens[2], ',');
	if (validate_assign_rgb(&scene->amb->color, rgb))
		close_program(scene, NULL, EXIT_ERROR_PARAM);
	free_tab(rgb);
	return (0);
}

//int	parse_ambient(char **tokens, t_scene *scene)
//{
//	char	**rgb;
//	int		i;
//
//	scene->amb = malloc(sizeof(t_ambient));
//	if (!scene->amb)
//		close_program(scene, "Error: memory allocation failed.\n", EXIT_ERROR_MALLOC);
//		//return (error_msg("memory allocation failed.", 1));
//	if (ft_count_size(tokens) != 3)
//		close_program(scene, "Error: invalid ambient parameter number.\n", EXIT_ERROR_PARAM);
//	//{
//	//	free(scene->amb);
//	//	return (error_msg("invalid ambient parameter.", 1));
//	//}
//	scene->amb->ratio = strtod(tokens[1], NULL);
//	if (scene->amb->ratio < 0.0 || scene->amb->ratio > 1.0)
//		close_program(scene, "Error: ambient ratio out of range.\n", EXIT_ERROR_PARAM);
//	rgb = ft_split(tokens[2], ',');
//	if (validate_assign_rgb(&scene->amb->color, rgb))
//	//if (!rgb || ft_count_size(rgb) != 3)
//		close_program(scene, NULL, EXIT_ERROR_PARAM);
//	//{
//	//	free(scene->amb);
//	//	return (error_msg("invalid ambient color format.", 1));
//	//}
//	//i = 0;
//	//while (i < 3)
//	//{
//	//	if (ft_atoi(rgb[i]) < 0 || ft_atoi(rgb[i]) > 255)
//	//		close_program(scene, "Error: ambient color component out of range.\n", EXIT_ERROR_PARAM);
//	//	//{
//	//	//	free(scene->amb);
//	//	//	return (error_msg("ambient color component out of range.", 1));
//	//	//}
//	//	i++;
//	//}
//	//scene->amb->color.r = ft_atoi(rgb[0]);
//	//scene->amb->color.g = ft_atoi(rgb[1]);
//	//scene->amb->color.b = ft_atoi(rgb[2]);
//	free_tab(rgb);
//	return (0);
//}

/**
 * Camera参数
 * C ([x, y, z] [xn, yn, zn] fov)
 *    位置            朝向       视角
 * 位置取值范围：任意实数
 * 朝向取值范围： -1.0 ～ 1.0 （必须是单位向量）
 * 视角：0 ～ 180（度）
 */

static int	parse_cam_pos_orientation(t_scene *scene, char **tokens, char ***pos, char ***orient)
{
	t_vec3	tmp_orient;
	
	*pos = ft_split(tokens[1], ',');
	*orient = ft_split(tokens[2], ',');
	if (!(*pos) || !(*orient) || ft_count_size(*pos) != 3 || ft_count_size(*orient) != 3)
	{
		free_multiple_tab(2, pos, orient);
		close_program(scene, "Error: invalid camera parameter formatting.\n", EXIT_ERROR_PARAM);
	}
	scene->cam->pos.x = atof((*pos)[0]);
	scene->cam->pos.y = atof((*pos)[1]);
	scene->cam->pos.z = atof((*pos)[2]);
	tmp_orient.x = atof((*orient)[0]);
	tmp_orient.y = atof((*orient)[1]);
	tmp_orient.z = atof((*orient)[2]);
	if (normal_is_unit(tmp_orient))
	{
		free_multiple_tab(2, pos, orient);
		close_program(scene, "Error: camera orient must be normalized.\n", EXIT_ERROR_PARAM);
	}
	scene->cam->orient = tmp_orient;
	return (0);
}

int	parse_camera(char **tokens, t_scene *scene)
{
	char	**pos;
	char	**orient;
	double	tmp_fov;
	//double	len;
	
	if (ft_count_size(tokens) != 4)
		close_program(scene, "Error: invalid camera parameter number.\n", EXIT_ERROR_PARAM);
	scene->cam = malloc(sizeof(t_camera));
	if (!scene->cam)
		close_program(scene, "Error: allocation failed for t_camera.\n", EXIT_ERROR_MALLOC);
	if (parse_cam_pos_orientation(scene, tokens, &pos, &orient))
		return (1);
	//len = vec3_length(scene->cam->orient);
	//if (len < 0.99 || len > 1.01)
	//{
	//if (normal_is_unit(scene->cam->orient))
	//{
	//	free_multiple_tab(2, pos, orient);
	//	close_program(scene, "Error: camera orientation must be normalized.\n", EXIT_ERROR_PARAM);
	//}
	tmp_fov = atof(tokens[3]);
	if (tmp_fov < 0.0 || tmp_fov > 180.0)
	{
		free_multiple_tab(2, pos, orient);
		close_program(scene, "Error: camera FOV out of range.\n", EXIT_ERROR_PARAM);
	}
	scene->cam->fov = tmp_fov;
	free_multiple_tab(2, pos, orient);
	return (0);
}

//int	parse_camera(char **tokens, t_scene *scene)
//{
//	char	**pos;
//	char	**orient;
//	double	len;
//
//	if (ft_count_size(tokens) != 4)
//		close_program(scene, "Error: invalid camera parameter number.\n", EXIT_ERROR_PARAM);
//		//return (error_msg("invalid camera parameter count.", 1));
//	scene->cam = malloc(sizeof(t_camera));
//	if (!scene->cam)
//		close_program(scene, "Error: allocation failed for t_camera.\n", EXIT_ERROR_MALLOC);
//		//return (error_msg("memory allocation failed", 1));
//	if (parse_cam_pos_orientation(scene, tokens, &pos, &orient))
//		return (1);
//	//pos = ft_split(tokens[1], ',');
//	//orient = ft_split(tokens[2], ',');
//	//if (!pos || !orient || ft_count_size(pos) != 3 || ft_count_size(orient) != //3)
//	//{
//	//	if (pos)
//	//		free_tab(pos);
//	//	if (orient)
//	//		free_tab(orient);
//	//	return (error_msg("invalid camera parameter.", 1));
//	//}
//	//scene->cam->pos.x = atof(pos[0]);
//	//scene->cam->pos.y = atof(pos[1]);
//	//scene->cam->pos.z = atof(pos[2]);
//	//scene->cam->orient.x = atof(orient[0]);
//	//scene->cam->orient.y = atof(orient[1]);
//	//scene->cam->orient.z = atof(orient[2]);
//
//	//len = sqrt(scene->cam->orient.x * scene->cam->orient.x + \
//			   scene->cam->orient.y * scene->cam->orient.y + \
//			   scene->cam->orient.z * scene->cam->orient.z);
//	len = vec3_length(scene->cam->orient);
//	if (len < 0.99 || len > 1.01)
//	{
//		//free_tab(pos);
//		//free_tab(orient);
//		//return (error_msg("camera orientation must be normalized.", 1));
//		free_multiple_tab(2, pos, orient);
//		close_program(scene, "Error: camera orientation must be normalized.\n", EXIT_ERROR_PARAM);
//	}
//	scene->cam->fov = atof(tokens[3]);
//	if (scene->cam->fov < 0.0 || scene->cam->fov > 180.0)
//	{
//		free_multiple_tab(2, pos, orient);
//		close_program(scene, "Error: camera FOV out of range.\n", EXIT_ERROR_PARAM);
//		//free_tab(pos);
//		//free_tab(orient);
//		//return (error_msg("camera FOV out of range", 1));
//	}
//	free_multiple_tab(2, pos, orient);
//	//free_tab(pos);
//	//free_tab(orient);
//	return (0);
//}

static int	parse_light_pos_color(t_scene *scene, char **tokens, char ***pos, char ***rgb)
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
		close_program(scene, "Error: invalid light parameter.\n", EXIT_ERROR_PARAM);
		//return (error_msg("invalid light parameter.", 1));
	}
	return (0);
}

static void	assign_light_pos(t_light *light, char **pos)
{
	light->pos.x = atof(pos[0]);
	light->pos.y = atof(pos[1]);
	light->pos.z = atof(pos[2]);
}

static int	validate_light_ratio(t_scene *scene, char *s, double *out_ratio)
{
	double	val;
	
	val = strtod(s, NULL);
	if (val < 0.0 || val > 1.0)
		close_program(scene, "Error: light ratio out of range.\n", EXIT_ERROR_PARAM);
		//return (error_msg("light ratio out of range.", 1));
	*out_ratio = val;
	return (0);
}

int	parse_light(char **tokens, t_scene *scene)
{
	char	**pos;
	char	**rgb;
	double	ratio;

	if (ft_count_size(tokens) != 4)
		close_program(scene, "Error: invalid light parameter number.\n", EXIT_ERROR_PARAM);
	scene->light = malloc(sizeof(t_light));
	if (!scene->light)
		close_program(scene, "Error: allocation failed for t_light.\n", EXIT_ERROR_MALLOC);
	parse_light_pos_color(scene, tokens, &pos, &rgb);
	assign_light_pos(scene->light, pos);
	if (validate_light_ratio(scene, tokens[2], &ratio))
	{
		free_multiple_tab(2, pos, rgb);
		close_program(scene, NULL, EXIT_ERROR_PARAM);
	}
	scene->light->ratio = ratio;
	if (validate_assign_rgb(&scene->light->color, rgb))
	{
		free_multiple_tab(2, pos, rgb);
		close_program(scene, NULL, EXIT_ERROR_PARAM);
	}
	free_multiple_tab(2, pos, rgb);
	return (0);
}


//int	parse_light(char **tokens, t_scene *scene)
//{
//	char	**pos;
//	char	**rgb;
//	//int		i;
//	double	ratio;
//	char	**tabs[3];
//
//	if (ft_count_size(tokens) != 4)
//		close_program(scene, "Error: invalid light parameter number.\n", EXIT_ERROR_PARAM);
//		//return (error_msg("invalid light parameter.", 1));
//	scene->light = malloc(sizeof(t_light));
//	if (!scene->light)
//		close_program(scene, "Error: allocation failed for t_light.\n", EXIT_ERROR_MALLOC);
//		//return (error_msg("light allocation failed.", 1));
//	//if (parse_light_pos_color(scene, tokens, &pos, &rgb))
//	//{
//	//	free(scene->light);
//	//	scene->light = NULL;
//	//	return (1);
//	//}
//	parse_light_pos_color(scene, tokens, &pos, &rgb);
//	assign_light_pos(scene->light, pos);
//	tabs[0] = pos;
//	tabs[1] = rgb;
//	tabs[2] = NULL;
//	validate_light_ratio(scene, tokens[2], &ratio);
//	//pos = ft_split(tokens[1], ',');
//	//rgb = ft_split(tokens[3], ',');
//	//if (!pos || !rgb || ft_count_size(pos) != 3 || ft_count_size(rgb) != 3)
//	//{
//	//	//if (pos)
//	//	//	free_tab(pos);
//	//	//if (rgb)
//	//	//	free_tab(rgb);
//	//	free_multiple_tab(2, pos, rgb);
//	//	return (error_msg("invalid light parameter.", 1));
//	//}
//	//scene->light->pos.x = atof(pos[0]);
//	//scene->light->pos.y = atof(pos[1]);
//	//scene->light->pos.z = atof(pos[2]);
//	if (validate_light_ratio(scene, tokens[2], &ratio))
//	{
//		free_multiple_tab(2, pos, rgb);
//		free(scene->light);
//		scene->light = NULL;
//		return (1);
//	}
//	//ratio = strtod(tokens[2], NULL);
//	//if (ratio < 0.0 || ratio > 1.0)
//	//{
//	//	free_tab(pos);
//	//	free_tab(rgb);
//	//	return (error_msg("light ratio out of range.", 1));
//	//}
//	scene->light->ratio = ratio;
//	if (validate_assign_rgb(&scene->light->color, rgb))
//	{
//		free_multiple_tab(2, pos, rgb);
//		free(scene->light);
//		scene->light = NULL;
//		return (1);
//	}
//	//i = 0;
//	//while (i < 3)
//	//{
//	//	if (ft_atoi(rgb[i]) < 0 || ft_atoi(rgb[i]) > 255)
//	//	{
//	//		free_tab(pos);
//	//		free_tab(rgb);
//	//		return (error_msg("light color component out of range.", 1));
//	//	}
//	//	i++;
//	//}
//	//scene->light->color.r = ft_atoi(rgb[0]);
//	//scene->light->color.g = ft_atoi(rgb[1]);
//	//scene->light->color.b = ft_atoi(rgb[2]);
//	//free_tab(pos);
//	//free_tab(rgb);
//	free_multiple_tab(2, pos, rgb);
//	return (0);
//}
