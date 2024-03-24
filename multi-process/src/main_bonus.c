/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 21:24:24 by Philip            #+#    #+#             */
/*   Updated: 2024/03/24 21:46:44 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <semaphore.h>
#include <fcntl.h>           /* For O_* constants */
#include <stdio.h>
#include <pthread.h>

// fork
#include <unistd.h>

// wait
#include <sys/wait.h>

//malloc
#include <stdlib.h>

/*
void	*monitor_full_philos(void *args)
{
	t_info	*info;
	int		i;

	info = (t_info *)args;
	sem_wait(info->printf_sem);
	printf("Moniroting count of full philosophers.\n");
	sem_post(info->printf_sem);
	i = 0;
	while (i < info->philo_count)
	{
		sem_wait(info->a_philo_is_full);
		i++;
	}
	i = 0;
	while (i < info->philo_count)
	{
		kill(info->philo_pids[i], SIGKILL);
		i++;
	}
	// sem_wait(info->printf_sem);

}
// */

void	*wait_philo_death(void *args)
{
	t_info	*info;

	info = (t_info *)args;
	sem_wait(info->printf_sem);
	// printf("Moniroting philosopher death\n");
	sem_post(info->printf_sem);
	usleep(10e3);
	sem_wait(info->a_philo_died);
	printf("\n");
	/* sem_wait(info->printf_sem);
	printf("A philosopher died, terminating simulation\n"); */
	int	i;
	i = 0;
	while (i < info->philo_count)
	{
		// printf("Killing a child\n");
		kill(info->philo_pids[i], SIGKILL);
		i++;
	}
	// sem_wait(info->printf_sem);
	return (NULL);
}

long long	safe_last_eat(t_info *info, t_mode mode)
{
	long long	last_eat;

	last_eat = 0;
	pthread_mutex_lock(&info->last_eat_mutex);
	if (mode == LOOKUP)
	{
		last_eat = info->last_eat;
	}
	else if (mode == UPDATE)
	{
		info->last_eat = time_since_start(info);
	}
	pthread_mutex_unlock(&info->last_eat_mutex);
	return (last_eat);
}

int	safe_eat_count(t_info *info, t_mode mode)
{
	int	eat_count;

	eat_count = 0;
	pthread_mutex_lock(&info->eat_count_mutex);
	if (mode == INCREMENT)
	{
		info->eat_count++;
	}
	else if (mode == LOOKUP)
	{
		eat_count = info->eat_count;
	}
	pthread_mutex_unlock(&info->eat_count_mutex);
	return (eat_count);
}

void	*monitor_this_philo(void *args)
{
	t_info	*info;

	info = (t_info *)args;
	while (true)
	{
		if (info->eat_max_count != -1
			&& safe_eat_count(info, LOOKUP) >= info->eat_max_count)
		{
			// printf("Eat enought\n");
			break ;
		}
		if (time_since_start(info) - safe_last_eat(info, LOOKUP) > info->time_to_die)
		{
			sem_wait(info->printf_sem);
			printf("%lld %d died after starving for %lld\n", 
				time_since_start(info),
				info->philo_no,
				time_since_start(info) - info->last_eat);
			// sem_post(info->printf_sem);
			sem_post(info->a_philo_died);
			break ;
		}
		usleep(1000);
	}
	/* close_all_sem(info);
	free(info->philo_pids);
	exit(0); */
	// printf("Stopped monitoring itself\n");
	return (NULL);
}

void	close_all_sem(t_info *info)
{
	sem_close(info->forks);
	sem_close(info->printf_sem);
	sem_close(info->a_philo_died);
}

void	philo_takes_two_forks(t_info *info)
{
	// printf("%lld %d is waiting for a forkt\t🍴\n", time_since_start(info),
	// 	info->philo_no);
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
	// info->last_eat = time_since_start(info);
	safe_eat_count(info, INCREMENT);
	// info->eat_count++;
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

	sem_wait(info->printf_sem);
	printf("%lld %d has put down forks.\n", time_since_start(info),
		info->philo_no);
	sem_post(info->printf_sem);
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

void	philo_routine(t_info *info)
{
	int			forks_num;
	pthread_t	death_monitor;

	sem_getvalue(info->forks, &forks_num);
	// printf("Available forks: %d %d\n", forks_num, getpid());

	pthread_create(&death_monitor, NULL, monitor_this_philo, info);
	if (info->philo_no %2 == 0)
			usleep(1e3);
	while (true)
	{
		// Philosopher routine: eat -> think -> sleep 
		// Eat
		philo_takes_two_forks(info);
		philo_eats(info);
		philo_puts_down_forks(info);

		if (info->eat_max_count != -1
			&& info->eat_count >= info->eat_max_count)
		{
			break ;
		}
		// Think
		philo_thinks(info);
		
		// Sleep
		philo_sleeps(info);
	}
	sem_wait(info->printf_sem);
	printf("%lld %d stops. %d\n", time_since_start(info),
		info->philo_no, getpid());
	sem_post(info->printf_sem);
	pthread_join(death_monitor, NULL);
	close_all_sem(info);
	free(info->philo_pids);
	exit(0);
}

void	unlink_all_sem(void)
{
	sem_unlink("forks");
	sem_unlink("printf");
	sem_unlink("died");
	// sem_unlink("full");
}

int	main(int argc, char const *argv[])
{
	t_info	info;
	int	i;

	check_input(argc, argv);
	parse_input(&info, argc, argv);
	sem_unlink("forks");
	sem_unlink("printf");
	sem_unlink("died");
	sem_unlink("full");

	info.forks = NULL;
	info.printf_sem = NULL;
	info.a_philo_died = NULL;
	if ((info.forks = sem_open("forks", O_CREAT, 0666, info.philo_count)) == SEM_FAILED)
		printf("Something went wrong\n");
	if ((info.printf_sem = sem_open("printf", O_CREAT, 0666, 1)) == SEM_FAILED)
		printf("Something went wrong\n");
	if ((info.a_philo_died = sem_open("died", O_CREAT, 0666, 0)) == SEM_FAILED)
		printf("Something went wrong\n");
	pthread_mutex_init(&info.eat_count_mutex, NULL);
	pthread_mutex_init(&info.last_eat_mutex, NULL);

	int	forks_val, printf_val, philodied_val;
	sem_getvalue(info.forks, &forks_val);
	sem_getvalue(info.printf_sem, &printf_val);
	sem_getvalue(info.a_philo_died, &philodied_val);
	printf("Forks: %d\n", forks_val);
	printf("printf: %d\n", printf_val);
	printf("a_philo_died: %d\n", philodied_val);

	// Create child processes
	pid_t	id;

	sem_wait(info.printf_sem);
	printf("\nInitialization complete\n\n");
	sem_post(info.printf_sem);

	info.philo_pids = (pid_t *)malloc(sizeof(pid_t) * info.philo_count);
	id = 1;
	i = 0;
	info.start_time = time_since_epoch();
	info.last_eat = time_since_start(&info);
	info.eat_count = 0;
	while (i < info.philo_count)
	{
		if (id != 0) // Parent process
		{
			info.philo_no = i + 1;
			/* sem_wait(info.printf_sem);
			printf("Forking child\n");
			sem_post(info.printf_sem); */
			id = fork();
			info.philo_pids[i] = id;
		}
		if (id == 0) // Child process
		{
			philo_routine(&info);
		}
		i++;
	}

	// Monitor full philos and any dead philo
	// pthread_t	full_philo;
	pthread_t	philo_death;
	// if (id)
	{
		// pthread_create(&full_philo, NULL, monitor_full_philos, &info);
		pthread_create(&philo_death, NULL, wait_philo_death, &info);
		i = 0;
		while (i < info.philo_count)
		{
			waitpid(info.philo_pids[i++], NULL, 0);
			// printf("One child finished\n");
		}
		// printf("All child processes terminated.\n");
	}
	sem_post(info.a_philo_died);
	pthread_join(philo_death, NULL);
	free(info.philo_pids);
	close_all_sem(&info);
	unlink_all_sem();
	// printf("Ending process.\n");
	return (0);
}
