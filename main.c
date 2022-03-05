#include "philo.h"

void	print_dragon(void)
{
	for (int i = 0; i < 3; i++)
	{
		sleep(1);
		printf("dragon\n");
	}   
}

void	*print_dog(void *one)
{
	int *ptr;

	ptr = malloc(sizeof(int));
	*ptr = 4;
	for (int i = 0; i < 7; i++)
	{
		sleep(1);
		printf("print_dog %d\n", *ptr);
		(*ptr)++;
	}
	return (void *)ptr;
}

void	*lenzao(void *arg)
{
	pthread_mutex_t	*mut;

	mut = (pthread_mutex_t *)arg;
	usleep(5 * 500000);
	pthread_mutex_unlock(mut);
	return NULL;
}

int	main(int argc, char **argv)
{
	// if (argc < 6 || argc > 7)
		// return (EXIT_FAILURE);
	pthread_mutex_t	mut;
	pthread_t	tread[5];
	int	*count;

	pthread_mutex_init(&mut, NULL);
	pthread_create(&tread, NULL, lenzao, &mut);
	pthread_mutex_lock(&mut);
	pthread_mutex_lock(&mut);
	pthread_create(&tread, NULL, print_dog, NULL);
	print_dragon();
	pthread_join(tread, (void *)&count);
	printf("result: %d\n", *count);
	return (EXIT_SUCCESS);
}
