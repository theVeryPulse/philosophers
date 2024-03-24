/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 22:28:24 by Philip            #+#    #+#             */
/*   Updated: 2024/03/24 22:44:46 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	close_all_sem(t_info *info)
{
	sem_close(info->forks);
	sem_close(info->printf_sem);
	sem_close(info->a_philo_died);
}

void	unlink_all_sem(void)
{
	sem_unlink("forks");
	sem_unlink("printf");
	sem_unlink("died");
}
