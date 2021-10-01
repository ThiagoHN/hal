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

#ifndef ARCH_CLUSTER_ARM64_CLUSTER_PSCI_H_
#define ARCH_CLUSTER_ARM64_CLUSTER_PSCI_H_

    /**
     * @cond arm64
     */

    #include <nanvix/const.h>

    /**
     * @name ARM64 PSCI ADDRESS
     */
    /**@{*/
    #define PSCI_v0_2_BASE          0x84000000
    #define PSCI_v0_2_BASE_64BIT    0xc4000000
    /**@}*/

    /**
     * @name ARM64 PSCI MACROS
     */
    /**@{*/
    #define PSCI_v0_2_64BIT_CPU_ON  (PSCI_v0_2_BASE_64BIT + (3))
    #define PSCI_v0_2_CPU_OFF       (PSCI_v0_2_BASE + (2))
    /**@}*/

    /**
     * @name ARM64 PSCI RETURN CODES
     */
    /**@{*/
    #define PSCI_RET_SUCCESS			 0
    #define PSCI_RET_NOT_SUPPORTED		-1
    #define PSCI_RET_INVALID_PARAMS		-2
    #define PSCI_RET_DENIED				-3
    #define PSCI_RET_ALREADY_ON			-4
    #define PSCI_RET_ON_PENDING			-5
    #define PSCI_RET_INTERNAL_FAILURE	-6
    #define PSCI_RET_NOT_PRESENT		-7
    #define PSCI_RET_DISABLED			-8
    #define PSCI_RET_INVALID_ADDRESS	-9
    /**@}*/

    /**
     * @name ARM64 core macros.
     */
    /**@{*/
    #define ARM64_CORE_MASTER (0)
    #define ARM64_CORE_SLAVE1 (1)
    #define ARM64_CORE_SLAVE2 (2)
    #define ARM64_CORE_SLAVE3 (3)
    /**@}*/

#ifndef _ASM_FILE_

    /**
	 * @name PSCI Core Types
	 */
	/**@{*/
    typedef int psci_t;
    typedef int core_id;
    /**@}*/

    /**
	 * @brief Boot the slaves cores.
	 */
    EXTERN void arm64_boot_slaves(void);

    /**
	 * @brief Turn on a core.
	 */
    EXTERN psci_t arm64_psci_core_boot(core_id);

#endif /* _ASM_FILE_ */

/**@endcond*/

#endif /* ARCH_CLUSTER_ARM64_CLUSTER_PSCI_H_ */