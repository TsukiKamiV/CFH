/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:58:35 by luxu              #+#    #+#             */
/*   Updated: 2025/09/08 14:59:06 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static int	init_mlx_and_window(t_scene *scene)
{
	scene->mlx_ptr = mlx_init();
	if (!scene->mlx_ptr)
		return (error_msg("mlx initiation failed", 1));
	scene->win_ptr = mlx_new_window(scene->mlx_ptr, 800, 600, "miniRT");
	if (!scene->win_ptr)
		return (error_msg("window initiation failed", 1));
	return (0);
}

static int	load_rt_file(const char *filename, t_scene *scene)
{
	int			ok;
	t_params	ls;

	ok = read_all_lines(filename, &ls);
	if (!ok)
		return (0);
	ok = parse_scene_from_lines(&ls, scene);
	if (!ok)
	{
		free_lines(&ls);
		return (0);
	}
	free_lines(&ls);
	return (1);
}

int	verify_arg(int argc, char *argv[])
{
	size_t	argv_len;

	if (argc != 2)
		return (1);
	argv_len = ft_strlen(argv[1]);
	if (!ft_strnstr(&argv[1][argv_len - 3], ".rt", 3))
		return (1);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_scene		*scene;

	if (verify_arg(argc, argv))
		return (error_msg("usage: ./miniRT scene.rt", 1));
	scene = malloc(sizeof(t_scene));
	if (!scene)
		return (error_msg("memory allocation failed", 1));
	ft_memset(scene, 0, sizeof(t_scene));
	if (!load_rt_file(argv[1], scene))
		return (close_program(scene, NULL, EXIT_ERROR_FILE));
	if (init_mlx_and_window(scene))
		return (close_program(scene, NULL, EXIT_ERROR_MLX));
	render_scene(scene);
	mlx_key_hook(scene->win_ptr, ft_key_hook, scene);
	mlx_hook(scene->win_ptr, 17, 0, my_mlx_hook_callback, scene);
	mlx_loop(scene->mlx_ptr);
	return (0);
}
