//
//  time.c
//  philo
//
//  Created by Luyao Xu on 17/03/2025.

#include "../includes/philo.h"

/**
 *时间管理逻辑：
 *全局参数time_to_die由simulation统一管理
 *私有时间（last_meal_time等）由各线程独立更新
 *通过start_time统一时间基准，避免系统时间漂移问题
 */

long	get_current_time(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long	get_relative_time(t_simulation *sim)
{
	//用于获取当前时间与模拟开始时间的相对时间差
	return (get_current_time() - sim->start_time);
}
