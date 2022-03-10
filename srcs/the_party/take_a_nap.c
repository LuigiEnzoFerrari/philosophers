/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_a_nap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenzo-pe <lenzo-pe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 01:33:22 by lenzo-pe          #+#    #+#             */
/*   Updated: 2022/03/10 01:35:40 by lenzo-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	time_to_waist(uint64_t thinking_about_her)
{
	usleep(thinking_about_her);
}

static int	nap_time(t_seats *seats, timeval *points)
{
	gettimeofday(&points[LAST_EAT], NULL);
	if (*seats->status == 0)
		return (1);
	printf(" %6lu \t%-15d is sleeping\n",
		micro_to_milli(difference(seats->rules->the_time,
				points[LAST_EAT])), seats->id);
	time_to_waist(seats->rules->act[SLEEP]);
	return (0);
}

int	sleeping_and_thinking(t_seats *seats, timeval *points)
{
	nap_time(seats, points);
	gettimeofday(&points[BREAK], NULL);
	if (*seats->status == 0)
		return (1);
	printf(" %6lu \t%-15d is thiking\n",
		micro_to_milli(difference(seats->rules->the_time,
				points[BREAK])), seats->id);
	return (0);
}
