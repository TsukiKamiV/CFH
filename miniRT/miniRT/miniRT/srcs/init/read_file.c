#include "../../includes/miniRT.h"
//
//void	print_tab(char **tab)
//{
//	int	i;
//
//	if (!tab)
//		return ;
//	i = 0;
//	while (tab[i])
//	{
//		printf("%d: %s\n", i, tab[i]);
//		i++;
//	}
//}



static char **read_file_with_gnl(int fd, char *line, char **tab)
{
	int	i;
	
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		trim_newline(line);
		tab[i] = line;
		i++;
		line = get_next_line(fd);
	}
	close(fd);
	tab[i] = NULL;
	return (tab);
}

int	load_lines_into_tab(const char *filename, char ***out_tab, int count)
{
	int		fd;
	char	**tab;
	char	*line;
	
	if (!filename || !out_tab || count < 0)
		return (0);
	*out_tab = NULL;
	line = NULL;
	tab = (char **)malloc(sizeof(char *) * (count + 1));
	if (!tab)
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		free(tab);
		return (0);
	}
	*out_tab = read_file_with_gnl(fd, line, tab);
	return (1);
}

//int	load_lines_into_tab(const char *filename, char ***out_tab, int count)
//{
//	int		fd;
//	char	**tab;
//	char	*line;
//	int		i;
//
//	if (!filename || !out_tab || count < 0)
//		return (0);
//	*out_tab = NULL;
//	tab = (char **)malloc(sizeof(char *) * (count + 1));
//	if (!tab)
//		return (0);
//	i = 0;
//	fd = open(filename, O_RDONLY);
//	if (fd < 0)
//	{
//		free(tab);
//		return (0);
//	}
//	line = get_next_line(fd);
//	while (line)
//	{
//		trim_newline(line);
//		tab[i] = line;
//		i++;
//		line = get_next_line(fd);
//	}
//	close(fd);
//	tab[i] = NULL;
//	*out_tab = tab;
//	return (1);
//}

int	read_all_lines(const char *filename, t_params *params)
{
	int		ok;
	int		count;
	char	**tab;
	
	if (!params)
		return (0);
	params->tab = NULL;
	params->count = 0;
	ok = count_lines_in_file(filename, &count);
	if (!ok)
		return (0);
	ok = load_lines_into_tab(filename, &tab, count);
	if (!ok)
		return (0);
	params->tab = tab;
	params->count = count;
	return (1);
}

void	dispatch_element(char **tokens, t_scene *scene, t_params *ls)
{
	if (ft_strcmp(tokens[0], "A") == 0 && !scene->amb)
		parse_ambient(tokens, scene, ls);
	else if(ft_strcmp(tokens[0], "C") == 0 && !scene->cam)
		parse_camera(tokens, scene, ls);
	else if(ft_strcmp(tokens[0], "L") == 0 && !scene->light)
		parse_light(tokens, scene, ls);
	else if(ft_strcmp(tokens[0], "sp") == 0)
		parse_sphere(tokens, scene, ls);
	else if (ft_strcmp(tokens[0], "pl") == 0)
		parse_plane(tokens, scene, ls);
	else if(ft_strcmp(tokens[0], "cy") == 0)
		parse_cylinder(tokens, scene, ls);
	else
	{
		free_tab(tokens);
		exit_with_lines(scene, ls, "Error\n key element type error found in rt file.\n", EXIT_ERROR_FILE);
	}
}

int parse_scene_from_lines(t_params *ls, t_scene *scene)
{
	int   i;
	char  **tokens;
	
	if (all_lines_empty(ls))
		exit_with_lines(scene, ls, "Error\n empty rt file.\n", EXIT_ERROR_FILE);
	i = 0;
	while (i < ls->count)
	{
		if (!is_line_empty(ls->tab[i]))
		{
			if (line_has_illegal_character(ls->tab[i]))
				exit_with_lines(scene, ls,
								"Error\n illegal character found in rt file.\n",
								EXIT_ERROR_PARAM);
			tokens = ft_split(ls->tab[i], ' ');
			if (!tokens)
				return (0);
			if (!is_valid_key(tokens[0]))
			{
				free_tab(tokens);
				return (error_msg("key element type error", 1) && 0);
			}
			dispatch_element(tokens, scene, ls);
			free_tab(tokens);
		}
		i++;
	}
	validate_scene_or_exit(scene, ls);
	return (1);
}
/*
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

static int	push_line(t_params *ls, char *line)
{
	t_line	*node;
	
	node = (t_line *)malloc(sizeof(t_line));
	if (!node)
		return (error_msg("malloc failed for inputting params", 0));
	node->s = line;
	node->next = NULL;
	if (!ls->head)
	{
		ls->head = node;
		ls->tail = node;
	}
	else
	{
		ls->tail->next = node;
		ls->tail = node;
	}
	ls->count++;
	return (1);
}

static void	trim_newline(char *s)
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

int	read_all_lines(const char *filename, t_params *out)
{
	int		fd;
	char	*line;
	int		ok;
	
	out->head = NULL;
	out->tail = NULL;
	out->count = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		trim_newline(line);
		if (is_line_empty(line))
		{
			free (line);
			line = get_next_line(fd);
			continue;
		}
		ok = push_line(out, line);
		if (!ok)
		{
			free (line);
			close (fd);
			free_lines(out);
			return (0);
		}
		line = get_next_line(fd);
	}
	if (line)
		free (line);
	close(fd);
	return (1);
}

static void	exit_with_lines(t_scene *scene, t_params *ls, const char *msg, int code)
{
	free_lines(ls);
	close_program(scene, msg, code);
}

void	free_lines(t_params *ls)
{
	t_line	*cur;
	t_line	*next;
	
	if (!ls)
		return ;
	cur = ls->head;
	while (cur)
	{
		next = cur->next;
		if (cur->s)
			free (cur->s);
		free (cur);
		cur = next;
	}
	ls->head = NULL;
	ls->tail = NULL;
	ls->count = 0;
}

static int	is_valid_key(const char *s)
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

static int	all_lines_empty(t_params *ls)
{
	t_line	*cur;
	
	if (!ls || ls->count == 0)
		return (1);
	cur = ls->head;
	while (cur)
	{
		if (!is_line_empty(cur->s))
			return (0);
		cur = cur->next;
	}
	return (1);
}

static void validate_scene_or_exit(t_scene *scene, t_params *ls)
{
	if (!scene->amb || !scene->cam || !scene->light)
		exit_with_lines(scene, ls,
						"Error: missing key element to create the scene.\n",
						EXIT_ERROR_PARAM);
	if (!scene->objs)
		exit_with_lines(scene, ls,
						"Error: at least one object (plane/sphere/cylinder) required.\n",
						EXIT_ERROR_PARAM);
}

int parse_scene_from_lines(t_params *ls, t_scene *scene)
{
	t_line  *cur;
	char    *line;
	char    **tokens;
	
	if (all_lines_empty(ls))
		exit_with_lines(scene, ls, "Error: empty rt file.\n", EXIT_ERROR_FILE);
	cur = ls->head;
	while (cur)
	{
		line = cur->s;
		if (!is_line_empty(line))
		{
			if (line_has_illegal_character(line))
				exit_with_lines(scene, ls,
								"Error: illegal character found in rt file.\n",
								EXIT_ERROR_PARAM);
			tokens = ft_split(line, ' ');
			if (!tokens)
				return (0);
			if (!is_valid_key(tokens[0]))
			{
				free_tab(tokens);
				return (error_msg("key element type error", 1) && 0);
			}
			dispatch_element(tokens, scene);
			free_tab(tokens);
		}
		cur = cur->next;
	}
	validate_scene_or_exit(scene, ls);
	return (1);
}

static int is_valid_number_list(const char *t)
{
	int	i;
	int	digits;
	int	frac;
	
	i = 0;
	if (!t || !*t)
		return (0);
	while (t[i]) 
	{
		digits = 0;
		frac = 0;
		if (t[i] == '+' || t[i] == '-')
			i++;
		while (ft_isdigit(t[i]))
		{
			i++; 
			digits++;
		}
		if (t[i] == '.')
		{
			i++;
			while(ft_isdigit(t[i]))
			{
				i++;
				frac++;
			}
		}
		if (digits + frac == 0)
			return (0);
		if (t[i] == '\0') 
			return (1);
		if (t[i] != ',') 
			return (0);
		i++;
		if (t[i] == '\0') 
			return (0);
	}
	return (1);
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

void	dispatch_element(char **tokens, t_scene *scene)
{
	if (ft_strcmp(tokens[0], "A") == 0 && !scene->amb)
		parse_ambient(tokens, scene);
	else if(ft_strcmp(tokens[0], "C") == 0 && !scene->cam)
		parse_camera(tokens, scene);
	else if(ft_strcmp(tokens[0], "L") == 0 && !scene->light)
		parse_light(tokens, scene);
	else if(ft_strcmp(tokens[0], "sp") == 0)
		parse_sphere(tokens, scene);
	else if (ft_strcmp(tokens[0], "pl") == 0)
		parse_plane(tokens, scene);
	else if(ft_strcmp(tokens[0], "cy") == 0)
		parse_cylinder(tokens, scene);
	else
		close_program(scene, "Error: key element type error found in rt file.\n", EXIT_ERROR_FILE);
}
*/
