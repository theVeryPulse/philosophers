/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 02:08:14 by Philip            #+#    #+#             */
/*   Updated: 2024/03/16 23:09:51 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include <stdlib.h>

void	free_and_exit(t_info *info, t_philo *philos)
{
	free(philos);
	free(info->forks);
	exit (0);
}
