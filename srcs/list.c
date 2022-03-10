/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenzo-pe <lenzo-pe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 01:37:54 by lenzo-pe          #+#    #+#             */
/*   Updated: 2022/03/10 01:39:43 by lenzo-pe         ###   ########.fr       */
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
