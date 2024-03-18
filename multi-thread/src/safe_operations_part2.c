/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_operations_part2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:41:30 by Philip            #+#    #+#             */
/*   Updated: 2024/03/18 13:45:46 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	safe_is_dead(t_philo *philo, t_mode mode)
{
	bool	is_dead;

	is_dead = 0;
	pthread_mutex_lock(&philo->is_dead_mutex);
	if (mode == LOOKUP)
	{
		is_dead = philo->is_dead;
	}
	else if (mode == TOGGLE_FALSE)
	{
		philo->is_dead = false;
	}
	else if (mode == TOGGLE_TRUE)
	{
		philo->is_dead = true;
	}
	pthread_mutex_unlock(&philo->is_dead_mutex);
	return (is_dead);
}
