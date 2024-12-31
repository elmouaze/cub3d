/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moua <ael-moua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:59:32 by ael-moua          #+#    #+#             */
/*   Updated: 2024/11/18 19:22:01 by ael-moua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int ft_strchr(const char *s)
{
    int index;

    index = 0;
	while (s[index])
	{
		if (s[index] == 'N' || s[index] == 'S' || s[index] == 'E' || s[index] == 'W')
			return (index);
		index++;
	}
	return (-1);
}