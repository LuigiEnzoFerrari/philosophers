#include "philo.h"

int gthing;

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
		pthread_mutex_init(&forks->mutex, NULL);
		philo[j].forks = forks;
		philo[j].sleep = forks->data;
		j++;
		forks = forks->next;
		if (forks == ptr)
			break ;
	}
	return (forks);
}

void	*lenzao(void *arg)
{
	t_philo *ph;
	
	ph = (t_philo *)arg;
	while (42)
	{
		pthread_mutex_lock(&ph->forks->mutex);
		pthread_mutex_lock(&ph->forks->next->mutex);
        ph->eattt++;
        printf("%s comeu: %d abacaxi\n", ph->name, ph->eattt);
		pthread_mutex_unlock(&ph->forks->mutex);
		pthread_mutex_unlock(&ph->forks->next->mutex);
		usleep(4);
	}
	return NULL;
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
    memset((void *)philo, 0, sizeof(t_philo) * n);
	one_fork_for_each(philo, n);
    philo[0].name = strdup("caio");
    philo[1].name = strdup("gadino");
    philo[2].name = strdup("rafa");
    philo[3].name = strdup("lenzo");
	for (int j = 0; j < n; j++) {
		pthread_create(th + j, NULL, &lenzao, (void *)&philo[j]);
	}
	for (int j = 0; j < n; j++) {
		pthread_join(th[j], NULL);
	}
	for (int j = 0; j < n; j++) {
		pthread_mutex_destroy(&philo[j].forks->mutex);
	}
	free(th);
	free(philo);
	return (EXIT_SUCCESS);
}
