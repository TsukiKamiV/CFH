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
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bits_per_pixel, \
								  &img->line_length, &img->endian);
	scene->img = img;
	return ;
}

void	put_pixel(t_image *img, int x, int y, t_color color)
{
	char	*dst;
	unsigned int	packed_color;
	
	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	packed_color = (color.r << 16) | (color.g << 8) | color.b;
	//在第y行->第x个像素->写入4字节的颜色值
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
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
