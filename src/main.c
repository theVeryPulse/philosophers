/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 23:34:31 by Philip            #+#    #+#             */
/*   Updated: 2024/03/09 23:09:03 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

bool	non_digit_in(char const **argv)
{
	size_t	i;
	size_t	j;

	i = 1;
	while(argv[i])
	{
		j = 0;
		while(argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) != true)
				return (true);
			j++;
		}
		i++;
	}
	return (false);
}

/**
 * philos 0 1 2
 * forks  0 1 2
 * fork2 philo0 fork0 philo1 fork1 philo2
 */
int	right_hand_fork(t_individual *this)
{
	return (this->philo_idx);
}

int	left_hand_fork(t_individual *this)
{
	if (this->philo_idx != 0)
		return (this->philo_idx - 1);
	else
		return (this->info->philos_count - 1);
}


/**
 * @brief 
 * 
 * @param 
 * @return 
 * @note
 * eat -> sleep -> think -> eat -> ... 
 * 
 * timestamp_in_ms X has taken a fork
 * timestamp_in_ms X is eating
 * timestamp_in_ms X is sleeping
 * timestamp_in_ms X is thinking
 * timestamp_in_ms X died 😵
 */
void *routine(void *args)
{
	t_individual	*this;
	struct timeval	time;

	this = (t_individual *)args;
	// printf("This is number %d, id: %ld\n", this->philo_idx, pthread_self());
	while (true)
	{
		// Eat
		/* gettimeofday(&time, NULL);
		printf("%ld %d is waiting for fork (%d)\n", time.tv_sec, this->philo_idx, right_hand_fork(this)); */
		pthread_mutex_lock(&(this->info->forks[right_hand_fork(this)]));
		gettimeofday(&time, NULL);
		printf("%ld %d has taken fork (%d) 🍴\n", time.tv_sec, this->philo_idx, right_hand_fork(this));

		/* gettimeofday(&time, NULL);
		printf("%ld %d is waiting for fork (%d)\n", time.tv_sec, this->philo_idx, left_hand_fork(this)); */
		pthread_mutex_lock(&(this->info->forks[left_hand_fork(this)]));
		gettimeofday(&time, NULL);
		printf("%ld %d has taken fork (%d) 🍴\n", time.tv_sec, this->philo_idx, left_hand_fork(this));

		gettimeofday(&time, NULL);
		printf("%ld %d is eating 🍝\n", time.tv_sec, this->philo_idx);
		usleep(this->info->time_to_eat);

/* 		if (pthread_mutex_unlock(&(this->info->forks[right_hand_fork(this)])) == 0)
			printf("%ld %d has put down fork (%d)\n", time.tv_sec, this->philo_idx, right_hand_fork(this));
		if (pthread_mutex_unlock(&(this->info->forks[left_hand_fork(this)])) == 0)
			printf("%ld %d has put down fork (%d)\n", time.tv_sec, this->philo_idx, left_hand_fork(this));
 */
		pthread_mutex_unlock(&(this->info->forks[right_hand_fork(this)]));
		pthread_mutex_unlock(&(this->info->forks[left_hand_fork(this)]));
		// Sleep
		printf("%ld %d is sleeping 😴\n", time.tv_sec, this->philo_idx);
		usleep(this->info->time_to_sleep);
		
		// Think
		gettimeofday(&time, NULL);
		printf("%ld %d is thinking 🤔\n", time.tv_sec, this->philo_idx);
		usleep((this->info->time_to_die) / 2);

	}
	pthread_exit(NULL);
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
 * [number_of_times_each_philosopher_must_eat] (optional)
 */
int main(int argc, char const **argv)
{
	t_info	info;

	if ((argc != 5 && argc != 6) || non_digit_in(argv))
		return (0);

	// Parse the input =========================================================

	info.philos_count = ft_atoi(argv[1]);
	info.time_to_die = ft_atoi(argv[2]);
	info.time_to_eat = ft_atoi(argv[3]);
	info.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info.eat_max_count = ft_atoi(argv[5]);
	else
		info.eat_max_count = -1;

	printf("philos_count:%d\n", info.philos_count);
	printf("time_to_die:%d\n", info.time_to_die);
	printf("time_to_eat:%d\n", info.time_to_eat);
	printf("time_to_sleep:%d\n", info.time_to_sleep);
	printf("eat_max_count:%d\n", info.eat_max_count);

	// Create mutexes ==========================================================

	int	i;

	info.forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * info.philos_count);
	if (!info.forks)
		return (1);
	i = 0;
	while (i < info.philos_count)
	{
		pthread_mutex_init(&info.forks[i], NULL);
		i++;
	}

	// Create threads ==========================================================

	pthread_t		*philos;
	t_individual	*individuals;

	philos = (pthread_t *)malloc(sizeof(pthread_t) * info.philos_count);
	individuals = (t_individual *)malloc(sizeof(t_individual) * info.philos_count);
	i = 0;
	while (i < info.philos_count)
	{
		individuals[i].info = &info;
		individuals[i].philo_idx = i;
		individuals[i].last_eat = 0;
		pthread_create(&philos[i], NULL, routine, &individuals[i]);
		i++;
	}

	// Monitor philosophers ====================================================

	// struct timeval	time;

	// while (true)
	// {
	// 	i = 0;
	// 	while (i < info.philos_count)
	// 	{
	// 		gettimeofday(&time, NULL);
	// 		if (individuals[i].last_eat > info.time_to_die)
	// 			printf("%ld %d died\n", )
	// 	}
	// }

	i = 0;
	while (i < info.philos_count)
	{
		pthread_join(philos[i], NULL);
		i++;
	}

	free(individuals);
	free(info.forks);
	free(philos);
}



