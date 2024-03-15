/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_philos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 23:00:13 by Philip            #+#    #+#             */
/*   Updated: 2024/03/15 01:35:31 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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

void	create_philos(t_info *info, t_philo **philos)
{
	int			i;

	info->full_philo_count = 0;
	*philos = (t_philo *)malloc(sizeof(t_philo) * info->philo_count);
	info->start_time = time_since_epoch();
	info->no_philo_died = true;
	i = 0;
	while (i < info->philo_count)
	{
		(*philos)[i].shared_info = info;
		(*philos)[i].philo_idx = i;
		(*philos)[i].last_eat = 0;
		(*philos)[i].eat_count = 0;
		(*philos)[i].left_fork = &(info->forks[left_hand_fork_idx(info, i)]);
		(*philos)[i].right_fork = &(info->forks[i]);
		(*philos)[i].is_not_eating = true;
		(*philos)[i].is_dead = false;
		(*philos)[i].idx_is_even_number = (i % 2 == 0);
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

	while (info->full_philo_count != info->philo_count
		&& info->no_philo_died)
	{
		i = 0;
		while (i < info->philo_count && info->no_philo_died)
		{
			if (philos[i].eat_count == info->eat_max_count)
			{
				i++;
				continue ;
			}
			if ((time_since_start(info) - philos[i].last_eat > info->time_to_die
					&& philos[i].is_not_eating))
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
	info->no_philo_died = false;
	philos[philo_idx].is_dead = true;
	printf("%lld %d died after starving for %lld\t😵\n",
		time_since_start(info),
		philo_idx + 1,
		time_since_start(info) - philos[philo_idx].last_eat);
}
