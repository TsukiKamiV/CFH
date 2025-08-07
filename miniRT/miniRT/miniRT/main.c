//
//  main.c
//  miniRT
//
//  Created by Luyao Xu on 22/05/2025.
//

#include "./includes/miniRT.h"
/**
 *
 *解析器（parser）解析.rt文件并构建场景结构体
 *向量工具(vector_utils) 实现加减法，点乘，叉乘，单位向量等；
 *相交检测 （intersection）球，平面，圆柱的相交函数；
 *光照模型 （lighting）环境光，漫反射的计算；
 *渲染器（rending）遍历每个像素，发射光线并求交计算颜色
 *图像绘制（mlx_utils)利用MiniLibX创建窗口，图像，显示像素；
 *main 初始化，读取文件，调用渲染，事件处理等
 */


int main(int argc, const char * argv[])
{
	int			fd;
	t_scene		*scene;
	
	if (argc != 2)
	{
		ft_putstr_fd("Error!\nUsage: ./miniRT scene.rt\n",2);
		return (1);
	}
	scene = malloc(sizeof(t_scene));
	if (!scene)
		return (1);
	ft_memset(scene, 0, sizeof(t_scene));
	scene->mlx_ptr = mlx_init();
	if (!scene->mlx_ptr)
	{
		ft_putstr_fd("Error: mlx_init failed\n", 2);
		return (1);
	}
	scene->win_ptr = mlx_new_window(scene->mlx_ptr, 800, 600, "miniRT");
	if (!scene->win_ptr)
	{
		ft_putstr_fd("Error: mlx_new_window failed\n", 2);
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error!/nFailed to load .rt file.");
		free (scene);
		return (1);
	}
	read_file(fd, scene);
	close(fd);
	
	render_scene(scene);
	mlx_key_hook(scene->win_ptr, ft_key_hook, scene);
	mlx_hook(scene->win_ptr, 17, 0, my_mlx_hook_callback, &scene);
	mlx_loop(scene->mlx_ptr);
	//return (0);
}
