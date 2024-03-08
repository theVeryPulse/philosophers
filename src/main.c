/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 23:34:31 by Philip            #+#    #+#             */
/*   Updated: 2024/03/08 23:46:27 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void *routine(void *args)
{
	
}

/**
 * @brief 
 * 
 * @note
 * ARGV:
 * number_of_philosophers
 * time_to_die (ms)
 * time_to_eat (ms)
 * time_to_sleep (ms)
 * [number_of_times_each_philosopher_must_eat] (optional) (ms)
 */
int main(int argc, char const **argv)
{
	int	i;
	pthread_mutex_t forks[5];
	pthread_t philos[5];
	i = 0;
	while (i < 5)
	{
		pthread_mutex_init(&forks[i], NULL);
	}

	i = 0;
	while (i < 5)
	{
		pthread_create(&philos[i], NULL, routine, NULL);
	}
	
	return 0;
}



