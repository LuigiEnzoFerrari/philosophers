/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_party.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenzo-pe <lenzo-pe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 01:37:58 by lenzo-pe          #+#    #+#             */
/*   Updated: 2022/03/10 05:39:27 by lenzo-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_seat_for_each_guest(t_seats **seats, size_t n)
{
	while (n--)
		add_seat_left(seats);
}

void	one_fork_for_each_guest(t_seats *seats)
{
	t_seats	*ptr;

	ptr = seats;
	while (42)
	{
		pthread_mutex_init(&ptr->t_pfork, NULL);
		ptr = ptr->right;
		if (ptr == seats)
			break ;
	}
}

void	guests_profile(t_seats *seats, char **argv)
{
	int		id;
	int		*status;
	t_seats	*ptr;

	id = 0;
	status = malloc(sizeof(int));
	*status = 1;
	ptr = seats;
	while (42)
	{
		ptr->id = id++;
		ptr->status = status;
		if (*(argv + 4) != NULL)
			ptr->eat[LIMIT] = my_strtoul(*(argv + 4));
		ptr = ptr->right;
		if (ptr == seats)
			break ;
	}
}

void	rules_of_the_party(t_seats *seats, char **argv)
{
	t_rules	*rules;
	t_seats	*ptr;

	rules = malloc(sizeof(t_rules));
	gettimeofday(&rules->the_time, NULL);
	rules->act[DYING] = milli_to_micro(my_abs(my_strtoul(*(argv + 1))));
	rules->act[EATTT] = milli_to_micro(my_abs(my_strtoul(*(argv + 2))));
	rules->act[SLEEP] = milli_to_micro(my_abs(my_strtoul(*(argv + 3))));
	ptr = seats;
	while (42)
	{
		ptr->rules = rules;
		ptr = ptr->right;
		if (ptr == seats)
			break ;
	}
}
