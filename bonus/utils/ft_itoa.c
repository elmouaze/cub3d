/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moua <ael-moua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 22:11:27 by ael-moua          #+#    #+#             */
/*   Updated: 2025/01/20 22:32:54 by ael-moua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static size_t	count_digits(long n)
{
	size_t	i;

	i = 1;
	while (n / 10)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*ascii;
	size_t	digits;
	long	nb;

	nb = n;
	digits = count_digits(nb);
	if (n < 0)
	{
		digits++;
		nb *= -1;
	}
	ascii = alloc(1, sizeof(char) * digits + 1);
	if (!ascii)
		return (NULL);
	*(ascii + (digits--)) = '\0';
	ascii[0] = '0';
	while (nb)
	{
		*(ascii + (digits--)) = nb % 10 + '0';
		nb = nb / 10;
	}
	if (n < 0)
		ascii[0] = '-';
	return (ascii);
}
