#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

struct	s_fork {
    int     data;
	pthread_mutex_t	mutex;
	struct s_fork	*next;
	struct s_fork	*prev;
};
typedef struct s_fork	t_fork;

struct s_philosopher {
	int		sleep;
	int		think;
	int		eattt;
	t_fork	*forks;
};
typedef struct s_philosopher	t_philo;

t_fork  *init_fork(void);
void    add_forks(t_fork **forke, size_t n);

#endif