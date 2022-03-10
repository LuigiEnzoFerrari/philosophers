/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenzo-pe <lenzo-pe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 01:33:17 by lenzo-pe          #+#    #+#             */
/*   Updated: 2022/03/10 01:36:33 by lenzo-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	release_the_forks(t_seats *seats)
{
	pthread_mutex_unlock(&seats->pfork);
	pthread_mutex_unlock(&seats->right->pfork);
}

int	take_the_first_fork(t_seats *seats, timeval *points)
{
	pthread_mutex_lock(&seats->pfork);
	gettimeofday(&points[BREAK], NULL);
	if (*seats->status == 0)
	{
		pthread_mutex_unlock(&seats->pfork);
		return (1);
	}
	printf(" %6lu \t%-15d has taken a fork\n",
		micro_to_milli(difference(seats->rules->the_time,
				points[BREAK])), seats->id);
	return (0);
}

int	take_the_second_fork(t_seats *seats, timeval *points)
{
	if (seats == seats->right)
		usleep(seats->rules->act[DYING]);
	else
		pthread_mutex_lock(&seats->right->pfork);
	gettimeofday(&points[BREAK], NULL);
	return (0);
}

int	take_the_forks(t_seats *seats, timeval *points)
{
	if (take_the_first_fork(seats, points))
		return (1);
	take_the_second_fork(seats, points);
	return (0);
}
