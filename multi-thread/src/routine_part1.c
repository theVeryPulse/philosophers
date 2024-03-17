/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_part1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 02:03:03 by Philip            #+#    #+#             */
/*   Updated: 2024/03/17 23:50:59 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>

/**
 * @brief 
 * 
 * @param 
 * @return 
 * @note
 * eat -> sleep -> think -> eat -> ... 
 * 
 * timestamp_in_ms X has taken a fork
 * timestamp_in_ms X is eating
 * timestamp_in_ms X is sleeping
 * timestamp_in_ms X is thinking
 * timestamp_in_ms X died 😵
 */
void	*routine(void *args)
{
	t_philo	*this;

	this = (t_philo *)args;
	while (this->shared_info->no_philo_died)
	{
		philo_takes_forks(this);
		philo_eats(this);
		if (philo_eats_enough(this))
			break ;
		philo_sleeps(this);
		philo_thinks(this);
	}
	if (this->shared_info->no_philo_died
		&& this->is_dead == false)
		safe_full_philo_count(this->shared_info, INCREMENT);
	pthread_exit(NULL);
}

void	philo_takes_forks(t_philo *philo)
{
	if (safe_no_philo_died(philo->shared_info, LOOKUP) != true)
		return ;
	if (philo->idx_is_even_number)
	{
		take_right_fork(philo);
		take_left_fork(philo);
	}
	else
	{
		if (philo->shared_info->philo_count_is_odd)
			usleep(1);
		take_left_fork(philo);
		take_right_fork(philo);
	}
}

void	take_right_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	if (safe_no_philo_died(philo->shared_info, LOOKUP) != true)
		return ;
	pthread_mutex_lock(&philo->shared_info->printf_mutex);
	printf("%lld %d has taken fork %d\t🍴\n",
		time_since_start(philo->shared_info),
		philo->philo_idx + 1,
		philo->philo_idx + 1);
	pthread_mutex_unlock(&philo->shared_info->printf_mutex);
}

void	take_left_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (safe_no_philo_died(philo->shared_info, LOOKUP) != true)
		return ;
	pthread_mutex_lock(&philo->shared_info->printf_mutex);
	printf("%lld %d has taken fork %d\t🍴\n",
		time_since_start(philo->shared_info),
		philo->philo_idx + 1,
		left_hand_fork_idx(philo->shared_info, philo->philo_idx) + 1);
	pthread_mutex_unlock(&philo->shared_info->printf_mutex);
}

void	philo_eats(t_philo *philo)
{
	if (safe_no_philo_died(philo->shared_info, LOOKUP) != true)
		return (put_down_forks(philo));
	safe_last_eat(philo, UPDATE);
	safe_is_not_eating(philo, TOGGLE_FALSE);
	pthread_mutex_lock(&philo->shared_info->printf_mutex);
	printf("%lld %d is eating\t🍝\n",
		time_since_start(philo->shared_info),
		philo->philo_idx + 1);
	pthread_mutex_unlock(&philo->shared_info->printf_mutex);
	usleep(philo->shared_info->time_to_eat * 1000);
	put_down_forks(philo);
	safe_is_not_eating(philo, TOGGLE_TRUE);
	safe_eat_count(philo, INCREMENT);
	if (safe_no_philo_died(philo->shared_info, LOOKUP) != true)
		return ;
	pthread_mutex_lock(&philo->shared_info->printf_mutex);
	printf("%lld %d has eaten %d times\n",
		time_since_start(philo->shared_info),
		philo->philo_idx + 1,
		philo->eat_count);
	pthread_mutex_unlock(&philo->shared_info->printf_mutex);
}
