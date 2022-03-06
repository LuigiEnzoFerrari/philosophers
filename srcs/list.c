#include "philo.h"

t_seats	*init_seat(void)
{
	t_seats	*seat;

	seat = malloc(sizeof(t_seats));
    memset((void *)seat, 0, sizeof(t_seats));
	seat->right = seat;
	seat->left = seat;
	return (seat);
}

void    add_seat_left(t_seats **seat)
{
	t_seats	*new;

	if (*seat == NULL)
    {
		*seat = init_seat();
        return ;
    }
    new = init_seat();
    new->right = (*seat);
    new->left = (*seat)->left;
    (*seat)->left->right = new;
    (*seat)->left = new;
}
