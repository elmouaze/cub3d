/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moua <ael-moua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 05:07:24 by ael-moua          #+#    #+#             */
/*   Updated: 2024/11/17 05:20:23 by ael-moua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static int	ft_count_words(char const *s, char c)
{
	int	counter;
	int	index;

	index = 0;
	counter = 0;
	if (!s)
		return (0);
	while (s[index])
	{
		while (s[index] == c)
			index++;
		if (s[index])
			counter++;
		while (s[index] != c && s[index])
			index++;
	}
	if (counter == 0)
		return (1);
	return (counter);
}

void	ft_free_memory(char **res)
{
	int	i;

	i = 0;
	while (res[i])
	{
		free(res[i]);
		i++;
	}
	free(res);
	res = NULL;
}

static char	*ft_count_char(char const *s, char c)
{
	char		*str;
	int			counter;
	int			index;

	counter = 0;
	index = 0;
	while (s[counter] != c && s[counter])
		counter++;
	str = (char *)malloc(sizeof(char) * (counter + 1));
	if (!str)
		return (NULL);
	while (counter)
	{
		str[index] = s[index];
		index++;
		counter--;
	}
	str[index] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		i;
	int		count_w;

	if (!s)
		return (NULL);
	count_w = ft_count_words(s, c);
	res = (char **)malloc(sizeof(char *) * (count_w + 1));
	if (!res)
		return (NULL);
	i = -1;
	while (++i < count_w)
	{
		while (*s == c && c)
			s++;
		res[i] = ft_count_char(s, c);
		if (!res[i])
		{
			ft_free_memory(res);
			return (NULL);
		}
		s += ft_strlen(res[i]);
	}
	res[i] = NULL;
	return (res);
}