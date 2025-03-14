/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moua <ael-moua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 03:16:03 by ael-moua          #+#    #+#             */
/*   Updated: 2025/01/20 22:34:25 by ael-moua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	index;

	index = 0;
	while (n > index)
	{
		((char *)s)[index] = 0;
		index++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	p = (void *)alloc(1, size * count);
	if (!p)
		alloc(0, 0);
	ft_bzero(p, count * size);
	return (p);
}
