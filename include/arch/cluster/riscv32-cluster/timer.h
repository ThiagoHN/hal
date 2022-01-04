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

#ifndef ARCH_CLUSTER_CLUSTER_RISCV32_CLUSTER_TIMER_H_
#define ARCH_CLUSTER_CLUSTER_RISCV32_CLUSTER_TIMER_H_

	/* Cluster Interface Implementation */
	#include <arch/cluster/riscv32-cluster/_riscv32-cluster.h>

	/* Must come first. */
	#define __NEED_CLUSTER_CLINT

/**
 * @addtogroup rscv32-cluster-timer Timer
 * @ingroup riscv32-cluster
 *
 * @brief 64-bit Timer
 */
/**@{*/

	#include <arch/cluster/riscv32-cluster/clint.h>
	#include <posix/stdint.h>

	/**
	 * @brief Timer frequency (10 MHz)
	 */
	#define RISCV32_CLUSTER_TIMEBASE 10000000

#ifndef _ASM_FILE_

	/**
	 * @brief Reads the mtime register.
	 *
	 * @returns The timestamp counter.
	 *
	 * @author João Vicente Souto
	 */
	EXTERN uint64_t rv32gc_clock_read(void);

#endif /* !_ASM_FILE_ */

/*============================================================================*
 * Exported Interface                                                         *
 *============================================================================*/

/**
 * @cond riscv32_cluster
 */

	/**
	 * @name Exported Constants
	 */
	/**@{*/
	#define CLUSTER_FREQ RISCV32_CLUSTER_TIMEBASE /**< @see RISCV32_CLUSTER_TIMEBASE */
	/**@}*/

	/**
	 * @name Exported Functions
	 */
	/**@{*/
	#define __timer_init_fn   /**< timer_init() */
	#define __timer_reset_fn /**< timer_reset() */
	#define __clock_read_fn  /**< clock_read()  */
	/**@}*/

#ifndef _ASM_FILE_

	/**
	 * @see timer_init().
	 */
	#define __timer_init(freq) \
		rv32gc_timer_init(freq, RISCV32_CLUSTER_TIMEBASE, (uint64_t *) RISCV32_CLUSTER_CLINT_MTIME_BASE,	(uint64_t *) RISCV32_CLUSTER_CLINT_MTIMECMP_BASE)

	/**
	 * @see rv32gc_timer_reset().
	 */
	#define timer_reset(void) \
		rv32gc_timer_reset(void)

	/**
	 * @see rv32gc_clock_read().
	 */
	#define clock_read(void) rv32gc_clock_read(void)

#endif /* !_ASM_FILE_ */

/**@endcond*/

/*============================================================================*/

/**@}*/

#endif /* ARCH_CLUSTER_CLUSTER_RISCV32_CLUSTER_TIMER */
