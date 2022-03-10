/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_party.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenzo-pe <lenzo-pe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 01:33:13 by lenzo-pe          #+#    #+#             */
/*   Updated: 2022/03/10 01:36:09 by lenzo-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	partying(t_seats *seats, timeval *points)
{
	uint64_t	waited;

	while (42)
	{
		if (take_the_forks(seats, points))
			break ;
		waited = time_hungry(seats, points);
		if (died_of_hungry(seats, points, waited))
			break ;
		else if (eating_time(seats, points))
			break ;
		release_the_forks(seats);
		if (sleeping_and_thinking(seats, points))
			break ;
	}
}

void	*the_party(void *arg)
{
	t_seats	*seats;
	timeval	points[2];

	memset(&points[LAST_EAT], 0, sizeof(timeval));
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
		usleep(5);
		pthread_create(&seats->philo, NULL, &the_party, seats);
		seats = seats->right;
		if (seats == ptr)
			break ;
	}
}
