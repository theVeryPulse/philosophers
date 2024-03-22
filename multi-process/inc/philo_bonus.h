/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 22:08:41 by Philip            #+#    #+#             */
/*   Updated: 2024/03/21 16:59:06 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

typedef struct s_info
{
	int	philo_count;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	eat_max_count;
	bool	philo_count_is_odd;
}	t_info;


void	check_input(int argc, char const **argv);
void	parse_input(t_info *info, int argc, char const **argv);

int		ft_isdigit(int c);
int		ft_atoi(const char *nptr);

