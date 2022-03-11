/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_time.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenzo-pe <lenzo-pe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 01:33:08 by lenzo-pe          #+#    #+#             */
/*   Updated: 2022/03/10 02:36:51 by lenzo-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	t_timeval_to_micro(t_timeval current_time)
{
	return ((current_time.tv_sec * 1000000 + current_time.tv_usec));
}

uint64_t	milli_to_micro(uint64_t milliseconds)
{
	return (milliseconds * 1000);
}

uint64_t	micro_to_milli(uint64_t microseconds)
{
	return (microseconds * 0.001);
}

uint64_t	micro_to_seconds(uint64_t microseconds)
{
	return (microseconds * 0.000001);
}

uint64_t	difference(t_timeval start, t_timeval end)
{
	return (t_timeval_to_micro(end)
		- t_timeval_to_micro(start));
}
