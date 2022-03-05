#include "philo.h"

void	*lenzao(void *arg)
{
	write(1, "ola\n", 4);
	return NULL;
}

int	main(int argc, char **argv)
{
	pthread_mutex_t	mut;
	pthread_t		*tread;
	int n;

	n = atoi(*(argv + 1));
	tread = malloc(sizeof(pthread_t) * n);
	for (int i = 0; i <= n; i++) {
		pthread_create(tread, NULL, lenzao, NULL);
	}
	for (int j = 0; j <= n; j++) {
		pthread_join(*tread, NULL);
	}
	free(tread);
	return (EXIT_SUCCESS);
}
