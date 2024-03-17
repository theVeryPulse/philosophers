/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 22:14:32 by Philip            #+#    #+#             */
/*   Updated: 2024/03/17 17:34:40 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	safe_eat_count(t_philo *philo, t_mode mode)
{
	int	eat_count;

	eat_count = 0;
	pthread_mutex_lock(&philo->eat_count_mutex);
	if (mode == INCREMENT)
		philo->eat_count++;
	else if (mode == LOOKUP)
		eat_count = philo->eat_count;
	pthread_mutex_unlock(&philo->eat_count_mutex);
	return (eat_count);
}

int	safe_full_philo_count(t_info *info, t_mode mode)
{
	int	full_philo_count;

	full_philo_count = 0;
	pthread_mutex_lock(&info->full_philo_count_mutex);
	if (mode == INCREMENT)
		info->full_philo_count++;
	else if (mode == LOOKUP)
		full_philo_count = info->full_philo_count;
	pthread_mutex_unlock(&info->full_philo_count_mutex);
	return (full_philo_count);
}

long long	safe_last_eat(t_philo *philo, t_mode mode)
{
	long long	last_eat;

	last_eat = 0;
	pthread_mutex_lock(&philo->last_eat_mutex);
	if (mode == LOOKUP)
		last_eat = philo->last_eat;
	else if (mode == UPDATE)
		philo->last_eat = time_since_start(philo->shared_info);
	pthread_mutex_unlock(&philo->last_eat_mutex);
	return (last_eat);
}

bool	safe_is_not_eating(t_philo *philo, t_mode mode)
{
	bool	is_not_eating;

	is_not_eating = 0;
	pthread_mutex_lock(&philo->is_not_eating_mutex);
	if (mode == LOOKUP)
		is_not_eating = philo->is_not_eating;
	else if (mode == TOGGLE_TRUE)
		philo->is_not_eating = true;
	else if (mode == TOGGLE_FALSE)
		philo->is_not_eating = false;
	pthread_mutex_unlock(&philo->is_not_eating_mutex);
	return (is_not_eating);
}

bool	safe_no_philo_died(t_info *info, t_mode mode)
{
	bool	no_philo_died;

	no_philo_died = 0;
	pthread_mutex_lock(&info->no_philo_died_mutex);
	if (mode == LOOKUP)
		no_philo_died = info->no_philo_died;
	else if (mode == TOGGLE_FALSE)
		info->no_philo_died = false;
	else if (mode == TOGGLE_TRUE)
		info->no_philo_died = true;
	pthread_mutex_unlock(&info->no_philo_died_mutex);
	return (no_philo_died);
}
