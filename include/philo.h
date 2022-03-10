/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 02:33:14 by lenzo-pe          #+#    #+#             */
/*   Updated: 2022/03/10 16:15:20 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <stdint.h>

typedef pthread_t		t_philo_id;
typedef pthread_mutex_t	t_pfork;
typedef struct timeval	t_timeval;

/*
** index of the actions of each filosopher
*/

# define DIED "\e\001\003[0;91m\002 %6lu \t%-15d is died\001\033[0m\002\n"
# define EATING "\e\001\003[0;93m\002 %6lu \t%-15d is eating\001\033[0m\002\n"
# define SLEEPING "\e\001\003[0;94m\002 %6lu \t%-15d is sleeping\001\033[0m\002\n"
# define THINKING "\e\001\003[0;95m\002 %6lu \t%-15d is thiking\001\033[0m\002\n"
# define FORKING "\e\001\003[0;97m\002 %6lu \t%-15d has taken a fork\001\033[0m\002\n"

# define LIMIT 0
# define EATEN 1

# define SLEEP 0
# define EATTT 1
# define THINK 2
# define DYING 3

# define BREAK 0
# define LAST_EAT 1

typedef struct s_rules
{
	t_timeval	the_time;
	uint64_t	act[4];
}	t_rules;

typedef struct s_seats
{
	int				id;
	size_t			eat[2];
	int				*status;
	t_rules			*rules;
	t_pfork			t_pfork;
	t_philo_id		philo;
	struct s_seats	*right;
	struct s_seats	*left;
}	t_seats;

uint64_t	my_strtoul(const char *nptr);
uint64_t	my_abs(int64_t n);

int			you_should_not_pass(int argc, char **argv);
t_seats		*init_seat(void);
void		add_seat_left(t_seats **seat);
void		clear_seats(t_seats *seats);

uint64_t	milli_to_micro(uint64_t milliseconds);
uint64_t	micro_to_milli(uint64_t microseconds);
uint64_t	micro_to_seconds(uint64_t microseconds);
uint64_t	difference(t_timeval start, t_timeval end);
uint64_t	t_timeval_to_micro(t_timeval current_time);

void		one_seat_for_each_guest(t_seats **seats, size_t n);
void		one_fork_for_each_guest(t_seats *seats);
void		guests_profile(t_seats *seats, char **argv);
void		rules_of_the_party(t_seats *seats, char **argv);

void		everyone_lets_party(t_seats *seats);
void		*party(void *arg);

int			take_the_forks(t_seats *seats, t_timeval *points);
int			take_the_first_fork(t_seats *seats, t_timeval *points);
int			take_the_second_fork(t_seats *seats, t_timeval *points);
int			died_of_hungry(t_seats *seats, t_timeval *points, uint64_t waited);
void		release_the_forks(t_seats *seats);
int			eating_time(t_seats *seats, t_timeval *points);
uint64_t	time_hungry(t_seats *seats, t_timeval *points);

int			sleeping_and_thinking(t_seats *seats, t_timeval *points);

#endif
