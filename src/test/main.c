/*
 * MIT License
 *
 * Copyright(c) 2011-2020 The Maintainers of Nanvix
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
#include <nanvix/hlib.h>
#include <nanvix/const.h>
#include "test.h"

/**
 * Horizontal line for tests.
 */
PUBLIC const char *HLINE = \
"--------------------------------------------------------------------------------";

/**
 * @brief Launch unit tests on performance interface?
 */
#ifdef __unix64__
#define TEST_PERF 0
#else
#define TEST_PERF 1
#endif

/**
 * @brief Timer frequency (in Hz).
 */
#define TIMER_FREQ 100

/**
 * @brief Launches unit tests on Core AL.
 */
PRIVATE void test_core_al(void)
{
	test_arithmetic();
	test_core();
	test_exception();
	//test_interrupt();
	test_mmu();
	test_tlb();
	test_trap();
#ifndef __unix64__
	test_upcall();
#endif
#if (CORE_HAS_PERF) && (TEST_PERF) && (!__arm64__)
	test_perf();
#endif
	test_abstract_resource();
}

/**
 * @brief Launches unit tests on Cluster AL.
 */
PRIVATE void test_cluster_al(void)
{
#if (CLUSTER_IS_MULTICORE)
	test_cluster_cores();
#endif
}

/**
 * @brief Launches unit tests on Processor AL.
 */
PRIVATE void test_processor_al(void)
{
#ifdef __mppa256__
	test_cnoc();
	test_dnoc();
#endif

#if (PROCESSOR_IS_MULTICLUSTER)
	test_clusters();
#endif
#if (PROCESSOR_HAS_NOC)
	test_noc();
#endif
}

/**
 * @brief Launches unit tests on Target AL.
 */
PRIVATE void test_target_al(void)
{
#if (__TARGET_HAS_SYNC)
	test_sync();
#endif

#if (__TARGET_HAS_MAILBOX)
	test_mailbox();
#endif

#if (__TARGET_HAS_PORTAL)
	test_portal();
#endif
}

#ifndef __unix64__

/**
 * @brief Dummy main function.
 */
PUBLIC int main(int argc, const char *argv[])
{
	UNUSED(argc);
	UNUSED(argv);

	return (0);
}

#endif

/**
 * @brief Initializes the kernel.
 */
PUBLIC NORETURN void kmain(int argc, const char *argv[])
{
	UNUSED(argc);
	UNUSED(argv);

	/*
	 * Initializes the HAL. Must come
	 * before everything else.
	 */
	hal_init();

#ifndef __unix64__

	timer_init(TIMER_FREQ);

#endif

#if (!PROCESSOR_IS_MULTICLUSTER)

	test_core_al();
	test_cluster_al();
	test_processor_al();
	test_target_al();

#else

	int nodenum = processor_node_get_num();

#ifdef __unix64__
	if (nodenum == NODENUM_MASTER)
#else
	/* Run local unit tests. */
	if ((nodenum == NODENUM_MASTER) || (nodenum == NODENUM_SLAVE))
#endif
	{
		test_core_al();
		test_cluster_al();
		test_processor_al();

#ifndef __unix64__
		/* Run comm. service unit tests. */
		if (nodenum == NODENUM_MASTER)
#endif
			test_target_al();
#ifndef __unix64__
		/* Run Inter-Cluster tests. */
		test_stress_al();
#endif
	}
#ifdef __unix64__
	if ((nodenum == NODENUM_MASTER) || (nodenum == NODENUM_SLAVE))
		test_stress_al();
#endif

#endif

	target_poweroff();
}
