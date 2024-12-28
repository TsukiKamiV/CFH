//
//  utils.c
//  philo
//
//  Created by Luyao Xu on 19/12/2024.
//

#include "../includes/philo.h"

long int	ft_atol(const char *str)
{
	long result = 0;
	int sign = 1;
	
	while (*str == ' ' || *str == '\t' || *str == '\n' ||
		   *str == '\r' || *str == '\v' || *str == '\f') {
		str++;
	}
	if (*str == '-' || *str == '+') {
		if (*str == '-') {
			sign = -1;
		}
		str++;
	}
	while (*str >= '0' && *str <= '9') 
	{
		long digit = *str - '0';
		if (result > (LONG_MAX - digit) / 10) 
		{
			return (sign == 1) ? LONG_MAX : LONG_MIN;
		}
		result = result * 10 + digit;
		str++;
	}
	return result * sign;
}
