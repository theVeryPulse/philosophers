/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_part2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 02:06:38 by Philip            #+#    #+#             */
/*   Updated: 2024/03/15 01:02:24 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool	philo_eats_enough(t_philo *philo)
{
	if (philo->shared_info->no_philo_died != true)
		return (false);
	if (philo->shared_info->eat_max_count > 0
		&& philo->eat_count == philo->shared_info->eat_max_count
		&& philo->shared_info->no_philo_died)
	{
		printf("%lld %d stops\n",
			time_since_start(philo->shared_info),
			philo->philo_idx + 1);
		return (true);
	}
	else
	{
		return (false);
	}
}

void	philo_sleeps(t_philo *philo)
{
	if (philo->shared_info->no_philo_died != true)
		return ;
	printf("%lld %d is sleeping\t😴\n",
		time_since_start(philo->shared_info),
		philo->philo_idx + 1);
	usleep(philo->shared_info->time_to_sleep * 1000);
}

void	philo_thinks(t_philo *philo)
{
	if (philo->shared_info->no_philo_died != true)
		return ;
	printf("%lld %d is thinking\t🤔\n",
		time_since_start(philo->shared_info),
		philo->philo_idx + 1);
	usleep(1000);
}
