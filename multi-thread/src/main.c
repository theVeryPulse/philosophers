/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 23:34:31 by Philip            #+#    #+#             */
/*   Updated: 2024/03/18 13:08:43 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void	one_philo_situation(t_info *info);
static void	join_threads(t_info *info, t_philo *philos);
static void	free_resources(t_info *info, t_philo *philos);

/**
 * @brief 
 * 
 * @note
 * ARGV:
 * number_of_philosophers
 * time_to_die (ms)
 * time_to_eat (ms)
 * time_to_sleep (ms)
 * [number_of_times_each_philosopher_must_eat] (optional)
 */
int	main(int argc, char const **argv)
{
	t_info	info;
	t_philo	*philos;

	check_input(argc, argv);
	parse_input(&info, argc, argv);
	if (info.philo_count == 1)
	{
		one_philo_situation(&info);
	}
	else
	{
		create_forks(&info);
		create_philos(&info, &philos);
		monitor_philos(&info, philos);
		join_threads(&info, philos);
		free_resources(&info, philos);
	}
	return (0);
}

static void	one_philo_situation(t_info *info)
{
	printf("0 1 has taken fork 1\t🍴\n");
	usleep(info->time_to_die * 1000);
	printf("%d 1 died after starving for %d\t😵\n",
		info->time_to_die, info->time_to_die);
}

static void	join_threads(t_info *info, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < info->philo_count)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}

static void	free_resources(t_info *info, t_philo *philos)
{
	free(philos);
	free(info->forks);
}
