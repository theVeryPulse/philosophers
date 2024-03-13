/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 23:34:31 by Philip            #+#    #+#             */
/*   Updated: 2024/03/13 23:44:55 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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
void	*routine(void *args)
{
	t_philo	*this;

	this = (t_philo *)args;
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
			time_since_start(this->shared_info),
			this->philo_idx + 1);
		usleep(this->shared_info->time_to_sleep * 1000);

		// Think

		printf("%lld %d is thinking\t🤔\n",
			time_since_start(this->shared_info),
			this->philo_idx + 1);
		usleep(1000); // 1ms
	}
	this->shared_info->full_philo_count++;
	/* printf("Increment full_philo_count to %d\n",
		this->shared_info->full_philo_count); */
	pthread_exit(NULL);
}

void	free_and_exit(t_info *info, t_philo *philos)
{
	free(philos);
	free(info->forks);
	// free(threads);
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



