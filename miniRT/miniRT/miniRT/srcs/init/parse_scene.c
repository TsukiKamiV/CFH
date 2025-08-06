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
	{
		ft_putstr_fd("Error\nAmbient allocation failed.\n", 2);
		return (1);
	}
	if (ft_count_size(tokens) != 3)
	{
		ft_putstr_fd("Error\nInvalid ambient parameter.\n", 2);
		return (1);
	}
	scene->amb->ratio = strtod(tokens[1], NULL);
	rgb = ft_split(tokens[2], ',');
	if (!rgb || ft_count_size(rgb) != 3)
	{
		ft_putstr_fd("Error\nInvalid ambient color format.\n", 2);
		return (1);
	}
	i = 0;
	while (i < 3)
	{
		if (ft_atoi(rgb[i]) < 0 || ft_atoi(rgb[i]) > 255)
		{
			ft_putstr_fd("Error\nAmbient color component out of range.\n", 2);
			return (1);
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

int	parse_camera(char **tokens, t_scene *scene)
{
	char	**pos;
	char	**orient;
	//int		i;
	double	len;
	
	if (ft_count_size(tokens) != 4)
	{
		ft_putstr_fd("Error\nInvalid camera parameter count.\n", 2);
		return (1);
	}
	scene->cam = malloc(sizeof(t_camera));
	if (!scene->cam)
	{
		ft_putstr_fd("Error\nCamera allocatoin failed.\n", 2);
		return (1);
	}
	pos = ft_split(tokens[1], ',');
	orient = ft_split(tokens[2], ',');
	if (!pos || !orient || ft_count_size(pos) != 3 || ft_count_size(orient) != 3)
	{
		ft_putstr_fd("Error\nInvalid camera parameter.\n", 2);
		if (pos)
			free_tab(pos);
		if (orient)
			free_tab(orient);
		return (1);
	}
	scene->cam->pos.x = atof(pos[0]);
	scene->cam->pos.y = atof(pos[1]);
	scene->cam->pos.z = atof(pos[2]);
	scene->cam->orient.x = atof(orient[0]);
	scene->cam->orient.y = atof(orient[1]);
	scene->cam->orient.z = atof(orient[2]);
	
	
	len = sqrt(scene->cam->orient.x * scene->cam->orient.x + \
			   scene->cam->orient.y * scene->cam->orient.y + \
			   scene->cam->orient.z * scene->cam->orient.z);
	if (len < 0.99 || len > 1.01)
	{
		ft_putstr_fd("Error\nCamera orientation must be normalized.\n", 2);
		free_tab(pos);
		free_tab(orient);
		return (1);
	}
	
	scene->cam->fov = atof(tokens[3]);
	if (scene->cam->fov < 0.0 || scene->cam->fov > 180.0)
	{
		ft_putstr_fd("Error\nCamera FOV out of range.\n", 2);
		free_tab(pos);
		free_tab(orient);
		return (1);
	}
	free_tab(pos);
	free_tab(orient);
	return (0);
}

int	parse_light(char **tokens, t_scene *scene)
{
	char	**pos;
	char	**rgb;
	int		i;
	double	ratio;
	
	if (ft_count_size(tokens) != 4)
	{
		ft_putstr_fd("Error\nInvalid light parameter.\n", 2);
		return (1);
	}
	scene->light = malloc(sizeof(t_light));
	if (!scene->light)
	{
		ft_putstr_fd("Error\nLight allocation failed.\n", 2);
		return (1);
	}
	pos = ft_split(tokens[1], ',');
	rgb = ft_split(tokens[3], ',');
	if (!pos || !rgb || ft_count_size(pos) != 3 || ft_count_size(rgb) != 3)
	{
		ft_putstr_fd("Error\nInvalid light parameter.\n", 2);
		if (pos)
			free_tab(pos);
		if (rgb)
			free_tab(rgb);
		return (1);
	}
	scene->light->pos.x = atof(pos[0]);
	scene->light->pos.y = atof(pos[1]);
	scene->light->pos.z = atof(pos[2]);
	
	ratio = strtod(tokens[2], NULL);
	if (ratio < 0.0 || ratio > 1.0)
	{
		ft_putstr_fd("Error\nLight ratio out of range.\n", 2);
		free_tab(pos);
		free_tab(rgb);
		return (1);
	}
	scene->light->ratio = ratio;
	i = 0;
	while (i < 3)
	{
		if (ft_atoi(rgb[i]) < 0 || ft_atoi(rgb[i]) > 255)
		{
			ft_putstr_fd("Error\nLight color component out of range.\n", 2);
			free_tab(pos);
			free_tab(rgb);
			return (1);
		}
		i++;
	}
	scene->light->color.r = ft_atoi(rgb[0]);
	scene->light->color.g = ft_atoi(rgb[1]);
	scene->light->color.b = ft_atoi(rgb[2]);
	
	free_tab(pos);
	free_tab(rgb);
	return (0);
}
