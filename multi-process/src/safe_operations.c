/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 22:24:31 by Philip            #+#    #+#             */
/*   Updated: 2024/03/24 22:40:53 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <pthread.h>

long long	safe_last_eat(t_info *info, t_mode mode)
{
	long long	last_eat;

	last_eat = 0;
	pthread_mutex_lock(&info->last_eat_mutex);
	if (mode == LOOKUP)
	{
		last_eat = info->last_eat;
	}
	else if (mode == UPDATE)
	{
		info->last_eat = time_since_start(info);
	}
	pthread_mutex_unlock(&info->last_eat_mutex);
	return (last_eat);
}

int	safe_eat_count(t_info *info, t_mode mode)
{
	int	eat_count;

	eat_count = 0;
	pthread_mutex_lock(&info->eat_count_mutex);
	if (mode == INCREMENT)
	{
		info->eat_count++;
	}
	else if (mode == LOOKUP)
	{
		eat_count = info->eat_count;
	}
	pthread_mutex_unlock(&info->eat_count_mutex);
	return (eat_count);
}
