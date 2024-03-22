/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 21:24:24 by Philip            #+#    #+#             */
/*   Updated: 2024/03/22 23:51:37 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <semaphore.h>
#include <fcntl.h>           /* For O_* constants */
#include <stdio.h>

// fork
#include <unistd.h>

int	main(int argc, char const *argv[])
{
	t_info	info;
	sem_t	*forks;
	sem_t	*printf_sem;

	check_input(argc, argv);
	parse_input(&info, argc, argv);
	// forks = sem_open("forks", O_CREAT, 0755, 5);
	forks = sem_open("forks", O_CREAT, 0755, info.philo_count);
	printf_sem = sem_open("printf", O_CREAT, 0755, 1);


	// Create child processes
	int	i;
	pid_t	id;
	int	philo_no;

	id = 1;
	i = 0;
	while (i < info.philo_count)
	{
		if (id != 0)
		{
			philo_no = i + 1;
			id = fork();
		}
		if (id == 0)
		{
			// TODO Left here
			// Philosopher routine: eat -> think -> sleep 
			sem_wait(forks);
			sem_wait(printf_sem);
			printf("Picks up ");
			sem_wait(forks);
		}
	}

	sem_close(forks);
	sem_unlink("forks");
	return (0);
}
