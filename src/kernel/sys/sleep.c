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

#include <nanvix/const.h>
#include <nanvix/thread.h>

/**
 * @brief Lock to sleeping queues.
 */
spinlock_t lock = SPINLOCK_UNLOCKED;

/**
 * brief Sleeping queues.
 */
PRIVATE struct
{
	int tid;
	struct condvar cond;
} queues[KTHREAD_MAX] = {
	[0 ... (KTHREAD_MAX - 1)] = {
		.tid = -1,
		.cond = COND_INITIALIZER
	},
};

/*============================================================================*
 * sys_sleep()                                                                *
 *============================================================================*/

/**
 * The sys_sleep() function causes the calling thread to block
 * until it receives a wakeup signal from another thread.
 */
PUBLIC int sys_sleep(void)
{
	int coreid;
	struct thread *t;

	t = thread_get_curr();
	coreid = thread_get_coreid(t);

	spinlock_lock(&lock);

		queues[coreid].tid = thread_get_id(t);
		cond_wait(&queues[coreid].cond, &lock);
		queues[coreid].tid = -1;

	spinlock_unlock(&lock);

	return (0);
}

/**
 * The sys_wakeup() function wakes up the thread whose identifier
 * matchers @p tid and it is asleep.
 *
 * @retval -EINVAL Invalid thread ID.
 */
PUBLIC int sys_wakeup(int tid)
{
	int ret = 0;

	/* Invalid thread ID. */
	if (tid < 0)
		return (-EINVAL);

	spinlock_lock(&lock);

		/* Search for sleeping thread. */
		for (int i = 0; i < KTHREAD_MAX; i++)
		{
			/* Found. */
			if (tid == queues[i].tid)
			{
				cond_broadcast(&queues[i].cond);
				goto done;
			}
		}

		ret = -EINVAL;

done:

	spinlock_unlock(&lock);

	return (ret);
}