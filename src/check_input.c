/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 22:44:32 by Philip            #+#    #+#             */
/*   Updated: 2024/03/13 23:45:51 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	check_input(int argc, char const **argv)
{
	if ((argc != 5 && argc != 6) || non_digit_in(argv))
		exit (1);
}

bool	non_digit_in(char const **argv)
{
	size_t	i;
	size_t	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) != true)
				return (true);
			j++;
		}
		i++;
	}
	return (false);
}

void	parse_input(t_info *info, int argc, char const **argv)
{
	info->philo_count = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->eat_max_count = ft_atoi(argv[5]);
	else
		info->eat_max_count = -1;
	printf("philo_count:%d\n", info->philo_count);
	printf("time_to_die:%d\n", info->time_to_die);
	printf("time_to_eat:%d\n", info->time_to_eat);
	printf("time_to_sleep:%d\n", info->time_to_sleep);
	printf("eat_max_count:%d\n\n", info->eat_max_count);
}
