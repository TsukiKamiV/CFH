#include "../../includes/miniRT.h"


int	ft_key_hook(int keycode, t_scene *scene)
{
	//printf("key code: %d\n", keycode);
	if (keycode == KEY_EXIT || keycode == KEY_QUIT)
		close_program(scene, NULL, EXIT_SUCCESS_KEY);
		//close_window(scene);
	return (0);
}
