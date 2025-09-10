#include "../../../includes/miniRT.h"

void	check_light_size(char **tokens, t_scene *scene, t_params *ls)
{
	if (ft_count_size(tokens) != 4)
	{
		free_tab(tokens);
		exit_with_lines(scene, ls, "wrong light param", ERR_PARAM);
	}
	return ;
}
