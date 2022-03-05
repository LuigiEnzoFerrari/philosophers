#include "philo.h"

int gthing;


void	*lenzao(void *arg)
{
	pthread_mutex_t *mut;
	
	mut = (pthread_mutex_t *)arg;
	while (gthing < 3000000)
	{
		pthread_mutex_lock(mut);
		gthing++;
		pthread_mutex_unlock(mut);
	}
	return NULL;
}

void	*one_fork_for_each(t_philo *philo, size_t n)
{
	t_fork	*forks;
	t_fork	*ptr;
	size_t  j;

	j = 0;
	forks = NULL;
	add_forks(&forks, n);
	ptr = forks;
	while (42)
	{
		// pthread_mutex_init(&forks->mutex, NULL);
		philo[j].forks = forks;
		philo[j].sleep = forks->data;
		j++;
		forks = forks->next;
		if (forks == ptr)
			break ;
	}
	return (forks);
}

int	main(int argc, char **argv)
{
	pthread_mutex_t	mut;
	pthread_t	*th;
	t_philo		*philo;
	int				n;

	if (argc != 2) {
		return(printf("misssing a argument\n"));
	}
	n = atoi(*(argv + 1));
	th = malloc(sizeof(pthread_t) * n);
	philo = malloc(sizeof(t_philo) * n);
	one_fork_for_each(philo, n);
	pthread_mutex_init(&mut, NULL);
	for (int j = 0; j < n; j++) {
		pthread_create(&th[j], NULL, &lenzao, (void *)&mut);
	}
	for (int j = 0; j < n; j++) {
		pthread_join(th[j], NULL);
	}
	for (int j = 0; j < n; j++) {
		pthread_mutex_destroy(&philo[j].forks->mutex);
	}
	for (int j = 0; j < n; j++) {
		printf("%d\n", philo[j].sleep);
	}
	printf("resultado: %d\n", gthing);
	free(th);
	free(philo);
	return (EXIT_SUCCESS);
}
