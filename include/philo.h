#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>

typedef pthread_t		philo_id;
typedef pthread_mutex_t pfork;

/*
** index of the actions of each filosopher
*/

#define SLEEP 0
#define EATTT 1
#define THINK 2

typedef struct	s_seats {
	int				id; //temp just to know which pthread
	int				act[3];
	pfork			pfork;
	philo_id		philo;
	struct	s_seats	*right; // next
	struct	s_seats	*left; // prev // It's possible that I won't need this one.
}	t_seats;

t_seats	*init_seat(void);
void	add_seat_left(t_seats **seat);

#endif
