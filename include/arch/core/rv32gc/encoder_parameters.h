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

#ifndef ARCH_CORE_RV32GC_ENCODER_PARAMETERS_H_
#define ARCH_CORE_RV32GC_ENCODER_PARAMETERS_H_

/* Defining the machine size */
#define RV32GC_XLEN 32 

/* 
* This document defines a number of parameters for describing aspects of the
* encoder such as the widths of buses, the presence or absence of optional features
* and the size of resources
*/

#define RV32GC_ARCH_P                           0 /**< The architecture specification version */
#define RV32GC_BPRED_SIZE_P                     0 /**< Number of entries in the branch predictor is 2^(bpred_size_p) */
#define RV32GC_CACHE_SIZE_P                     0 /**< Number of entries in the jump target cache is 2^(cache_size_p) */
#define RV32GC_CALL_COUNTER_SIZE_P              0 /**< Number of bits in the nested call counter is 2^(call_counter_size_p) */
#define RV32GC_CTYPE_WIDTH_P                    1 /**< Width of the ctype bus */
#define RV32GC_CONTEXT_WIDTH_P                  0 /**< Width of context bus */ 
#define RV32GC_ECAUSE_WIDTH_P                   3 /**< Width of exception cause bus */
#define RV32GC_ECAUSE_CHOICE_P                  5 /**< Number of bits of exception cause to match using multiple choice */
#define RV32GC_F0S_WIDTH_P                      0 /**< Width of the subformat field in format 0 te_inst packets */
#define RV32GC_FILTER_CONTEXT_P                 1 /**< Filtering on context supported when 1 */
#define RV32GC_FILTER_EXCINT_P                  1 /**< Filtering on exception cause or interrupt supported when non_zero */
#define RV32GC_FILTER_PRIVILEGE_P               1 /**< Filtering on privilege supported when 1 */
#define RV32GC_FILTER_TVAL_P                    1 /**< Filtering on trap value supported when 1 */
#define RV32GC_IADDRESS_LSB_P                   0 /**< LSB of instruction address bus to trace */
#define RV32GC_IADRESS_WIDTH_P   (RV32GC_XLEN -1) /**< Width of instruction address bus */
#define RV32GC_IRETIRE_WIDTH_P                  2 /**< Width of the iretire bus */
#define RV32GC_ILASTSIZE_WIDTH_P                0 /**< Width of the ilastsize bus */
#define RV32GC_ITYPE_WIDTH_P                    4 /**< Width of the itype bus */
#define RV32GC_NOCONTEXT_P                      0 /**< Exclude context from te_inst packets if 1 */
#define RV32GC_PRIVILEGE_WIDTH_P                2 /**< Width of privilege bus */
#define RV32GC_RETIRES_P                        0 /**< Maximum number of instructions that can be retired per block */
#define RV32GC_RETURN_STACK_SIZE_P              0 /**< Number of entries in the return address stack is 2^(return_stack_size_p) */
#define RV32GC_SIZUMP_P                         0 /**< sijump is used to identify sequentially inferable jumps */
#define RV32GC_TAKEN_BRANCHES_P                 0 /**< Number of times iretire, itype etc */
#define RV32GC_IMPDEEF_WIDTH_P                  0 /**< Width of implementation-defined input bus */

#endif