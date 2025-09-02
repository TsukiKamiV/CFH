#include "../../includes/miniRT.h"


int	ft_key_hook(int keycode, t_scene *scene)
{
	printf("key code: %d\n", keycode);
	if (keycode == 53 || keycode == 12)
		close_program(scene, NULL, EXIT_SUCCESS_KEY);
		//close_window(scene);
	return (0);
}
