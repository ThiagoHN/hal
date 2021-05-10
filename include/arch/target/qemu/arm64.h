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

#ifndef TARGET_QEMU_ARM64_H_
#define TARGET_QEMU_ARM64_H_

	#ifndef __NEED_TARGET_QEMU_ARM64
		#error "bad target configuration?"
	#endif

	/* Target Interface Implementation */
	#include <arch/target/qemu/arm64/_arm64.h>

/**
 * @defgroup target-qemu-arm64 QEMU ARM8 64-bits
 * @ingroup targets
 *
 * @brief QEMU ARM8 64-bits
 */
/**@{*/

	#include <arch/target/qemu/arm64/stdout.h>

	/**
	 * @brief Frequency (in MHz).
	 */
	#define QEMU_ARM64_FREQUENCY 10

/**@}*/

/*============================================================================*
 * Exported Interface                                                         *
 *============================================================================*/

/**
 * @cond qemu_arm64
 */

	/**
	 * @name Exported Constants
	 */
	/**@{*/
	#define TARGET_FREQUENCY QEMU_ARM64_FREQUENCY
	/**@}*/

	/**
	 * @name Provided Features
	 */
	/**@{*/
	#define __TARGET_HAS_STDOUT  1 /**< Standard Output feature */
	#define __TARGET_HAS_SYNC    0 /**< Synchronization feature */
	#define __TARGET_HAS_MAILBOX 0 /**< Mailbox feature         */
	#define __TARGET_HAS_PORTAL  0 /**< Portal feature          */
	/**@}*/

/**@endcond*/

#endif /* TARGET_QEMU_ARM64_H_ */
