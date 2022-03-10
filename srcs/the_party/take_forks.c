/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenzo-pe <lenzo-pe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 01:33:17 by lenzo-pe          #+#    #+#             */
/*   Updated: 2022/03/10 02:36:51 by lenzo-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	release_the_forks(t_seats *seats)
{
	pthread_mutex_unlock(&seats->t_pfork);
	pthread_mutex_unlock(&seats->right->t_pfork);
}

int	take_the_first_fork(t_seats *seats, t_timeval *points)
{
	pthread_mutex_lock(&seats->t_pfork);
	gettimeofday(&points[BREAK], NULL);
	if (*seats->status == 0)
	{
		pthread_mutex_unlock(&seats->t_pfork);
		return (1);
	}
	printf(" %6lu \t%-15d has taken a fork\n",
		micro_to_milli(difference(seats->rules->the_time,
				points[BREAK])), seats->id);
	return (0);
}

int	take_the_second_fork(t_seats *seats, t_timeval *points)
{
	if (seats == seats->right)
		usleep(seats->rules->act[DYING]);
	else
		pthread_mutex_lock(&seats->right->t_pfork);
	gettimeofday(&points[BREAK], NULL);
	return (0);
}

int	take_the_forks(t_seats *seats, t_timeval *points)
{
	if (take_the_first_fork(seats, points))
		return (1);
	take_the_second_fork(seats, points);
	return (0);
}
