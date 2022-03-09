#include "philo.h"

void	time_to_waist(uint64_t thinking_about_her)
{
	usleep(thinking_about_her);
}

void	*routine(void *arg)
{
	t_seats *seat;
	timeval last_eat, bpoint;
	uint64_t waited;
	char names[22][15] = {"luigi", "caio", "rafael",
		"gariadno", "adrian", "victor", "fabio",
		"paula", "nathalia", "tuco", "tuca",
		"clarisse", "mari", "mariah", "luiz",
		"lucas", "marce", "debora", "matheus",
		"juliano", "gui"};
	
	memset(&last_eat, 0, sizeof(timeval));
	seat = (t_seats *)arg;
	while (42)
	{
		// take a fork
		pthread_mutex_lock(&seat->pfork);
		gettimeofday(&bpoint, NULL);
		if (*seat->status == 0) {
			pthread_mutex_unlock(&seat->pfork);
			return (NULL);
		}
		printf(" %6lu \t%-15s has taken a fork\n", micro_to_milli(difference(seat->ctime, bpoint)), names[seat->id]);

		// take the second and starts eating
		pthread_mutex_lock(&seat->right->pfork);
		gettimeofday(&bpoint, NULL);
		// diference he waited to eat (last_eat - start_eat)
		if (last_eat.tv_sec != 0)
			waited = difference(last_eat, bpoint);
		else
			waited = difference(seat->ctime, bpoint);
		if (*seat->status == 0) {
			pthread_mutex_unlock(&seat->pfork);
			return (NULL);
		}
		if (waited > seat->act[DYING]) {
			*seat->status = 0;
			printf(" %6lu \t%-15s IS DIED\n", micro_to_milli(difference(seat->ctime, bpoint)), names[seat->id]);
		}
		else {
		// eating
			printf(" %6lu \t%-15s is eating\n", micro_to_milli(difference(seat->ctime, bpoint)), names[seat->id]);
			seat->eat[EATEN]++;
			usleep(seat->act[EATTT]);
			if (seat->eat[EATEN] == seat->eat[LIMIT]) {
				pthread_mutex_unlock(&seat->pfork);
				pthread_mutex_unlock(&seat->right->pfork);
				return (NULL);
			}
		}

		// releasing the forks
		pthread_mutex_unlock(&seat->pfork);
		pthread_mutex_unlock(&seat->right->pfork);
		// starts sleeping
		gettimeofday(&last_eat, NULL);
		if (*seat->status == 0) {
			return (NULL);
		}
		printf(" %6lu \t%-15s is sleeping\n", micro_to_milli(difference(seat->ctime, last_eat)), names[seat->id]);
		time_to_waist(seat->act[SLEEP]);
		// starts thinking
		gettimeofday(&bpoint, NULL);
		if (*seat->status == 0) {
			return (NULL);
		}
		printf(" %6lu \t%-15s is thiking\n", micro_to_milli(difference(seat->ctime, bpoint)), names[seat->id]);
	}
	return (NULL);
}

void	add_seats(t_seats **seats, size_t n)
{
	while (n--)
		add_seat_left(seats);
}

void	add_one_fork_each_philo(t_seats *seats)
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

void	philo_perfil(t_seats *seats, char **argv)
{
	int		id;
	int		*status;
	t_seats	*ptr;
	timeval	ctime;

	id = 0;
	status = malloc(sizeof(int));
	*status = 1;
	ptr = seats;
	gettimeofday(&ctime, NULL);
	while (42) {
		ptr->id = id++;
		ptr->status = status;
		ptr->ctime = ctime;
		ptr->act[DYING] = milli_to_micro(atoi(*(argv + 1)));
		ptr->act[EATTT] = milli_to_micro(atoi(*(argv + 2)));
		ptr->act[SLEEP] = milli_to_micro(atoi(*(argv + 3)));
		if (*(argv + 4) != NULL)
			ptr->eat[LIMIT] = atoi(*(argv + 4));
		ptr = ptr->right;
		if (ptr == seats)
			break ;
	}
}

void    everyone_setting(t_seats *seats)
{
	t_seats     *ptr;

	ptr = seats;
	while (42) {
		usleep(5);
		pthread_create(&seats->philo, NULL, &routine, (void *)seats);
		seats = seats->right;
		if (seats == ptr)
			break ;
	}
}

void    wait_the_last_one(t_seats *seats)
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
	add_seats(&seats, atoi(*(argv + 1)));
	add_one_fork_each_philo(seats);
	philo_perfil(seats, argv + 1);;
	everyone_setting(seats);
	wait_the_last_one(seats);
	clean_the_dirty_dishes(seats);
	return (EXIT_SUCCESS);
}
