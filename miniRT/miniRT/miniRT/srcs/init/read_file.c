#include "../../includes/miniRT.h"

static int	is_line_empty(char *line)
{
	int	i;
	
	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	dispatch_element(char **tokens, t_scene *scene)
{
	if (ft_strcmp(tokens[0], "A") == 0)
		parse_ambient(tokens, scene);
	//else if(ft_strcmp(tokens[0], "C") == 0)
	//	parse_camera(tokens, scene);
	//else if(ft_strcmp(tokens[0], "L") == 0)
		//parse_light(tokens, scene);
	//else if(ft_strcmp(tokens[0], "sp") == 0)
	//	parse_sphere(tokens, scene);
	else if (ft_strcmp(tokens[0], "pl") == 0)
		parse_plane(tokens, scene);
	//else if(ft_strcmp(tokens[0], "cy") == 0)
	//	parse_cylinder(tokens, scene);
	//else
	//	ft_putstr_fd("Unknown element type\n", 2);
}

/*void	read_file(int fd, t_scene *scene)
{
	char	*line;
	char	**tokens;
	
	line = get_next_line(fd);
	while (line)
	{
		if (is_line_empty(line))
		{
			free (line);
			line = get_next_line(fd);
			continue;
		}
		tokens = ft_split(line, ' ');
		if (!tokens || !tokens[0])
		{
			free (line);
			continue;
		}
		dispatch_element(tokens, scene);
		free_tab(tokens);
		free (line);
	}
}*/

void	read_file(int fd, t_scene *scene)
{
	char	*line;
	char	**tokens;
	
	line = get_next_line(fd);
	while (line)
	{
		if (is_line_empty(line))
		{
			free(line);
			line = get_next_line(fd);
			continue;
		}
		tokens = ft_split(line, ' ');
		if (tokens && tokens[0])
			dispatch_element(tokens, scene);
		free_tab(tokens);
		free(line);
		line = get_next_line(fd);
	}
}
