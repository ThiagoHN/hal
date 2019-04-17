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

#define __NEED_HAL_CLUSTER
#include <nanvix/hal/cluster.h>
#include <nanvix/klib.h>
#include <nanvix/const.h>

/* Import definitions. */
EXTERN NORETURN void kmain(int, const char *[]);

/**
 * @brief Startup fence.
 */
PRIVATE struct
{
	int master_alive;
	or1k_spinlock_t lock;
} fence = { FALSE , OR1K_SPINLOCK_UNLOCKED};

/**
 * @brief Releases the startup fence.
 */
PRIVATE void or1k_fence_release(void)
{
	or1k_spinlock_lock(&fence.lock);
		fence.master_alive = TRUE;
	or1k_spinlock_unlock(&fence.lock);
}

/**
 * @brief Waits on the startup fence.
 */
PRIVATE void or1k_fence_wait(void)
{
	while (TRUE)
	{
		or1k_spinlock_lock(&fence.lock);

			/* Fence is released. */
			if (fence.master_alive)
			{
				or1k_spinlock_unlock(&fence.lock);
				break;
			}

			noop();
		or1k_spinlock_unlock(&fence.lock);
	}
}

/**
 * Initializes the core components for or1k.
 */
PUBLIC void or1k_cluster_setup(void)
{
	/* Configure Memory Layout. */
	or1k_cluster_mem_setup();

	/* Enable MMU. */
	or1k_mmu_setup();

	/* Configure OMPIC. */
	or1k_ompic_init();

	/* Enable OMPIC interrupts. */
	or1k_pic_unmask(OR1K_INT_OMPIC);

	/* Enable interrupts. */
	or1k_mtspr(OR1K_SPR_SR, or1k_mfspr(OR1K_SPR_SR) | OR1K_SPR_SR_IEE);

	or1k_fence_release();
}

/**
 * @brief Initializes a slave core.
 *
 * The or1k_slave_setup() function initializes the underlying slave
 * core.  It setups the stack and then call the kernel main function.
 * Architectural structures are initialized by the master core and
 * registered later on, when the slave core is started effectively.
 *
 * @note This function does not return.
 *
 * @see or1k_core_setup() and or1k_master_setup().
 *
 * @author Davidson Francis
 */
PUBLIC NORETURN void or1k_cluster_slave_setup(void)
{
	or1k_fence_wait();

	/* Initial TLB. */
	or1k_tlb_init();

	/* Enable MMU. */
	or1k_enable_mmu();

	/* Enable OMPIC interrupts. */
	or1k_pic_unmask(OR1K_INT_OMPIC);

	/* Enable interrupts. */
	or1k_mtspr(OR1K_SPR_SR, or1k_mfspr(OR1K_SPR_SR) | OR1K_SPR_SR_IEE);

	while (TRUE)
	{
		core_idle();
		core_run();
	}
}

/**
 * @brief Initializes the master core.
 *
 * The or1k_cluster_master_setup() function initializes the underlying
 * master core. It setups the stack and then call the kernel main
 * function.
 *
 * @note This function does not return.
 *
 * @author Davidson Francis
 */
PUBLIC NORETURN void or1k_cluster_master_setup(void)
{
	/* Core setup. */
	or1k_cluster_setup();

	/* Kernel main. */
	kmain(0, NULL);
}