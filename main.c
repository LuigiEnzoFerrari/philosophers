#include "philo.h"

int i = 0;

void	*lenzao(void *arg)
{
	pthread_mutex_t *mut;
	
	mut = (pthread_mutex_t *)arg;
	for (; i < 300000;)
	{
		pthread_mutex_lock(mut);
		i++;
		printf("%d\n", i);
		pthread_mutex_unlock(mut);
	}
	return NULL;
}

void	*one_fork_for_each(t_philo *philo, size_t n)
{
	t_fork	*forks;
	t_fork	*ptr;
    size_t  i;

    i = 0;
	forks = NULL;
	add_forks(&forks, n);
	ptr = forks;
	while (42)
	{
		pthread_mutex_init(&forks->mutex, NULL);
        philo[i].table = forks;
        philo[i].sleep = forks->data;
		i++;
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
	for (int i = 0; i < n; i++) {
		pthread_create(&th[i], NULL, &lenzao, (void *)&mut);
	}
	for (int j = 0; j < n; j++) {
		pthread_join(th[j], NULL);
	}
	for (int j = 0; j < n; j++) {
        printf("%d\n", philo[j].sleep);
    }
	for (int j = 0; j < n; j++) {

        pthread_mutex_destroy(&philo[j].table->mutex);
	}
	free(th);
	free(philo);
	return (EXIT_SUCCESS);
}
