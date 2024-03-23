/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 21:24:24 by Philip            #+#    #+#             */
/*   Updated: 2024/03/23 01:59:09 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <semaphore.h>
#include <fcntl.h>           /* For O_* constants */
#include <stdio.h>

// fork
#include <unistd.h>

// wait
#include <sys/wait.h>

int	main(int argc, char const *argv[])
{
	t_info	info;
	sem_t	*forks;
	sem_t	*printf_sem;
	int	i;

	check_input(argc, argv);
	parse_input(&info, argc, argv);
	forks = sem_open("forks", O_CREAT, 0755, 5);
	// i = 0;
	// while (i++ < info.philo_count)
	// 	sem_post(forks);
	printf_sem = sem_open("printf", O_CREAT, 0755, 1);

	// Create child processes
	pid_t	id;
	int	philo_no;

	id = 1;
	i = 0;
	while (i < info.philo_count)
	{
		if (id != 0) // Parent process
		{
			philo_no = i + 1;
			id = fork();
		}
		if (id == 0) // Child process
		{
			sem_wait(printf_sem);
			printf("This is child %d\n", getpid());
			sem_post(printf_sem);
			while (true)
			{
				// Philosopher routine: eat -> think -> sleep 
				// Eat
				sem_wait(forks);
				sem_wait(printf_sem);
				printf("%d has taken a fork.\n", philo_no);
				sem_post(printf_sem);

				sem_wait(forks);
				sem_wait(printf_sem);
				printf("%d has taken another fork.\n", philo_no);
				sem_post(printf_sem);

				sem_wait(printf_sem);
				printf("%d is eating.\n", philo_no);
				sem_post(printf_sem);
				sem_post(forks);
				sem_post(forks);
				usleep(info.time_to_eat * 1e3);

				// Think
				sem_wait(printf_sem);
				printf("%d is thinking.\n", philo_no);
				sem_post(printf_sem);
				usleep(1e3);
				
				// Sleep
				sem_wait(printf_sem);
				printf("%d is sleeping.\n", philo_no);
				sem_post(printf_sem);
				usleep(info.time_to_sleep * 1e3);
			}

		}
		i++;
	}

	if (id)
	{
		i = 0;
		while (i++ < info.philo_count)
		wait(NULL);
		sem_close(forks);
		sem_unlink("forks");
	}
	return (0);
}
