#include "../../includes/miniRT.h"

void	render_scene(t_scene *scene)
{
	//t_image	*img;
	//t_object	*obj;
	t_point2	pixel;
	t_ray		ray;
	t_color		color;
	
	create_image(scene);
	//if (!img)
		//return ;
	//scene->img = img;
	pixel.y = 0;
	while (pixel.y < scene->img->height)
	{
		pixel.x = 0;
		//printf("%d\n", (pixel.y * 100)/(img->height - 1));
		while (pixel.x < scene->img->width)
		{
			ray = generate_ray(scene->cam, pixel, *(scene->img));
			color = trace_ray(ray, scene, pixel);
			put_pixel(scene->img, pixel.x, scene->img->height - 1 - pixel.y, color);
			pixel.x++;
		}
		pixel.y++;
	}
	mlx_put_image_to_window(scene->mlx_ptr, scene->win_ptr, scene->img->img_ptr, 0, 0);
}
