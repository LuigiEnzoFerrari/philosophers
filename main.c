#include "philo.h"

int gthing;

// void	*one_fork_for_each(t_philo *philo, size_t n)
// {
// 	t_fork	*forks;
// 	t_fork	*ptr;
// 	size_t  j;

// 	j = 0;
// 	forks = NULL;
// 	add_forks(&forks, n);
// 	ptr = forks;
// 	while (42)
// 	{
// 		pthread_mutex_init(&forks->mutex, NULL);
// 		philo[j].forks = forks;
// 		philo[j].sleep = forks->data;
// 		j++;
// 		forks = forks->next;
// 		if (forks == ptr)
// 			break ;
// 	}
// 	return (forks);
// }

void	*lenzao(void *arg)
{
	t_seats *seat;
	
	seat = (t_seats *)arg;
	while (42)
	{
		pthread_mutex_lock(&seat->pfork);
		pthread_mutex_lock(&seat->right->pfork);
		seat->act[EATTT]++;
		printf("%d comeu: %d abacaxi\n", seat->id, seat->act[EATTT]);
		pthread_mutex_unlock(&seat->pfork);
		pthread_mutex_unlock(&seat->right->pfork);
		usleep(10);
	}
	return NULL;
}

int	main(int argc, char **argv)
{
	int				n;
	t_seats		*seats;
	if (argc != 2) {
		return(printf("misssing a argument\n"));
	}
	n = atoi(*(argv + 1));
	seats = NULL;
	while (n--)
		add_seat_left(&seats);
	t_seats	*ptr = seats;
	while (42) {
		pthread_create(&seats->philo, NULL, &lenzao, (void *)seats);
		seats = seats->right;
		if (seats == ptr)
			break ;
	}
	while (42) {
		pthread_join(seats->philo, NULL);
		seats = seats->right;
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
