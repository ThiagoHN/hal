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

#ifndef NANVIX_HAL_TARGET_PORTAL_H_
#define NANVIX_HAL_TARGET_PORTAL_H_

	/* Target Interface Implementation */
	#include <nanvix/hal/target/_target.h>

/*============================================================================*
 * Interface Implementation Checking                                          *
 *============================================================================*/

#if defined(__INTERFACE_CHECK) || defined(__INTERFACE_CHECK_TARGET_AL) || defined(__INTERFACE_CHECK_PORTAL)

	/* Feature Checking */
	#ifndef __TARGET_HAS_PORTAL
	#error "does this target feature a portal interface?"
	#endif

	/* Has Mailbox Interface */
	#if (__TARGET_HAS_PORTAL)

		/* Constants */
		#ifndef PORTAL_CREATE_MAX
		#error "PORTAL_CREATE_MAX not defined"
		#endif
		#ifndef PORTAL_OPEN_MAX
		#error "PORTAL_OPEN_MAX not defined"
		#endif
		#ifndef PORTAL_MAX_SIZE
		#error "PORTAL_MAX_SIZE not defined"
		#endif

		/* Structures */
		#ifndef __aiocb_struct
		#error "struct aiocb not defined?"
		#endif

		/* Functions */
		#ifndef __portal_create_fn
		#error "portal_create() not defined?"
		#endif
		#ifndef __portal_allow_fn
		#error "portal_allow() not defined?"
		#endif
		#ifndef __portal_open_fn
		#error "portal_open() not defined?"
		#endif
		#ifndef __portal_unlink_fn
		#error "portal_unlink() not defined?"
		#endif
		#ifndef __portal_close_fn
		#error "portal_close() not defined?"
		#endif
		#ifndef __portal_awrite_fn
		#error "portal_write() not defined?"
		#endif
		#ifndef __portal_aread_fn
		#error "portal_aread() not defined?"
		#endif
		#ifndef __portal_wait_fn
		#error "portal_wait() not defined?"
		#endif

	#else

		/* Constants */
		#define PORTAL_CREATE_MAX 1
		#define PORTAL_OPEN_MAX   1
		#define PORTAL_MAX_SIZE   1

	#endif

#endif

/*============================================================================*
 * Provided Interface                                                         *
 *============================================================================*/

/**
 * @defgroup kernel-hal-target-sync Syncrhonization service
 * @ingroup kernel-hal-target
 *
 * @brief Target Standard Output HAL Interface
 */
/**@{*/

	#include <nanvix/const.h>
	#include <nanvix/klib.h>
	#include <errno.h>

	/**
	 * @brief Creates a portal.
	 *
	 * @param nodenum Logic ID of the underlying NoC node.
	 *
	 * @returns Upon successful completion, the ID of the newly created
	 * portal is returned. Upon failure, a negative error code is
	 * returned instead.
	 */
#if (__TARGET_HAS_PORTAL)
	EXTERN int portal_create(int nodenum);
#else
	static inline int portal_create(int nodenum)
	{
		UNUSED(nodenum);

		return (-ENOSYS);
	}
#endif

	/**
	 * @brief Enables read operations from a remote.
	 *
	 * @param portalid ID of the target portal.
	 * @param remote   NoC node ID of target remote.
	 *
	 * @returns Upons successful completion zero is returned. Upon failure,
	 * a negative error code is returned instead.
	 */
#if (__TARGET_HAS_PORTAL)
	EXTERN int portal_open(int local, int remote);
#else
	static inline int portal_open(int local, int remote)
	{
		UNUSED(local);
		UNUSED(remote);

		return (-ENOSYS);
	}
#endif

	/**
	 * @brief Allows remote writes in a portal.
	 *
	 * @param portalid ID of the target portal.
	 * @param nodenum  Logic ID of the target NoC node.
	 *
	 * @reutrns Upon successful completion, zero is returned. Upon
	 * failure, a negative error code is returned instead.
	 */
#if (__TARGET_HAS_PORTAL)
	EXTERN int portal_allow(int portalid, int remote);
#else
	static inline int portal_allow(int portalid, int remote)
	{
		UNUSED(portalid);
		UNUSED(remote);

		return (-ENOSYS);
	}
#endif

	/**
	 * @brief Destroys a portal.
	 *
	 * @param portalid ID of the target portal.
	 *
	 * @returns Upon successful completion, zero is returned. Upon failure,
	 * a negative error code is returned instead.
	 */
#if (__TARGET_HAS_PORTAL)
	EXTERN int portal_unlink(int portalid);
#else
	static inline int portal_unlink(int portalid)
	{
		UNUSED(portalid);

		return (-ENOSYS);
	}
#endif

	/**
	 * @brief Closes a portal.
	 *
	 * @param portalid ID of the target portal.
	 *
	 * @returns Upon successful completion, zero is returned. Upon
	 * failure, a negative error code is returned instead.
	 */
#if (__TARGET_HAS_PORTAL)
	EXTERN int portal_close(int portalid);
#else
	static inline int portal_close(int portalid)
	{
		UNUSED(portalid);

		return (-ENOSYS);
	}
#endif

	/**
	 * @brief Writes data to a portal.
	 *
	 * @param portalid  ID of the target portal.
	 * @param buffer Buffer where the data should be read from.
	 * @param size   Number of bytes to write.
	 *
	 * @returns Upon successful completion, the number of bytes
	 * successfully written is returned. Upon failure, a negative error
	 * code is returned instead.
	 */
#if (__TARGET_HAS_PORTAL)
	EXTERN int portal_awrite(int portalid, const void * buffer, uint64_t size, struct aiocb * aiocb);
#else
	static inline int portal_awrite(int portalid, const void * buffer, uint64_t size, struct aiocb * aiocb)
	{
		UNUSED(portalid);
		UNUSED(buffer);
		UNUSED(size);
		UNUSED(aiocb);

		return (-ENOSYS);
	}
#endif

	/**
	 * @brief Reads data from a portal.
	 *
	 * @param portalid  ID of the target portal.
	 * @param buffer Buffer where the data should be written to.
	 * @param size   Number of bytes to read.
	 * @param aiocb  Asynchronous operation control.
	 *
	 * @returns Upon successful completion, 0 is returned
	 * and non zero otherwise.
	 */
#if (__TARGET_HAS_PORTAL)
	EXTERN int portal_aread(int portalid, void * buffer, uint64_t size, struct aiocb * aiocb);
#else
	static inline int portal_aread(int portalid, void * buffer, uint64_t size, struct aiocb * aiocb)
	{
		UNUSED(portalid);
		UNUSED(buffer);
		UNUSED(size);
		UNUSED(aiocb);

		return (-ENOSYS);
	}
#endif

	/**
	 * @brief Waits asynchronous operation.
	 *
	 * @param aiocb Asynchronous operation control.
	 *
	 * @return Zero if wait read correctly and non zero otherwise.
	 */
#if (__TARGET_HAS_PORTAL)
	EXTERN int portal_wait(struct aiocb * aiocb);
#else
	static inline int portal_wait(struct aiocb * aiocb)
	{
		UNUSED(aiocb);

		return (-ENOSYS);
	}
#endif

/**@}*/

#endif /* NANVIX_HAL_TARGET_PORTAL_H_ */