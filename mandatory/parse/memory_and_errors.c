/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_and_errors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 04:23:16 by ael-moua          #+#    #+#             */
/*   Updated: 2025/01/24 09:29:57 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_all(t_gbc_data **data)
{
	t_gbc_data	*tmp;
	t_gbc_data	*node;

	if (!data || !*data)
		return ;
	node = *data;
	while (node && *data)
	{
		tmp = node->next;
		if (node->value)
			free(node->value);
		free(node);
		node = tmp;
	}
	*data = NULL;
}

void	*alloc(int mode, int size)
{
	static t_gbc_data	*head;
	void				*res;
	t_gbc_data			*node;

	if (mode == 1)
	{
		node = malloc(sizeof(t_gbc_data));
		if (!node)
			return (free_all(&head), exit(1), NULL);
		res = malloc(size);
		if (!res)
			return (free_all(&head), exit(1), NULL);
		node->value = res;
		node->next = NULL;
		if (head)
			node->next = head;
		head = node;
		return (res);
	}
	return (free_all(&head), NULL);
}

void	ft_perror(char *str)
{
	printf("%s\n", str);
	alloc(0, 0);
	exit(1);
}

void	init_map(t_data *map)
{
	map->map_hieght = -1;
	map->map_width = -1;
	map->x_player = -1;
	map->y_player = -1;
	map->ciel_rgb = -1;
	map->floor_rgb = -1;
	map->ea = NULL;
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
}
