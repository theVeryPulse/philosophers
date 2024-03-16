/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_philos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 23:00:13 by Philip            #+#    #+#             */
/*   Updated: 2024/03/16 23:10:53 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void	philo_death_notif(t_info *info, t_philo *philos, int philo_idx);

void	create_forks(t_info *info)
{
	int	i;

	info->forks = malloc(sizeof(pthread_mutex_t) * info->philo_count);
	if (!info->forks)
		exit (1);
	i = 0;
	while (i < info->philo_count)
	{
		pthread_mutex_init(&(info->forks[i]), NULL);
		i++;
	}
}

void	philo_init(t_philo *philo, t_info *info, int idx)
{
	philo->shared_info = info;
	philo->philo_idx = idx;
	philo->last_eat = 0;
	pthread_mutex_init(&philo->last_eat_mutex, NULL);
	philo->eat_count = 0;
	pthread_mutex_init(&philo->eat_count_mutex, NULL);
	philo->left_fork = &(info->forks[left_hand_fork_idx(info, idx)]);
	philo->right_fork = &(info->forks[idx]);
	philo->is_not_eating = true;
	pthread_mutex_init(&philo->is_not_eating_mutex, NULL);
	philo->is_dead = false;
	philo->idx_is_even_number = (bool)(idx % 2 == 0);
}

void	create_philos(t_info *info, t_philo **philos)
{
	int		i;

	info->full_philo_count = 0;
	pthread_mutex_init(&info->full_philo_count_mutex, NULL);
	*philos = (t_philo *)malloc(sizeof(t_philo) * info->philo_count);
	info->no_philo_died = true;
	pthread_mutex_init(&info->no_philo_died_mutex, NULL);
	info->start_time = time_since_epoch();
	i = 0;
	while (i < info->philo_count)
	{
		philo_init(&(*philos)[i], info, i);
		pthread_create(&(*philos)[i].thread, NULL, routine, &(*philos)[i]);
		i++;
	}
}

int	left_hand_fork_idx(t_info *info, int philo_idx)
{
	if (philo_idx != 0)
		return (philo_idx - 1);
	else
		return (info->philo_count - 1);
}

void	monitor_philos(t_info *info, t_philo *philos)
{
	int	i;

	while (safe_full_philo_count(info, LOOKUP) != info->philo_count
		&& info->no_philo_died)
	{
		i = 0;
		while (i < info->philo_count && info->no_philo_died)
		{
			if (safe_eat_count(&philos[i], LOOKUP) == info->eat_max_count)
			{
				i++;
				continue ;
			}
			if (time_since_start(info) - safe_last_eat(&philos[i], LOOKUP) >
					info->time_to_die
					&& safe_is_not_eating(&philos[i], LOOKUP))
			{
				philo_death_notif(info, philos, i);
				break ;
			}
			i++;
		}
		usleep(1e2);
	}
}

static void	philo_death_notif(t_info *info, t_philo *philos, int philo_idx)
{
	safe_no_philo_died(info, TOGGLE_FALSE);
	philos[philo_idx].is_dead = true;
	pthread_mutex_lock(&info->printf_mutex);
	printf("%lld %d died after starving for %lld\t😵\n",
		time_since_start(info),
		philo_idx + 1,
		time_since_start(info) - philos[philo_idx].last_eat);
	pthread_mutex_unlock(&info->printf_mutex);
}
