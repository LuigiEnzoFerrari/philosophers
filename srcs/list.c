#include "philo.h"

t_fork	*init_fork(void)
{
	t_fork	*forke;

	forke = malloc(sizeof(t_fork));
	forke->next = forke;
	forke->prev = forke;
	return (forke);
}

void    add_forks(t_fork **forke, size_t n)
{
	t_fork	*new;
    size_t  i;

	if (n == 0)
		return ;
        i = 0;
	if (*forke == NULL)
	{
		*forke = init_fork();
		(*forke)->data = i;
		i++;
	}
	while (n > i)
	{
		new = init_fork();
		new->data = i;
		new->next = (*forke);
		new->prev = (*forke)->prev;
		(*forke)->prev->next = new;
		(*forke)->prev = new;
		i++;
	}
}
