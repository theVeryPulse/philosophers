/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 16:07:15 by Philip            #+#    #+#             */
/*   Updated: 2024/03/17 17:34:11 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

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

int	left_hand_fork_idx(t_info *info, int philo_idx)
{
	if (philo_idx != 0)
		return (philo_idx - 1);
	else
		return (info->philo_count - 1);
}
