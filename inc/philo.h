/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 23:35:43 by Philip            #+#    #+#             */
/*   Updated: 2024/03/13 23:42:50 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_info
{
	pthread_mutex_t	*forks;
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_max_count;
	long long		start_time;
	int				full_philo_count;
}	t_info;

typedef struct s_philo
{
	// Time of last eat, measured from start of stimulation
	long long		last_eat;
	t_info			*shared_info;
	int				eat_count;
	int				philo_idx;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	bool			is_not_eating;
	pthread_t		thread;
}	t_philo;

int	ft_atoi(const char *nptr);
int	ft_isdigit(int c);
int	ft_isspace(int c);

void	check_input(int argc, char const **argv);
bool	non_digit_in(char const **argv);

/* Parse input */

void	parse_input(t_info *info, int argc, char const **argv);

/* Forks and philosophers */

void	create_forks(t_info *info);
void	create_philos(t_info *info, t_philo **philos);
int		left_hand_fork_idx(t_info *info, int philo_idx);
void	*routine(void *args);
void	monitor_philos(t_info *info, t_philo *philos);


/* Time */

long long	time_since_epoch(void);
long long	time_since_start(t_info *info);

void	free_and_exit(t_info *info, t_philo *philos);
