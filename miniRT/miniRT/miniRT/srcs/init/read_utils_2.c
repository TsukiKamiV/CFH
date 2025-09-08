#include "../../includes/miniRT.h"

int	is_valid_key(const char *s)
{
	if (!s)
		return (0);
	if (ft_strcmp(s, "A") == 0)
		return (1);
	if (ft_strcmp(s, "C") == 0)
		return (1);
	if (ft_strcmp(s, "L") == 0)
		return (1);
	if (ft_strcmp(s, "sp") == 0)
		return (1);
	if (ft_strcmp(s, "pl") == 0)
		return (1);
	if (ft_strcmp(s, "cy") == 0)
		return (1);
	return (0);
}

int	line_has_illegal_character(char *line)
{
	char	**tokens;
	int		i;
	
	tokens = ft_split(line, ' ');
	if (!tokens)
		return (1);
	if (!tokens[0])
	{
		free_tab(tokens);
		return (1);
	}
	i = 1;
	while (tokens[i])
	{
		if (!is_valid_number_list(tokens[i]))
		{
			free_tab(tokens);
			return (1);
		}
		i++;
	}
	free_tab(tokens);
	return (0);
}

void validate_scene_or_exit(t_scene *scene, t_params *ls)
{
	if (!scene->amb || !scene->cam || !scene->light)
		exit_with_lines(scene, ls,
						"Error\n missing key element to create the scene.\n",
						EXIT_ERROR_PARAM);
	if (!scene->objs)
		exit_with_lines(scene, ls,
						"Error\n at least one object (plane/sphere/cylinder) required.\n",
						EXIT_ERROR_PARAM);
}

void	trim_newline(char *s)
{
	int	i;
	
	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
		{
			s[i] = '\0';
			break;
		}
		i++;
	}
}
