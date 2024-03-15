/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 23:34:31 by Philip            #+#    #+#             */
/*   Updated: 2024/03/15 01:36:59 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	one_philo_situation(t_info *info);
static void	join_threads(t_info *info, t_philo *philos);

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
		return (0);
	}
	create_forks(&info);
	philos = NULL;
	create_philos(&info, &philos);
	monitor_philos(&info, philos);
	join_threads(&info, philos);
	free_and_exit(&info, philos);
	return (0);
}

static void	one_philo_situation(t_info *info)
{
	printf("0 1 has taken fork 1\t🍴\n");
	usleep(info->time_to_die);
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
