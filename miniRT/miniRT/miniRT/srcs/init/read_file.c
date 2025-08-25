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

//static int	line_has_illegal_character(char *line)
//{
//	int		i;
//	char	c;
//
//	i = 0;
//	while (line[i])
//	{
//		c = line[i];
//		if (!ft_isdigit(c) && !ft_isspace(c)
//			&& c != '-' && c != '+' && c != ',' && c != '.'
//			&& !(c >= 'a' && c <= 'z') && !(c >= 'A' && c <= 'Z'))
//			return (1);
//		// 检查非法组合
//		if ((c == ',' || c == '.' || c == '-' || c == '+')
//			&& (!line[i + 1] || line[i + 1] == ',' || line[i + 1] == '.'
//				|| line[i + 1] == '-' || line[i + 1] == '+'))
//			return (1);
//		i++;
//	}
//	return (0);
//}

//static int	line_has_illegal_character(char *line)
//{
//	int		i;
//	char	c;
//	int		skip_letters;
//
//	i = 0;
//	skip_letters = 1;
//	while (line[i])
//	{
//		c = line[i];
//
//		if (skip_letters && ft_isalpha(c))
//		{
//			i++;
//			continue;
//		}
//		skip_letters = 0;
//
//		if (!ft_isdigit(c) && !ft_isspace(c)
//			&& c != '-' && c != '+' && c != ',' && c != '.')
//			return (1);
//		if ((c == ',' || c == '.' || c == '-' || c == '+')
//			&& (!line[i + 1] || line[i + 1] == ',' || line[i + 1] == '.'
//				|| line[i + 1] == '-' || line[i + 1] == '+'))
//			return (1);
//		i++;
//	}
//	return (0);
//}

//static int	is_valid_number_str(char *s)
//{
//	int	i;
//	int	dot_count;
//
//	i = 0;
//	dot_count = 0;
//	if (!s || !*s)
//	{
//		printf("invalid: empty string\n");
//		return (0);
//	}
//		//return (0);
//	if (s[i] == '-' || s[i] == '+')
//		i++;
//	while (s[i])
//	{
//		if (s[i] == '.')
//		{
//			dot_count++;
//			if (dot_count > 1)
//			{
//				printf("invalid: multiple dots in %s\n", s);
//				return (0);
//			}
//		}
//		else if (!ft_isdigit(s[i]))
//			return (0);
//		i++;
//	}
//	return (1);
//}

//static int	line_has_illegal_character(char *line)
//{
//	char	**tokens;
//	int		i, j;
//
//	tokens = ft_split(line, ' ');
//	if (!tokens || !tokens[0])
//		return (1);
//	i = 1;
//	while (tokens[i])
//	{
//		j = 0;
//		printf("%s\n", tokens[i]);
//		while (tokens[i][j])
//		{
//			printf("current char: %c\n", tokens[i][j]);
//			if (!ft_isdigit(tokens[i][j]) && !ft_isspace(tokens[i][j])
//				&& tokens[i][j] != '-' && tokens[i][j] != '+'
//				&& tokens[i][j] != ',' && tokens[i][j] != '.')
//			{
//				printf("%s, %c", tokens[i], tokens[i][j]);
//				free_tab(tokens);
//				return (1);
//			}
//			j++;
//		}
//		// 每个数字参数中间可能用 , 分隔，逐个检查
//		char **sub = ft_split(tokens[i], ',');
//		j = 0;
//		while (sub && sub[j])
//		{
//			if (!is_valid_number_str(sub[j]))
//			{
//				printf("checking sub[%d]: \"%s\"\n", j, sub[j]);
//				free_tab(sub);
//				free_tab(tokens);
//				return (1);
//			}
//			j++;
//		}
//		free_tab(sub);
//		i++;
//	}
//	free_tab(tokens);
//	return (0);
//}

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

static int	line_has_illegal_character(char *line)
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

static void	dispatch_element(char **tokens, t_scene *scene)
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

static void	dispatch_valid_line(char *line, t_scene *scene)
{
	char	**tokens;
	
	tokens = ft_split(line, ' ');
	if (tokens && tokens[0])
	{
		if (!is_valid_key(tokens[0]))
		{
			free_tab(tokens);
			free(line);
			close_program(scene, "Error: key element type error found in rt file.\n", EXIT_ERROR_FILE);
		}
		dispatch_element(tokens, scene);
	}
	free_tab(tokens);
	free(line);
}

static void	strip_newline(char *line)
{
	size_t	len;
	
	if (!line)
		return;
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

static void	gnl_drain(int fd)
{
	char	*tmp;
	
	tmp = get_next_line(fd);
	while (tmp)
	{
		free(tmp);
		tmp = get_next_line(fd);
	}
}

void	read_file(int fd, t_scene *scene)
{
	char	*line;
	//char	**tokens;
	
	line = get_next_line(fd);
	while (line)
	{
		strip_newline(line);
		if (is_line_empty(line))
		{
			free(line);
			line = get_next_line(fd);
			continue;
		}
		if (line_has_illegal_character(line))
		{
			gnl_drain(fd);
			free (line);
			close_program(scene, "Error: illegal character found in rt file.\n", EXIT_ERROR_PARAM);
		}
		dispatch_valid_line(line, scene);
		//tokens = ft_split(line, ' ');
		//if (tokens && tokens[0])
		//	dispatch_element(tokens, scene);
		//free_tab(tokens);
		//free(line);
		line = get_next_line(fd);
	}
	if (!scene->amb || !scene->cam || !scene->light)
		close_program(scene, "Error: missing key element to create the scene.\n", EXIT_ERROR_PARAM);
	if (!scene->objs)
		close_program(scene, "Error: at least one object (plane/sphere/cylinder) required.\n", EXIT_ERROR_PARAM);
}
