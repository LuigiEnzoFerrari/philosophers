#include "minunit.h"
#include "philo.h"

MU_TEST(test_number_of_seats_zero) {
	t_seats	*seats = NULL;
	int	how_many = 0;
	int	expected = 0;
	while (expected--)
		add_seat_left(&seats);
	if (seats != NULL)
	{
		t_seats *ptr = seats;
		do{
			how_many++;
			seats = seats->right;
		}
		while (seats != ptr);
	}
	mu_assert(how_many == 0, "expected 0");
}

MU_TEST(test_number_of_seats_one) {
	t_seats *seats = NULL;
	int	how_many = 0;
	int	expected = 1;
	while (expected--)
		add_seat_left(&seats);
	if (seats != NULL)
	{
		t_seats *ptr = seats;
		do{
			how_many++;
			seats = seats->right;
		}
		while (seats != ptr);
	}
	mu_assert(how_many == 1, "expected 1");
}

MU_TEST(test_number_of_seats_two) {
	t_seats *seats = NULL;
	int	how_many = 0;
	int	expected = 2;
	while (expected--)
		add_seat_left(&seats);
	if (seats != NULL)
	{
		t_seats *ptr = seats;
		do{
			how_many++;
			seats = seats->right;
		}
		while (seats != ptr);
	}
	mu_assert(how_many == 2, "expected 2");
}

MU_TEST(test_number_of_seats_five) {
	t_seats *seats = NULL;
	int	how_many = 0;
	int	expected = 5;
	while (expected--)
		add_seat_left(&seats);
	if (seats != NULL)
	{
		t_seats *ptr = seats;
		do{
			how_many++;
			seats = seats->right;
		}
		while (seats != ptr);
	}
	mu_assert(how_many == 5, "expected 5");
}

MU_TEST(test_number_of_seats_ten) {
	t_seats *seats = NULL;
	int	how_many = 0;
	int	expected = 10;
	while (expected--)
		add_seat_left(&seats);
	if (seats != NULL)
	{
		t_seats *ptr = seats;
		do{
			how_many++;
			seats = seats->right;
		}
		while (seats != ptr);
	}
	mu_assert(how_many == 10, "expected 10");
}

MU_TEST_SUITE(test_suite) {
	// MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
	MU_RUN_TEST(test_number_of_seats_zero);
	MU_RUN_TEST(test_number_of_seats_one);
	MU_RUN_TEST(test_number_of_seats_two);
	MU_RUN_TEST(test_number_of_seats_five);
	MU_RUN_TEST(test_number_of_seats_ten);
}

int main (int argc, char **argv)
{
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}