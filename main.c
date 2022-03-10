#include "philo.h"

void	time_to_waist(uint64_t thinking_about_her)
{
	usleep(thinking_about_her);
}

int take_the_first_fork(t_seats *seats, timeval *points, char names[22][15])
{
	pthread_mutex_lock(&seats->pfork);
	gettimeofday(&points[BREAK], NULL);
	if (*seats->status == 0)
	{
		pthread_mutex_unlock(&seats->pfork);
		return (1);
	}
	printf(" %6lu \t%-15s has taken a fork\n", micro_to_milli(difference(seats->rules->the_time, points[BREAK])), names[seats->id]);
	return (0);
}

int take_the_second_fork(t_seats *seats, timeval *points)
{
	if (seats == seats->right)
		usleep(seats->rules->act[DYING]);
	else
		pthread_mutex_lock(&seats->right->pfork);
	gettimeofday(&points[BREAK], NULL);
	return (0);
}

int	nap_time(t_seats *seats, timeval *points, char names[22][15])
{
	gettimeofday(&points[LAST_EAT], NULL);
	if (*seats->status == 0)
		return (1);
	printf(" %6lu \t%-15s is sleeping\n", micro_to_milli(difference(seats->rules->the_time, points[LAST_EAT])), names[seats->id]);
	time_to_waist(seats->rules->act[SLEEP]);
	return (0);
}

uint64_t	time_hungry(t_seats *seats, timeval *points)
{
	uint64_t hungry;

	if (points[LAST_EAT].tv_sec != 0)
		hungry = difference(points[LAST_EAT], points[BREAK]);
	else
		hungry = difference(seats->rules->the_time, points[BREAK]);
	return (hungry);
}

int	that_was_enough(t_seats *seats, timeval *points)
{
	if (seats->eat[EATEN] == seats->eat[LIMIT]) {
		pthread_mutex_unlock(&seats->pfork);
		pthread_mutex_unlock(&seats->right->pfork);
		return (1);
	}
	return (0);
}

int	died_of_hungry(t_seats *seats, timeval *points,uint64_t waited, char names[22][15])
{
	if (waited > seats->rules->act[DYING])
	{
		*seats->status = 0;
		printf(" %6lu \t%-15s IS DIED\n", micro_to_milli(difference(seats->rules->the_time, points[BREAK])), names[seats->id]);
		return (1);
	}
	return (0);
}

int	eating_time(t_seats *seat, timeval *points, char names[22][15])
{
	printf(" %6lu \t%-15s is eating\n", micro_to_milli(difference(seat->rules->the_time, points[BREAK])), names[seat->id]);
	usleep(seat->rules->act[EATTT]);
	seat->eat[EATEN]++;
	if (that_was_enough(seat, points))
		return (1);
	return (0);
}

void	*routine(void *arg)
{
	t_seats *seat;
	timeval points[2];
	uint64_t waited;
	char names[22][15] = {"luigi", "caio", "rafael",
		"gariadno", "adrian", "victor", "fabio",
		"paula", "nathalia", "tuco", "tuca",
		"clarisse", "mari", "mariah", "luiz",
		"lucas", "marce", "debora", "matheus",
		"juliano", "gui"};
	
	memset(&points[LAST_EAT], 0, sizeof(timeval));
	seat = (t_seats *)arg;
	while (42)
	{
		if (take_the_first_fork(seat, points, names))
			return (NULL);
		take_the_second_fork(seat, points);
		waited = time_hungry(seat, points);
		if (*seat->status == 0) {
			pthread_mutex_unlock(&seat->pfork);
			return (NULL);
		}
		if (died_of_hungry(seat, points, waited, names))
			;
		else if(eating_time(seat, points, names))
			return (NULL);
		// releasing the forks
		pthread_mutex_unlock(&seat->pfork);
		pthread_mutex_unlock(&seat->right->pfork);
		nap_time(seat, points, names);
		gettimeofday(&points[BREAK], NULL);
		if (*seat->status == 0)
			return (NULL);
		printf(" %6lu \t%-15s is thiking\n", micro_to_milli(difference(seat->rules->the_time, points[BREAK])), names[seat->id]);
	}
	return (NULL);
}

void	one_seat_for_each_guest(t_seats **seats, size_t n)
{
	while (n--)
		add_seat_left(seats);
}

void	one_fork_for_each_guest(t_seats *seats)
{
	t_seats	*ptr;

	ptr = seats;
	while (42) {
		pthread_mutex_init(&ptr->pfork, NULL);
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
	rules->act[DYING] = milli_to_micro(atoi(*(argv + 1)));
	rules->act[EATTT] = milli_to_micro(atoi(*(argv + 2)));
	rules->act[SLEEP] = milli_to_micro(atoi(*(argv + 3)));
	ptr = seats;
	while (42) {
		ptr->rules = rules;
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
	while (42) {
		ptr->id = id++;
		ptr->status = status;
		if (*(argv + 4) != NULL)
			ptr->eat[LIMIT] = atoi(*(argv + 4));
		ptr = ptr->right;
		if (ptr == seats)
			break ;
	}
}

void    everyone_lets_party(t_seats *seats)
{
	t_seats     *ptr;

	ptr = seats;
	while (42) {
		usleep(5);
		pthread_create(&seats->philo, NULL, &routine, seats);
		seats = seats->right;
		if (seats == ptr)
			break ;
	}
}

void    everyone_getout_together(t_seats *seats)
{
	t_seats	*ptr;

	ptr = seats;
	while (42) {
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
	while (42) {
		pthread_mutex_destroy(&seats->pfork);
		seats = seats->right;
		if (seats == ptr)
			break ;
	}
}

int	main(int argc, char **argv)
{
	t_seats	*seats;
	if (argc > 6 || argc < 5) {
		return(write(STDERR_FILENO, "misssing a argument\n", 20));
	}
	seats = NULL;
	one_seat_for_each_guest(&seats, atoi(*(argv + 1)));
	one_fork_for_each_guest(seats);
	guests_profile(seats, argv + 1);
	rules_of_the_party(seats, argv + 1);
	everyone_lets_party(seats);
	everyone_getout_together(seats);
	clean_the_dirty_dishes(seats);
	return (EXIT_SUCCESS);
}
