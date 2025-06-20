#ifndef miniRT_h
#define miniRT_h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../mlx/mlx.h"
#include "../libft/libft.h"

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}		t_color;

typedef struct s_ambient
{
	double	ratio;
	t_color	color;
}			t_ambient;

typedef struct s_camera
{
	t_vec3	pos; //位置向量
	t_vec3	orient;//normalized vector 方向向量
	double	fov;//视角，角度，范围（0 - 180）
}		t_camera;

typedef struct s_light
{
	t_vec3	pos;
	int		ratio;
	t_color	color;
}		t_light;

typedef enum	e_object_type
{
	SPHERE,
	PLANE,
	CYLINDER
}	t_object_type;

typedef struct	s_sphere
{
	t_vec3	center;
	double	radius;
	t_color	color;
}	t_sphere;

typedef struct	s_plane
{
	t_vec3	point;
	t_vec3	normal;
	t_color	color;
}		t_plane;

typedef struct	s_cylinder
{
	t_vec3	centre;
	t_vec3	axis;
	double	radius;
	double	height;
	t_vec3	color;
}		t_cylinder;

typedef struct	s_object
{
	t_object_type type;
	void	*element;
	struct	s_object *next;
}		t_object;

typedef struct	s_image
{
	void	*img_ptr;
	char	*addr;//指向图像缓冲区的起始地址
	int		bits_per_pixel;//每像素位数，通常是32
	int		line_length;//每行字节数
	int		endian;//大小端，一般为0
	int		width;//图像宽度
	int		height;//图像高度
}				t_image;

typedef struct	s_scene
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		height;
	int		width;
	
	t_ambient	*amb;
	t_light		*light;
	t_camera	*cam;
	t_list	*objs;
}	t_scene;

//init
//read_file.c
void	read_file(int fd, t_scene *scene);

//parse_scene.c
int	parse_ambient(char **tokens, t_scene *scene);
int	parse_camera(char **tokens, t_scene *scene);
int	parse_light(char **tokens, t_scene *scene);

//parse_obj.c
int	parse_sphere(char **tokens, t_scene *scene);
int	parse_plane(char **tokens, t_scene *scene);
int	parse_cylinder(char **tokens, t_scene *scene);

//parse_utils.c
void	free_tab(char **tab);
t_color	parse_color(char *str);
void	add_object(t_scene *scene, t_object *new);


//utils
//utils.c
int	ft_isspace(char c);
int	ft_strcmp(const char *s1, const char *s2);
int	ft_count_size(char **tokens);

//image
//img_utils
t_image	*create_image(t_scene *scene);
void	put_pixel(t_image *img, int x, int y, int color);
int		create_color(int r, int g, int b);

//render
//render_scene.c
void	render_scene(t_scene *scene);

#endif /* miniRT_h */
