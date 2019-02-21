/*
 * MIT License
 *
 * Copyright(c) 2018 Pedro Henrique Penna <pedrohenriquepenna@gmail.com>
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

#include <nanvix/mm.h>
#include <nanvix/thread.h>
#include <nanvix.h>
#include "test.h"

/**
 * @brief Number of threads to spawn.
 */
#define NTHREADS (THREAD_MAX - 1)

/**
 * @name Extra Tests
 */
/**@{*/
#define UTEST_KTHREAD_BAD_START 0 /**< Test bad thread start?    */
#define UTEST_KTHREAD_BAD_ARG   0 /**< Test bad thread argument? */
#define UTEST_KTHREAD_BAD_JOIN  0 /**< Test bad thread join?     */
#define UTEST_KTHREAD_BAD_EXIT  0 /**< Test bad thread exit?     */
/**@}*/

/**
 * @brief Dummy task.
 *
 * @param arg Unused argument.
 */
static void *task(void *arg)
{
	((void) arg);

	return (NULL);
}

/*============================================================================*
 * API Testing Units                                                          *
 *============================================================================*/

/**
 * @brief API test for thread identification.
 */
void test_api_kthread_self(void)
{
	test_assert(kthread_self() == 1);
}

/**
 * @brief API test for thread creation/termination.
 */
void test_api_kthread_create(void)
{
	kthread_t tid[NTHREADS];

	/* Spawn threads. */
	for (int i = 0; i < NTHREADS; i++)
		test_assert(kthread_create(&tid[i], task, NULL) == 0);

	/* Wait for threads. */
	for (int i = 0; i < NTHREADS; i++)
		test_assert(kthread_join(tid[i], NULL) == 0);
}

/*============================================================================*
 * Fault Injection Testing Units                                              *
 *============================================================================*/

/**
 * @brief Fault Injection test for thread creation/termination.
 */
void test_fault_kthread_create(void)
{
	kthread_t tid[NTHREADS + 1];

	/* Invalid start routine. */
	test_assert(kthread_create(&tid[0], NULL, NULL) < 0);

	/* Bad starting routine. */
#if (defined(UTEST_KTHREAD_BAD_START) && (UTEST_KTHREAD_BAD_START == 1))
	test_assert(kthread_create(&tid[0], (void *(*)(void *)) KBASE_VIRT, NULL) < 0);
	test_assert(kthread_create(&tid[0], (void *(*)(void *)) (UBASE_VIRT - PAGE_SIZE), NULL) < 0);
#endif

	/* Bad argument. */
#if (defined(UTEST_KTHREAD_BAD_ARG) && (UTEST_KTHREAD_BAD_ARG == 1))
	test_assert(kthread_create(&tid[0], task, (void *(*)(void *)) KBASE_VIRT) < 0);
	test_assert(kthread_create(&tid[0], task, (void *(*)(void *)) (UBASE_VIRT - PAGE_SIZE)) < 0);
#endif

	/* Spawn too many threads. */
	for (int i = 0; i < NTHREADS; i++)
		test_assert(kthread_create(&tid[i], task, NULL) == 0);
	test_assert(kthread_create(&tid[NTHREADS], task, NULL) < 0);
	for (int i = 0; i < NTHREADS; i++)
		test_assert(kthread_join(tid[i], NULL) == 0);

	/* Join invalid thread. */
	test_assert(kthread_join(-1, NULL) < 0);
	test_assert(kthread_join(0, NULL) < 0);
	test_assert(kthread_join(1, NULL) < 0);

	/* Join bad thread. */
	test_assert(kthread_create(&tid[0], task, NULL) == 0);
	test_assert(kthread_join(2, NULL) < 0);
	test_assert(kthread_join(tid[0], NULL) == 0);

	/* Join with bad return value. */
#if (defined(UTEST_KTHREAD_BAD_JOIN) && (UTEST_KTHREAD_BAD_JOIN == 1))
	test_assert(kthread_create(&tid[0], task, NULL) == 0);
	test_assert(kthread_join(tid[0], (void *)(KBASE_VIRT)) < 0);
	test_assert(kthread_join(tid[0], (void *)(UBASE_VIRT - PAGE_SIZE)) < 0);
	test_assert(kthread_join(tid[0], NULL) == 0);
#endif

	/* Exit with bad return value. */
#if (defined(UTEST_KTHREAD_BAD_EXIT) && (UTEST_KTHREAD_BAD_EXIT == 1))
	test_assert(kthread_exit((void *)(KBASE_VIRT)) < 0);
	test_assert(kthread_exit((void *)(UBASE_VIRT - PAGE_SIZE)) < 0);
#endif
}

/*============================================================================*
 * Stress Testing Units                                                       *
 *============================================================================*/

/**
 * @brief Stress test for thread creation/termination.
 */
void test_stress_kthread_create(void)
{
	for (int j = 0; j < NITERATIONS; j++)
	{
		kthread_t tid[NTHREADS];

		/* Spawn threads. */
		for (int i = 0; i < NTHREADS; i++)
			test_assert(kthread_create(&tid[i], task, NULL) == 0);

		/* Wait for threads. */
		for (int i = 0; i < NTHREADS; i++)
			test_assert(kthread_join(tid[i], NULL) == 0);
	}
}
