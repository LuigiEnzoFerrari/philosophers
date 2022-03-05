#include "minunit.h"
#include "philo.h"

MU_TEST(test_number_of_forks_zero) {
	t_fork *forks = NULL;
	int  how_many = 0;
	add_forks(&forks, 0);
	if (forks != NULL)
	{
		t_fork *ptr = forks;
		do{
			how_many++;
			forks = forks->next;
		}
		while (forks != ptr);
	}
	mu_assert(how_many == 0, "expected 0");
}


MU_TEST(test_number_of_forks_one) {
	t_fork *forks = NULL;
	int  how_many = 0;
	add_forks(&forks, 1);
	if (forks != NULL)
	{
		t_fork *ptr = forks;
		do{
			how_many++;
			forks = forks->next;
		}
		while (forks != ptr);
	}
	mu_assert(how_many == 1, "expected 1");
}

MU_TEST(test_number_of_forks_two) {
	t_fork *forks = NULL;
	int  how_many = 0;
	add_forks(&forks, 2);
	if (forks != NULL)
	{
		t_fork *ptr = forks;
		do{
			how_many++;
			forks = forks->next;
		}
		while (forks != ptr);
	}
	mu_assert(how_many == 2, "expected 2");
}

MU_TEST(test_number_of_forks_five) {
	t_fork *forks = NULL;
	int  how_many = 0;
	add_forks(&forks, 5);
	if (forks != NULL)
	{
		t_fork *ptr = forks;
		do{
			how_many++;
			forks = forks->next;
		}
		while (forks != ptr);
	}
	mu_assert(how_many == 5, "expected 5");
}

MU_TEST(test_number_of_forks_ten) {
	t_fork *forks = NULL;
	int  how_many = 0;
	add_forks(&forks, 10);
	if (forks != NULL)
	{
		t_fork *ptr = forks;
		do{
			how_many++;
			forks = forks->next;
		}
		while (forks != ptr);
	}
	mu_assert(how_many == 10, "expected 10");
}

MU_TEST_SUITE(test_suite) {
	// MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
	MU_RUN_TEST(test_number_of_forks_zero);
	MU_RUN_TEST(test_number_of_forks_one);
	MU_RUN_TEST(test_number_of_forks_two);
	MU_RUN_TEST(test_number_of_forks_five);
	MU_RUN_TEST(test_number_of_forks_ten);
}


int main (int argc, char **argv)
{
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}