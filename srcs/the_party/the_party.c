/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_party.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 01:33:13 by lenzo-pe          #+#    #+#             */
/*   Updated: 2022/03/10 22:16:11 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	partying(t_seats *seats, t_timeval *points)
{
	uint64_t	waited;

	gettimeofday(&points[LAST_EAT], NULL);
	while (42)
	{
		if (take_the_forks(seats, points))
			break ;
		waited = time_hungry(points);
		if (died_of_hungry(seats, points, waited))
			break ;
		else if (eating_time(seats, points, waited))
			break ;
		release_the_forks(seats);
		if (sleeping_and_thinking(seats, points))
			break ;
	}
}

void	*the_party(void *arg)
{
	t_seats		*seats;
	t_timeval	points[2];

	seats = (t_seats *)arg;
	partying(seats, points);
	return (NULL);
}

void	everyone_lets_party(t_seats *seats)
{
	t_seats	*ptr;

	ptr = seats;
	while (42)
	{
		usleep(420);
		pthread_create(&seats->philo, NULL, &the_party, seats);
		seats = seats->right;
		if (seats == ptr)
			break ;
	}
}
