#include "minunit.h"
#include "philo.h"

MU_TEST(test_milli_to_micro_seconds) {
    uint64_t microsec;

    microsec = milli_to_micro(42000);

	mu_assert(microsec == 42000000, "expected 42000000");
}

MU_TEST(test_micro_to_milli_seconds) {
    uint64_t millisec;

    millisec = micro_to_milli(42000000);

	mu_assert(millisec == 42000, "expected 42000");
}

MU_TEST(test_micro_to_seconds) {
    uint64_t second;

    second = micro_to_seconds(42000000);

	mu_assert(second == 42, "expected 42");
}

MU_TEST_SUITE(test_suite) {
	// MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
	MU_RUN_TEST(test_milli_to_micro_seconds);
	MU_RUN_TEST(test_micro_to_milli_seconds);
	MU_RUN_TEST(test_micro_to_seconds);
}

int main (void)
{
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}