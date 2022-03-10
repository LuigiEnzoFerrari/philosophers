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

typedef pthread_t		philo_id;
typedef pthread_mutex_t pfork;
typedef struct timeval timeval;

/*
** index of the actions of each filosopher
*/

# define LIMIT 0
# define EATEN 1

# define SLEEP 0
# define EATTT 1
# define THINK 2
# define DYING 3

# define BREAK 0
# define LAST_EAT 1

typedef struct s_rules {
    timeval         the_time;
	uint64_t		act[4];
}	t_rules;

typedef struct	s_seats {
	int				id; //temp just to know which pthread
	size_t          eat[2];
	int             *status;
	t_rules			*rules;
	pfork			pfork;
	philo_id		philo;
	struct	s_seats	*right; // next
	struct	s_seats	*left; // prev // It's possible that I won't need this one.
}	t_seats;

t_seats	*init_seat(void);
void	add_seat_left(t_seats **seat);

uint64_t	milli_to_micro(uint64_t milliseconds);
uint64_t	micro_to_milli(uint64_t microseconds);
uint64_t	micro_to_seconds(uint64_t microseconds);
uint64_t	difference(timeval start, timeval end);
uint64_t    timeval_to_micro(timeval current_time);

#endif
