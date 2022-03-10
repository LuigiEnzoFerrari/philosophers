/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenzo-pe <lenzo-pe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 01:37:54 by lenzo-pe          #+#    #+#             */
/*   Updated: 2022/03/10 11:26:29 by lenzo-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_seats	*init_seat(void)
{
	t_seats	*seat;

	seat = malloc(sizeof(t_seats));
	memset((void *)seat, 0, sizeof(t_seats));
	seat->right = seat;
	seat->left = seat;
	return (seat);
}

void	add_seat_left(t_seats **seat)
{
	t_seats	*new;

	if (*seat == NULL)
	{
		*seat = init_seat();
		return ;
	}
	new = init_seat();
	new->right = (*seat);
	new->left = (*seat)->left;
	(*seat)->left->right = new;
	(*seat)->left = new;
}

static size_t	how_many_seats(t_seats *seats)
{
	t_seats	*ptr;
	size_t	i;

	ptr = seats;
	i = 0;
	while (42)
	{
		i++;
		ptr = ptr->right;
		if (ptr == seats)
			break ;
	}
	return (i);
}

void	clear_seats(t_seats *seats)
{
	t_seats	*ptr;
	size_t	i;

	i = how_many_seats(seats);
	ptr = seats;
	while (i--)
	{
		ptr = ptr->right;
		free(seats);
		seats = ptr;
	}
}
