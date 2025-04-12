#ifndef philo_h
#define philo_h

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <limits.h>
#include <sys/time.h>
#include <limits.h>

#define SLEEP_SLICE 500
#define	DEATH_MONITOR_SLICE 1000
#define CLEAN_FORKS	0x01
#define CLEAN_END_MUTEX	0x02
#define CLEAN_PRINT_MUTEX	0x04


typedef struct	s_philo	t_philo;
typedef struct	s_simulation	t_simulation;

enum e_state
{
	EATING,
	SLEEPING,
	THINKING,
};

typedef struct s_fork
{
	pthread_mutex_t	mutex;//资源锁🔒 => 每个叉子对应一个互斥锁，确保同一时间只能被一个哲学家持有（资源访问控制）
	int				owner_id;//（可选）记录当前持有叉子的哲学家ID，用于调试或可视化
}	t_fork;

/**
 *全局模拟控制，包含整个程序的运行参数和共享状态*
 */
struct s_simulation
{
	//输入参数
	long			philo_num;//哲学家总数，决定叉子数量和线程数量
	long			time_to_die;//哲学家饿死时间（毫秒）	↘️
	long			time_to_eat;//进食耗时（毫秒）     ➡️   这三个时间变量全局共享
	long			time_to_sleep;//睡眠耗时（毫秒）   ↗️
	long			number_of_times_to_eat;//（可选）：每个哲学家需完成的最少进食次数，一旦全部达到，程序结束
	
	//共享状态
	long			start_time;//模拟开始的基准时间（毫秒）：所有时间计算的基准点（如get_relative_time()依赖此值），用于计算相对时间
	int				full_philos;//完成最少进食次数的哲学家人数
	bool			sim_end;//全局模拟结束标志，一旦为真，全局终止
	
	//互斥锁
	pthread_mutex_t	end_mutex;//全局锁🔒  =>  👆保护sim_end和full_philos的互斥锁
	pthread_mutex_t print_mutex;//输出流控制锁🔒 => 保护打印输出的互斥锁（避免打印混乱）
	
	//资源
	t_fork			*forks;//指向叉子数组的指针，每个叉子对应一个互斥锁（在叉子数组中声明）
	pthread_t		monitor_thread;//统一的监控线程，用于检查哲学家是否饿死
	t_philo			*philo_array;
};

/**
 *该结构体只负责管理每个哲学家个体
 *（不需要声明哲学家个数）
 */

struct s_philo
{
	//标识
	long			philo_id;//从1开始
	//每个哲学家的私有状态（需保护）
	long			last_meal_time;//最后一次进食的相对时间
	int				eat_count;//已进食次数
	pthread_t		thread;//哲学家对应的线程
	//共享状态
	t_simulation	*sim_data;//指向全局控制中心的指针
	//互斥锁
	pthread_mutex_t	meal_mutex;//私有锁🔒 => 保护last_meal_time和eat_count
	//左右叉子的index(动态计算）
	int				l_fork;
	int				r_fork;
};

//init.c
int				init_philo(t_simulation *sim, t_philo *philo, long start_time);
//int	init_forks_mutex(long num);
int 			init_simulation(t_simulation *sim, const char **argv, t_philo *philo);
int				init_forks_mutex(t_simulation *sim);

//routine.c
bool		everybody_is_full(t_philo *philo, t_simulation *sim);
void		*routine(void *arg);
void 		*handle_single_philo(t_philo *philo, t_simulation *sim);
void		*handle_multiple_philo(t_philo *philo, t_simulation *sim);

//eat.c
void		eat(t_philo *philo);

//fork.c
bool		take_forks(t_philo *philo);
void		drop_forks(t_philo *philo);

//death.c
int			kill_philo(t_philo *philo, t_simulation *sim, long cur_time);
void		*monitor_sim_routine(void *arg);
bool	check_sim_end(t_simulation *sim);

//philo.c
//main

//utils.c
void		free_structs(t_philo *philo, t_simulation *sim);
long		ft_atol(const char *str);
int			check_args(int argc, const char **args, long *n);
void 		print_status(t_philo *philo, const char *status);

//time.c
long		get_current_time(void);
long		get_relative_time(t_simulation *sim);//修正与系统的时间差
void	ft_usleep(long duration_ms, t_simulation *sim);
void	ft_think(t_philo *philo, int befor_begin);

//clean.c
void	cleanup_simulation(t_simulation *sim, int flags);

#endif
