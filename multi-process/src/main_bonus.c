/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 21:24:24 by Philip            #+#    #+#             */
/*   Updated: 2024/03/24 22:44:20 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
// For O_* constants
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
// malloc
#include <stdlib.h>
// fork()
#include <unistd.h>
#include <sys/wait.h>

static void	set_up_sem_and_mutex(t_info *info);
static void	create_philo_child_processes(t_info *info);
static void	monitor_philos(t_info *info);
static void	destroy_resources(t_info *info);

int	main(int argc, char const *argv[])
{
	t_info	info;

	check_input(argc, argv);
	parse_input(&info, argc, argv);
	set_up_sem_and_mutex(&info);
	create_philo_child_processes(&info);
	monitor_philos(&info);
	destroy_resources(&info);
	return (0);
}

static void	set_up_sem_and_mutex(t_info *info)
{
	unlink_all_sem();
	info->forks = NULL;
	info->printf_sem = NULL;
	info->a_philo_died = NULL;
	info->forks = sem_open("forks", O_CREAT, 0666, info->philo_count);
	info->printf_sem = sem_open("printf", O_CREAT, 0666, 1);
	info->a_philo_died = sem_open("died", O_CREAT, 0666, 0);
	pthread_mutex_init(&info->eat_count_mutex, NULL);
	pthread_mutex_init(&info->last_eat_mutex, NULL);
}

static void	create_philo_child_processes(t_info *info)
{
	pid_t	id;
	int		i;

	info->philo_pids = (pid_t *)malloc(sizeof(pid_t) * info->philo_count);
	id = 1;
	i = 0;
	info->start_time = time_since_epoch();
	info->last_eat = time_since_start(info);
	info->eat_count = 0;
	while (i < info->philo_count)
	{
		if (id != 0)
		{
			info->philo_no = i + 1;
			id = fork();
			info->philo_pids[i] = id;
		}
		if (id == 0)
		{
			philo_routine(info);
		}
		i++;
	}
}

static void	monitor_philos(t_info *info)
{
	pthread_t	philo_death;
	int			i;

	pthread_create(&philo_death, NULL, wait_philo_death, info);
	i = 0;
	while (i < info->philo_count)
	{
		waitpid(info->philo_pids[i++], NULL, 0);
	}
	sem_post(info->a_philo_died);
	pthread_join(philo_death, NULL);
}

static void	destroy_resources(t_info *info)
{
	free(info->philo_pids);
	close_all_sem(info);
	unlink_all_sem();
}
