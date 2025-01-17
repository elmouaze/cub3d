/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 19:39:20 by abennar           #+#    #+#             */
/*   Updated: 2023/12/17 19:27:49 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


char	*ft_strndup(char *str, size_t n)
{
	char	*r_str;
	size_t	i;

	if (!str || n == 0)
		return (NULL);
	i = 0;
	r_str = (char *)alloc(1, (n + 1) * sizeof(char));
	if (!r_str)
		return (NULL);
	while (i < n && str[i])
	{
		r_str[i] = str[i];
		i++;
	}
	r_str[i] = '\0';
	return (r_str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*r_line;

	if (!s1 || !s2)
	{
		if (s1)
			return (ft_strndup(s1, ft_strlen(s1)));
		else if (s2)
			return (ft_strndup(s2, ft_strlen(s2)));
		return (NULL);
	}
	i = 0;
	r_line = (char *)alloc(1, sizeof(char) * (ft_strlen(s2) + ft_strlen(s1) + 1));
	if (!r_line)
		return (s1 = NULL, NULL);
	j = 0;
	while (s1[i])
		r_line[j++] = s1[i++];
	i = 0;
	while (s2[i])
		r_line[j++] = s2[i++];
	r_line[j] = '\0';
	return (s1 = NULL, r_line);
}

bool	detect_n(char *buff)
{
	int	i;

	if (!buff)
		return (false);
	i = 0;
	while (buff[i])
	{
		if (buff[i] == '\n')
			return (true);
		i++;
	}
	return (false);
}
