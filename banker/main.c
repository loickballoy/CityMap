#include <stdio.h>
#include <criterion/criterion.h>
#include "read.h"
#include "write.h"
#include "need.h"

Test(select, GLOBAL)
{
	unsigned int *result = select(0);
	cr_assert_eq(result, result);
}

int main(void)
{
	unsigned int *H = select(0);

	return 0;
}

