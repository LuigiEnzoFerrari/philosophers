/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_or_die.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenzo-pe <lenzo-pe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 01:33:25 by lenzo-pe          #+#    #+#             */
/*   Updated: 2022/03/10 01:34:36 by lenzo-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	someone_die(t_seats *seats)
{
	if (*seats->status == 0)
	{
		release_the_forks(seats);
		return (1);
	}
	return (0);
}

uint64_t	time_hungry(t_seats *seats, timeval *points)
{
	uint64_t	hungry;

	if (points[LAST_EAT].tv_sec != 0)
		hungry = difference(points[LAST_EAT], points[BREAK]);
	else
		hungry = difference(seats->rules->the_time, points[BREAK]);
	return (hungry);
}

static int	that_was_enough(t_seats *seats, timeval *points)
{
	if (seats->eat[EATEN] == seats->eat[LIMIT])
	{
		release_the_forks(seats);
		return (1);
	}
	return (0);
}

int	died_of_hungry(t_seats *seats, timeval *points, uint64_t waited)
{
	if (someone_die(seats))
		return (1);
	if (waited > seats->rules->act[DYING])
	{
		*seats->status = 0;
		release_the_forks(seats);
		printf(" %6lu \t%-15d IS DIED\n",
			micro_to_milli(difference(seats->rules->the_time,
					points[BREAK])), seats->id);
		return (1);
	}
	return (0);
}

int	eating_time(t_seats *seats, timeval *points)
{
	printf(" %6lu \t%-15d is eating\n",
		micro_to_milli(difference(seats->rules->the_time,
				points[BREAK])), seats->id);
	usleep(seats->rules->act[EATTT]);
	seats->eat[EATEN]++;
	if (that_was_enough(seats, points))
		return (1);
	return (0);
}
