/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 23:34:31 by Philip            #+#    #+#             */
/*   Updated: 2024/03/12 23:44:13 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long long	time_now(void)
{
	struct timeval	time;
	long long		milliseconds;

	gettimeofday(&time, NULL);
	milliseconds = time.tv_sec * 1000LL + time.tv_usec / 1000LL;
	return (milliseconds);
}

long long	time_since_start(t_info *info)
{
	return (time_now() - info->start_time);
}

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
int	right_hand_fork(t_philo *this)
{
	return (this->philo_idx);
}

int	left_hand_fork_idx(t_info *info, int philo_idx)
{
	if (philo_idx != 0)
		return (philo_idx - 1);
	else
		return (info->philo_count - 1);
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
	t_philo	*this;

	this = (t_philo *)args;
	// printf("This is number %d, id: %ld\n", this->philo_idx, pthread_self());
	while (true)
	{

		// Eat

		// Right then left forks
		if (this->philo_idx % 2 == 0)
		{
			pthread_mutex_lock(this->right_fork);
			printf("%lld %d has taken fork %d\t🍴\n",
				time_since_start(this->shared_info),
				this->philo_idx + 1,
				this->philo_idx + 1);

			pthread_mutex_lock(this->left_fork);
			printf("%lld %d has taken fork %d\t🍴\n",
				time_since_start(this->shared_info),
				this->philo_idx + 1,
				left_hand_fork_idx(this->shared_info, this->philo_idx) + 1);
		}
		else // Left then right forks 
		{
			pthread_mutex_lock(this->left_fork);
			printf("%lld %d has taken fork %d\t🍴\n",
				time_since_start(this->shared_info),
				this->philo_idx + 1,
				left_hand_fork_idx(this->shared_info, this->philo_idx) + 1);

			pthread_mutex_lock(this->right_fork);
			printf("%lld %d has taken fork %d\t🍴\n",
				time_since_start(this->shared_info),
				this->philo_idx + 1,
				this->philo_idx + 1);
		}

		this->last_eat = time_since_start(this->shared_info);
		this->is_not_eating = false;
		printf("%lld %d is eating\t🍝\n",
			time_since_start(this->shared_info),
			this->philo_idx + 1);
		usleep(this->shared_info->time_to_eat * 1000);

		pthread_mutex_unlock(this->right_fork);
		pthread_mutex_unlock(this->left_fork);

		this->is_not_eating = true;
		this->eat_count++;

		printf("%lld %d has eaten %d times\n",
			time_since_start(this->shared_info),
			this->philo_idx + 1,
			this->eat_count);
		if (this->shared_info->eat_max_count > 0
			&& this->eat_count == this->shared_info->eat_max_count)
		{
			printf("%lld %d stops\n",
				time_since_start(this->shared_info),
				this->philo_idx + 1);
			break;
		}

		// Sleep

		printf("%lld %d is sleeping\t😴\n", 
			time_now() - this->shared_info->start_time,
			this->philo_idx + 1);
		usleep(this->shared_info->time_to_sleep * 1000);

		// Think

		printf("%lld %d is thinking\t🤔\n",
			time_now() - this->shared_info->start_time,
			this->philo_idx + 1);
		usleep(1000); // 1ms
	}
	this->shared_info->full_philo_count++;
	/* printf("Increment full_philo_count to %d\n",
		this->shared_info->full_philo_count); */
	pthread_exit(NULL);
}

void	free_and_exit(t_philo *philos, t_info *info, pthread_t *threads)
{
	free(philos);
	free(info->forks);
	free(threads);
	exit (0);
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
		return (1);

	// Parse the input =========================================================

	info.philo_count = ft_atoi(argv[1]);
	info.time_to_die = ft_atoi(argv[2]);
	info.time_to_eat = ft_atoi(argv[3]);
	info.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info.eat_max_count = ft_atoi(argv[5]);
	else
		info.eat_max_count = -1;

	printf("philo_count:%d\n", info.philo_count);
	printf("time_to_die:%d\n", info.time_to_die);
	printf("time_to_eat:%d\n", info.time_to_eat);
	printf("time_to_sleep:%d\n", info.time_to_sleep);
	printf("eat_max_count:%d\n\n", info.eat_max_count);

	// Create mutexes ==========================================================

	int	i;

	info.forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * info.philo_count);
	if (!info.forks)
		return (1);
	i = 0;
	while (i < info.philo_count)
	{
		pthread_mutex_init(&info.forks[i], NULL);
		i++;
	}

	// Create threads ==========================================================

	pthread_t		*threads;
	t_philo	*philos;

	info.full_philo_count = 0;
	threads = (pthread_t *)malloc(sizeof(pthread_t) * info.philo_count);
	philos = (t_philo *)malloc(sizeof(t_philo) * info.philo_count);
	info.start_time = time_now();
	i = 0;
	while (i < info.philo_count)
	{
		philos[i].shared_info = &info;
		philos[i].philo_idx = i;
		philos[i].last_eat = 0;
		philos[i].eat_count = 0;
		philos[i].left_fork = &info.forks[left_hand_fork_idx(&info, i)];
		philos[i].right_fork = &info.forks[i];
		philos[i].is_not_eating = true;
		pthread_create(&threads[i], NULL, routine, &philos[i]);
		i++;
	}

	// Monitor philosophers ====================================================

	while (info.full_philo_count != info.philo_count)
	{
		/* printf("full_philo_count: %d, philo_count: %d\n",
			info.full_philo_count,
			info.philo_count); */
		i = 0;
		while (i < info.philo_count)
		{
			/* printf("%lld %d since last eat: %lld\n",
				time_since_start(&info),
				i,
				time_since_start(&info) - philos[i].last_eat); */
			if (philos[i].eat_count == info.eat_max_count)
			{
				i++;
				continue ;
			}
			if ((time_since_start(&info) - philos[i].last_eat > info.time_to_die
				&& philos[i].is_not_eating))
			{
				printf("%lld %d died after starving for %lld\t😵\n",
					time_since_start(&info),
					i + 1,
					time_since_start(&info) - philos[i].last_eat);
				free_and_exit(philos, &info, threads);
			}
			i++;
		}
		usleep(1e3); // 0.5 millisecond
	}
	// printf("Main stops monitoring.\n");
	/* i = 0;
	while (i < info.philo_count)
	{
		pthread_join(threads[i], NULL);
		i++;
	} */

	free(philos);
	free(info.forks);
	free(threads);
	return (0);
}



