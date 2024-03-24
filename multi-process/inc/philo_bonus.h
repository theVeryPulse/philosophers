/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 22:08:41 by Philip            #+#    #+#             */
/*   Updated: 2024/03/24 21:39:03 by Philip           ###   ########.fr       */
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
	// TOGGLE_TRUE,
	// TOGGLE_FALSE,
}	t_mode;


void	check_input(int argc, char const **argv);
void	parse_input(t_info *info, int argc, char const **argv);

int		ft_isdigit(int c);
int		ft_atoi(const char *nptr);

long long	time_since_epoch(void);
long long	time_since_start(t_info *info);


void	close_all_sem(t_info *info);
