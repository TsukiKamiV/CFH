#ifndef miniRT_h
#define miniRT_h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>
#include <stdarg.h>

#include "vec3.h"

#include "../mlx/mlx.h"
#include "../libft/libft.h"
	
 #define		EPSILON 			1e-4
 #define		EXIT_SUCCESS_MXL	0
 #define		EXIT_SUCCESS_KEY	1
 #define		EXIT_ERROR_MLX 		2
 #define		EXIT_ERROR_FILE		3
 #define		EXIT_ERROR_PARAM	4
 #define		EXIT_ERROR_MALLOC	5

 #ifdef __APPLE__
 # define KEY_Q 12
 # define KEY_ESC 53
 #else
 # define KEY_Q	113
 # define KEY_ESC 65307
 #endif

typedef enum e_key
{
	KEY_QUIT = KEY_Q,
	KEY_EXIT = KEY_ESC
}				t_key;

typedef struct	s_line
{
	char	*s;
	struct s_line *next;
}				t_line;


typedef struct	s_params
{
	char	**tab;
	int		count;
}				t_params;
//typedef struct s_params
//{
//	t_line	*head;
//	t_line	*tail;
//	int		count;
//}				t_params;

typedef struct	s_point2
{
	int	x;
	int	y;
}				t_point2;

typedef struct s_ray
{
	t_vec3 origin;
	t_vec3 direction;
}	t_ray;

typedef struct	s_viewport
{
	double	width;
	double	height;
	double	aspect_ratio;
	double	focal_length;
}				t_viewport;

typedef struct	s_basis//代表摄像机坐标系的三个正交基向量
{
	t_vec3	u;
	t_vec3	v;
	t_vec3	w;
}				t_basis;

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
	double		ratio;
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
	t_color	color;
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
	t_object	*objs;
	t_image		*img;
}	t_scene;

typedef struct	s_hit
{
	double	t;
	t_vec3	point;
	t_vec3 	normal;
	t_color	color;
	t_object	*obj;
}				t_hit;

typedef struct s_quad 
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
}	t_quad;

//init
//read_file.c
void	read_file(int fd, t_scene *scene);
void	dispatch_element(char **tokens, t_scene *scene, t_params *ls);
int		read_all_lines(const char *filename, t_params *out);
int 	parse_scene_from_lines(t_params *ls, t_scene *scene);
void	free_lines(t_params *ls);
int		line_has_illegal_character(char *line);

//parse_scene.c
int	parse_ambient(char **tokens, t_scene *scene, t_params *ls);
int	parse_camera(char **tokens, t_scene *scene, t_params *ls);
int	parse_light(char **tokens, t_scene *scene, t_params *ls);

//parse_obj.c
int	parse_sphere(char **tokens, t_scene *scene, t_params *ls);
int	parse_plane(char **tokens, t_scene *scene, t_params *ls);
int	parse_cylinder(char **tokens, t_scene *scene, t_params *ls);

//parse_utils.c
int	validate_assign_rgb(t_color *color, char **rgb);
int		normal_is_unit(t_vec3 n);
t_color	parse_color(char *str);
void	add_object(t_scene *scene, t_object *new);
int	create_and_fill_obj(t_scene *scene, t_object_type type, void *element);
void	free_lines(t_params *ls);
void	exit_with_lines(t_scene *scene, t_params *ls, const char *msg, int code);

//hook.c
int	ft_key_hook(int keycode, t_scene *scene);


//utils
//utils.c
int		ft_isspace(char c);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_count_size(char **tokens);
void	free_multiple_tab(int count, ...);
void	free_tab(char **tab);

//img_utils
t_image	*create_image(t_scene *scene);
void	put_pixel(t_image *img, int x, int y, t_color color);
t_color		create_color(int r, int g, int b);

//error.c
int	error_msg(const char *msg, int ret);

//render
//render_scene.c
void	render_scene(t_scene *scene);

//render_objs.c
void	render_object(t_image *img, t_object *obj);
void	render_plane(t_image *img, t_plane *pl);

//ray.c
t_ray	generate_ray(t_camera *cam, t_point2 pixel, t_image img);
t_color		trace_ray(t_ray ray, t_scene *scene, t_point2 pixel);//引入pixel是为了debug

//ray_hit.c
int	hit_plane(t_ray ray, t_plane *pl, t_hit *hit);
bool	hit_sphere(t_ray ray, t_sphere *sphere, t_hit *hit);
bool	hit_cylinder_body(t_ray ray, t_cylinder *cy, t_hit *hit);
bool	hit_cylinder_cap(t_ray ray, t_cylinder *cy, t_hit *hit);
bool	hit_cylinder(t_ray ray, t_cylinder *cy, t_hit *hit);

//ray_utils.c
t_vec3	ray_at(t_ray ray, double t);

//ambient.c
t_color	compute_ambient(t_color obj_color, t_scene *scene);

//lighting.c
t_color	compute_lighting(t_scene *scene, t_hit *hit);

//diffuse.c
t_color	compute_diffuse(t_scene *scene, t_hit *hit);
bool	is_in_shadow(t_scene *scene, t_vec3 p, t_vec3 dir);

//free
//exit_free.c
void	free_objects(t_object *obj);
void	free_scene(t_scene *scene);
int		my_mlx_hook_callback(int keycode, t_scene *scene);

//exit
//close_window.c
void	free_all_allocated_memory(t_scene *scene);
int		close_window(t_scene *scene);
int	close_program(t_scene *scene, const char *msg, int state);

#endif /* miniRT_h */
