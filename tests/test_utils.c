#include "minunit.h"
#include "philo.h"

MU_TEST(test_my_abs_with_negative) {
	uint64_t value;

	value = my_abs(-420000000);

	mu_assert(value == 420000000, "expected 420000000");
}

MU_TEST(test_my_abs_with_positive) {
	uint64_t value;

	value = my_abs(420000000);

	mu_assert(value == 420000000, "expected 420000000");
}

MU_TEST(test_my_abs_with_zero) {
	uint64_t value;

	value = my_abs(0);

	mu_assert(value == 0, "expected 0");
}

MU_TEST(test_my_strtoul_with_zero) {
	uint64_t value;

	value = my_strtoul("0");

	mu_assert(value == (uint64_t)0, "expected 0");
}


MU_TEST(test_my_strtoul_with_big_positive) {
	uint64_t value;

	value = my_strtoul("4294967295");

	mu_assert(value == (uint64_t)4294967295, "expected 4294967295");
}


MU_TEST(test_my_strtoul_with_big_negative) {
	uint64_t value;

	value = my_strtoul("-4294967295");

	mu_assert(value == (uint64_t)-4294967295, "expected -4294967295");
}

MU_TEST_SUITE(test_suite) {
	// MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
	MU_RUN_TEST(test_my_abs_with_negative);
	MU_RUN_TEST(test_my_abs_with_positive);
	MU_RUN_TEST(test_my_abs_with_zero);
	MU_RUN_TEST(test_my_strtoul_with_big_negative);
	MU_RUN_TEST(test_my_strtoul_with_big_positive);
	MU_RUN_TEST(test_my_strtoul_with_zero);
}

int main (void)
{
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}