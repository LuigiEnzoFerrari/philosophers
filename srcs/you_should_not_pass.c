/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   you_should_not_pass.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenzo-pe <lenzo-pe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 03:49:50 by lenzo-pe          #+#    #+#             */
/*   Updated: 2022/03/10 04:19:40 by lenzo-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	you_should_not_pass(int argc, char **argv)
{
	if (argc > 6)
	{
		printf("%s\n%s %s %s %s %s %s\n",
			"more arguments than should be",
			"syntex", "[number of philosophers]", "[time to die]",
			"[time to eat]", "[time to sleep]",
			"[number of times_each philosopher must eat]");
		return (1);
	}
	else if (argc < 5)
	{
		printf("%s\n%s %s %s %s %s %s\n",
			"less arguments than should be",
			"syntex", "[number of philosophers]", "[time to die]",
			"[time to eat]", "[time to sleep]",
			"[number of times_each philosopher must eat]");
		return (1);
	}
	return (0);
}
