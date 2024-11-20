/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moua <ael-moua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 09:07:44 by ael-moua          #+#    #+#             */
/*   Updated: 2024/11/20 04:28:03 by ael-moua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static int	is_sep(char c, char const	*s)
{
	int	index;

	index = 0;
	while (s[index] != '\0')
	{
		if (s[index] == c)
			return (1);
		index++;
	}
	return (0);
}

char	*ft_strtrim(char *s1, char const *set)
{
	char	*res;
	int		index;
	int		end;

	if (!s1 || !set)
		return (NULL);
	end = ft_strlen(s1);
	if (end == 0)
		return (NULL);
	index = 0;
	while (is_sep(s1[index], set) == 1 && s1[index] != '\0')
		index++;
	while (is_sep(s1[end - 1], set) == 1 && end >= index)
		end--;
	if (index >= end)
		return (NULL);
	res = (char *)alloc (1,sizeof(char) * (end - index + 1));
	if (!res)
		return (alloc(0,0));
	ft_strlcpy(res, &s1[index], end - index + 1);
	return (res);
}
