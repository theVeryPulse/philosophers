/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 22:23:03 by Philip            #+#    #+#             */
/*   Updated: 2024/03/24 22:38:14 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

void	philo_takes_two_forks(t_info *info)
{
	sem_wait(info->forks);
	sem_wait(info->printf_sem);
	printf("%lld %d has taken a forkt\t🍴\n", time_since_start(info),
		info->philo_no);
	sem_post(info->printf_sem);
	sem_wait(info->forks);
	sem_wait(info->printf_sem);
	printf("%lld %d has taken another fork.\n", time_since_start(info),
		info->philo_no);
	sem_post(info->printf_sem);
}

void	philo_eats(t_info *info)
{
	sem_wait(info->printf_sem);
	printf("%lld %d is eating\t🍝\n", time_since_start(info),
		info->philo_no);
	sem_post(info->printf_sem);
	safe_last_eat(info, UPDATE);
	safe_eat_count(info, INCREMENT);
	usleep(info->time_to_eat * 1e3);
	sem_wait(info->printf_sem);
	printf("%lld %d has eaten %d times.\n", time_since_start(info),
		info->philo_no, info->eat_count);
	sem_post(info->printf_sem);
}

void	philo_puts_down_forks(t_info *info)
{
	sem_post(info->forks);
	sem_post(info->forks);
}

void	philo_thinks(t_info *info)
{
	sem_wait(info->printf_sem);
	printf("%lld %d is thinking\t🤔\n", time_since_start(info),
		info->philo_no);
	sem_post(info->printf_sem);
	usleep(1e3);
}

void	philo_sleeps(t_info *info)
{
	sem_wait(info->printf_sem);
	printf("%lld %d is sleeping\t😴\n", time_since_start(info),
		info->philo_no);
	sem_post(info->printf_sem);
	usleep(info->time_to_sleep * 1e3);
}
