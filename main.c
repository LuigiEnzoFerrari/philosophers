#include "philo.h"

void	time_to_waist(uint64_t thinking_about_her)
{
	usleep(thinking_about_her);
}

void	*routine(void *arg)
{
	char names[22][15] = {"luigi", "caio", "rafael",
        "gariadno", "adrian", "victor", "fabio",
        "paula", "nathalia", "tuco", "tuca",
        "clarisse", "mari", "mariah", "luiz",
        "lucas", "marce", "debora", "matheus",
        "juliano", "gui"};
	t_seats *seat;
	timeval start, end;
    
    memset(&end, 0, sizeof(timeval));
	seat = (t_seats *)arg;
	while (42)
	{
        // prepere to eat
        if (end.tv_sec == 0)
            gettimeofday(&end, NULL);
    
        // taking the forks
		pthread_mutex_lock(&seat->pfork);
		pthread_mutex_lock(&seat->right->pfork);

        // start eat
		gettimeofday(&start, NULL);
		usleep(milli_to_micro(seat->act[EATTT]));

        int waited = difference(end, start);

        if (micro_to_milli(waited) > seat->act[DYING])
            *seat->status = 0;

        // timeo waited to eating
		printf("%s:\n", names[seat->id]);
        printf("   esperou: %lums\n", micro_to_milli(waited));
        printf("   esperou: %lus\n", micro_to_seconds(waited));

        // release the forks
		pthread_mutex_unlock(&seat->pfork);
		pthread_mutex_unlock(&seat->right->pfork);

        if (*seat->status == 0) {
            printf("   DIED\n");
            return NULL;
        }
        // time since stop eat
		gettimeofday(&end, NULL);
		printf("   comeu em: %lus\n", micro_to_seconds(difference(start, end)));

        // thinking sleeping and play video game
		time_to_waist(seat->act[SLEEP]);
	}
	return NULL;
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

	while (42) {
		ptr->id = id++;
        ptr->status = status;
        ptr->act[DYING] = atoi(*(argv + 1));
        ptr->act[EATTT] = atoi(*(argv + 2));
        ptr->act[SLEEP] = atoi(*(argv + 3));
		ptr->num = 1;
		ptr = ptr->right;
		if (ptr == (*seats))
			break ;
	}
}

int	main(int argc, char **argv)
{
	t_seats		*seats;
	t_seats     *ptr;
	// if (argc != 2) {
	// 	return(write(STDERR_FILENO, "misssing a argument\n", 20));
	// }
	prepere_the_table(&seats, argv + 1);
	ptr = seats;
	while (42) {
		pthread_create(&seats->philo, NULL, &routine, (void *)seats);
		seats = seats->right;
		if (seats == ptr)
			break ;
        usleep(2);
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
