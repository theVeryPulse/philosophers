/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_philo_death.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 22:26:27 by Philip            #+#    #+#             */
/*   Updated: 2024/03/24 22:44:40 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <signal.h>
#include <stddef.h>
#include <unistd.h>

void	*wait_philo_death(void *args)
{
	t_info	*info;
	int		i;

	info = (t_info *)args;
	sem_wait(info->printf_sem);
	sem_post(info->printf_sem);
	usleep(10e3);
	sem_wait(info->a_philo_died);
	i = 0;
	while (i < info->philo_count)
	{
		kill(info->philo_pids[i], SIGKILL);
		i++;
	}
	return (NULL);
}
