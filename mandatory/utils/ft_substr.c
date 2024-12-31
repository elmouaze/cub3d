/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moua <ael-moua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 03:43:19 by ael-moua          #+#    #+#             */
/*   Updated: 2024/11/17 03:43:36 by ael-moua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*p;
	int				index;
	unsigned int	size;

	size = (unsigned int) ft_strlen(s);
	index = 0;
	if (len > size - start)
		len = size - start;
	if (start > size)
		len = 0;
	p = (char *) malloc(sizeof(char) * (len + 1));
	if (!p)
		return (NULL);
	if (size >= start)
	{
		while (s[start] != '\0' && len)
		{
			p[index++] = s[start++];
			len--;
		}
	}
	p[index] = '\0';
	return (p);
}