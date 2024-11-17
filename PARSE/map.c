/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moua <ael-moua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 09:09:31 by ael-moua          #+#    #+#             */
/*   Updated: 2024/11/17 11:10:32 by ael-moua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static t_map    *new_node(char *line)
{
	t_map	*res;

	res = malloc(sizeof(t_map));
    if(!res)
        return (NULL);
	res->line = line;
    res->next = NULL;
	return (res);
}

static void	add_token(t_map **lst, t_map *new)
{
	t_map	*node;

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

int check_end(char *line)
{
    int i;

    i = 0;
    while(line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;
    if (line[i] == '\n' || !line[i])
        return(0);
    return (1);
}

char  **fill_map(char *str, int fd)
{
    t_map   *map;
    int     cond,size;
    char    *line;

    map = NULL;
    line = NULL;
    cond = 0;
    size = 0;
    add_token(&map,new_node(str));
    while ((line = get_next_line(fd)) )
    {
        if (!check_end(line))
        {
            free(line);
            break;
        }
        add_token(&map,new_node(line));
        line = NULL;
        size++;
    }
    while ((line = get_next_line(fd)))
    {
        if (check_end(line))
        {
            free(line);
            close(fd);
            ft_perror("something wrong");
        }
        free(line);
        line = NULL;
    }
    close(fd);
    return (build_map(map));
}