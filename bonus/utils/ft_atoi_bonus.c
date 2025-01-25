/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 05:13:20 by ael-moua          #+#    #+#             */
/*   Updated: 2025/01/25 11:08:08 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	ft_atoi(const char *str)
{
	unsigned long long	res;

	res = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '\0' || *str == '-')
		return (-1);
	if (*str == '+')
		str++;
	if (*str == '\0' || (*str >= 9 && *str <= 13) || *str == ' ')
		return (-1);
	while (*str >= '0' && *str <= '9')
	{
		res = (res * 10) + (*str - '0');
		if (res > 255)
			return (-1);
		str++;
	}
	while (*str == ' ')
		str++;
	if (*str != '\0')
		return (-1);
	return ((int)res);
}
