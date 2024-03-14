/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 23:34:31 by Philip            #+#    #+#             */
/*   Updated: 2024/03/14 02:09:44 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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
	create_forks(&info);
	philos = NULL;
	create_philos(&info, &philos);
	monitor_philos(&info, philos);
	free_and_exit(&info, philos);
	return (0);
}
