/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:12:00 by luxu              #+#    #+#             */
/*   Updated: 2025/09/10 16:12:47 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

# include "miniRT.h"

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

//vec3.c
t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_sub(t_vec3 a, t_vec3 b);
t_vec3	vec3_scale(t_vec3 v, double s);
t_vec3	vec3_normalize(t_vec3 v);
double	vec3_dot(t_vec3 a, t_vec3 b);

//vec3_bis.c
t_vec3	vec3_cross(t_vec3 a, t_vec3 b);
double	vec3_length(t_vec3 v);

#endif /* vec3_h */
