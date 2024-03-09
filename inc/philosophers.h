/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 23:35:43 by Philip            #+#    #+#             */
/*   Updated: 2024/03/09 22:27:21 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

// printf for testing
#include <stdio.h>

typedef struct s_info
{
	pthread_mutex_t	*forks;
	int				philos_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_max_count;
}	t_info;

typedef struct s_indi
{
	t_info	*info;
	int		philo_idx;
	long	last_eat;
}	t_individual;



int	ft_atoi(const char *nptr);
int	ft_isdigit(int c);
int	ft_isspace(int c);

