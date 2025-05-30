#include "../../includes/miniRT.h"

void	render_scene(t_scene *scene)
{
	t_image	*img;
	int		x;
	int		y;
	
	img = create_image(scene);
	if (!img)
		return ;
	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			put_pixel(img, x, y, create_color(0, 0, 255));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(scene->mlx_ptr, scene->win_ptr, img->img_ptr, 0, 0);
}
