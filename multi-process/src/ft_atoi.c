/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:42:04 by juli              #+#    #+#             */
/*   Updated: 2024/03/21 16:59:54 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

#define POSITIVE (+1)
#define NEGATIVE (-1)
#define BASE_TEN (10)

static int	num(char c);
static int	ft_isspace(int c);

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = POSITIVE;
	result = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-')
	{
		sign = NEGATIVE;
		i++;
	}
	else if (nptr[i] == '+')
	{
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		result = result * BASE_TEN + num(nptr[i]);
		i++;
	}
	return (result * sign);
}

static int	num(char c)
{
	if (ft_isdigit(c))
	{
		return (c - '0');
	}
	else
	{
		return (c);
	}
}

/**
 * @brief Checks if the 'c' is a white-space character.
 * 
 * White-space characters are: ' ', '\\t', '\\n', '\\v', '\\f', and '\\r'.
 * 
 * @param c Character to check.
 * @return int 
 * Non-zero if the character is a white-space character, and zero otherwise.
 */
static int	ft_isspace(int c)
{
	return ((c >= '\t' && c <= '\r') || c == ' ');
}
