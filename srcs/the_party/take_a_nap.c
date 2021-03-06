/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_a_nap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenzo-pe <lenzo-pe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 01:33:22 by lenzo-pe          #+#    #+#             */
/*   Updated: 2022/03/11 02:43:26 by lenzo-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	time_to_waist(uint64_t thinking_about_her)
{
	usleep(thinking_about_her);
}

static int	nap_time(t_seats *seats)
{
	t_timeval	time;

	gettimeofday(&time, NULL);
	if (*seats->status == 0)
		return (1);
	printf(SLEEPING,
		micro_to_milli(difference(seats->rules->the_time,
				time)), seats->id);
	time_to_waist(seats->rules->act[SLEEP]);
	return (0);
}

int	sleeping_and_thinking(t_seats *seats, t_timeval *points)
{
	nap_time(seats);
	gettimeofday(&points[BREAK], NULL);
	if (*seats->status == 0)
		return (1);
	printf(THINKING,
		micro_to_milli(difference(seats->rules->the_time,
				points[BREAK])), seats->id);
	if (*seats->status == 0)
		return (1);
	return (0);
}
