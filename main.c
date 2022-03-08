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
		printf("   %-8lu %-15s has taken a fork\n", micro_to_milli(difference(seat->ctime, bpoint)), names[seat->id]);

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
            printf("   %-8lu %-15s IS DIED\n", micro_to_milli(difference(seat->ctime, bpoint)), names[seat->id]);
        }
        else {
		// eating
            printf("   %-8lu %-15s is eating\n", micro_to_milli(difference(seat->ctime, bpoint)), names[seat->id]);
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
		printf("   %-8lu %-15s is sleeping\n", micro_to_milli(difference(seat->ctime, last_eat)), names[seat->id]);
		time_to_waist(seat->act[SLEEP]);
        // starts thinking
		gettimeofday(&bpoint, NULL);
		if (*seat->status == 0) {
			return (NULL);
		}
		printf("   %-8lu %-15s is thiking\n", micro_to_milli(difference(seat->ctime, bpoint)), names[seat->id]);
	}
	return (NULL);
}

void    prepere_the_table(t_seats **seats, char **argv)
{
	t_seats *ptr;

	int *status;
	status = malloc(sizeof(int));
	*status = 1;
	*seats = NULL;

	int n = atoi(*argv);
	while (n--)
		add_seat_left(seats);
	ptr = *seats;
	// add_one_fork_for_each

	while (42) {
		pthread_mutex_init(&ptr->pfork, NULL);
		ptr = ptr->right;
		if (ptr == (*seats))
			break ;
	}

	// just to know who is who
	int id = 0;
    timeval nanana;

    gettimeofday(&nanana, NULL);
	while (42) {
		ptr->id = id++;
		ptr->status = status;
        ptr->ctime = nanana;
		ptr->act[DYING] = milli_to_micro(atoi(*(argv + 1)));
		ptr->act[EATTT] = milli_to_micro(atoi(*(argv + 2)));
		ptr->act[SLEEP] = milli_to_micro(atoi(*(argv + 3)));
		ptr->eat[LIMIT] = atoi(*(argv + 4));
		ptr = ptr->right;
		if (ptr == (*seats))
			break ;
	}
}

void    everyone_sitting();

int	main(int argc, char **argv)
{
	t_seats		*seats;
	t_seats     *ptr;
	if (argc > 6 || argc < 5) {
		return(write(STDERR_FILENO, "misssing a argument\n", 20));
	}
	prepere_the_table(&seats, argv + 1);
	ptr = seats;
	while (42) {
		usleep(5);
		pthread_create(&seats->philo, NULL, &routine, (void *)seats);
		seats = seats->right;
		if (seats == ptr)
			break ;
	}
	while (42) {
		seats = seats->right;
		pthread_join(seats->philo, NULL);
		if (seats == ptr)
			break ;
	}
	while (42) {
		pthread_mutex_destroy(&seats->pfork);
		seats = seats->right;
		if (seats == ptr)
			break ;
	}
	return (EXIT_SUCCESS);
}
