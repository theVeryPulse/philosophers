/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 22:08:41 by Philip            #+#    #+#             */
/*   Updated: 2024/03/24 22:49:57 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <semaphore.h>

typedef struct s_info
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	// Must hold lock to read/write
	int				eat_count;
	pthread_mutex_t	eat_count_mutex;
	int				eat_max_count;
	bool			philo_count_is_odd;
	sem_t			*a_philo_died;
	// sem_t			*a_philo_is_full;
	sem_t			*printf_sem;
	sem_t			*forks;
	pid_t			*philo_pids;
	int				philo_no;
	long long		start_time;
	// Time of last eat, measured from the start of stimulation.
	// Must hold lock to read/write
	long long		last_eat;
	pthread_mutex_t	last_eat_mutex;
}	t_info;

typedef enum e_mode
{
	INCREMENT,
	LOOKUP,
	UPDATE,
}	t_mode;

/* Input */

int			ft_atoi(const char *nptr);
int			ft_isdigit(int c);
void		check_input(int argc, char const **argv);
void		parse_input(t_info *info, int argc, char const **argv);

/* Race-condition-safe operations */

long long	safe_last_eat(t_info *info, t_mode mode);
int			safe_eat_count(t_info *info, t_mode mode);

/* Philosopher routine */

void		philo_routine(t_info *info);
void		philo_takes_two_forks(t_info *info);
void		philo_eats(t_info *info);
void		philo_puts_down_forks(t_info *info);
void		philo_thinks(t_info *info);
void		philo_sleeps(t_info *info);

/* Track philosopher death */

void		*wait_philo_death(void *args);

/* Utilities */

void		unlink_all_sem(void);
void		close_all_sem(t_info *info);

/* Time */

long long	time_since_epoch(void);
long long	time_since_start(t_info *info);
