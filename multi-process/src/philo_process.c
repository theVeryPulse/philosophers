/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 22:20:17 by Philip            #+#    #+#             */
/*   Updated: 2024/03/25 01:56:52 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <pthread.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void	*monitor_this_philo(void *args);

void	philo_routine(t_info *info)
{
	pthread_t	death_monitor;

	pthread_create(&death_monitor, NULL, monitor_this_philo, info);
	if (info->philo_no % 2 == 0)
		usleep(1e3);
	while (true)
	{
		philo_takes_two_forks(info);
		philo_eats(info);
		philo_puts_down_forks(info);
		if (info->eat_max_count != -1
			&& info->eat_count >= info->eat_max_count)
		{
			break ;
		}
		philo_thinks(info);
		philo_sleeps(info);
	}
	pthread_join(death_monitor, NULL);
	close_all_sem(info);
	free(info->philo_pids);
	exit(0);
}

static void	*monitor_this_philo(void *args)
{
	t_info	*info;

	info = (t_info *)args;
	while (true)
	{
		if (info->eat_max_count != -1
			&& safe_eat_count(info, LOOKUP) >= info->eat_max_count)
		{
			break ;
		}
		if (time_since_start(info) - safe_last_eat(info, LOOKUP)
			> info->time_to_die)
		{
			sem_wait(info->printf_sem);
			printf("%lld %d died after starving for %lld\t😵\n",
				time_since_start(info),
				info->philo_no,
				time_since_start(info) - info->last_eat);
			sem_post(info->a_philo_died);
			break ;
		}
		usleep(1000);
	}
	return (NULL);
}
