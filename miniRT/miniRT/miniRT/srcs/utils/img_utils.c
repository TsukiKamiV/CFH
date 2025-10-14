/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:05:13 by luxu              #+#    #+#             */
/*   Updated: 2025/09/10 16:06:09 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	create_image(t_scene *scene)
{
	t_image	*img;

	img = malloc(sizeof(t_image));
	if (!img)
		close_program(scene, "malloc failed: image", ERR_MALLOC);
	img->width = 800;
	img->height = 600;
	img->img_ptr = mlx_new_image(scene->mlx_ptr, img->width, img->height);
	if (!img->img_ptr)
	{
		free (img);
		close_program(scene, "failed to create image", ERR_MLX);
	}
	img->addr = mlx_get_data_addr(img->img_ptr, \
			&img->bits_per_pixel, &img->line_length, &img->endian);
	scene->img = img;
	return ;
}

/**
 *RGB 占 3 字节
 *第四个字节用来做 padding（对齐） 或 Alpha 通道
 *Alpha 通道：有些图形库会把第 4 个字节当作透明度（A），所以格式是 ARGB 或 BGRA。
 *内存对齐：即使不用 Alpha，很多显卡和图形 API 也会要求每个像素占 4 字节，方便 CPU/GPU 在内存里读取（因为 4 字节正好是 32bit，对齐更快）。
 *如果只用 24bit，一个像素就是 3 字节，那一行像素可能不是 4 的倍数，就会导致访问效率下降。
 *在 MiniLibX 里，具体是 BGRA 格式（B 在低字节，A 在最高字节)
 */
void	put_pixel(t_image *img, int x, int y, t_color color)
{
	char			*dst;
	unsigned int	packed_color;
	
	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	packed_color = (color.r << 16) | (color.g << 8) | color.b;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));//32，除以 8 得到字节数（即 4）
	*(unsigned int *)dst = packed_color;
}

t_color	create_color(int r, int g, int b)
{
	t_color	res;

	res.r = r;
	res.g = g;
	res.b = b;
	return (res);
}
