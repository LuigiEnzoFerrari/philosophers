/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_or_die.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 01:33:25 by lenzo-pe          #+#    #+#             */
/*   Updated: 2022/03/10 21:21:08 by coder            ###   ########.fr       */
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

uint64_t	time_hungry(t_timeval *points)
{
	uint64_t	hungry;

	hungry = difference(points[LAST_EAT], points[BREAK]);
	return (hungry);
}

static int	that_was_enough(t_seats *seats)
{
	if (seats->eat[EATEN] == seats->eat[LIMIT])
	{
		release_the_forks(seats);
		return (1);
	}
	return (0);
}

int	died_of_hungry(t_seats *seats, t_timeval *points, uint64_t waited)
{
	if (someone_die(seats))
		return (1);
	if (waited > seats->rules->act[DYING])
	{
		*seats->status = 0;
		release_the_forks(seats);
		usleep(8);
		printf(DIED,
			micro_to_milli(difference(seats->rules->the_time,
					points[BREAK])), seats->id);
		return (1);
	}
	return (0);
}

int	eating_time(t_seats *seats, t_timeval *points, uint64_t waited)
{
	printf(EATING,
		micro_to_milli(difference(seats->rules->the_time,
				points[BREAK])), seats->id);
	usleep(seats->rules->act[EATTT]);
	waited = time_hungry(points);
	if (died_of_hungry(seats, points, waited))
		return (1);
	seats->eat[EATEN]++;
	if (that_was_enough(seats))
		return (1);
	return (0);
}
