/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moua <ael-moua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 08:10:02 by abennar           #+#    #+#             */
/*   Updated: 2024/11/20 12:27:13 by ael-moua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "cube3d.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	index;

	index = 0;
	while (s[index] != '\0')
	{
		write (fd, &s[index], 1);
		index++;
	}
}
void print_error(char *str,int exit_flag)
{
    ft_putstr_fd(str,2);
    if(exit_flag)
        exit(errno);
}

void    error(char *where, char *unexpactd, char *reason)
{
    if (where)
        write(2, where, ft_strlen(where));
    if (unexpactd)
        write(2, unexpactd, ft_strlen(unexpactd));
    if (reason)
        write(2, reason, ft_strlen(reason));
}