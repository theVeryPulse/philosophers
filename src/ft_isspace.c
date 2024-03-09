/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:00:17 by juli              #+#    #+#             */
/*   Updated: 2024/01/15 00:07:37 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Checks if the 'c' is a white-space character.
 * 
 * White-space characters are: ' ', '\\t', '\\n', '\\v', '\\f', and '\\r'.
 * 
 * @param c Character to check.
 * @return int 
 * Non-zero if the character is a white-space character, and zero otherwise.
 */
int	ft_isspace(int c)
{
	return ((c >= '\t' && c <= '\r') || c == ' ');
}
