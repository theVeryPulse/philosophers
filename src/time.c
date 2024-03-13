/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 22:40:13 by Philip            #+#    #+#             */
/*   Updated: 2024/03/13 22:42:47 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long long	time_since_epoch(void)
{
	struct timeval	time;
	long long		milliseconds;

	gettimeofday(&time, NULL);
	milliseconds = time.tv_sec * 1000LL + time.tv_usec / 1000LL;
	return (milliseconds);
}

long long	time_since_start(t_info *info)
{
	return (time_since_epoch() - info->start_time);
}
