/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenzo-pe <lenzo-pe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 01:41:21 by lenzo-pe          #+#    #+#             */
/*   Updated: 2022/03/10 04:19:09 by lenzo-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	everyone_getout_together(t_seats *seats)
{
	t_seats	*ptr;

	ptr = seats;
	while (42)
	{
		seats = seats->right;
		pthread_join(seats->philo, NULL);
		if (seats == ptr)
			break ;
	}
}

void	clean_the_dirty_dishes(t_seats *seats)
{
	t_seats	*ptr;

	ptr = seats;
	free(ptr->status);
	while (42)
	{
		pthread_mutex_destroy(&seats->t_pfork);
		seats = seats->right;
		if (seats == ptr)
			break ;
	}
}

int	main(int argc, char **argv)
{
	t_seats	*seats;

	if (you_should_not_pass(argc, argv + 1))
		return (EXIT_FAILURE);
	seats = NULL;
	one_seat_for_each_guest(&seats, my_strtoul(*(argv + 1)));
	one_fork_for_each_guest(seats);
	guests_profile(seats, argv + 1);
	rules_of_the_party(seats, argv + 1);
	everyone_lets_party(seats);
	everyone_getout_together(seats);
	clean_the_dirty_dishes(seats);
	return (EXIT_SUCCESS);
}
