#include "philo.h"

void	time_to_waist(uint64_t thinking_about_her)
{
	usleep(thinking_about_her);
}

void	*routine(void *arg)
{
    t_table *table;
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
    table = (t_table *)arg;
    seat = table->seats;
	while (42)
	{
		// take a fork
		pthread_mutex_lock(&seat->pfork);
		gettimeofday(&bpoint, NULL);
		if (table->status == 0) {
			pthread_mutex_unlock(&seat->pfork);
			return (NULL);
		}
		printf(" %6lu \t%-15s has taken a fork\n", micro_to_milli(difference(table->the_time, bpoint)), names[seat->id]);

		// take the second and starts eating
        if (seat == seat->right)
            usleep(table->act_time[DYING]);
        else
            pthread_mutex_lock(&seat->right->pfork);
		gettimeofday(&bpoint, NULL);
		// diference he waited to eat (last_eat - start_eat)
		if (last_eat.tv_sec != 0)
			waited = difference(last_eat, bpoint);
		else
			waited = difference(table->the_time, bpoint);
		if (table->status == 0) {
			pthread_mutex_unlock(&seat->pfork);
			return (NULL);
		}
		if (waited > table->act_time[DYING]) {
			table->status = 0;
			printf(" %6lu \t%-15s IS DIED\n", micro_to_milli(difference(table->the_time, bpoint)), names[seat->id]);
		}
		else {
		// eating
			printf(" %6lu \t%-15s is eating\n", micro_to_milli(difference(table->the_time, bpoint)), names[seat->id]);
			seat->eat[EATEN]++;
			usleep(table->act_time[EATTT]);
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
		if (table->status == 0) {
			return (NULL);
		}
		printf(" %6lu \t%-15s is sleeping\n", micro_to_milli(difference(table->the_time, last_eat)), names[seat->id]);
		time_to_waist(table->act_time[SLEEP]);
		// starts thinking
		gettimeofday(&bpoint, NULL);
		if (table->status == 0) {
			return (NULL);
		}
		printf(" %6lu \t%-15s is thiking\n", micro_to_milli(difference(table->the_time, bpoint)), names[seat->id]);
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

void    dinner_rules(t_table *table, char **argv)
{
	timeval	ctime;

	gettimeofday(&ctime, NULL);
	table->the_time = ctime;
	table->status = 1;
	table->n_seats = atoi(*argv);
	table->act_time[DYING] = milli_to_micro(atoi(*(argv + 1)));
	table->act_time[EATTT] = milli_to_micro(atoi(*(argv + 2)));
	table->act_time[SLEEP] = milli_to_micro(atoi(*(argv + 3)));
}

void	philo_perfil(t_table *table, t_seats *seats, char **argv)
{
	int		id;
	t_seats	*ptr;

	id = 0;
	ptr = seats;
	while (42) {
		ptr->id = id++;
		if (*(argv + 4) != NULL)
			ptr->eat[LIMIT] = atoi(*(argv + 4));
		ptr = ptr->right;
		if (ptr == seats)
			break ;
	}
}

void    everyone_setting(t_table *table)
{
	t_seats     *ptr;

	ptr = table->seats;
	while (42) {
		usleep(5);
		pthread_create(&table->seats->philo, NULL, &routine, (void *)table);
		table->seats = table->seats->right;
		if (table->seats == ptr)
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
	t_table	table;
	if (argc > 6 || argc < 5) {
		return(write(STDERR_FILENO, "misssing a argument\n", 20));
	}
	table.seats = NULL;
	add_seats(&table.seats, atoi(*(argv + 1)));
	add_one_fork_each_philo(table.seats);
	philo_perfil(&table, table.seats, argv + 1);
    dinner_rules(&table, argv + 1);
	everyone_setting(&table);
	wait_the_last_one(table.seats);
	clean_the_dirty_dishes(table.seats);
	return (EXIT_SUCCESS);
}
