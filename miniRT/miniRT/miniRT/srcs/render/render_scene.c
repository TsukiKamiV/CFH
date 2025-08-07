#include "../../includes/miniRT.h"

void	render_scene(t_scene *scene)
{
	t_image	*img;
	//t_object	*obj;
	t_point2	pixel;
	t_ray		ray;
	t_color		color;
	
	img = create_image(scene);
	if (!img)
		return ;
	pixel.y = 0;
	while (pixel.y < img->height)
	{
		pixel.x = 0;
		while (pixel.x < img->width)
		{
			ray = generate_ray(scene->cam, pixel, *img);
			color = trace_ray(ray, scene, pixel);
			put_pixel(img, pixel.x, img->height - 1 - pixel.y, color);
			pixel.x++;
		}
		pixel.y++;
	}
	mlx_put_image_to_window(scene->mlx_ptr, scene->win_ptr, img->img_ptr, 0, 0);
}
