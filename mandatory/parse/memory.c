/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moua <ael-moua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 04:23:16 by ael-moua          #+#    #+#             */
/*   Updated: 2024/11/20 04:43:56 by ael-moua         ###   ########.fr       */
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
