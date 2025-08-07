#include "../../includes/miniRT.h"


int	ft_key_hook(int keycode, t_scene *scene)
{
	if (keycode == 53 || keycode == 12)
		close_window(scene);
	return (0);
}
