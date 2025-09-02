#include "../../includes/miniRT.h"

//t_image	*create_image(t_scene *scene)
//{
//	t_image	*img;
//
//	img = malloc(sizeof(t_image));
//	if (!img)
//	{
//		ft_putstr_fd("Error\nFailed to malloc image.", 1);
//		return (NULL);
//	}
//	//img->width = scene->width;
//	//img->height = scene->height;
//	img->width = 800;
//	img->height = 600;
//	img->img_ptr = mlx_new_image(scene->mlx_ptr, img->width, img->height);
//	if (!img->img_ptr)
//	{
//		ft_putstr_fd("Error\nFailed to create image.", 1);
//		free (img);
//		return (NULL);
//	}
//	//mlx_get_data_addr返回通过mlx_new_image()创建的图像数据的起始地址（即第一个像素的地址），同时提供每像素大小、每行长度、端序等信息）
//	//line_length 每一行的字节数（通常是宽度x4)
//	//bits_per_pixel 每个像素的位数（通常是32）
//	//endian 系统大小端模式（影响颜色字节顺序）
//	img->addr = mlx_get_data_addr(img->img_ptr, &img->bits_per_pixel, &img->line_length, &img->endian);
//	return (img);
//}

t_image	*create_image(t_scene *scene)
{
	t_image	*img;
	
	img = malloc(sizeof(t_image));
	if (!img)
	{
		ft_putstr_fd("Error\nFailed to malloc image.", 1);
		return (NULL);
	}
	/* 你也可以改成使用 scene->width/height */
	img->width = 800;
	img->height = 600;
	img->img_ptr = mlx_new_image(scene->mlx_ptr, img->width, img->height);
	if (!img->img_ptr)
	{
		ft_putstr_fd("Error\nFailed to create image.", 1);
		free(img);
		return (NULL);
	}
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bits_per_pixel, &img->line_length, &img->endian);
	
	/* 将当前图像托管给 scene，便于统一在退出时销毁 */
	scene->img = img;
	return (img);
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
