/*
 * MIT License
 *
 * Copyright(c) 2011-2019 The Maintainers of Nanvix
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <nanvix/hal/hal.h>
#include <nanvix/const.h>
#include <nanvix/klib.h>
#include "test.h"

/*============================================================================*
 * API Tests                                                                  *
 *============================================================================*/

/**
 * @brief API Test: Query Core ID
 */
PRIVATE void test_core_get_id(void)
{
	KASSERT(core_get_id() == COREID_MASTER);
}

/**
 * @brief API Test: Number of cores started.
 */
PRIVATE int cores_started = 1;

/**
 * @brief API Test: Spinlock for number of cores.
 */
PRIVATE spinlock_t core_start_lock = SPINLOCK_UNLOCKED;

/**
 * @brief API Test: Slave Core Entry Point.
 */
PRIVATE void test_core_slave_entry(void)
{
	spinlock_lock(&core_start_lock);
		cores_started++;
	spinlock_unlock(&core_start_lock);
}

/**
 * @brief API Test: Start Execution in Slave Cores
 */
PRIVATE void test_core_start_slave(void)
{
	/* Unit test not applicable. */
	if (!CLUSTER_IS_MULTICORE)
		return;

	/**
	 * Start each slave core.
	 */
	for (int i = 0; i < HAL_NUM_CORES; i++)
		if (i != COREID_MASTER)
			core_start(i, test_core_slave_entry);

	/**
	 * Wait indefinitely for all cores start.
	 *
	 * @note: If for some reason not all cores were started,
	 * the master core will hang forever.
	 */
	while (TRUE)
	{
		dcache_invalidate();

		if (cores_started == HAL_NUM_CORES)
			break;
	}
}

/*============================================================================*
 * Test Driver                                                                *
 *============================================================================*/

/**
 * @brief Unit tests.
 */
PRIVATE struct test core_tests_api[] = {
	{ test_core_get_id,      "Get Core ID"           },
	{ test_core_start_slave, "Start Execution Slave" },
	{ NULL,                  NULL                    },
};

/**
 * The test_core() function launches testing units on the core
 * interface of the HAL.
 *
 * @author Pedro Henrique Penna
 */
PUBLIC void test_core(void)
{
	/* API Tests */
	for (int i = 0; core_tests_api[i].test_fn != NULL; i++)
	{
		core_tests_api[i].test_fn();
		kprintf("[test][api][core] %s [passed]", core_tests_api[i].name);
	}
}
