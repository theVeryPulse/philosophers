/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 23:35:43 by Philip            #+#    #+#             */
/*   Updated: 2024/03/18 13:46:16 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdbool.h>

typedef struct s_info
{
	pthread_mutex_t	*forks;
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_max_count;
	// Must hold lock to read/write
	int				full_philo_count;
	pthread_mutex_t	full_philo_count_mutex;
	long long		start_time;
	// Must hold lock to read/write
	bool			no_philo_died;
	pthread_mutex_t	no_philo_died_mutex;
	bool			philo_count_is_odd;
	pthread_mutex_t	printf_mutex;
}	t_info;

typedef struct s_philo
{
	// Time of last eat, measured from the start of stimulation.
	// Must hold lock to read/write
	long long		last_eat;
	pthread_mutex_t	last_eat_mutex;
	t_info			*shared_info;
	// Must hold lock to read/write
	int				eat_count;
	pthread_mutex_t	eat_count_mutex;
	int				philo_idx;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread;
	// Must hold lock to read/write
	bool			is_not_eating;
	pthread_mutex_t	is_not_eating_mutex;
	// Must hold lock to read/write
	bool			is_dead;
	pthread_mutex_t	is_dead_mutex;
	bool			idx_is_even_number;
}	t_philo;

typedef enum e_mode
{
	INCREMENT,
	LOOKUP,
	UPDATE,
	TOGGLE_TRUE,
	TOGGLE_FALSE,
}	t_mode;

/* Parse input */

int			ft_atoi(const char *nptr);
int			ft_isdigit(int c);
void		check_input(int argc, char const **argv);
void		parse_input(t_info *info, int argc, char const **argv);

/* Forks and philosophers management */

void		create_forks(t_info *info);
void		create_philos(t_info *info, t_philo **philos);
int			left_hand_fork_idx(t_info *info, int philo_idx);
void		monitor_philos(t_info *info, t_philo *philos);

/* Race-condition-safe operations */

long long	safe_last_eat(t_philo *philo, t_mode mode);
int			safe_eat_count(t_philo *philo, t_mode mode);
bool		safe_is_not_eating(t_philo *philo, t_mode mode);
int			safe_full_philo_count(t_info *info, t_mode mode);
bool		safe_no_philo_died(t_info *info, t_mode mode);
bool		safe_is_dead(t_philo *philo, t_mode mode);

/* Philosopher routine */

void		*routine(void *args);
void		philo_takes_forks(t_philo *philo);
void		put_down_forks(t_philo *philo);
void		philo_eats(t_philo *philo);
bool		philo_eats_enough(t_philo *philo);
void		philo_sleeps(t_philo *philo);
void		philo_thinks(t_philo *philo);

/* Time */

long long	time_since_epoch(void);
long long	time_since_start(t_info *info);
