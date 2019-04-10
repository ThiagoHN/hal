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

#include <arch/cluster/riscv32-cluster/cores.h>
#include <nanvix/const.h>

/**
 * @brief Table of locks.
 */
PRIVATE rv32i_spinlock_t locks[RISCV32_CLUSTER_NUM_CORES] = {
	RV32I_SPINLOCK_UNLOCKED, /* Master Core  */
	RV32I_SPINLOCK_UNLOCKED, /* Slave Core 1 */
	RV32I_SPINLOCK_UNLOCKED, /* Slave Core 2 */
	RV32I_SPINLOCK_UNLOCKED, /* Slave Core 3 */
	RV32I_SPINLOCK_UNLOCKED, /* Slave Core 4 */
};

/**
 * Table of pending events.
 */
PRIVATE int events[RISCV32_CLUSTER_NUM_CORES] ALIGN(RV32I_CACHE_LINE_SIZE) = {
	0, /* Master Core  */
	0, /* Slave Core 1 */
	0, /* Slave Core 2 */
	0, /* Slave Core 3 */
	0, /* Slave Core 4 */
};

/*============================================================================*
 * riscv32_cluster_event_send()                                               *
 *============================================================================*/

/**
 * @todo TODO provide a detailed description of this function.
 */
PUBLIC int riscv32_cluster_event_send(int coreid)
{
	int mycoreid;

	/* Invalid core. */
	if (UNLIKELY(coreid < 0))
		return (-EINVAL);

	mycoreid = rv32i_core_get_id();

	/* Bad core. */
	if (UNLIKELY(coreid == mycoreid))
		return (-EINVAL);

	/* Set the pending IPI flag. */
	events[coreid] |= (1 << mycoreid);
	rv32i_cache_inval();

	return (0);
}

/*============================================================================*
 * riscv32_cluster_event_ack()                                                *
 *============================================================================*/

/**
 * @todo TODO provide a detailed description of this function.
 */
PUBLIC int riscv32_cluster_event_ack(void)
{
	int mycoreid = rv32i_core_get_id();

	/* Clear pending events in the current core. */
	events[mycoreid] = 0;
	rv32i_cache_inval();

	return (0);
}

/*============================================================================*
 * rv32i_core_waitclear()                                                      *
 *============================================================================*/

/**
 * @todo TODO provide a detailed description of this function.
 */
PUBLIC int riscv32_cluster_event_waitclear(void)
{
	int mycoreid = rv32i_core_get_id();

	while (TRUE)
	{
		rv32i_spinlock_lock(&locks[mycoreid]);

			if (events[mycoreid])
				break;

		rv32i_spinlock_unlock(&locks[mycoreid]);
	}

		/* Clear IPI. */
		for (int i = 0; i < RISCV32_CLUSTER_NUM_CORES; i++)
		{
			if (events[mycoreid] & (1 << i))
			{
				events[mycoreid] &= ~(1 << i);
				break;
			}
		}

	rv32i_spinlock_unlock(&locks[mycoreid]);

	return (0);
}