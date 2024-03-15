/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_part1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 02:03:03 by Philip            #+#    #+#             */
/*   Updated: 2024/03/15 01:01:08 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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
		this->shared_info->full_philo_count++;
	pthread_exit(NULL);
}

void	philo_takes_forks(t_philo *philo)
{
	if (philo->shared_info->no_philo_died != true)
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
	if (philo->shared_info->no_philo_died != true)
		return ;
	printf("%lld %d has taken fork %d\t🍴\n",
		time_since_start(philo->shared_info),
		philo->philo_idx + 1,
		philo->philo_idx + 1);
}

void	take_left_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (philo->shared_info->no_philo_died != true)
		return ;
	printf("%lld %d has taken fork %d\t🍴\n",
		time_since_start(philo->shared_info),
		philo->philo_idx + 1,
		left_hand_fork_idx(philo->shared_info, philo->philo_idx) + 1);
}

void	philo_eats(t_philo *philo)
{
	if (philo->shared_info->no_philo_died != true)
		return ;
	philo->last_eat = time_since_start(philo->shared_info);
	philo->is_not_eating = false;
	printf("%lld %d is eating\t🍝\n",
		time_since_start(philo->shared_info),
		philo->philo_idx + 1);
	usleep(philo->shared_info->time_to_eat * 1000);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	philo->is_not_eating = true;
	philo->eat_count++;
	if (philo->shared_info->no_philo_died != true)
		return ;
	printf("%lld %d has eaten %d times\n",
		time_since_start(philo->shared_info),
		philo->philo_idx + 1,
		philo->eat_count);
}
