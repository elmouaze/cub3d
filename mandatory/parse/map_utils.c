/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moua <ael-moua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 22:12:40 by ael-moua          #+#    #+#             */
/*   Updated: 2025/01/26 19:25:35 by ael-moua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_fill(char *str)
{
	int		index;
	char	*res;

	index = 0;
	if (!str)
		return (NULL);
	res = alloc (1, ft_strlen(str) + 1);
	if (!res)
		return (alloc(0, 0), NULL);
	while (str[index] != '\0')
	{
		res[index] = str[index];
		index++;
	}
	res[index] = '\0';
	return (res);
}

t_parse_map	*new_node(char *line, size_t len)
{
	t_parse_map	*res;

	res = alloc(1, sizeof(t_parse_map));
	if (!res)
		alloc(0, 0);
	res->line = ft_fill(line);
	res->size = len;
	res->next = NULL;
	return (res);
}

void	add_token(t_parse_map **lst, t_parse_map *new)
{
	t_parse_map	*node;

	if (!*lst)
		*lst = new;
	else
	{
		node = *lst;
		while (node && (node)->next != NULL)
			node = (node)->next;
		(node)->next = new;
	}
}

int	check_end(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\n'))
		i++;
	if (!line[i])
		return (0);
	return (1);
}

int	is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	if (c != '0' && c != '1' && c != ' ' )
		return (ft_perror("Error: Forbidden symbols"), 1);
	return (0);
}
