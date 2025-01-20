/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_and_errors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moua <ael-moua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 04:23:16 by ael-moua          #+#    #+#             */
/*   Updated: 2025/01/20 22:31:38 by ael-moua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_all(_data **data)
{
	_data	*tmp;
	_data	*node;

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
	static _data	*head;
	void			*res;
	_data			*node;

	if (mode == 1)
	{
		node = malloc(sizeof(_data));
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
	map->EA = NULL;
	map->NO = NULL;
	map->SO = NULL;
	map->WE = NULL;
}
