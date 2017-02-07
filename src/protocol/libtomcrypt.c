#define CRYPT 0x0117
#define LTC_NO_ROLC

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://math.libtomcrypt.com
 */
#ifndef BN_H_
#define BN_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

#if !(defined(LTM1) && defined(LTM2) && defined(LTM3))
 #if defined(LTM2)
  #define LTM3
 #endif
 #if defined(LTM1)
  #define LTM2
 #endif
 #define LTM1

 #if defined(LTM_ALL)
  #define BN_ERROR_C
  #define BN_FAST_MP_INVMOD_C
  #define BN_FAST_MP_MONTGOMERY_REDUCE_C
  #define BN_FAST_S_MP_MUL_DIGS_C
  #define BN_FAST_S_MP_MUL_HIGH_DIGS_C
  #define BN_FAST_S_MP_SQR_C
  #define BN_MP_2EXPT_C
  #define BN_MP_ABS_C
  #define BN_MP_ADD_C
  #define BN_MP_ADD_D_C
  #define BN_MP_ADDMOD_C
  #define BN_MP_AND_C
  #define BN_MP_CLAMP_C
  #define BN_MP_CLEAR_C
  #define BN_MP_CLEAR_MULTI_C
  #define BN_MP_CMP_C
  #define BN_MP_CMP_D_C
  #define BN_MP_CMP_MAG_C
  #define BN_MP_CNT_LSB_C
  #define BN_MP_COPY_C
  #define BN_MP_COUNT_BITS_C
  #define BN_MP_DIV_C
  #define BN_MP_DIV_2_C
  #define BN_MP_DIV_2D_C
  #define BN_MP_DIV_3_C
  #define BN_MP_DIV_D_C
  #define BN_MP_DR_IS_MODULUS_C
  #define BN_MP_DR_REDUCE_C
  #define BN_MP_DR_SETUP_C
  #define BN_MP_EXCH_C
  #define BN_MP_EXPORT_C
  #define BN_MP_EXPT_D_C
  #define BN_MP_EXPT_D_EX_C
  #define BN_MP_EXPTMOD_C
  #define BN_MP_EXPTMOD_FAST_C
  #define BN_MP_EXTEUCLID_C
  #define BN_MP_FREAD_C
  #define BN_MP_FWRITE_C
  #define BN_MP_GCD_C
  #define BN_MP_GET_INT_C
  #define BN_MP_GET_LONG_C
  #define BN_MP_GET_LONG_LONG_C
  #define BN_MP_GROW_C
  #define BN_MP_IMPORT_C
  #define BN_MP_INIT_C
  #define BN_MP_INIT_COPY_C
  #define BN_MP_INIT_MULTI_C
  #define BN_MP_INIT_SET_C
  #define BN_MP_INIT_SET_INT_C
  #define BN_MP_INIT_SIZE_C
  #define BN_MP_INVMOD_C
  #define BN_MP_INVMOD_SLOW_C
  #define BN_MP_IS_SQUARE_C
  #define BN_MP_JACOBI_C
  #define BN_MP_KARATSUBA_MUL_C
  #define BN_MP_KARATSUBA_SQR_C
  #define BN_MP_LCM_C
  #define BN_MP_LSHD_C
  #define BN_MP_MOD_C
  #define BN_MP_MOD_2D_C
  #define BN_MP_MOD_D_C
  #define BN_MP_MONTGOMERY_CALC_NORMALIZATION_C
  #define BN_MP_MONTGOMERY_REDUCE_C
  #define BN_MP_MONTGOMERY_SETUP_C
  #define BN_MP_MUL_C
  #define BN_MP_MUL_2_C
  #define BN_MP_MUL_2D_C
  #define BN_MP_MUL_D_C
  #define BN_MP_MULMOD_C
  #define BN_MP_N_ROOT_C
  #define BN_MP_N_ROOT_EX_C
  #define BN_MP_NEG_C
  #define BN_MP_OR_C
  #define BN_MP_PRIME_FERMAT_C
  #define BN_MP_PRIME_IS_DIVISIBLE_C
  #define BN_MP_PRIME_IS_PRIME_C
  #define BN_MP_PRIME_MILLER_RABIN_C
  #define BN_MP_PRIME_NEXT_PRIME_C
  #define BN_MP_PRIME_RABIN_MILLER_TRIALS_C
  #define BN_MP_PRIME_RANDOM_EX_C
  #define BN_MP_RADIX_SIZE_C
  #define BN_MP_RADIX_SMAP_C
  #define BN_MP_RAND_C
  #define BN_MP_READ_RADIX_C
  #define BN_MP_READ_SIGNED_BIN_C
  #define BN_MP_READ_UNSIGNED_BIN_C
  #define BN_MP_REDUCE_C
  #define BN_MP_REDUCE_2K_C
  #define BN_MP_REDUCE_2K_L_C
  #define BN_MP_REDUCE_2K_SETUP_C
  #define BN_MP_REDUCE_2K_SETUP_L_C
  #define BN_MP_REDUCE_IS_2K_C
  #define BN_MP_REDUCE_IS_2K_L_C
  #define BN_MP_REDUCE_SETUP_C
  #define BN_MP_RSHD_C
  #define BN_MP_SET_C
  #define BN_MP_SET_INT_C
  #define BN_MP_SET_LONG_C
  #define BN_MP_SET_LONG_LONG_C
  #define BN_MP_SHRINK_C
  #define BN_MP_SIGNED_BIN_SIZE_C
  #define BN_MP_SQR_C
  #define BN_MP_SQRMOD_C
  #define BN_MP_SQRT_C
  #define BN_MP_SQRTMOD_PRIME_C
  #define BN_MP_SUB_C
  #define BN_MP_SUB_D_C
  #define BN_MP_SUBMOD_C
  #define BN_MP_TO_SIGNED_BIN_C
  #define BN_MP_TO_SIGNED_BIN_N_C
  #define BN_MP_TO_UNSIGNED_BIN_C
  #define BN_MP_TO_UNSIGNED_BIN_N_C
  #define BN_MP_TOOM_MUL_C
  #define BN_MP_TOOM_SQR_C
  #define BN_MP_TORADIX_C
  #define BN_MP_TORADIX_N_C
  #define BN_MP_UNSIGNED_BIN_SIZE_C
  #define BN_MP_XOR_C
  #define BN_MP_ZERO_C
  #define BN_PRIME_TAB_C
  #define BN_REVERSE_C
  #define BN_S_MP_ADD_C
  #define BN_S_MP_EXPTMOD_C
  #define BN_S_MP_MUL_DIGS_C
  #define BN_S_MP_MUL_HIGH_DIGS_C
  #define BN_S_MP_SQR_C
  #define BN_S_MP_SUB_C
  #define BNCORE_C
 #endif
#define BN_MP_INIT_MULTI_C
 #if defined(BN_ERROR_C)
  #define BN_MP_ERROR_TO_STRING_C
 #endif

 #if defined(BN_FAST_MP_INVMOD_C)
  #define BN_MP_ISEVEN_C
  #define BN_MP_INIT_MULTI_C
  #define BN_MP_COPY_C
  #define BN_MP_MOD_C
  #define BN_MP_SET_C
  #define BN_MP_DIV_2_C
  #define BN_MP_ISODD_C
  #define BN_MP_SUB_C
  #define BN_MP_CMP_C
  #define BN_MP_ISZERO_C
  #define BN_MP_CMP_D_C
  #define BN_MP_ADD_C
  #define BN_MP_EXCH_C
  #define BN_MP_CLEAR_MULTI_C
 #endif

 #if defined(BN_FAST_MP_MONTGOMERY_REDUCE_C)
  #define BN_MP_GROW_C
  #define BN_MP_RSHD_C
  #define BN_MP_CLAMP_C
  #define BN_MP_CMP_MAG_C
  #define BN_S_MP_SUB_C
 #endif

 #if defined(BN_FAST_S_MP_MUL_DIGS_C)
  #define BN_MP_GROW_C
  #define BN_MP_CLAMP_C
 #endif

 #if defined(BN_FAST_S_MP_MUL_HIGH_DIGS_C)
  #define BN_MP_GROW_C
  #define BN_MP_CLAMP_C
 #endif

 #if defined(BN_FAST_S_MP_SQR_C)
  #define BN_MP_GROW_C
  #define BN_MP_CLAMP_C
 #endif

 #if defined(BN_MP_2EXPT_C)
  #define BN_MP_ZERO_C
  #define BN_MP_GROW_C
 #endif

 #if defined(BN_MP_ABS_C)
  #define BN_MP_COPY_C
 #endif

 #if defined(BN_MP_ADD_C)
  #define BN_S_MP_ADD_C
  #define BN_MP_CMP_MAG_C
  #define BN_S_MP_SUB_C
 #endif

 #if defined(BN_MP_ADD_D_C)
  #define BN_MP_GROW_C
  #define BN_MP_SUB_D_C
  #define BN_MP_CLAMP_C
 #endif

 #if defined(BN_MP_ADDMOD_C)
  #define BN_MP_INIT_C
  #define BN_MP_ADD_C
  #define BN_MP_CLEAR_C
  #define BN_MP_MOD_C
 #endif

 #if defined(BN_MP_AND_C)
  #define BN_MP_INIT_COPY_C
  #define BN_MP_CLAMP_C
  #define BN_MP_EXCH_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_MP_CLAMP_C)
 #endif

 #if defined(BN_MP_CLEAR_C)
 #endif

 #if defined(BN_MP_CLEAR_MULTI_C)
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_MP_CMP_C)
  #define BN_MP_CMP_MAG_C
 #endif

 #if defined(BN_MP_CMP_D_C)
 #endif

 #if defined(BN_MP_CMP_MAG_C)
 #endif

 #if defined(BN_MP_CNT_LSB_C)
  #define BN_MP_ISZERO_C
 #endif

 #if defined(BN_MP_COPY_C)
  #define BN_MP_GROW_C
 #endif

 #if defined(BN_MP_COUNT_BITS_C)
 #endif

 #if defined(BN_MP_DIV_C)
  #define BN_MP_ISZERO_C
  #define BN_MP_CMP_MAG_C
  #define BN_MP_COPY_C
  #define BN_MP_ZERO_C
  #define BN_MP_INIT_MULTI_C
  #define BN_MP_SET_C
  #define BN_MP_COUNT_BITS_C
  #define BN_MP_ABS_C
  #define BN_MP_MUL_2D_C
  #define BN_MP_CMP_C
  #define BN_MP_SUB_C
  #define BN_MP_ADD_C
  #define BN_MP_DIV_2D_C
  #define BN_MP_EXCH_C
  #define BN_MP_CLEAR_MULTI_C
  #define BN_MP_INIT_SIZE_C
  #define BN_MP_INIT_C
  #define BN_MP_INIT_COPY_C
  #define BN_MP_LSHD_C
  #define BN_MP_RSHD_C
  #define BN_MP_MUL_D_C
  #define BN_MP_CLAMP_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_MP_DIV_2_C)
  #define BN_MP_GROW_C
  #define BN_MP_CLAMP_C
 #endif

 #if defined(BN_MP_DIV_2D_C)
  #define BN_MP_COPY_C
  #define BN_MP_ZERO_C
  #define BN_MP_INIT_C
  #define BN_MP_MOD_2D_C
  #define BN_MP_CLEAR_C
  #define BN_MP_RSHD_C
  #define BN_MP_CLAMP_C
  #define BN_MP_EXCH_C
 #endif

 #if defined(BN_MP_DIV_3_C)
  #define BN_MP_INIT_SIZE_C
  #define BN_MP_CLAMP_C
  #define BN_MP_EXCH_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_MP_DIV_D_C)
  #define BN_MP_ISZERO_C
  #define BN_MP_COPY_C
  #define BN_MP_DIV_2D_C
  #define BN_MP_DIV_3_C
  #define BN_MP_INIT_SIZE_C
  #define BN_MP_CLAMP_C
  #define BN_MP_EXCH_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_MP_DR_IS_MODULUS_C)
 #endif

 #if defined(BN_MP_DR_REDUCE_C)
  #define BN_MP_GROW_C
  #define BN_MP_CLAMP_C
  #define BN_MP_CMP_MAG_C
  #define BN_S_MP_SUB_C
 #endif

 #if defined(BN_MP_DR_SETUP_C)
 #endif

 #if defined(BN_MP_EXCH_C)
 #endif

 #if defined(BN_MP_EXPORT_C)
  #define BN_MP_INIT_COPY_C
  #define BN_MP_COUNT_BITS_C
  #define BN_MP_DIV_2D_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_MP_EXPT_D_C)
  #define BN_MP_EXPT_D_EX_C
 #endif

 #if defined(BN_MP_EXPT_D_EX_C)
  #define BN_MP_INIT_COPY_C
  #define BN_MP_SET_C
  #define BN_MP_MUL_C
  #define BN_MP_CLEAR_C
  #define BN_MP_SQR_C
 #endif

 #if defined(BN_MP_EXPTMOD_C)
  #define BN_MP_INIT_C
  #define BN_MP_INVMOD_C
  #define BN_MP_CLEAR_C
  #define BN_MP_ABS_C
  #define BN_MP_CLEAR_MULTI_C
  #define BN_MP_REDUCE_IS_2K_L_C
  #define BN_S_MP_EXPTMOD_C
  #define BN_MP_DR_IS_MODULUS_C
  #define BN_MP_REDUCE_IS_2K_C
  #define BN_MP_ISODD_C
  #define BN_MP_EXPTMOD_FAST_C
 #endif

 #if defined(BN_MP_EXPTMOD_FAST_C)
  #define BN_MP_COUNT_BITS_C
  #define BN_MP_INIT_C
  #define BN_MP_CLEAR_C
  #define BN_MP_MONTGOMERY_SETUP_C
  #define BN_FAST_MP_MONTGOMERY_REDUCE_C
  #define BN_MP_MONTGOMERY_REDUCE_C
  #define BN_MP_DR_SETUP_C
  #define BN_MP_DR_REDUCE_C
  #define BN_MP_REDUCE_2K_SETUP_C
  #define BN_MP_REDUCE_2K_C
  #define BN_MP_MONTGOMERY_CALC_NORMALIZATION_C
  #define BN_MP_MULMOD_C
  #define BN_MP_SET_C
  #define BN_MP_MOD_C
  #define BN_MP_COPY_C
  #define BN_MP_SQR_C
  #define BN_MP_MUL_C
  #define BN_MP_EXCH_C
 #endif

 #if defined(BN_MP_EXTEUCLID_C)
  #define BN_MP_INIT_MULTI_C
  #define BN_MP_SET_C
  #define BN_MP_COPY_C
  #define BN_MP_ISZERO_C
  #define BN_MP_DIV_C
  #define BN_MP_MUL_C
  #define BN_MP_SUB_C
  #define BN_MP_NEG_C
  #define BN_MP_EXCH_C
  #define BN_MP_CLEAR_MULTI_C
 #endif

 #if defined(BN_MP_FREAD_C)
  #define BN_MP_ZERO_C
  #define BN_MP_S_RMAP_C
  #define BN_MP_MUL_D_C
  #define BN_MP_ADD_D_C
  #define BN_MP_CMP_D_C
 #endif

 #if defined(BN_MP_FWRITE_C)
  #define BN_MP_RADIX_SIZE_C
  #define BN_MP_TORADIX_C
 #endif

 #if defined(BN_MP_GCD_C)
  #define BN_MP_ISZERO_C
  #define BN_MP_ABS_C
  #define BN_MP_INIT_COPY_C
  #define BN_MP_CNT_LSB_C
  #define BN_MP_DIV_2D_C
  #define BN_MP_CMP_MAG_C
  #define BN_MP_EXCH_C
  #define BN_S_MP_SUB_C
  #define BN_MP_MUL_2D_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_MP_GET_INT_C)
 #endif

 #if defined(BN_MP_GET_LONG_C)
 #endif

 #if defined(BN_MP_GET_LONG_LONG_C)
 #endif

 #if defined(BN_MP_GROW_C)
 #endif

 #if defined(BN_MP_IMPORT_C)
  #define BN_MP_ZERO_C
  #define BN_MP_MUL_2D_C
  #define BN_MP_CLAMP_C
 #endif

 #if defined(BN_MP_INIT_C)
 #endif

 #if defined(BN_MP_INIT_COPY_C)
  #define BN_MP_INIT_SIZE_C
  #define BN_MP_COPY_C
 #endif

 #if defined(BN_MP_INIT_MULTI_C)
  #define BN_MP_ERR_C
  #define BN_MP_INIT_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_MP_INIT_SET_C)
  #define BN_MP_INIT_C
  #define BN_MP_SET_C
 #endif

 #if defined(BN_MP_INIT_SET_INT_C)
  #define BN_MP_INIT_C
  #define BN_MP_SET_INT_C
 #endif

 #if defined(BN_MP_INIT_SIZE_C)
  #define BN_MP_INIT_C
 #endif

 #if defined(BN_MP_INVMOD_C)
  #define BN_MP_ISZERO_C
  #define BN_MP_ISODD_C
  #define BN_FAST_MP_INVMOD_C
  #define BN_MP_INVMOD_SLOW_C
 #endif

 #if defined(BN_MP_INVMOD_SLOW_C)
  #define BN_MP_ISZERO_C
  #define BN_MP_INIT_MULTI_C
  #define BN_MP_MOD_C
  #define BN_MP_COPY_C
  #define BN_MP_ISEVEN_C
  #define BN_MP_SET_C
  #define BN_MP_DIV_2_C
  #define BN_MP_ISODD_C
  #define BN_MP_ADD_C
  #define BN_MP_SUB_C
  #define BN_MP_CMP_C
  #define BN_MP_CMP_D_C
  #define BN_MP_CMP_MAG_C
  #define BN_MP_EXCH_C
  #define BN_MP_CLEAR_MULTI_C
 #endif

 #if defined(BN_MP_IS_SQUARE_C)
  #define BN_MP_MOD_D_C
  #define BN_MP_INIT_SET_INT_C
  #define BN_MP_MOD_C
  #define BN_MP_GET_INT_C
  #define BN_MP_SQRT_C
  #define BN_MP_SQR_C
  #define BN_MP_CMP_MAG_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_MP_JACOBI_C)
  #define BN_MP_CMP_D_C
  #define BN_MP_ISZERO_C
  #define BN_MP_INIT_COPY_C
  #define BN_MP_CNT_LSB_C
  #define BN_MP_DIV_2D_C
  #define BN_MP_MOD_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_MP_KARATSUBA_MUL_C)
  #define BN_MP_MUL_C
  #define BN_MP_INIT_SIZE_C
  #define BN_MP_CLAMP_C
  #define BN_S_MP_ADD_C
  #define BN_MP_ADD_C
  #define BN_S_MP_SUB_C
  #define BN_MP_LSHD_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_MP_KARATSUBA_SQR_C)
  #define BN_MP_INIT_SIZE_C
  #define BN_MP_CLAMP_C
  #define BN_MP_SQR_C
  #define BN_S_MP_ADD_C
  #define BN_S_MP_SUB_C
  #define BN_MP_LSHD_C
  #define BN_MP_ADD_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_MP_LCM_C)
  #define BN_MP_INIT_MULTI_C
  #define BN_MP_GCD_C
  #define BN_MP_CMP_MAG_C
  #define BN_MP_DIV_C
  #define BN_MP_MUL_C
  #define BN_MP_CLEAR_MULTI_C
 #endif

 #if defined(BN_MP_LSHD_C)
  #define BN_MP_GROW_C
  #define BN_MP_RSHD_C
 #endif

 #if defined(BN_MP_MOD_C)
  #define BN_MP_INIT_C
  #define BN_MP_DIV_C
  #define BN_MP_CLEAR_C
  #define BN_MP_ISZERO_C
  #define BN_MP_EXCH_C
  #define BN_MP_ADD_C
 #endif

 #if defined(BN_MP_MOD_2D_C)
  #define BN_MP_ZERO_C
  #define BN_MP_COPY_C
  #define BN_MP_CLAMP_C
 #endif

 #if defined(BN_MP_MOD_D_C)
  #define BN_MP_DIV_D_C
 #endif

 #if defined(BN_MP_MONTGOMERY_CALC_NORMALIZATION_C)
  #define BN_MP_COUNT_BITS_C
  #define BN_MP_2EXPT_C
  #define BN_MP_SET_C
  #define BN_MP_MUL_2_C
  #define BN_MP_CMP_MAG_C
  #define BN_S_MP_SUB_C
 #endif

 #if defined(BN_MP_MONTGOMERY_REDUCE_C)
  #define BN_FAST_MP_MONTGOMERY_REDUCE_C
  #define BN_MP_GROW_C
  #define BN_MP_CLAMP_C
  #define BN_MP_RSHD_C
  #define BN_MP_CMP_MAG_C
  #define BN_S_MP_SUB_C
 #endif

 #if defined(BN_MP_MONTGOMERY_SETUP_C)
 #endif

 #if defined(BN_MP_MUL_C)
  #define BN_MP_TOOM_MUL_C
  #define BN_MP_KARATSUBA_MUL_C
  #define BN_FAST_S_MP_MUL_DIGS_C
  #define BN_S_MP_MUL_C
  #define BN_S_MP_MUL_DIGS_C
 #endif

 #if defined(BN_MP_MUL_2_C)
  #define BN_MP_GROW_C
 #endif

 #if defined(BN_MP_MUL_2D_C)
  #define BN_MP_COPY_C
  #define BN_MP_GROW_C
  #define BN_MP_LSHD_C
  #define BN_MP_CLAMP_C
 #endif

 #if defined(BN_MP_MUL_D_C)
  #define BN_MP_GROW_C
  #define BN_MP_CLAMP_C
 #endif

 #if defined(BN_MP_MULMOD_C)
  #define BN_MP_INIT_C
  #define BN_MP_MUL_C
  #define BN_MP_CLEAR_C
  #define BN_MP_MOD_C
 #endif

 #if defined(BN_MP_N_ROOT_C)
  #define BN_MP_N_ROOT_EX_C
 #endif

 #if defined(BN_MP_N_ROOT_EX_C)
  #define BN_MP_INIT_C
  #define BN_MP_SET_C
  #define BN_MP_COPY_C
  #define BN_MP_EXPT_D_EX_C
  #define BN_MP_MUL_C
  #define BN_MP_SUB_C
  #define BN_MP_MUL_D_C
  #define BN_MP_DIV_C
  #define BN_MP_CMP_C
  #define BN_MP_SUB_D_C
  #define BN_MP_EXCH_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_MP_NEG_C)
  #define BN_MP_COPY_C
  #define BN_MP_ISZERO_C
 #endif

 #if defined(BN_MP_OR_C)
  #define BN_MP_INIT_COPY_C
  #define BN_MP_CLAMP_C
  #define BN_MP_EXCH_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_MP_PRIME_FERMAT_C)
  #define BN_MP_CMP_D_C
  #define BN_MP_INIT_C
  #define BN_MP_EXPTMOD_C
  #define BN_MP_CMP_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_MP_PRIME_IS_DIVISIBLE_C)
  #define BN_MP_MOD_D_C
 #endif

 #if defined(BN_MP_PRIME_IS_PRIME_C)
  #define BN_MP_CMP_D_C
  #define BN_MP_PRIME_IS_DIVISIBLE_C
  #define BN_MP_INIT_C
  #define BN_MP_SET_C
  #define BN_MP_PRIME_MILLER_RABIN_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_MP_PRIME_MILLER_RABIN_C)
  #define BN_MP_CMP_D_C
  #define BN_MP_INIT_COPY_C
  #define BN_MP_SUB_D_C
  #define BN_MP_CNT_LSB_C
  #define BN_MP_DIV_2D_C
  #define BN_MP_EXPTMOD_C
  #define BN_MP_CMP_C
  #define BN_MP_SQRMOD_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_MP_PRIME_NEXT_PRIME_C)
  #define BN_MP_CMP_D_C
  #define BN_MP_SET_C
  #define BN_MP_SUB_D_C
  #define BN_MP_ISEVEN_C
  #define BN_MP_MOD_D_C
  #define BN_MP_INIT_C
  #define BN_MP_ADD_D_C
  #define BN_MP_PRIME_MILLER_RABIN_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_MP_PRIME_RABIN_MILLER_TRIALS_C)
 #endif

 #if defined(BN_MP_PRIME_RANDOM_EX_C)
  #define BN_MP_READ_UNSIGNED_BIN_C
  #define BN_MP_PRIME_IS_PRIME_C
  #define BN_MP_SUB_D_C
  #define BN_MP_DIV_2_C
  #define BN_MP_MUL_2_C
  #define BN_MP_ADD_D_C
 #endif

 #if defined(BN_MP_RADIX_SIZE_C)
  #define BN_MP_ISZERO_C
  #define BN_MP_COUNT_BITS_C
  #define BN_MP_INIT_COPY_C
  #define BN_MP_DIV_D_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_MP_RADIX_SMAP_C)
  #define BN_MP_S_RMAP_C
 #endif

 #if defined(BN_MP_RAND_C)
  #define BN_MP_ZERO_C
  #define BN_MP_ADD_D_C
  #define BN_MP_LSHD_C
 #endif

 #if defined(BN_MP_READ_RADIX_C)
  #define BN_MP_ZERO_C
  #define BN_MP_S_RMAP_C
  #define BN_MP_MUL_D_C
  #define BN_MP_ADD_D_C
  #define BN_MP_ISZERO_C
 #endif

 #if defined(BN_MP_READ_SIGNED_BIN_C)
  #define BN_MP_READ_UNSIGNED_BIN_C
 #endif

 #if defined(BN_MP_READ_UNSIGNED_BIN_C)
  #define BN_MP_GROW_C
  #define BN_MP_ZERO_C
  #define BN_MP_MUL_2D_C
  #define BN_MP_CLAMP_C
 #endif

 #if defined(BN_MP_REDUCE_C)
  #define BN_MP_REDUCE_SETUP_C
  #define BN_MP_INIT_COPY_C
  #define BN_MP_RSHD_C
  #define BN_MP_MUL_C
  #define BN_S_MP_MUL_HIGH_DIGS_C
  #define BN_FAST_S_MP_MUL_HIGH_DIGS_C
  #define BN_MP_MOD_2D_C
  #define BN_S_MP_MUL_DIGS_C
  #define BN_MP_SUB_C
  #define BN_MP_CMP_D_C
  #define BN_MP_SET_C
  #define BN_MP_LSHD_C
  #define BN_MP_ADD_C
  #define BN_MP_CMP_C
  #define BN_S_MP_SUB_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_MP_REDUCE_2K_C)
  #define BN_MP_INIT_C
  #define BN_MP_COUNT_BITS_C
  #define BN_MP_DIV_2D_C
  #define BN_MP_MUL_D_C
  #define BN_S_MP_ADD_C
  #define BN_MP_CMP_MAG_C
  #define BN_S_MP_SUB_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_MP_REDUCE_2K_L_C)
  #define BN_MP_INIT_C
  #define BN_MP_COUNT_BITS_C
  #define BN_MP_DIV_2D_C
  #define BN_MP_MUL_C
  #define BN_S_MP_ADD_C
  #define BN_MP_CMP_MAG_C
  #define BN_S_MP_SUB_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_MP_REDUCE_2K_SETUP_C)
  #define BN_MP_INIT_C
  #define BN_MP_COUNT_BITS_C
  #define BN_MP_2EXPT_C
  #define BN_MP_CLEAR_C
  #define BN_S_MP_SUB_C
 #endif

 #if defined(BN_MP_REDUCE_2K_SETUP_L_C)
  #define BN_MP_INIT_C
  #define BN_MP_2EXPT_C
  #define BN_MP_COUNT_BITS_C
  #define BN_S_MP_SUB_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_MP_REDUCE_IS_2K_C)
  #define BN_MP_REDUCE_2K_C
  #define BN_MP_COUNT_BITS_C
 #endif

 #if defined(BN_MP_REDUCE_IS_2K_L_C)
 #endif

 #if defined(BN_MP_REDUCE_SETUP_C)
  #define BN_MP_2EXPT_C
  #define BN_MP_DIV_C
 #endif

 #if defined(BN_MP_RSHD_C)
  #define BN_MP_ZERO_C
 #endif

 #if defined(BN_MP_SET_C)
  #define BN_MP_ZERO_C
 #endif

 #if defined(BN_MP_SET_INT_C)
  #define BN_MP_ZERO_C
  #define BN_MP_MUL_2D_C
  #define BN_MP_CLAMP_C
 #endif

 #if defined(BN_MP_SET_LONG_C)
 #endif

 #if defined(BN_MP_SET_LONG_LONG_C)
 #endif

 #if defined(BN_MP_SHRINK_C)
 #endif

 #if defined(BN_MP_SIGNED_BIN_SIZE_C)
  #define BN_MP_UNSIGNED_BIN_SIZE_C
 #endif

 #if defined(BN_MP_SQR_C)
  #define BN_MP_TOOM_SQR_C
  #define BN_MP_KARATSUBA_SQR_C
  #define BN_FAST_S_MP_SQR_C
  #define BN_S_MP_SQR_C
 #endif

 #if defined(BN_MP_SQRMOD_C)
  #define BN_MP_INIT_C
  #define BN_MP_SQR_C
  #define BN_MP_CLEAR_C
  #define BN_MP_MOD_C
 #endif

 #if defined(BN_MP_SQRT_C)
  #define BN_MP_N_ROOT_C
  #define BN_MP_ISZERO_C
  #define BN_MP_ZERO_C
  #define BN_MP_INIT_COPY_C
  #define BN_MP_RSHD_C
  #define BN_MP_DIV_C
  #define BN_MP_ADD_C
  #define BN_MP_DIV_2_C
  #define BN_MP_CMP_MAG_C
  #define BN_MP_EXCH_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_MP_SQRTMOD_PRIME_C)
  #define BN_MP_CMP_D_C
  #define BN_MP_ZERO_C
  #define BN_MP_JACOBI_C
  #define BN_MP_INIT_MULTI_C
  #define BN_MP_MOD_D_C
  #define BN_MP_ADD_D_C
  #define BN_MP_DIV_2_C
  #define BN_MP_EXPTMOD_C
  #define BN_MP_COPY_C
  #define BN_MP_SUB_D_C
  #define BN_MP_ISEVEN_C
  #define BN_MP_SET_INT_C
  #define BN_MP_SQRMOD_C
  #define BN_MP_MULMOD_C
  #define BN_MP_SET_C
  #define BN_MP_CLEAR_MULTI_C
 #endif

 #if defined(BN_MP_SUB_C)
  #define BN_S_MP_ADD_C
  #define BN_MP_CMP_MAG_C
  #define BN_S_MP_SUB_C
 #endif

 #if defined(BN_MP_SUB_D_C)
  #define BN_MP_GROW_C
  #define BN_MP_ADD_D_C
  #define BN_MP_CLAMP_C
 #endif

 #if defined(BN_MP_SUBMOD_C)
  #define BN_MP_INIT_C
  #define BN_MP_SUB_C
  #define BN_MP_CLEAR_C
  #define BN_MP_MOD_C
 #endif

 #if defined(BN_MP_TO_SIGNED_BIN_C)
  #define BN_MP_TO_UNSIGNED_BIN_C
 #endif

 #if defined(BN_MP_TO_SIGNED_BIN_N_C)
  #define BN_MP_SIGNED_BIN_SIZE_C
  #define BN_MP_TO_SIGNED_BIN_C
 #endif

 #if defined(BN_MP_TO_UNSIGNED_BIN_C)
  #define BN_MP_INIT_COPY_C
  #define BN_MP_ISZERO_C
  #define BN_MP_DIV_2D_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_MP_TO_UNSIGNED_BIN_N_C)
  #define BN_MP_UNSIGNED_BIN_SIZE_C
  #define BN_MP_TO_UNSIGNED_BIN_C
 #endif

 #if defined(BN_MP_TOOM_MUL_C)
  #define BN_MP_INIT_MULTI_C
  #define BN_MP_MOD_2D_C
  #define BN_MP_COPY_C
  #define BN_MP_RSHD_C
  #define BN_MP_MUL_C
  #define BN_MP_MUL_2_C
  #define BN_MP_ADD_C
  #define BN_MP_SUB_C
  #define BN_MP_DIV_2_C
  #define BN_MP_MUL_2D_C
  #define BN_MP_MUL_D_C
  #define BN_MP_DIV_3_C
  #define BN_MP_LSHD_C
  #define BN_MP_CLEAR_MULTI_C
 #endif

 #if defined(BN_MP_TOOM_SQR_C)
  #define BN_MP_INIT_MULTI_C
  #define BN_MP_MOD_2D_C
  #define BN_MP_COPY_C
  #define BN_MP_RSHD_C
  #define BN_MP_SQR_C
  #define BN_MP_MUL_2_C
  #define BN_MP_ADD_C
  #define BN_MP_SUB_C
  #define BN_MP_DIV_2_C
  #define BN_MP_MUL_2D_C
  #define BN_MP_MUL_D_C
  #define BN_MP_DIV_3_C
  #define BN_MP_LSHD_C
  #define BN_MP_CLEAR_MULTI_C
 #endif

 #if defined(BN_MP_TORADIX_C)
  #define BN_MP_ISZERO_C
  #define BN_MP_INIT_COPY_C
  #define BN_MP_DIV_D_C
  #define BN_MP_CLEAR_C
  #define BN_MP_S_RMAP_C
 #endif

 #if defined(BN_MP_TORADIX_N_C)
  #define BN_MP_ISZERO_C
  #define BN_MP_INIT_COPY_C
  #define BN_MP_DIV_D_C
  #define BN_MP_CLEAR_C
  #define BN_MP_S_RMAP_C
 #endif

 #if defined(BN_MP_UNSIGNED_BIN_SIZE_C)
  #define BN_MP_COUNT_BITS_C
 #endif

 #if defined(BN_MP_XOR_C)
  #define BN_MP_INIT_COPY_C
  #define BN_MP_CLAMP_C
  #define BN_MP_EXCH_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_MP_ZERO_C)
 #endif

 #if defined(BN_PRIME_TAB_C)
 #endif

 #if defined(BN_REVERSE_C)
 #endif

 #if defined(BN_S_MP_ADD_C)
  #define BN_MP_GROW_C
  #define BN_MP_CLAMP_C
 #endif

 #if defined(BN_S_MP_EXPTMOD_C)
  #define BN_MP_COUNT_BITS_C
  #define BN_MP_INIT_C
  #define BN_MP_CLEAR_C
  #define BN_MP_REDUCE_SETUP_C
  #define BN_MP_REDUCE_C
  #define BN_MP_REDUCE_2K_SETUP_L_C
  #define BN_MP_REDUCE_2K_L_C
  #define BN_MP_MOD_C
  #define BN_MP_COPY_C
  #define BN_MP_SQR_C
  #define BN_MP_MUL_C
  #define BN_MP_SET_C
  #define BN_MP_EXCH_C
 #endif

 #if defined(BN_S_MP_MUL_DIGS_C)
  #define BN_FAST_S_MP_MUL_DIGS_C
  #define BN_MP_INIT_SIZE_C
  #define BN_MP_CLAMP_C
  #define BN_MP_EXCH_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_S_MP_MUL_HIGH_DIGS_C)
  #define BN_FAST_S_MP_MUL_HIGH_DIGS_C
  #define BN_MP_INIT_SIZE_C
  #define BN_MP_CLAMP_C
  #define BN_MP_EXCH_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_S_MP_SQR_C)
  #define BN_MP_INIT_SIZE_C
  #define BN_MP_CLAMP_C
  #define BN_MP_EXCH_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_S_MP_SUB_C)
  #define BN_MP_GROW_C
  #define BN_MP_CLAMP_C
 #endif

 #if defined(BNCORE_C)
 #endif

 #ifdef LTM3
  #define LTM_LAST
 #endif
/* super class file for PK algos */

/* default ... include all MPI */
//#define LTM_ALL

/* RSA only (does not support DH/DSA/ECC) */
/* #define SC_RSA_1 */

/* For reference.... On an Athlon64 optimizing for speed...

   LTM's mpi.o with all functions [striped] is 142KiB in size.

 */

/* Works for RSA only, mpi.o is 68KiB */
#ifdef SC_RSA_1
 #define BN_MP_SHRINK_C
 #define BN_MP_LCM_C
 #define BN_MP_PRIME_RANDOM_EX_C
 #define BN_MP_INVMOD_C
 #define BN_MP_GCD_C
 #define BN_MP_MOD_C
 #define BN_MP_MULMOD_C
 #define BN_MP_ADDMOD_C
 #define BN_MP_EXPTMOD_C
 #define BN_MP_SET_INT_C
 #define BN_MP_INIT_MULTI_C
 #define BN_MP_CLEAR_MULTI_C
 #define BN_MP_UNSIGNED_BIN_SIZE_C
 #define BN_MP_TO_UNSIGNED_BIN_C
 #define BN_MP_MOD_D_C
 #define BN_MP_PRIME_RABIN_MILLER_TRIALS_C
 #define BN_REVERSE_C
 #define BN_PRIME_TAB_C

/* other modifiers */
 #define BN_MP_DIV_SMALL    /* Slower division, not critical */

/* here we are on the last pass so we turn things off.  The functions classes are still there
 * but we remove them specifically from the build.  This also invokes tweaks in functions
 * like removing support for even moduli, etc...
 */
 #ifdef LTM_LAST
  #undef  BN_MP_TOOM_MUL_C
  #undef  BN_MP_TOOM_SQR_C
  #undef  BN_MP_KARATSUBA_MUL_C
  #undef  BN_MP_KARATSUBA_SQR_C
  #undef  BN_MP_REDUCE_C
  #undef  BN_MP_REDUCE_SETUP_C
  #undef  BN_MP_DR_IS_MODULUS_C
  #undef  BN_MP_DR_SETUP_C
  #undef  BN_MP_DR_REDUCE_C
  #undef  BN_MP_REDUCE_IS_2K_C
  #undef  BN_MP_REDUCE_2K_SETUP_C
  #undef  BN_MP_REDUCE_2K_C
  #undef  BN_S_MP_EXPTMOD_C
  #undef  BN_MP_DIV_3_C
  #undef  BN_S_MP_MUL_HIGH_DIGS_C
  #undef  BN_FAST_S_MP_MUL_HIGH_DIGS_C
  #undef  BN_FAST_MP_INVMOD_C

/* To safely undefine these you have to make sure your RSA key won't exceed the Comba threshold
 * which is roughly 255 digits [7140 bits for 32-bit machines, 15300 bits for 64-bit machines]
 * which means roughly speaking you can handle upto 2536-bit RSA keys with these defined without
 * trouble.
 */
  #undef  BN_S_MP_MUL_DIGS_C
  #undef  BN_S_MP_SQR_C
  #undef  BN_MP_MONTGOMERY_REDUCE_C
 #endif
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */ 
#if !(defined(LTM1) && defined(LTM2) && defined(LTM3))
 #if defined(LTM2)
  #define LTM3
 #endif
 #if defined(LTM1)
  #define LTM2
 #endif
 #define LTM1

 #if defined(LTM_ALL)
  #define BN_ERROR_C
  #define BN_FAST_MP_INVMOD_C
  #define BN_FAST_MP_MONTGOMERY_REDUCE_C
  #define BN_FAST_S_MP_MUL_DIGS_C
  #define BN_FAST_S_MP_MUL_HIGH_DIGS_C
  #define BN_FAST_S_MP_SQR_C
  #define BN_MP_2EXPT_C
  #define BN_MP_ABS_C
  #define BN_MP_ADD_C
  #define BN_MP_ADD_D_C
  #define BN_MP_ADDMOD_C
  #define BN_MP_AND_C
  #define BN_MP_CLAMP_C
  #define BN_MP_CLEAR_C
  #define BN_MP_CLEAR_MULTI_C
  #define BN_MP_CMP_C
  #define BN_MP_CMP_D_C
  #define BN_MP_CMP_MAG_C
  #define BN_MP_CNT_LSB_C
  #define BN_MP_COPY_C
  #define BN_MP_COUNT_BITS_C
  #define BN_MP_DIV_C
  #define BN_MP_DIV_2_C
  #define BN_MP_DIV_2D_C
  #define BN_MP_DIV_3_C
  #define BN_MP_DIV_D_C
  #define BN_MP_DR_IS_MODULUS_C
  #define BN_MP_DR_REDUCE_C
  #define BN_MP_DR_SETUP_C
  #define BN_MP_EXCH_C
  #define BN_MP_EXPORT_C
  #define BN_MP_EXPT_D_C
  #define BN_MP_EXPT_D_EX_C
  #define BN_MP_EXPTMOD_C
  #define BN_MP_EXPTMOD_FAST_C
  #define BN_MP_EXTEUCLID_C
  #define BN_MP_FREAD_C
  #define BN_MP_FWRITE_C
  #define BN_MP_GCD_C
  #define BN_MP_GET_INT_C
  #define BN_MP_GET_LONG_C
  #define BN_MP_GET_LONG_LONG_C
  #define BN_MP_GROW_C
  #define BN_MP_IMPORT_C
  #define BN_MP_INIT_C
  #define BN_MP_INIT_COPY_C
  #define BN_MP_INIT_MULTI_C
  #define BN_MP_INIT_SET_C
  #define BN_MP_INIT_SET_INT_C
  #define BN_MP_INIT_SIZE_C
  #define BN_MP_INVMOD_C
  #define BN_MP_INVMOD_SLOW_C
  #define BN_MP_IS_SQUARE_C
  #define BN_MP_JACOBI_C
  #define BN_MP_KARATSUBA_MUL_C
  #define BN_MP_KARATSUBA_SQR_C
  #define BN_MP_LCM_C
  #define BN_MP_LSHD_C
  #define BN_MP_MOD_C
  #define BN_MP_MOD_2D_C
  #define BN_MP_MOD_D_C
  #define BN_MP_MONTGOMERY_CALC_NORMALIZATION_C
  #define BN_MP_MONTGOMERY_REDUCE_C
  #define BN_MP_MONTGOMERY_SETUP_C
  #define BN_MP_MUL_C
  #define BN_MP_MUL_2_C
  #define BN_MP_MUL_2D_C
  #define BN_MP_MUL_D_C
  #define BN_MP_MULMOD_C
  #define BN_MP_N_ROOT_C
  #define BN_MP_N_ROOT_EX_C
  #define BN_MP_NEG_C
  #define BN_MP_OR_C
  #define BN_MP_PRIME_FERMAT_C
  #define BN_MP_PRIME_IS_DIVISIBLE_C
  #define BN_MP_PRIME_IS_PRIME_C
  #define BN_MP_PRIME_MILLER_RABIN_C
  #define BN_MP_PRIME_NEXT_PRIME_C
  #define BN_MP_PRIME_RABIN_MILLER_TRIALS_C
  #define BN_MP_PRIME_RANDOM_EX_C
  #define BN_MP_RADIX_SIZE_C
  #define BN_MP_RADIX_SMAP_C
  #define BN_MP_RAND_C
  #define BN_MP_READ_RADIX_C
  #define BN_MP_READ_SIGNED_BIN_C
  #define BN_MP_READ_UNSIGNED_BIN_C
  #define BN_MP_REDUCE_C
  #define BN_MP_REDUCE_2K_C
  #define BN_MP_REDUCE_2K_L_C
  #define BN_MP_REDUCE_2K_SETUP_C
  #define BN_MP_REDUCE_2K_SETUP_L_C
  #define BN_MP_REDUCE_IS_2K_C
  #define BN_MP_REDUCE_IS_2K_L_C
  #define BN_MP_REDUCE_SETUP_C
  #define BN_MP_RSHD_C
  #define BN_MP_SET_C
  #define BN_MP_SET_INT_C
  #define BN_MP_SET_LONG_C
  #define BN_MP_SET_LONG_LONG_C
  #define BN_MP_SHRINK_C
  #define BN_MP_SIGNED_BIN_SIZE_C
  #define BN_MP_SQR_C
  #define BN_MP_SQRMOD_C
  #define BN_MP_SQRT_C
  #define BN_MP_SQRTMOD_PRIME_C
  #define BN_MP_SUB_C
  #define BN_MP_SUB_D_C
  #define BN_MP_SUBMOD_C
  #define BN_MP_TO_SIGNED_BIN_C
  #define BN_MP_TO_SIGNED_BIN_N_C
  #define BN_MP_TO_UNSIGNED_BIN_C
  #define BN_MP_TO_UNSIGNED_BIN_N_C
  #define BN_MP_TOOM_MUL_C
  #define BN_MP_TOOM_SQR_C
  #define BN_MP_TORADIX_C
  #define BN_MP_TORADIX_N_C
  #define BN_MP_UNSIGNED_BIN_SIZE_C
  #define BN_MP_XOR_C
  #define BN_MP_ZERO_C
  #define BN_PRIME_TAB_C
  #define BN_REVERSE_C
  #define BN_S_MP_ADD_C
  #define BN_S_MP_EXPTMOD_C
  #define BN_S_MP_MUL_DIGS_C
  #define BN_S_MP_MUL_HIGH_DIGS_C
  #define BN_S_MP_SQR_C
  #define BN_S_MP_SUB_C
  #define BNCORE_C
 #endif
//#ifndef BN_MP_EXPTMOD_FAST_C
//#define BN_MP_EXPTMOD_FAST_C
//#endif
 #if defined(BN_ERROR_C)
  #define BN_MP_ERROR_TO_STRING_C
 #endif

 #if defined(BN_FAST_MP_INVMOD_C)
  #define BN_MP_ISEVEN_C
  #define BN_MP_INIT_MULTI_C
  #define BN_MP_COPY_C
  #define BN_MP_MOD_C
  #define BN_MP_SET_C
  #define BN_MP_DIV_2_C
  #define BN_MP_ISODD_C
  #define BN_MP_SUB_C
  #define BN_MP_CMP_C
  #define BN_MP_ISZERO_C
  #define BN_MP_CMP_D_C
  #define BN_MP_ADD_C
  #define BN_MP_EXCH_C
  #define BN_MP_CLEAR_MULTI_C
 #endif

 #if defined(BN_FAST_MP_MONTGOMERY_REDUCE_C)
  #define BN_MP_GROW_C
  #define BN_MP_RSHD_C
  #define BN_MP_CLAMP_C
  #define BN_MP_CMP_MAG_C
  #define BN_S_MP_SUB_C
 #endif

 #if defined(BN_FAST_S_MP_MUL_DIGS_C)
  #define BN_MP_GROW_C
  #define BN_MP_CLAMP_C
 #endif

 #if defined(BN_FAST_S_MP_MUL_HIGH_DIGS_C)
  #define BN_MP_GROW_C
  #define BN_MP_CLAMP_C
 #endif

 #if defined(BN_FAST_S_MP_SQR_C)
  #define BN_MP_GROW_C
  #define BN_MP_CLAMP_C
 #endif

 #if defined(BN_MP_2EXPT_C)
  #define BN_MP_ZERO_C
  #define BN_MP_GROW_C
 #endif

 #if defined(BN_MP_ABS_C)
  #define BN_MP_COPY_C
 #endif

 #if defined(BN_MP_ADD_C)
  #define BN_S_MP_ADD_C
  #define BN_MP_CMP_MAG_C
  #define BN_S_MP_SUB_C
 #endif

 #if defined(BN_MP_ADD_D_C)
  #define BN_MP_GROW_C
  #define BN_MP_SUB_D_C
  #define BN_MP_CLAMP_C
 #endif

 #if defined(BN_MP_ADDMOD_C)
  #define BN_MP_INIT_C
  #define BN_MP_ADD_C
  #define BN_MP_CLEAR_C
  #define BN_MP_MOD_C
 #endif

 #if defined(BN_MP_AND_C)
  #define BN_MP_INIT_COPY_C
  #define BN_MP_CLAMP_C
  #define BN_MP_EXCH_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_MP_CLAMP_C)
 #endif

 #if defined(BN_MP_CLEAR_C)
 #endif

 #if defined(BN_MP_CLEAR_MULTI_C)
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_MP_CMP_C)
  #define BN_MP_CMP_MAG_C
 #endif

 #if defined(BN_MP_CMP_D_C)
 #endif

 #if defined(BN_MP_CMP_MAG_C)
 #endif

 #if defined(BN_MP_CNT_LSB_C)
  #define BN_MP_ISZERO_C
 #endif

 #if defined(BN_MP_COPY_C)
  #define BN_MP_GROW_C
 #endif

 #if defined(BN_MP_COUNT_BITS_C)
 #endif

 #if defined(BN_MP_DIV_C)
  #define BN_MP_ISZERO_C
  #define BN_MP_CMP_MAG_C
  #define BN_MP_COPY_C
  #define BN_MP_ZERO_C
  #define BN_MP_INIT_MULTI_C
  #define BN_MP_SET_C
  #define BN_MP_COUNT_BITS_C
  #define BN_MP_ABS_C
  #define BN_MP_MUL_2D_C
  #define BN_MP_CMP_C
  #define BN_MP_SUB_C
  #define BN_MP_ADD_C
  #define BN_MP_DIV_2D_C
  #define BN_MP_EXCH_C
  #define BN_MP_CLEAR_MULTI_C
  #define BN_MP_INIT_SIZE_C
  #define BN_MP_INIT_C
  #define BN_MP_INIT_COPY_C
  #define BN_MP_LSHD_C
  #define BN_MP_RSHD_C
  #define BN_MP_MUL_D_C
  #define BN_MP_CLAMP_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_MP_DIV_2_C)
  #define BN_MP_GROW_C
  #define BN_MP_CLAMP_C
 #endif

 #if defined(BN_MP_DIV_2D_C)
  #define BN_MP_COPY_C
  #define BN_MP_ZERO_C
  #define BN_MP_INIT_C
  #define BN_MP_MOD_2D_C
  #define BN_MP_CLEAR_C
  #define BN_MP_RSHD_C
  #define BN_MP_CLAMP_C
  #define BN_MP_EXCH_C
 #endif

 #if defined(BN_MP_DIV_3_C)
  #define BN_MP_INIT_SIZE_C
  #define BN_MP_CLAMP_C
  #define BN_MP_EXCH_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_MP_DIV_D_C)
  #define BN_MP_ISZERO_C
  #define BN_MP_COPY_C
  #define BN_MP_DIV_2D_C
  #define BN_MP_DIV_3_C
  #define BN_MP_INIT_SIZE_C
  #define BN_MP_CLAMP_C
  #define BN_MP_EXCH_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_MP_DR_IS_MODULUS_C)
 #endif

 #if defined(BN_MP_DR_REDUCE_C)
  #define BN_MP_GROW_C
  #define BN_MP_CLAMP_C
  #define BN_MP_CMP_MAG_C
  #define BN_S_MP_SUB_C
 #endif

 #if defined(BN_MP_DR_SETUP_C)
 #endif

 #if defined(BN_MP_EXCH_C)
 #endif

 #if defined(BN_MP_EXPORT_C)
  #define BN_MP_INIT_COPY_C
  #define BN_MP_COUNT_BITS_C
  #define BN_MP_DIV_2D_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_MP_EXPT_D_C)
  #define BN_MP_EXPT_D_EX_C
 #endif

 #if defined(BN_MP_EXPT_D_EX_C)
  #define BN_MP_INIT_COPY_C
  #define BN_MP_SET_C
  #define BN_MP_MUL_C
  #define BN_MP_CLEAR_C
  #define BN_MP_SQR_C
 #endif

 #if defined(BN_MP_EXPTMOD_C)
  #define BN_MP_INIT_C
  #define BN_MP_INVMOD_C
  #define BN_MP_CLEAR_C
  #define BN_MP_ABS_C
  #define BN_MP_CLEAR_MULTI_C
  #define BN_MP_REDUCE_IS_2K_L_C
  #define BN_S_MP_EXPTMOD_C
  #define BN_MP_DR_IS_MODULUS_C
  #define BN_MP_REDUCE_IS_2K_C
  #define BN_MP_ISODD_C
  #define BN_MP_EXPTMOD_FAST_C
 #endif

 #if defined(BN_MP_EXPTMOD_FAST_C)
  #define BN_MP_COUNT_BITS_C
  #define BN_MP_INIT_C
  #define BN_MP_CLEAR_C
  #define BN_MP_MONTGOMERY_SETUP_C
  #define BN_FAST_MP_MONTGOMERY_REDUCE_C
  #define BN_MP_MONTGOMERY_REDUCE_C
  #define BN_MP_DR_SETUP_C
  #define BN_MP_DR_REDUCE_C
  #define BN_MP_REDUCE_2K_SETUP_C
  #define BN_MP_REDUCE_2K_C
  #define BN_MP_MONTGOMERY_CALC_NORMALIZATION_C
  #define BN_MP_MULMOD_C
  #define BN_MP_SET_C
  #define BN_MP_MOD_C
  #define BN_MP_COPY_C
  #define BN_MP_SQR_C
  #define BN_MP_MUL_C
  #define BN_MP_EXCH_C
 #endif

 #if defined(BN_MP_EXTEUCLID_C)
  #define BN_MP_INIT_MULTI_C
  #define BN_MP_SET_C
  #define BN_MP_COPY_C
  #define BN_MP_ISZERO_C
  #define BN_MP_DIV_C
  #define BN_MP_MUL_C
  #define BN_MP_SUB_C
  #define BN_MP_NEG_C
  #define BN_MP_EXCH_C
  #define BN_MP_CLEAR_MULTI_C
 #endif

 #if defined(BN_MP_FREAD_C)
  #define BN_MP_ZERO_C
  #define BN_MP_S_RMAP_C
  #define BN_MP_MUL_D_C
  #define BN_MP_ADD_D_C
  #define BN_MP_CMP_D_C
 #endif

 #if defined(BN_MP_FWRITE_C)
  #define BN_MP_RADIX_SIZE_C
  #define BN_MP_TORADIX_C
 #endif

 #if defined(BN_MP_GCD_C)
  #define BN_MP_ISZERO_C
  #define BN_MP_ABS_C
  #define BN_MP_INIT_COPY_C
  #define BN_MP_CNT_LSB_C
  #define BN_MP_DIV_2D_C
  #define BN_MP_CMP_MAG_C
  #define BN_MP_EXCH_C
  #define BN_S_MP_SUB_C
  #define BN_MP_MUL_2D_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_MP_GET_INT_C)
 #endif

 #if defined(BN_MP_GET_LONG_C)
 #endif

 #if defined(BN_MP_GET_LONG_LONG_C)
 #endif

 #if defined(BN_MP_GROW_C)
 #endif

 #if defined(BN_MP_IMPORT_C)
  #define BN_MP_ZERO_C
  #define BN_MP_MUL_2D_C
  #define BN_MP_CLAMP_C
 #endif

 #if defined(BN_MP_INIT_C)
 #endif

 #if defined(BN_MP_INIT_COPY_C)
  #define BN_MP_INIT_SIZE_C
  #define BN_MP_COPY_C
 #endif

 #if defined(BN_MP_INIT_MULTI_C)
  #define BN_MP_ERR_C
  #define BN_MP_INIT_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_MP_INIT_SET_C)
  #define BN_MP_INIT_C
  #define BN_MP_SET_C
 #endif

 #if defined(BN_MP_INIT_SET_INT_C)
  #define BN_MP_INIT_C
  #define BN_MP_SET_INT_C
 #endif

 #if defined(BN_MP_INIT_SIZE_C)
  #define BN_MP_INIT_C
 #endif

 #if defined(BN_MP_INVMOD_C)
  #define BN_MP_ISZERO_C
  #define BN_MP_ISODD_C
  #define BN_FAST_MP_INVMOD_C
  #define BN_MP_INVMOD_SLOW_C
 #endif

 #if defined(BN_MP_INVMOD_SLOW_C)
  #define BN_MP_ISZERO_C
  #define BN_MP_INIT_MULTI_C
  #define BN_MP_MOD_C
  #define BN_MP_COPY_C
  #define BN_MP_ISEVEN_C
  #define BN_MP_SET_C
  #define BN_MP_DIV_2_C
  #define BN_MP_ISODD_C
  #define BN_MP_ADD_C
  #define BN_MP_SUB_C
  #define BN_MP_CMP_C
  #define BN_MP_CMP_D_C
  #define BN_MP_CMP_MAG_C
  #define BN_MP_EXCH_C
  #define BN_MP_CLEAR_MULTI_C
 #endif

 #if defined(BN_MP_IS_SQUARE_C)
  #define BN_MP_MOD_D_C
  #define BN_MP_INIT_SET_INT_C
  #define BN_MP_MOD_C
  #define BN_MP_GET_INT_C
  #define BN_MP_SQRT_C
  #define BN_MP_SQR_C
  #define BN_MP_CMP_MAG_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_MP_JACOBI_C)
  #define BN_MP_CMP_D_C
  #define BN_MP_ISZERO_C
  #define BN_MP_INIT_COPY_C
  #define BN_MP_CNT_LSB_C
  #define BN_MP_DIV_2D_C
  #define BN_MP_MOD_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_MP_KARATSUBA_MUL_C)
  #define BN_MP_MUL_C
  #define BN_MP_INIT_SIZE_C
  #define BN_MP_CLAMP_C
  #define BN_S_MP_ADD_C
  #define BN_MP_ADD_C
  #define BN_S_MP_SUB_C
  #define BN_MP_LSHD_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_MP_KARATSUBA_SQR_C)
  #define BN_MP_INIT_SIZE_C
  #define BN_MP_CLAMP_C
  #define BN_MP_SQR_C
  #define BN_S_MP_ADD_C
  #define BN_S_MP_SUB_C
  #define BN_MP_LSHD_C
  #define BN_MP_ADD_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_MP_LCM_C)
  #define BN_MP_INIT_MULTI_C
  #define BN_MP_GCD_C
  #define BN_MP_CMP_MAG_C
  #define BN_MP_DIV_C
  #define BN_MP_MUL_C
  #define BN_MP_CLEAR_MULTI_C
 #endif

 #if defined(BN_MP_LSHD_C)
  #define BN_MP_GROW_C
  #define BN_MP_RSHD_C
 #endif

 #if defined(BN_MP_MOD_C)
  #define BN_MP_INIT_C
  #define BN_MP_DIV_C
  #define BN_MP_CLEAR_C
  #define BN_MP_ISZERO_C
  #define BN_MP_EXCH_C
  #define BN_MP_ADD_C
 #endif

 #if defined(BN_MP_MOD_2D_C)
  #define BN_MP_ZERO_C
  #define BN_MP_COPY_C
  #define BN_MP_CLAMP_C
 #endif

 #if defined(BN_MP_MOD_D_C)
  #define BN_MP_DIV_D_C
 #endif

 #if defined(BN_MP_MONTGOMERY_CALC_NORMALIZATION_C)
  #define BN_MP_COUNT_BITS_C
  #define BN_MP_2EXPT_C
  #define BN_MP_SET_C
  #define BN_MP_MUL_2_C
  #define BN_MP_CMP_MAG_C
  #define BN_S_MP_SUB_C
 #endif

 #if defined(BN_MP_MONTGOMERY_REDUCE_C)
  #define BN_FAST_MP_MONTGOMERY_REDUCE_C
  #define BN_MP_GROW_C
  #define BN_MP_CLAMP_C
  #define BN_MP_RSHD_C
  #define BN_MP_CMP_MAG_C
  #define BN_S_MP_SUB_C
 #endif

 #if defined(BN_MP_MONTGOMERY_SETUP_C)
 #endif

 #if defined(BN_MP_MUL_C)
  #define BN_MP_TOOM_MUL_C
  #define BN_MP_KARATSUBA_MUL_C
  #define BN_FAST_S_MP_MUL_DIGS_C
  #define BN_S_MP_MUL_C
  #define BN_S_MP_MUL_DIGS_C
 #endif

 #if defined(BN_MP_MUL_2_C)
  #define BN_MP_GROW_C
 #endif

 #if defined(BN_MP_MUL_2D_C)
  #define BN_MP_COPY_C
  #define BN_MP_GROW_C
  #define BN_MP_LSHD_C
  #define BN_MP_CLAMP_C
 #endif

 #if defined(BN_MP_MUL_D_C)
  #define BN_MP_GROW_C
  #define BN_MP_CLAMP_C
 #endif

 #if defined(BN_MP_MULMOD_C)
  #define BN_MP_INIT_C
  #define BN_MP_MUL_C
  #define BN_MP_CLEAR_C
  #define BN_MP_MOD_C
 #endif

 #if defined(BN_MP_N_ROOT_C)
  #define BN_MP_N_ROOT_EX_C
 #endif

 #if defined(BN_MP_N_ROOT_EX_C)
  #define BN_MP_INIT_C
  #define BN_MP_SET_C
  #define BN_MP_COPY_C
  #define BN_MP_EXPT_D_EX_C
  #define BN_MP_MUL_C
  #define BN_MP_SUB_C
  #define BN_MP_MUL_D_C
  #define BN_MP_DIV_C
  #define BN_MP_CMP_C
  #define BN_MP_SUB_D_C
  #define BN_MP_EXCH_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_MP_NEG_C)
  #define BN_MP_COPY_C
  #define BN_MP_ISZERO_C
 #endif

 #if defined(BN_MP_OR_C)
  #define BN_MP_INIT_COPY_C
  #define BN_MP_CLAMP_C
  #define BN_MP_EXCH_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_MP_PRIME_FERMAT_C)
  #define BN_MP_CMP_D_C
  #define BN_MP_INIT_C
  #define BN_MP_EXPTMOD_C
  #define BN_MP_CMP_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_MP_PRIME_IS_DIVISIBLE_C)
  #define BN_MP_MOD_D_C
 #endif

 #if defined(BN_MP_PRIME_IS_PRIME_C)
  #define BN_MP_CMP_D_C
  #define BN_MP_PRIME_IS_DIVISIBLE_C
  #define BN_MP_INIT_C
  #define BN_MP_SET_C
  #define BN_MP_PRIME_MILLER_RABIN_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_MP_PRIME_MILLER_RABIN_C)
  #define BN_MP_CMP_D_C
  #define BN_MP_INIT_COPY_C
  #define BN_MP_SUB_D_C
  #define BN_MP_CNT_LSB_C
  #define BN_MP_DIV_2D_C
  #define BN_MP_EXPTMOD_C
  #define BN_MP_CMP_C
  #define BN_MP_SQRMOD_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_MP_PRIME_NEXT_PRIME_C)
  #define BN_MP_CMP_D_C
  #define BN_MP_SET_C
  #define BN_MP_SUB_D_C
  #define BN_MP_ISEVEN_C
  #define BN_MP_MOD_D_C
  #define BN_MP_INIT_C
  #define BN_MP_ADD_D_C
  #define BN_MP_PRIME_MILLER_RABIN_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_MP_PRIME_RABIN_MILLER_TRIALS_C)
 #endif

 #if defined(BN_MP_PRIME_RANDOM_EX_C)
  #define BN_MP_READ_UNSIGNED_BIN_C
  #define BN_MP_PRIME_IS_PRIME_C
  #define BN_MP_SUB_D_C
  #define BN_MP_DIV_2_C
  #define BN_MP_MUL_2_C
  #define BN_MP_ADD_D_C
 #endif

 #if defined(BN_MP_RADIX_SIZE_C)
  #define BN_MP_ISZERO_C
  #define BN_MP_COUNT_BITS_C
  #define BN_MP_INIT_COPY_C
  #define BN_MP_DIV_D_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_MP_RADIX_SMAP_C)
  #define BN_MP_S_RMAP_C
 #endif

 #if defined(BN_MP_RAND_C)
  #define BN_MP_ZERO_C
  #define BN_MP_ADD_D_C
  #define BN_MP_LSHD_C
 #endif

 #if defined(BN_MP_READ_RADIX_C)
  #define BN_MP_ZERO_C
  #define BN_MP_S_RMAP_C
  #define BN_MP_MUL_D_C
  #define BN_MP_ADD_D_C
  #define BN_MP_ISZERO_C
 #endif

 #if defined(BN_MP_READ_SIGNED_BIN_C)
  #define BN_MP_READ_UNSIGNED_BIN_C
 #endif

 #if defined(BN_MP_READ_UNSIGNED_BIN_C)
  #define BN_MP_GROW_C
  #define BN_MP_ZERO_C
  #define BN_MP_MUL_2D_C
  #define BN_MP_CLAMP_C
 #endif

 #if defined(BN_MP_REDUCE_C)
  #define BN_MP_REDUCE_SETUP_C
  #define BN_MP_INIT_COPY_C
  #define BN_MP_RSHD_C
  #define BN_MP_MUL_C
  #define BN_S_MP_MUL_HIGH_DIGS_C
  #define BN_FAST_S_MP_MUL_HIGH_DIGS_C
  #define BN_MP_MOD_2D_C
  #define BN_S_MP_MUL_DIGS_C
  #define BN_MP_SUB_C
  #define BN_MP_CMP_D_C
  #define BN_MP_SET_C
  #define BN_MP_LSHD_C
  #define BN_MP_ADD_C
  #define BN_MP_CMP_C
  #define BN_S_MP_SUB_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_MP_REDUCE_2K_C)
  #define BN_MP_INIT_C
  #define BN_MP_COUNT_BITS_C
  #define BN_MP_DIV_2D_C
  #define BN_MP_MUL_D_C
  #define BN_S_MP_ADD_C
  #define BN_MP_CMP_MAG_C
  #define BN_S_MP_SUB_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_MP_REDUCE_2K_L_C)
  #define BN_MP_INIT_C
  #define BN_MP_COUNT_BITS_C
  #define BN_MP_DIV_2D_C
  #define BN_MP_MUL_C
  #define BN_S_MP_ADD_C
  #define BN_MP_CMP_MAG_C
  #define BN_S_MP_SUB_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_MP_REDUCE_2K_SETUP_C)
  #define BN_MP_INIT_C
  #define BN_MP_COUNT_BITS_C
  #define BN_MP_2EXPT_C
  #define BN_MP_CLEAR_C
  #define BN_S_MP_SUB_C
 #endif

 #if defined(BN_MP_REDUCE_2K_SETUP_L_C)
  #define BN_MP_INIT_C
  #define BN_MP_2EXPT_C
  #define BN_MP_COUNT_BITS_C
  #define BN_S_MP_SUB_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_MP_REDUCE_IS_2K_C)
  #define BN_MP_REDUCE_2K_C
  #define BN_MP_COUNT_BITS_C
 #endif

 #if defined(BN_MP_REDUCE_IS_2K_L_C)
 #endif

 #if defined(BN_MP_REDUCE_SETUP_C)
  #define BN_MP_2EXPT_C
  #define BN_MP_DIV_C
 #endif

 #if defined(BN_MP_RSHD_C)
  #define BN_MP_ZERO_C
 #endif

 #if defined(BN_MP_SET_C)
  #define BN_MP_ZERO_C
 #endif

 #if defined(BN_MP_SET_INT_C)
  #define BN_MP_ZERO_C
  #define BN_MP_MUL_2D_C
  #define BN_MP_CLAMP_C
 #endif

 #if defined(BN_MP_SET_LONG_C)
 #endif

 #if defined(BN_MP_SET_LONG_LONG_C)
 #endif

 #if defined(BN_MP_SHRINK_C)
 #endif

 #if defined(BN_MP_SIGNED_BIN_SIZE_C)
  #define BN_MP_UNSIGNED_BIN_SIZE_C
 #endif

 #if defined(BN_MP_SQR_C)
  #define BN_MP_TOOM_SQR_C
  #define BN_MP_KARATSUBA_SQR_C
  #define BN_FAST_S_MP_SQR_C
  #define BN_S_MP_SQR_C
 #endif

 #if defined(BN_MP_SQRMOD_C)
  #define BN_MP_INIT_C
  #define BN_MP_SQR_C
  #define BN_MP_CLEAR_C
  #define BN_MP_MOD_C
 #endif

 #if defined(BN_MP_SQRT_C)
  #define BN_MP_N_ROOT_C
  #define BN_MP_ISZERO_C
  #define BN_MP_ZERO_C
  #define BN_MP_INIT_COPY_C
  #define BN_MP_RSHD_C
  #define BN_MP_DIV_C
  #define BN_MP_ADD_C
  #define BN_MP_DIV_2_C
  #define BN_MP_CMP_MAG_C
  #define BN_MP_EXCH_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_MP_SQRTMOD_PRIME_C)
  #define BN_MP_CMP_D_C
  #define BN_MP_ZERO_C
  #define BN_MP_JACOBI_C
  #define BN_MP_INIT_MULTI_C
  #define BN_MP_MOD_D_C
  #define BN_MP_ADD_D_C
  #define BN_MP_DIV_2_C
  #define BN_MP_EXPTMOD_C
  #define BN_MP_COPY_C
  #define BN_MP_SUB_D_C
  #define BN_MP_ISEVEN_C
  #define BN_MP_SET_INT_C
  #define BN_MP_SQRMOD_C
  #define BN_MP_MULMOD_C
  #define BN_MP_SET_C
  #define BN_MP_CLEAR_MULTI_C
 #endif

 #if defined(BN_MP_SUB_C)
  #define BN_S_MP_ADD_C
  #define BN_MP_CMP_MAG_C
  #define BN_S_MP_SUB_C
 #endif

 #if defined(BN_MP_SUB_D_C)
  #define BN_MP_GROW_C
  #define BN_MP_ADD_D_C
  #define BN_MP_CLAMP_C
 #endif

 #if defined(BN_MP_SUBMOD_C)
  #define BN_MP_INIT_C
  #define BN_MP_SUB_C
  #define BN_MP_CLEAR_C
  #define BN_MP_MOD_C
 #endif

 #if defined(BN_MP_TO_SIGNED_BIN_C)
  #define BN_MP_TO_UNSIGNED_BIN_C
 #endif

 #if defined(BN_MP_TO_SIGNED_BIN_N_C)
  #define BN_MP_SIGNED_BIN_SIZE_C
  #define BN_MP_TO_SIGNED_BIN_C
 #endif

 #if defined(BN_MP_TO_UNSIGNED_BIN_C)
  #define BN_MP_INIT_COPY_C
  #define BN_MP_ISZERO_C
  #define BN_MP_DIV_2D_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_MP_TO_UNSIGNED_BIN_N_C)
  #define BN_MP_UNSIGNED_BIN_SIZE_C
  #define BN_MP_TO_UNSIGNED_BIN_C
 #endif

 #if defined(BN_MP_TOOM_MUL_C)
  #define BN_MP_INIT_MULTI_C
  #define BN_MP_MOD_2D_C
  #define BN_MP_COPY_C
  #define BN_MP_RSHD_C
  #define BN_MP_MUL_C
  #define BN_MP_MUL_2_C
  #define BN_MP_ADD_C
  #define BN_MP_SUB_C
  #define BN_MP_DIV_2_C
  #define BN_MP_MUL_2D_C
  #define BN_MP_MUL_D_C
  #define BN_MP_DIV_3_C
  #define BN_MP_LSHD_C
  #define BN_MP_CLEAR_MULTI_C
 #endif

 #if defined(BN_MP_TOOM_SQR_C)
  #define BN_MP_INIT_MULTI_C
  #define BN_MP_MOD_2D_C
  #define BN_MP_COPY_C
  #define BN_MP_RSHD_C
  #define BN_MP_SQR_C
  #define BN_MP_MUL_2_C
  #define BN_MP_ADD_C
  #define BN_MP_SUB_C
  #define BN_MP_DIV_2_C
  #define BN_MP_MUL_2D_C
  #define BN_MP_MUL_D_C
  #define BN_MP_DIV_3_C
  #define BN_MP_LSHD_C
  #define BN_MP_CLEAR_MULTI_C
 #endif

 #if defined(BN_MP_TORADIX_C)
  #define BN_MP_ISZERO_C
  #define BN_MP_INIT_COPY_C
  #define BN_MP_DIV_D_C
  #define BN_MP_CLEAR_C
  #define BN_MP_S_RMAP_C
 #endif

 #if defined(BN_MP_TORADIX_N_C)
  #define BN_MP_ISZERO_C
  #define BN_MP_INIT_COPY_C
  #define BN_MP_DIV_D_C
  #define BN_MP_CLEAR_C
  #define BN_MP_S_RMAP_C
 #endif

 #if defined(BN_MP_UNSIGNED_BIN_SIZE_C)
  #define BN_MP_COUNT_BITS_C
 #endif

 #if defined(BN_MP_XOR_C)
  #define BN_MP_INIT_COPY_C
  #define BN_MP_CLAMP_C
  #define BN_MP_EXCH_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_MP_ZERO_C)
 #endif

 #if defined(BN_PRIME_TAB_C)
 #endif

 #if defined(BN_REVERSE_C)
 #endif

 #if defined(BN_S_MP_ADD_C)
  #define BN_MP_GROW_C
  #define BN_MP_CLAMP_C
 #endif

 #if defined(BN_S_MP_EXPTMOD_C)
  #define BN_MP_COUNT_BITS_C
  #define BN_MP_INIT_C
  #define BN_MP_CLEAR_C
  #define BN_MP_REDUCE_SETUP_C
  #define BN_MP_REDUCE_C
  #define BN_MP_REDUCE_2K_SETUP_L_C
  #define BN_MP_REDUCE_2K_L_C
  #define BN_MP_MOD_C
  #define BN_MP_COPY_C
  #define BN_MP_SQR_C
  #define BN_MP_MUL_C
  #define BN_MP_SET_C
  #define BN_MP_EXCH_C
 #endif

 #if defined(BN_S_MP_MUL_DIGS_C)
  #define BN_FAST_S_MP_MUL_DIGS_C
  #define BN_MP_INIT_SIZE_C
  #define BN_MP_CLAMP_C
  #define BN_MP_EXCH_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_S_MP_MUL_HIGH_DIGS_C)
  #define BN_FAST_S_MP_MUL_HIGH_DIGS_C
  #define BN_MP_INIT_SIZE_C
  #define BN_MP_CLAMP_C
  #define BN_MP_EXCH_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_S_MP_SQR_C)
  #define BN_MP_INIT_SIZE_C
  #define BN_MP_CLAMP_C
  #define BN_MP_EXCH_C
  #define BN_MP_CLEAR_C
 #endif

 #if defined(BN_S_MP_SUB_C)
  #define BN_MP_GROW_C
  #define BN_MP_CLAMP_C
 #endif

 #if defined(BNCORE_C)
 #endif

 #ifdef LTM3
  #define LTM_LAST
 #endif
#else
 #define LTM_LAST
#endif 
#else
 #define LTM_LAST
#endif 

#ifdef __cplusplus
extern "C" {
#endif

/* detect 64-bit mode if possible */
#if defined(__x86_64__)
 #if !(defined(MP_32BIT) || defined(MP_16BIT) || defined(MP_8BIT))
  #define MP_64BIT
 #endif
#endif

/* some default configurations.
 *
 * A "mp_digit" must be able to hold DIGIT_BIT + 1 bits
 * A "mp_word" must be able to hold 2*DIGIT_BIT + 1 bits
 *
 * At the very least a mp_digit must be able to hold 7 bits
 * [any size beyond that is ok provided it doesn't overflow the data type]
 */
#ifdef MP_8BIT
typedef uint8_t    mp_digit;
typedef uint16_t   mp_word;
 #define MP_SIZEOF_MP_DIGIT    1
 #ifdef DIGIT_BIT
  #error You must not define DIGIT_BIT when using MP_8BIT
 #endif
#elif defined(MP_16BIT)
typedef uint16_t   mp_digit;
typedef uint32_t   mp_word;
 #define MP_SIZEOF_MP_DIGIT    2
 #ifdef DIGIT_BIT
  #error You must not define DIGIT_BIT when using MP_16BIT
 #endif
#elif defined(MP_64BIT)
/* for GCC only on supported platforms */
 #ifndef CRYPT
typedef unsigned long long   ulong64;
typedef signed long long     long64;
 #endif

typedef uint64_t             mp_digit;
 #if defined(_WIN32)
typedef unsigned __int128    mp_word;
 #elif defined(__GNUC__)
typedef unsigned long        mp_word __attribute__ ((mode(TI)));
 #else

/* it seems you have a problem
 * but we assume you can somewhere define your own uint128_t */
typedef uint128_t            mp_word;
 #endif

 #define DIGIT_BIT    60
#else
/* this is the default case, 28-bit digits */

/* this is to make porting into LibTomCrypt easier :-) */
 #ifndef CRYPT
typedef unsigned long long   ulong64;
typedef signed long long     long64;
 #endif

typedef uint32_t             mp_digit;
typedef uint64_t             mp_word;

 #ifdef MP_31BIT
/* this is an extension that uses 31-bit digits */
  #define DIGIT_BIT    31
 #else
/* default case is 28-bit digits, defines MP_28BIT as a handy macro to test */
  #define DIGIT_BIT    28
  #define MP_28BIT
 #endif
#endif

/* otherwise the bits per digit is calculated automatically from the size of a mp_digit */
#ifndef DIGIT_BIT
 #define DIGIT_BIT    (((CHAR_BIT * MP_SIZEOF_MP_DIGIT) - 1))     /* bits per digit */
typedef uint_least32_t   mp_min_u32;
#else
typedef mp_digit         mp_min_u32;
#endif

/* platforms that can use a better rand function */
#if defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__NetBSD__) || defined(__DragonFly__)
 #define MP_USE_ALT_RAND    1
#endif

/* use arc4random on platforms that support it */
#ifdef MP_USE_ALT_RAND
 #define MP_GEN_RANDOM()    arc4random()
#else
 #define MP_GEN_RANDOM()    rand()
#endif

#define MP_DIGIT_BIT         DIGIT_BIT
#define MP_MASK              ((((mp_digit)1) << ((mp_digit)DIGIT_BIT)) - ((mp_digit)1))
#define MP_DIGIT_MAX         MP_MASK

/* equalities */
#define MP_LT                -1 /* less than */
#define MP_EQ                0  /* equal to */
#define MP_GT                1  /* greater than */

#define MP_ZPOS              0  /* positive integer */
#define MP_NEG               1  /* negative */

#define MP_OKAY              0  /* ok result */
#define MP_MEM               -2 /* out of mem */
#define MP_VAL               -3 /* invalid input */
#define MP_RANGE             MP_VAL

#define MP_YES               1 /* yes response */
#define MP_NO                0 /* no response */

/* Primality generation flags */
#define LTM_PRIME_BBS        0x0001 /* BBS style prime */
#define LTM_PRIME_SAFE       0x0002 /* Safe prime (p-1)/2 == prime */
#define LTM_PRIME_2MSB_ON    0x0008 /* force 2nd MSB to 1 */

typedef int   mp_err;

/* you'll have to tune these... */
extern int KARATSUBA_MUL_CUTOFF,
           KARATSUBA_SQR_CUTOFF,
           TOOM_MUL_CUTOFF,
           TOOM_SQR_CUTOFF;

/* define this to use lower memory usage routines (exptmods mostly) */
/* #define MP_LOW_MEM */

/* default precision */
#ifndef MP_PREC
 #ifndef MP_LOW_MEM
  #define MP_PREC    32                      /* default digits of precision */
 #else
  #define MP_PREC    8                       /* default digits of precision */
 #endif
#endif

/* size of comba arrays, should be at least 2 * 2**(BITS_PER_WORD - BITS_PER_DIGIT*2) */
#define MP_WARRAY    (1 << (((sizeof(mp_word) * CHAR_BIT) - (2 * DIGIT_BIT)) + 1))

/* the infamous mp_int structure */
typedef struct  {
    int      used, alloc, sign;
    mp_digit *dp;
} mp_int;

/* callback for mp_prime_random, should fill dst with random bytes and return how many read [upto len] */
typedef int ltm_prime_callback (unsigned char *dst, int len, void *dat);


#define USED(m)        ((m)->used)
#define DIGIT(m, k)    ((m)->dp[(k)])
#define SIGN(m)        ((m)->sign)

/* error code to char* string */
const char *mp_error_to_string(int code);

/* ---> init and deinit bignum functions <--- */
/* init a bignum */
int mp_init(mp_int *a);

/* free a bignum */
void mp_clear(mp_int *a);

/* init a null terminated series of arguments */
int mp_init_multi(mp_int *mp, ...);

/* clear a null terminated series of arguments */
void mp_clear_multi(mp_int *mp, ...);

/* exchange two ints */
void mp_exch(mp_int *a, mp_int *b);

/* shrink ram required for a bignum */
int mp_shrink(mp_int *a);

/* grow an int to a given size */
int mp_grow(mp_int *a, int size);

/* init to a given number of digits */
int mp_init_size(mp_int *a, int size);

/* ---> Basic Manipulations <--- */
#define mp_iszero(a)    (((a)->used == 0) ? MP_YES : MP_NO)
#define mp_iseven(a)    ((((a)->used > 0) && (((a)->dp[0] & 1u) == 0u)) ? MP_YES : MP_NO)
#define mp_isodd(a)     ((((a)->used > 0) && (((a)->dp[0] & 1u) == 1u)) ? MP_YES : MP_NO)
#define mp_isneg(a)     (((a)->sign != MP_ZPOS) ? MP_YES : MP_NO)

/* set to zero */
void mp_zero(mp_int *a);

/* set to a digit */
void mp_set(mp_int *a, mp_digit b);

/* set a 32-bit const */
int mp_set_int(mp_int *a, unsigned long b);

/* set a platform dependent unsigned long value */
int mp_set_long(mp_int *a, unsigned long b);

/* set a platform dependent unsigned long long value */
int mp_set_long_long(mp_int *a, unsigned long long b);

/* get a 32-bit value */
unsigned long mp_get_int(mp_int *a);

/* get a platform dependent unsigned long value */
unsigned long mp_get_long(mp_int *a);

/* get a platform dependent unsigned long long value */
unsigned long long mp_get_long_long(mp_int *a);

/* initialize and set a digit */
int mp_init_set(mp_int *a, mp_digit b);

/* initialize and set 32-bit value */
int mp_init_set_int(mp_int *a, unsigned long b);

/* copy, b = a */
int mp_copy(mp_int *a, mp_int *b);

/* inits and copies, a = b */
int mp_init_copy(mp_int *a, mp_int *b);

/* trim unused digits */
void mp_clamp(mp_int *a);

/* import binary data */
int mp_import(mp_int *rop, size_t count, int order, size_t size, int endian, size_t nails, const void *op);

/* export binary data */
int mp_export(void *rop, size_t *countp, int order, size_t size, int endian, size_t nails, mp_int *op);

/* ---> digit manipulation <--- */

/* right shift by "b" digits */
void mp_rshd(mp_int *a, int b);

/* left shift by "b" digits */
int mp_lshd(mp_int *a, int b);

/* c = a / 2**b, implemented as c = a >> b */
int mp_div_2d(mp_int *a, int b, mp_int *c, mp_int *d);

/* b = a/2 */
int mp_div_2(mp_int *a, mp_int *b);

/* c = a * 2**b, implemented as c = a << b */
int mp_mul_2d(mp_int *a, int b, mp_int *c);

/* b = a*2 */
int mp_mul_2(mp_int *a, mp_int *b);

/* c = a mod 2**b */
int mp_mod_2d(mp_int *a, int b, mp_int *c);

/* computes a = 2**b */
int mp_2expt(mp_int *a, int b);

/* Counts the number of lsbs which are zero before the first zero bit */
int mp_cnt_lsb(mp_int *a);

/* I Love Earth! */

/* makes a pseudo-random int of a given size */
int mp_rand(mp_int *a, int digits);

/* ---> binary operations <--- */
/* c = a XOR b  */
int mp_xor(mp_int *a, mp_int *b, mp_int *c);

/* c = a OR b */
int mp_or(mp_int *a, mp_int *b, mp_int *c);

/* c = a AND b */
int mp_and(mp_int *a, mp_int *b, mp_int *c);

/* ---> Basic arithmetic <--- */

/* b = -a */
int mp_neg(mp_int *a, mp_int *b);

/* b = |a| */
int mp_abs(mp_int *a, mp_int *b);

/* compare a to b */
int mp_cmp(mp_int *a, mp_int *b);

/* compare |a| to |b| */
int mp_cmp_mag(mp_int *a, mp_int *b);

/* c = a + b */
int mp_add(mp_int *a, mp_int *b, mp_int *c);

/* c = a - b */
int mp_sub(mp_int *a, mp_int *b, mp_int *c);

/* c = a * b */
int mp_mul(mp_int *a, mp_int *b, mp_int *c);

/* b = a*a  */
int mp_sqr(mp_int *a, mp_int *b);

/* a/b => cb + d == a */
int mp_div(mp_int *a, mp_int *b, mp_int *c, mp_int *d);

/* c = a mod b, 0 <= c < b  */
int mp_mod(mp_int *a, mp_int *b, mp_int *c);

/* ---> single digit functions <--- */

/* compare against a single digit */
int mp_cmp_d(mp_int *a, mp_digit b);

/* c = a + b */
int mp_add_d(mp_int *a, mp_digit b, mp_int *c);

/* c = a - b */
int mp_sub_d(mp_int *a, mp_digit b, mp_int *c);

/* c = a * b */
int mp_mul_d(mp_int *a, mp_digit b, mp_int *c);

/* a/b => cb + d == a */
int mp_div_d(mp_int *a, mp_digit b, mp_int *c, mp_digit *d);

/* a/3 => 3c + d == a */
int mp_div_3(mp_int *a, mp_int *c, mp_digit *d);

/* c = a**b */
int mp_expt_d(mp_int *a, mp_digit b, mp_int *c);
int mp_expt_d_ex(mp_int *a, mp_digit b, mp_int *c, int fast);

/* c = a mod b, 0 <= c < b  */
int mp_mod_d(mp_int *a, mp_digit b, mp_digit *c);

/* ---> number theory <--- */

/* d = a + b (mod c) */
int mp_addmod(mp_int *a, mp_int *b, mp_int *c, mp_int *d);

/* d = a - b (mod c) */
int mp_submod(mp_int *a, mp_int *b, mp_int *c, mp_int *d);

/* d = a * b (mod c) */
int mp_mulmod(mp_int *a, mp_int *b, mp_int *c, mp_int *d);

/* c = a * a (mod b) */
int mp_sqrmod(mp_int *a, mp_int *b, mp_int *c);

/* c = 1/a (mod b) */
int mp_invmod(mp_int *a, mp_int *b, mp_int *c);

/* c = (a, b) */
int mp_gcd(mp_int *a, mp_int *b, mp_int *c);

/* produces value such that U1*a + U2*b = U3 */
int mp_exteuclid(mp_int *a, mp_int *b, mp_int *U1, mp_int *U2, mp_int *U3);

/* c = [a, b] or (a*b)/(a, b) */
int mp_lcm(mp_int *a, mp_int *b, mp_int *c);

/* finds one of the b'th root of a, such that |c|**b <= |a|
 *
 * returns error if a < 0 and b is even
 */
int mp_n_root(mp_int *a, mp_digit b, mp_int *c);
int mp_n_root_ex(mp_int *a, mp_digit b, mp_int *c, int fast);

/* special sqrt algo */
int mp_sqrt(mp_int *arg, mp_int *ret);

/* special sqrt (mod prime) */
int mp_sqrtmod_prime(mp_int *arg, mp_int *prime, mp_int *ret);

/* is number a square? */
int mp_is_square(mp_int *arg, int *ret);

/* computes the jacobi c = (a | n) (or Legendre if b is prime)  */
int mp_jacobi(mp_int *a, mp_int *n, int *c);

/* used to setup the Barrett reduction for a given modulus b */
int mp_reduce_setup(mp_int *a, mp_int *b);

/* Barrett Reduction, computes a (mod b) with a precomputed value c
 *
 * Assumes that 0 < a <= b*b, note if 0 > a > -(b*b) then you can merely
 * compute the reduction as -1 * mp_reduce(mp_abs(a)) [pseudo code].
 */
int mp_reduce(mp_int *a, mp_int *b, mp_int *c);

/* setups the montgomery reduction */
int mp_montgomery_setup(mp_int *a, mp_digit *mp);

/* computes a = B**n mod b without division or multiplication useful for
 * normalizing numbers in a Montgomery system.
 */
int mp_montgomery_calc_normalization(mp_int *a, mp_int *b);

/* computes x/R == x (mod N) via Montgomery Reduction */
int mp_montgomery_reduce(mp_int *a, mp_int *m, mp_digit mp);

/* returns 1 if a is a valid DR modulus */
int mp_dr_is_modulus(mp_int *a);

/* sets the value of "d" required for mp_dr_reduce */
void mp_dr_setup(mp_int *a, mp_digit *d);

/* reduces a modulo b using the Diminished Radix method */
int mp_dr_reduce(mp_int *a, mp_int *b, mp_digit mp);

/* returns true if a can be reduced with mp_reduce_2k */
int mp_reduce_is_2k(mp_int *a);

/* determines k value for 2k reduction */
int mp_reduce_2k_setup(mp_int *a, mp_digit *d);

/* reduces a modulo b where b is of the form 2**p - k [0 <= a] */
int mp_reduce_2k(mp_int *a, mp_int *n, mp_digit d);

/* returns true if a can be reduced with mp_reduce_2k_l */
int mp_reduce_is_2k_l(mp_int *a);

/* determines k value for 2k reduction */
int mp_reduce_2k_setup_l(mp_int *a, mp_int *d);

/* reduces a modulo b where b is of the form 2**p - k [0 <= a] */
int mp_reduce_2k_l(mp_int *a, mp_int *n, mp_int *d);

/* d = a**b (mod c) */
int mp_exptmod(mp_int *a, mp_int *b, mp_int *c, mp_int *d);

/* ---> Primes <--- */

/* number of primes */
#ifdef MP_8BIT
 #define PRIME_SIZE    31
#else
 #define PRIME_SIZE    256
#endif

/* table of first PRIME_SIZE primes */
extern const mp_digit ltm_prime_tab[PRIME_SIZE];

/* result=1 if a is divisible by one of the first PRIME_SIZE primes */
int mp_prime_is_divisible(mp_int *a, int *result);

/* performs one Fermat test of "a" using base "b".
 * Sets result to 0 if composite or 1 if probable prime
 */
int mp_prime_fermat(mp_int *a, mp_int *b, int *result);

/* performs one Miller-Rabin test of "a" using base "b".
 * Sets result to 0 if composite or 1 if probable prime
 */
int mp_prime_miller_rabin(mp_int *a, mp_int *b, int *result);

/* This gives [for a given bit size] the number of trials required
 * such that Miller-Rabin gives a prob of failure lower than 2^-96
 */
int mp_prime_rabin_miller_trials(int size);

/* performs t rounds of Miller-Rabin on "a" using the first
 * t prime bases.  Also performs an initial sieve of trial
 * division.  Determines if "a" is prime with probability
 * of error no more than (1/4)**t.
 *
 * Sets result to 1 if probably prime, 0 otherwise
 */
int mp_prime_is_prime(mp_int *a, int t, int *result);

/* finds the next prime after the number "a" using "t" trials
 * of Miller-Rabin.
 *
 * bbs_style = 1 means the prime must be congruent to 3 mod 4
 */
int mp_prime_next_prime(mp_int *a, int t, int bbs_style);

/* makes a truly random prime of a given size (bytes),
 * call with bbs = 1 if you want it to be congruent to 3 mod 4
 *
 * You have to supply a callback which fills in a buffer with random bytes.  "dat" is a parameter you can
 * have passed to the callback (e.g. a state or something).  This function doesn't use "dat" itself
 * so it can be NULL
 *
 * The prime generated will be larger than 2^(8*size).
 */
#define mp_prime_random(a, t, size, bbs, cb, dat)    mp_prime_random_ex(a, t, ((size) * 8) + 1, (bbs == 1) ? LTM_PRIME_BBS : 0, cb, dat)

/* makes a truly random prime of a given size (bits),
 *
 * Flags are as follows:
 *
 *   LTM_PRIME_BBS      - make prime congruent to 3 mod 4
 *   LTM_PRIME_SAFE     - make sure (p-1)/2 is prime as well (implies LTM_PRIME_BBS)
 *   LTM_PRIME_2MSB_ON  - make the 2nd highest bit one
 *
 * You have to supply a callback which fills in a buffer with random bytes.  "dat" is a parameter you can
 * have passed to the callback (e.g. a state or something).  This function doesn't use "dat" itself
 * so it can be NULL
 *
 */
int mp_prime_random_ex(mp_int *a, int t, int size, int flags, ltm_prime_callback cb, void *dat);

/* ---> radix conversion <--- */
int mp_count_bits(mp_int *a);

int mp_unsigned_bin_size(mp_int *a);
int mp_read_unsigned_bin(mp_int *a, const unsigned char *b, int c);
int mp_to_unsigned_bin(mp_int *a, unsigned char *b);
int mp_to_unsigned_bin_n(mp_int *a, unsigned char *b, unsigned long *outlen);

int mp_signed_bin_size(mp_int *a);
int mp_read_signed_bin(mp_int *a, const unsigned char *b, int c);
int mp_to_signed_bin(mp_int *a, unsigned char *b);
int mp_to_signed_bin_n(mp_int *a, unsigned char *b, unsigned long *outlen);

int mp_read_radix(mp_int *a, const char *str, int radix);
int mp_toradix(mp_int *a, char *str, int radix);
int mp_toradix_n(mp_int *a, char *str, int radix, int maxlen);
int mp_radix_size(mp_int *a, int radix, int *size);

#ifndef LTM_NO_FILE
int mp_fread(mp_int *a, int radix, FILE *stream);
int mp_fwrite(mp_int *a, int radix, FILE *stream);
#endif

#define mp_read_raw(mp, str, len)    mp_read_signed_bin((mp), (str), (len))
#define mp_raw_size(mp)              mp_signed_bin_size(mp)
#define mp_toraw(mp, str)            mp_to_signed_bin((mp), (str))
#define mp_read_mag(mp, str, len)    mp_read_unsigned_bin((mp), (str), (len))
#define mp_mag_size(mp)              mp_unsigned_bin_size(mp)
#define mp_tomag(mp, str)            mp_to_unsigned_bin((mp), (str))

#define mp_tobinary(M, S)            mp_toradix((M), (S), 2)
#define mp_tooctal(M, S)             mp_toradix((M), (S), 8)
#define mp_todecimal(M, S)           mp_toradix((M), (S), 10)
#define mp_tohex(M, S)               mp_toradix((M), (S), 16)

#ifdef __cplusplus
}
#endif
#endif


/* $Source$ */
/* $Revision$ */
/* $Date$ */ 

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://math.libtomcrypt.com
 */
#ifndef TOMMATH_PRIV_H_
#define TOMMATH_PRIV_H_

#include <ctype.h>

#define MIN(x, y)    (((x) < (y)) ? (x) : (y))

#define MAX(x, y)    (((x) > (y)) ? (x) : (y))

#ifdef __cplusplus
extern "C" {
/* C++ compilers don't like assigning void * to mp_digit * */
 #define  OPT_CAST(x)    (x *)

#else

/* C on the other hand doesn't care */
 #define  OPT_CAST(x)
#endif

/* define heap macros */
#ifndef XMALLOC
/* default to libc stuff */
 #define XMALLOC     malloc
 #define XFREE       free
 #define XREALLOC    realloc
 #define XCALLOC     calloc
#else
/* prototypes for our heap functions */
extern void *XMALLOC(size_t n);
extern void *XREALLOC(void *p, size_t n);
extern void *XCALLOC(size_t n, size_t s);
extern void XFREE(void *p);
#endif

/* lowlevel functions, do not call! */
int s_mp_add(mp_int *a, mp_int *b, mp_int *c);
int s_mp_sub(mp_int *a, mp_int *b, mp_int *c);

#define s_mp_mul(a, b, c)    s_mp_mul_digs(a, b, c, (a)->used + (b)->used + 1)
int fast_s_mp_mul_digs(mp_int *a, mp_int *b, mp_int *c, int digs);
int s_mp_mul_digs(mp_int *a, mp_int *b, mp_int *c, int digs);
int fast_s_mp_mul_high_digs(mp_int *a, mp_int *b, mp_int *c, int digs);
int s_mp_mul_high_digs(mp_int *a, mp_int *b, mp_int *c, int digs);
int fast_s_mp_sqr(mp_int *a, mp_int *b);
int s_mp_sqr(mp_int *a, mp_int *b);
int mp_karatsuba_mul(mp_int *a, mp_int *b, mp_int *c);
int mp_toom_mul(mp_int *a, mp_int *b, mp_int *c);
int mp_karatsuba_sqr(mp_int *a, mp_int *b);
int mp_toom_sqr(mp_int *a, mp_int *b);
int fast_mp_invmod(mp_int *a, mp_int *b, mp_int *c);
int mp_invmod_slow(mp_int *a, mp_int *b, mp_int *c);
int fast_mp_montgomery_reduce(mp_int *x, mp_int *n, mp_digit rho);
int mp_exptmod_fast(mp_int *G, mp_int *X, mp_int *P, mp_int *Y, int redmode);
int s_mp_exptmod(mp_int *G, mp_int *X, mp_int *P, mp_int *Y, int redmode);
void bn_reverse(unsigned char *s, int len);

extern const char *mp_s_rmap;

/* Fancy macro to set an MPI from another type.
 * There are several things assumed:
 *  x is the counter and unsigned
 *  a is the pointer to the MPI
 *  b is the original value that should be set in the MPI.
 */
#define MP_SET_XLONG(func_name, type)                            \
    int func_name(mp_int * a, type b)                            \
    {                                                            \
        unsigned int x;                                          \
        int          res;                                        \
                                                                 \
        mp_zero(a);                                              \
                                                                 \
        /* set four bits at a time */                            \
        for (x = 0; x < (sizeof(type) * 2u); x++) {              \
            /* shift the number up four bits */                  \
            if ((res = mp_mul_2d(a, 4, a)) != MP_OKAY) {         \
                return res;                                      \
            }                                                    \
                                                                 \
            /* OR in the top four bits of the source */          \
            a->dp[0] |= (b >> ((sizeof(type) * 8u) - 4u)) & 15u; \
                                                                 \
            /* shift the source up to the next four bits */      \
            b <<= 4;                                             \
                                                                 \
            /* ensure that digits are not clamped off */         \
            a->used += 1;                                        \
        }                                                        \
        mp_clamp(a);                                             \
        return MP_OKAY;                                          \
    }

#ifdef __cplusplus
}
#endif
#endif


/* $Source$ */
/* $Revision$ */
/* $Date$ */ 

#define BN_FAST_MP_INVMOD_C
#ifdef BN_FAST_MP_INVMOD_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* computes the modular inverse via binary extended euclidean algorithm,
 * that is c = 1/a mod b
 *
 * Based on slow invmod except this is optimized for the case where b is
 * odd as per HAC Note 14.64 on pp. 610
 */
int fast_mp_invmod(mp_int *a, mp_int *b, mp_int *c) {
    mp_int x, y, u, v, B, D;
    int    res, neg;

    /* 2. [modified] b must be odd   */
    if (mp_iseven(b) == MP_YES) {
        return MP_VAL;
    }

    /* init all our temps */
    if ((res = mp_init_multi(&x, &y, &u, &v, &B, &D, NULL)) != MP_OKAY) {
        return res;
    }

    /* x == modulus, y == value to invert */
    if ((res = mp_copy(b, &x)) != MP_OKAY) {
        goto LBL_ERR;
    }

    /* we need y = |a| */
    if ((res = mp_mod(a, b, &y)) != MP_OKAY) {
        goto LBL_ERR;
    }

    /* 3. u=x, v=y, A=1, B=0, C=0,D=1 */
    if ((res = mp_copy(&x, &u)) != MP_OKAY) {
        goto LBL_ERR;
    }
    if ((res = mp_copy(&y, &v)) != MP_OKAY) {
        goto LBL_ERR;
    }
    mp_set(&D, 1);

top:
    /* 4.  while u is even do */
    while (mp_iseven(&u) == MP_YES) {
        /* 4.1 u = u/2 */
        if ((res = mp_div_2(&u, &u)) != MP_OKAY) {
            goto LBL_ERR;
        }
        /* 4.2 if B is odd then */
        if (mp_isodd(&B) == MP_YES) {
            if ((res = mp_sub(&B, &x, &B)) != MP_OKAY) {
                goto LBL_ERR;
            }
        }
        /* B = B/2 */
        if ((res = mp_div_2(&B, &B)) != MP_OKAY) {
            goto LBL_ERR;
        }
    }

    /* 5.  while v is even do */
    while (mp_iseven(&v) == MP_YES) {
        /* 5.1 v = v/2 */
        if ((res = mp_div_2(&v, &v)) != MP_OKAY) {
            goto LBL_ERR;
        }
        /* 5.2 if D is odd then */
        if (mp_isodd(&D) == MP_YES) {
            /* D = (D-x)/2 */
            if ((res = mp_sub(&D, &x, &D)) != MP_OKAY) {
                goto LBL_ERR;
            }
        }
        /* D = D/2 */
        if ((res = mp_div_2(&D, &D)) != MP_OKAY) {
            goto LBL_ERR;
        }
    }

    /* 6.  if u >= v then */
    if (mp_cmp(&u, &v) != MP_LT) {
        /* u = u - v, B = B - D */
        if ((res = mp_sub(&u, &v, &u)) != MP_OKAY) {
            goto LBL_ERR;
        }

        if ((res = mp_sub(&B, &D, &B)) != MP_OKAY) {
            goto LBL_ERR;
        }
    } else {
        /* v - v - u, D = D - B */
        if ((res = mp_sub(&v, &u, &v)) != MP_OKAY) {
            goto LBL_ERR;
        }

        if ((res = mp_sub(&D, &B, &D)) != MP_OKAY) {
            goto LBL_ERR;
        }
    }

    /* if not zero goto step 4 */
    if (mp_iszero(&u) == MP_NO) {
        goto top;
    }

    /* now a = C, b = D, gcd == g*v */

    /* if v != 1 then there is no inverse */
    if (mp_cmp_d(&v, 1) != MP_EQ) {
        res = MP_VAL;
        goto LBL_ERR;
    }

    /* b is now the inverse */
    neg = a->sign;
    while (D.sign == MP_NEG) {
        if ((res = mp_add(&D, b, &D)) != MP_OKAY) {
            goto LBL_ERR;
        }
    }
    mp_exch(&D, c);
    c->sign = neg;
    res     = MP_OKAY;

LBL_ERR: mp_clear_multi(&x, &y, &u, &v, &B, &D, NULL);
    return res;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_FAST_MP_MONTGOMERY_REDUCE_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* computes xR**-1 == x (mod N) via Montgomery Reduction
 *
 * This is an optimized implementation of montgomery_reduce
 * which uses the comba method to quickly calculate the columns of the
 * reduction.
 *
 * Based on Algorithm 14.32 on pp.601 of HAC.
 */
int fast_mp_montgomery_reduce(mp_int *x, mp_int *n, mp_digit rho) {
    int     ix, res, olduse;
    mp_word W[MP_WARRAY];

    /* get old used count */
    olduse = x->used;

    /* grow a as required */
    if (x->alloc < (n->used + 1)) {
        if ((res = mp_grow(x, n->used + 1)) != MP_OKAY) {
            return res;
        }
    }

    /* first we have to get the digits of the input into
     * an array of double precision words W[...]
     */
    {
        mp_word  *_W;
        mp_digit *tmpx;

        /* alias for the W[] array */
        _W = W;

        /* alias for the digits of  x*/
        tmpx = x->dp;

        /* copy the digits of a into W[0..a->used-1] */
        for (ix = 0; ix < x->used; ix++) {
            *_W++ = *tmpx++;
        }

        /* zero the high words of W[a->used..m->used*2] */
        for ( ; ix < ((n->used * 2) + 1); ix++) {
            *_W++ = 0;
        }
    }

    /* now we proceed to zero successive digits
     * from the least significant upwards
     */
    for (ix = 0; ix < n->used; ix++) {
        /* mu = ai * m' mod b
         *
         * We avoid a double precision multiplication (which isn't required)
         * by casting the value down to a mp_digit.  Note this requires
         * that W[ix-1] have  the carry cleared (see after the inner loop)
         */
        mp_digit mu;
        mu = (mp_digit)(((W[ix] & MP_MASK) * rho) & MP_MASK);

        /* a = a + mu * m * b**i
         *
         * This is computed in place and on the fly.  The multiplication
         * by b**i is handled by offseting which columns the results
         * are added to.
         *
         * Note the comba method normally doesn't handle carries in the
         * inner loop In this case we fix the carry from the previous
         * column since the Montgomery reduction requires digits of the
         * result (so far) [see above] to work.  This is
         * handled by fixing up one carry after the inner loop.  The
         * carry fixups are done in order so after these loops the
         * first m->used words of W[] have the carries fixed
         */
        {
            int      iy;
            mp_digit *tmpn;
            mp_word  *_W;

            /* alias for the digits of the modulus */
            tmpn = n->dp;

            /* Alias for the columns set by an offset of ix */
            _W = W + ix;

            /* inner loop */
            for (iy = 0; iy < n->used; iy++) {
                *_W++ += ((mp_word)mu) * ((mp_word) * tmpn++);
            }
        }

        /* now fix carry for next digit, W[ix+1] */
        W[ix + 1] += W[ix] >> ((mp_word)DIGIT_BIT);
    }

    /* now we have to propagate the carries and
     * shift the words downward [all those least
     * significant digits we zeroed].
     */
    {
        mp_digit *tmpx;
        mp_word  *_W, *_W1;

        /* nox fix rest of carries */

        /* alias for current word */
        _W1 = W + ix;

        /* alias for next word, where the carry goes */
        _W = W + ++ix;

        for ( ; ix <= ((n->used * 2) + 1); ix++) {
            *_W++ += *_W1++ >> ((mp_word)DIGIT_BIT);
        }

        /* copy out, A = A/b**n
         *
         * The result is A/b**n but instead of converting from an
         * array of mp_word to mp_digit than calling mp_rshd
         * we just copy them in the right order
         */

        /* alias for destination word */
        tmpx = x->dp;

        /* alias for shifted double precision result */
        _W = W + n->used;

        for (ix = 0; ix < (n->used + 1); ix++) {
            *tmpx++ = (mp_digit)(*_W++ & ((mp_word)MP_MASK));
        }

        /* zero oldused digits, if the input a was larger than
         * m->used+1 we'll have to clear the digits
         */
        for ( ; ix < olduse; ix++) {
            *tmpx++ = 0;
        }
    }

    /* set the max used and clamp */
    x->used = n->used + 1;
    mp_clamp(x);

    /* if A >= m then A = A - m */
    if (mp_cmp_mag(x, n) != MP_LT) {
        return s_mp_sub(x, n, x);
    }
    return MP_OKAY;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_FAST_S_MP_MUL_DIGS_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* Fast (comba) multiplier
 *
 * This is the fast column-array [comba] multiplier.  It is
 * designed to compute the columns of the product first
 * then handle the carries afterwards.  This has the effect
 * of making the nested loops that compute the columns very
 * simple and schedulable on super-scalar processors.
 *
 * This has been modified to produce a variable number of
 * digits of output so if say only a half-product is required
 * you don't have to compute the upper half (a feature
 * required for fast Barrett reduction).
 *
 * Based on Algorithm 14.12 on pp.595 of HAC.
 *
 */
int fast_s_mp_mul_digs(mp_int *a, mp_int *b, mp_int *c, int digs) {
    int      olduse, res, pa, ix, iz;
    mp_digit W[MP_WARRAY];
    mp_word  _W;

    /* grow the destination as required */
    if (c->alloc < digs) {
        if ((res = mp_grow(c, digs)) != MP_OKAY) {
            return res;
        }
    }

    /* number of output digits to produce */
    pa = MIN(digs, a->used + b->used);

    /* clear the carry */
    _W = 0;
    for (ix = 0; ix < pa; ix++) {
        int      tx, ty;
        int      iy;
        mp_digit *tmpx, *tmpy;

        /* get offsets into the two bignums */
        ty = MIN(b->used - 1, ix);
        tx = ix - ty;

        /* setup temp aliases */
        tmpx = a->dp + tx;
        tmpy = b->dp + ty;

        /* this is the number of times the loop will iterrate, essentially
           while (tx++ < a->used && ty-- >= 0) { ... }
         */
        iy = MIN(a->used - tx, ty + 1);

        /* execute loop */
        for (iz = 0; iz < iy; ++iz) {
            _W += ((mp_word) * tmpx++) * ((mp_word) * tmpy--);
        }

        /* store term */
        W[ix] = ((mp_digit)_W) & MP_MASK;

        /* make next carry */
        _W = _W >> ((mp_word)DIGIT_BIT);
    }

    /* setup dest */
    olduse  = c->used;
    c->used = pa;

    {
        mp_digit *tmpc;
        tmpc = c->dp;
        for (ix = 0; ix < (pa + 1); ix++) {
            /* now extract the previous digit [below the carry] */
            *tmpc++ = W[ix];
        }

        /* clear unused digits [that existed in the old copy of c] */
        for ( ; ix < olduse; ix++) {
            *tmpc++ = 0;
        }
    }
    mp_clamp(c);
    return MP_OKAY;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_FAST_S_MP_MUL_HIGH_DIGS_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* this is a modified version of fast_s_mul_digs that only produces
 * output digits *above* digs.  See the comments for fast_s_mul_digs
 * to see how it works.
 *
 * This is used in the Barrett reduction since for one of the multiplications
 * only the higher digits were needed.  This essentially halves the work.
 *
 * Based on Algorithm 14.12 on pp.595 of HAC.
 */
int fast_s_mp_mul_high_digs(mp_int *a, mp_int *b, mp_int *c, int digs) {
    int      olduse, res, pa, ix, iz;
    mp_digit W[MP_WARRAY];
    mp_word  _W;

    /* grow the destination as required */
    pa = a->used + b->used;
    if (c->alloc < pa) {
        if ((res = mp_grow(c, pa)) != MP_OKAY) {
            return res;
        }
    }

    /* number of output digits to produce */
    pa = a->used + b->used;
    _W = 0;
    for (ix = digs; ix < pa; ix++) {
        int      tx, ty, iy;
        mp_digit *tmpx, *tmpy;

        /* get offsets into the two bignums */
        ty = MIN(b->used - 1, ix);
        tx = ix - ty;

        /* setup temp aliases */
        tmpx = a->dp + tx;
        tmpy = b->dp + ty;

        /* this is the number of times the loop will iterrate, essentially its
           while (tx++ < a->used && ty-- >= 0) { ... }
         */
        iy = MIN(a->used - tx, ty + 1);

        /* execute loop */
        for (iz = 0; iz < iy; iz++) {
            _W += ((mp_word) * tmpx++) * ((mp_word) * tmpy--);
        }

        /* store term */
        W[ix] = ((mp_digit)_W) & MP_MASK;

        /* make next carry */
        _W = _W >> ((mp_word)DIGIT_BIT);
    }

    /* setup dest */
    olduse  = c->used;
    c->used = pa;

    {
        mp_digit *tmpc;

        tmpc = c->dp + digs;
        for (ix = digs; ix < pa; ix++) {
            /* now extract the previous digit [below the carry] */
            *tmpc++ = W[ix];
        }

        /* clear unused digits [that existed in the old copy of c] */
        for ( ; ix < olduse; ix++) {
            *tmpc++ = 0;
        }
    }
    mp_clamp(c);
    return MP_OKAY;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_FAST_S_MP_SQR_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* the jist of squaring...
 * you do like mult except the offset of the tmpx [one that
 * starts closer to zero] can't equal the offset of tmpy.
 * So basically you set up iy like before then you min it with
 * (ty-tx) so that it never happens.  You double all those
 * you add in the inner loop

   After that loop you do the squares and add them in.
 */

int fast_s_mp_sqr(mp_int *a, mp_int *b) {
    int      olduse, res, pa, ix, iz;
    mp_digit W[MP_WARRAY], *tmpx;
    mp_word  W1;

    /* grow the destination as required */
    pa = a->used + a->used;
    if (b->alloc < pa) {
        if ((res = mp_grow(b, pa)) != MP_OKAY) {
            return res;
        }
    }

    /* number of output digits to produce */
    W1 = 0;
    for (ix = 0; ix < pa; ix++) {
        int      tx, ty, iy;
        mp_word  _W;
        mp_digit *tmpy;

        /* clear counter */
        _W = 0;

        /* get offsets into the two bignums */
        ty = MIN(a->used - 1, ix);
        tx = ix - ty;

        /* setup temp aliases */
        tmpx = a->dp + tx;
        tmpy = a->dp + ty;

        /* this is the number of times the loop will iterrate, essentially
           while (tx++ < a->used && ty-- >= 0) { ... }
         */
        iy = MIN(a->used - tx, ty + 1);

        /* now for squaring tx can never equal ty
         * we halve the distance since they approach at a rate of 2x
         * and we have to round because odd cases need to be executed
         */
        iy = MIN(iy, ((ty - tx) + 1) >> 1);

        /* execute loop */
        for (iz = 0; iz < iy; iz++) {
            _W += ((mp_word) * tmpx++) * ((mp_word) * tmpy--);
        }

        /* double the inner product and add carry */
        _W = _W + _W + W1;

        /* even columns have the square term in them */
        if ((ix & 1) == 0) {
            _W += ((mp_word)a->dp[ix >> 1]) * ((mp_word)a->dp[ix >> 1]);
        }

        /* store it */
        W[ix] = (mp_digit)(_W & MP_MASK);

        /* make next carry */
        W1 = _W >> ((mp_word)DIGIT_BIT);
    }

    /* setup dest */
    olduse  = b->used;
    b->used = a->used + a->used;

    {
        mp_digit *tmpb;
        tmpb = b->dp;
        for (ix = 0; ix < pa; ix++) {
            *tmpb++ = W[ix] & MP_MASK;
        }

        /* clear unused digits [that existed in the old copy of c] */
        for ( ; ix < olduse; ix++) {
            *tmpb++ = 0;
        }
    }
    mp_clamp(b);
    return MP_OKAY;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_2EXPT_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* computes a = 2**b
 *
 * Simple algorithm which zeroes the int, grows it then just sets one bit
 * as required.
 */
int
mp_2expt(mp_int *a, int b) {
    int res;

    /* zero a as per default */
    mp_zero(a);

    /* grow a to accomodate the single bit */
    if ((res = mp_grow(a, (b / DIGIT_BIT) + 1)) != MP_OKAY) {
        return res;
    }

    /* set the used count of where the bit will go */
    a->used = (b / DIGIT_BIT) + 1;

    /* put the single bit in its place */
    a->dp[b / DIGIT_BIT] = ((mp_digit)1) << (b % DIGIT_BIT);

    return MP_OKAY;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_ABS_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* b = |a|
 *
 * Simple function copies the input and fixes the sign to positive
 */
int
mp_abs(mp_int *a, mp_int *b) {
    int res;

    /* copy a to b */
    if (a != b) {
        if ((res = mp_copy(a, b)) != MP_OKAY) {
            return res;
        }
    }

    /* force the sign of b to positive */
    b->sign = MP_ZPOS;

    return MP_OKAY;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_ADD_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* high level addition (handles signs) */
int mp_add(mp_int *a, mp_int *b, mp_int *c) {
    int sa, sb, res;

    /* get sign of both inputs */
    sa = a->sign;
    sb = b->sign;

    /* handle two cases, not four */
    if (sa == sb) {
        /* both positive or both negative */
        /* add their magnitudes, copy the sign */
        c->sign = sa;
        res     = s_mp_add(a, b, c);
    } else {
        /* one positive, the other negative */
        /* subtract the one with the greater magnitude from */
        /* the one of the lesser magnitude.  The result gets */
        /* the sign of the one with the greater magnitude. */
        if (mp_cmp_mag(a, b) == MP_LT) {
            c->sign = sb;
            res     = s_mp_sub(b, a, c);
        } else {
            c->sign = sa;
            res     = s_mp_sub(a, b, c);
        }
    }
    return res;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_ADD_D_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* single digit addition */
int
mp_add_d(mp_int *a, mp_digit b, mp_int *c) {
    int      res, ix, oldused;
    mp_digit *tmpa, *tmpc, mu;

    /* grow c as required */
    if (c->alloc < (a->used + 1)) {
        if ((res = mp_grow(c, a->used + 1)) != MP_OKAY) {
            return res;
        }
    }

    /* if a is negative and |a| >= b, call c = |a| - b */
    if ((a->sign == MP_NEG) && ((a->used > 1) || (a->dp[0] >= b))) {
        /* temporarily fix sign of a */
        a->sign = MP_ZPOS;

        /* c = |a| - b */
        res = mp_sub_d(a, b, c);

        /* fix sign  */
        a->sign = c->sign = MP_NEG;

        /* clamp */
        mp_clamp(c);

        return res;
    }

    /* old number of used digits in c */
    oldused = c->used;

    /* sign always positive */
    c->sign = MP_ZPOS;

    /* source alias */
    tmpa = a->dp;

    /* destination alias */
    tmpc = c->dp;

    /* if a is positive */
    if (a->sign == MP_ZPOS) {
        /* add digit, after this we're propagating
         * the carry.
         */
        *tmpc    = *tmpa++ + b;
        mu       = *tmpc >> DIGIT_BIT;
        *tmpc++ &= MP_MASK;

        /* now handle rest of the digits */
        for (ix = 1; ix < a->used; ix++) {
            *tmpc    = *tmpa++ + mu;
            mu       = *tmpc >> DIGIT_BIT;
            *tmpc++ &= MP_MASK;
        }
        /* set final carry */
        ix++;
        *tmpc++ = mu;

        /* setup size */
        c->used = a->used + 1;
    } else {
        /* a was negative and |a| < b */
        c->used = 1;

        /* the result is a single digit */
        if (a->used == 1) {
            *tmpc++ = b - a->dp[0];
        } else {
            *tmpc++ = b;
        }

        /* setup count so the clearing of oldused
         * can fall through correctly
         */
        ix = 1;
    }

    /* now zero to oldused */
    while (ix++ < oldused) {
        *tmpc++ = 0;
    }
    mp_clamp(c);

    return MP_OKAY;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_ADDMOD_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* d = a + b (mod c) */
int
mp_addmod(mp_int *a, mp_int *b, mp_int *c, mp_int *d) {
    int    res;
    mp_int t;

    if ((res = mp_init(&t)) != MP_OKAY) {
        return res;
    }

    if ((res = mp_add(a, b, &t)) != MP_OKAY) {
        mp_clear(&t);
        return res;
    }
    res = mp_mod(&t, c, d);
    mp_clear(&t);
    return res;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_AND_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* AND two ints together */
int
mp_and(mp_int *a, mp_int *b, mp_int *c) {
    int    res, ix, px;
    mp_int t, *x;

    if (a->used > b->used) {
        if ((res = mp_init_copy(&t, a)) != MP_OKAY) {
            return res;
        }
        px = b->used;
        x  = b;
    } else {
        if ((res = mp_init_copy(&t, b)) != MP_OKAY) {
            return res;
        }
        px = a->used;
        x  = a;
    }

    for (ix = 0; ix < px; ix++) {
        t.dp[ix] &= x->dp[ix];
    }

    /* zero digits above the last from the smallest mp_int */
    for ( ; ix < t.used; ix++) {
        t.dp[ix] = 0;
    }

    mp_clamp(&t);
    mp_exch(c, &t);
    mp_clear(&t);
    return MP_OKAY;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_CLAMP_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* trim unused digits
 *
 * This is used to ensure that leading zero digits are
 * trimed and the leading "used" digit will be non-zero
 * Typically very fast.  Also fixes the sign if there
 * are no more leading digits
 */
void
mp_clamp(mp_int *a) {
    /* decrease used while the most significant digit is
     * zero.
     */
    while ((a->used > 0) && (a->dp[a->used - 1] == 0)) {
        --(a->used);
    }

    /* reset the sign flag if used == 0 */
    if (a->used == 0) {
        a->sign = MP_ZPOS;
    }
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_CLEAR_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* clear one (frees)  */
void
mp_clear(mp_int *a) {
    int i;

    /* only do anything if a hasn't been freed previously */
    if (a->dp != NULL) {
        /* first zero the digits */
        for (i = 0; i < a->used; i++) {
            a->dp[i] = 0;
        }

        /* free ram */
        XFREE(a->dp);

        /* reset members to make debugging easier */
        a->dp    = NULL;
        a->alloc = a->used = 0;
        a->sign  = MP_ZPOS;
    }
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_CLEAR_MULTI_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */
#include <stdarg.h>

void mp_clear_multi(mp_int *mp, ...) {
    mp_int  *next_mp = mp;
    va_list args;

    va_start(args, mp);
    while (next_mp != NULL) {
        mp_clear(next_mp);
        next_mp = va_arg(args, mp_int *);
    }
    va_end(args);
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_CMP_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* compare two ints (signed)*/
int
mp_cmp(mp_int *a, mp_int *b) {
    /* compare based on sign */
    if (a->sign != b->sign) {
        if (a->sign == MP_NEG) {
            return MP_LT;
        } else {
            return MP_GT;
        }
    }

    /* compare digits */
    if (a->sign == MP_NEG) {
        /* if negative compare opposite direction */
        return mp_cmp_mag(b, a);
    } else {
        return mp_cmp_mag(a, b);
    }
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_CMP_D_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* compare a digit */
int mp_cmp_d(mp_int *a, mp_digit b) {
    /* compare based on sign */
    if (a->sign == MP_NEG) {
        return MP_LT;
    }

    /* compare based on magnitude */
    if (a->used > 1) {
        return MP_GT;
    }

    /* compare the only digit of a to b */
    if (a->dp[0] > b) {
        return MP_GT;
    } else if (a->dp[0] < b) {
        return MP_LT;
    } else {
        return MP_EQ;
    }
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_CMP_MAG_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* compare maginitude of two ints (unsigned) */
int mp_cmp_mag(mp_int *a, mp_int *b) {
    int      n;
    mp_digit *tmpa, *tmpb;

    /* compare based on # of non-zero digits */
    if (a->used > b->used) {
        return MP_GT;
    }

    if (a->used < b->used) {
        return MP_LT;
    }

    /* alias for a */
    tmpa = a->dp + (a->used - 1);

    /* alias for b */
    tmpb = b->dp + (a->used - 1);

    /* compare based on digits  */
    for (n = 0; n < a->used; ++n, --tmpa, --tmpb) {
        if (*tmpa > *tmpb) {
            return MP_GT;
        }

        if (*tmpa < *tmpb) {
            return MP_LT;
        }
    }
    return MP_EQ;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_CNT_LSB_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

static const int lnz[16] = {
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0
};

/* Counts the number of lsbs which are zero before the first zero bit */
int mp_cnt_lsb(mp_int *a) {
    int      x;
    mp_digit q, qq;

    /* easy out */
    if (mp_iszero(a) == MP_YES) {
        return 0;
    }

    /* scan lower digits until non-zero */
    for (x = 0; (x < a->used) && (a->dp[x] == 0); x++) {
    }
    q  = a->dp[x];
    x *= DIGIT_BIT;

    /* now scan this digit until a 1 is found */
    if ((q & 1) == 0) {
        do {
            qq  = q & 15;
            x  += lnz[qq];
            q >>= 4;
        } while (qq == 0);
    }
    return x;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_COPY_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* copy, b = a */
int
mp_copy(mp_int *a, mp_int *b) {
    int res, n;

    /* if dst == src do nothing */
    if (a == b) {
        return MP_OKAY;
    }

    /* grow dest */
    if (b->alloc < a->used) {
        if ((res = mp_grow(b, a->used)) != MP_OKAY) {
            return res;
        }
    }

    /* zero b and copy the parameters over */
    {
        mp_digit *tmpa, *tmpb;

        /* pointer aliases */

        /* source */
        tmpa = a->dp;

        /* destination */
        tmpb = b->dp;

        /* copy all the digits */
        for (n = 0; n < a->used; n++) {
            *tmpb++ = *tmpa++;
        }

        /* clear high digits */
        for ( ; n < b->used; n++) {
            *tmpb++ = 0;
        }
    }

    /* copy used count and sign */
    b->used = a->used;
    b->sign = a->sign;
    return MP_OKAY;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_COUNT_BITS_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* returns the number of bits in an int */
int
mp_count_bits(mp_int *a) {
    int      r;
    mp_digit q;

    /* shortcut */
    if (a->used == 0) {
        return 0;
    }

    /* get number of digits and add that */
    r = (a->used - 1) * DIGIT_BIT;

    /* take the last digit and count the bits in it */
    q = a->dp[a->used - 1];
    while (q > ((mp_digit)0)) {
        ++r;
        q >>= ((mp_digit)1);
    }
    return r;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_DIV_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

 #ifdef BN_MP_DIV_SMALL

/* slower bit-bang division... also smaller */
int mp_div(mp_int *a, mp_int *b, mp_int *c, mp_int *d) {
    mp_int ta, tb, tq, q;
    int    res, n, n2;

    /* is divisor zero ? */
    if (mp_iszero(b) == MP_YES) {
        return MP_VAL;
    }

    /* if a < b then q=0, r = a */
    if (mp_cmp_mag(a, b) == MP_LT) {
        if (d != NULL) {
            res = mp_copy(a, d);
        } else {
            res = MP_OKAY;
        }
        if (c != NULL) {
            mp_zero(c);
        }
        return res;
    }

    /* init our temps */
    if ((res = mp_init_multi(&ta, &tb, &tq, &q, NULL)) != MP_OKAY) {
        return res;
    }


    mp_set(&tq, 1);
    n = mp_count_bits(a) - mp_count_bits(b);
    if (((res = mp_abs(a, &ta)) != MP_OKAY) ||
        ((res = mp_abs(b, &tb)) != MP_OKAY) ||
        ((res = mp_mul_2d(&tb, n, &tb)) != MP_OKAY) ||
        ((res = mp_mul_2d(&tq, n, &tq)) != MP_OKAY)) {
        goto LBL_ERR;
    }

    while (n-- >= 0) {
        if (mp_cmp(&tb, &ta) != MP_GT) {
            if (((res = mp_sub(&ta, &tb, &ta)) != MP_OKAY) ||
                ((res = mp_add(&q, &tq, &q)) != MP_OKAY)) {
                goto LBL_ERR;
            }
        }
        if (((res = mp_div_2d(&tb, 1, &tb, NULL)) != MP_OKAY) ||
            ((res = mp_div_2d(&tq, 1, &tq, NULL)) != MP_OKAY)) {
            goto LBL_ERR;
        }
    }

    /* now q == quotient and ta == remainder */
    n  = a->sign;
    n2 = (a->sign == b->sign) ? MP_ZPOS : MP_NEG;
    if (c != NULL) {
        mp_exch(c, &q);
        c->sign = (mp_iszero(c) == MP_YES) ? MP_ZPOS : n2;
    }
    if (d != NULL) {
        mp_exch(d, &ta);
        d->sign = (mp_iszero(d) == MP_YES) ? MP_ZPOS : n;
    }
LBL_ERR:
    mp_clear_multi(&ta, &tb, &tq, &q, NULL);
    return res;
}

 #else

/* integer signed division.
 * c*b + d == a [e.g. a/b, c=quotient, d=remainder]
 * HAC pp.598 Algorithm 14.20
 *
 * Note that the description in HAC is horribly
 * incomplete.  For example, it doesn't consider
 * the case where digits are removed from 'x' in
 * the inner loop.  It also doesn't consider the
 * case that y has fewer than three digits, etc..
 *
 * The overall algorithm is as described as
 * 14.20 from HAC but fixed to treat these cases.
 */
int mp_div(mp_int *a, mp_int *b, mp_int *c, mp_int *d) {
    mp_int q, x, y, t1, t2;
    int    res, n, t, i, norm, neg;

    /* is divisor zero ? */
    if (mp_iszero(b) == MP_YES) {
        return MP_VAL;
    }

    /* if a < b then q=0, r = a */
    if (mp_cmp_mag(a, b) == MP_LT) {
        if (d != NULL) {
            res = mp_copy(a, d);
        } else {
            res = MP_OKAY;
        }
        if (c != NULL) {
            mp_zero(c);
        }
        return res;
    }

    if ((res = mp_init_size(&q, a->used + 2)) != MP_OKAY) {
        return res;
    }
    q.used = a->used + 2;

    if ((res = mp_init(&t1)) != MP_OKAY) {
        goto LBL_Q;
    }

    if ((res = mp_init(&t2)) != MP_OKAY) {
        goto LBL_T1;
    }

    if ((res = mp_init_copy(&x, a)) != MP_OKAY) {
        goto LBL_T2;
    }

    if ((res = mp_init_copy(&y, b)) != MP_OKAY) {
        goto LBL_X;
    }

    /* fix the sign */
    neg    = (a->sign == b->sign) ? MP_ZPOS : MP_NEG;
    x.sign = y.sign = MP_ZPOS;

    /* normalize both x and y, ensure that y >= b/2, [b == 2**DIGIT_BIT] */
    norm = mp_count_bits(&y) % DIGIT_BIT;
    if (norm < (int)(DIGIT_BIT - 1)) {
        norm = (DIGIT_BIT - 1) - norm;
        if ((res = mp_mul_2d(&x, norm, &x)) != MP_OKAY) {
            goto LBL_Y;
        }
        if ((res = mp_mul_2d(&y, norm, &y)) != MP_OKAY) {
            goto LBL_Y;
        }
    } else {
        norm = 0;
    }

    /* note hac does 0 based, so if used==5 then its 0,1,2,3,4, e.g. use 4 */
    n = x.used - 1;
    t = y.used - 1;

    /* while (x >= y*b**n-t) do { q[n-t] += 1; x -= y*b**{n-t} } */
    if ((res = mp_lshd(&y, n - t)) != MP_OKAY) { /* y = y*b**{n-t} */
        goto LBL_Y;
    }

    while (mp_cmp(&x, &y) != MP_LT) {
        ++(q.dp[n - t]);
        if ((res = mp_sub(&x, &y, &x)) != MP_OKAY) {
            goto LBL_Y;
        }
    }

    /* reset y by shifting it back down */
    mp_rshd(&y, n - t);

    /* step 3. for i from n down to (t + 1) */
    for (i = n; i >= (t + 1); i--) {
        if (i > x.used) {
            continue;
        }

        /* step 3.1 if xi == yt then set q{i-t-1} to b-1,
        * otherwise set q{i-t-1} to (xi*b + x{i-1})/yt */
        if (x.dp[i] == y.dp[t]) {
            q.dp[(i - t) - 1] = ((((mp_digit)1) << DIGIT_BIT) - 1);
        } else {
            mp_word tmp;
            tmp  = ((mp_word)x.dp[i]) << ((mp_word)DIGIT_BIT);
            tmp |= ((mp_word)x.dp[i - 1]);
            tmp /= ((mp_word)y.dp[t]);
            if (tmp > (mp_word)MP_MASK) {
                tmp = MP_MASK;
            }
            q.dp[(i - t) - 1] = (mp_digit)(tmp & (mp_word)(MP_MASK));
        }

        /* while (q{i-t-1} * (yt * b + y{t-1})) >
                 xi * b**2 + xi-1 * b + xi-2

           do q{i-t-1} -= 1;
         */
        q.dp[(i - t) - 1] = (q.dp[(i - t) - 1] + 1) & MP_MASK;
        do {
            q.dp[(i - t) - 1] = (q.dp[(i - t) - 1] - 1) & MP_MASK;

            /* find left hand */
            mp_zero(&t1);
            t1.dp[0] = ((t - 1) < 0) ? 0 : y.dp[t - 1];
            t1.dp[1] = y.dp[t];
            t1.used  = 2;
            if ((res = mp_mul_d(&t1, q.dp[(i - t) - 1], &t1)) != MP_OKAY) {
                goto LBL_Y;
            }

            /* find right hand */
            t2.dp[0] = ((i - 2) < 0) ? 0 : x.dp[i - 2];
            t2.dp[1] = ((i - 1) < 0) ? 0 : x.dp[i - 1];
            t2.dp[2] = x.dp[i];
            t2.used  = 3;
        } while (mp_cmp_mag(&t1, &t2) == MP_GT);

        /* step 3.3 x = x - q{i-t-1} * y * b**{i-t-1} */
        if ((res = mp_mul_d(&y, q.dp[(i - t) - 1], &t1)) != MP_OKAY) {
            goto LBL_Y;
        }

        if ((res = mp_lshd(&t1, (i - t) - 1)) != MP_OKAY) {
            goto LBL_Y;
        }

        if ((res = mp_sub(&x, &t1, &x)) != MP_OKAY) {
            goto LBL_Y;
        }

        /* if x < 0 then { x = x + y*b**{i-t-1}; q{i-t-1} -= 1; } */
        if (x.sign == MP_NEG) {
            if ((res = mp_copy(&y, &t1)) != MP_OKAY) {
                goto LBL_Y;
            }
            if ((res = mp_lshd(&t1, (i - t) - 1)) != MP_OKAY) {
                goto LBL_Y;
            }
            if ((res = mp_add(&x, &t1, &x)) != MP_OKAY) {
                goto LBL_Y;
            }

            q.dp[(i - t) - 1] = (q.dp[(i - t) - 1] - 1UL) & MP_MASK;
        }
    }

    /* now q is the quotient and x is the remainder
     * [which we have to normalize]
     */

    /* get sign before writing to c */
    x.sign = (x.used == 0) ? MP_ZPOS : a->sign;

    if (c != NULL) {
        mp_clamp(&q);
        mp_exch(&q, c);
        c->sign = neg;
    }

    if (d != NULL) {
        if ((res = mp_div_2d(&x, norm, &x, NULL)) != MP_OKAY) {
            goto LBL_Y;
        }
        mp_exch(&x, d);
    }

    res = MP_OKAY;

LBL_Y: mp_clear(&y);
LBL_X: mp_clear(&x);
LBL_T2: mp_clear(&t2);
LBL_T1: mp_clear(&t1);
LBL_Q: mp_clear(&q);
    return res;
}
 #endif
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_DIV_2_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* b = a/2 */
int mp_div_2(mp_int *a, mp_int *b) {
    int x, res, oldused;

    /* copy */
    if (b->alloc < a->used) {
        if ((res = mp_grow(b, a->used)) != MP_OKAY) {
            return res;
        }
    }

    oldused = b->used;
    b->used = a->used;
    {
        mp_digit r, rr, *tmpa, *tmpb;

        /* source alias */
        tmpa = a->dp + b->used - 1;

        /* dest alias */
        tmpb = b->dp + b->used - 1;

        /* carry */
        r = 0;
        for (x = b->used - 1; x >= 0; x--) {
            /* get the carry for the next iteration */
            rr = *tmpa & 1;

            /* shift the current digit, add in carry and store */
            *tmpb-- = (*tmpa-- >> 1) | (r << (DIGIT_BIT - 1));

            /* forward carry to next iteration */
            r = rr;
        }

        /* zero excess digits */
        tmpb = b->dp + b->used;
        for (x = b->used; x < oldused; x++) {
            *tmpb++ = 0;
        }
    }
    b->sign = a->sign;
    mp_clamp(b);
    return MP_OKAY;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_DIV_2D_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* shift right by a certain bit count (store quotient in c, optional remainder in d) */
int mp_div_2d(mp_int *a, int b, mp_int *c, mp_int *d) {
    mp_digit D, r, rr;
    int      x, res;
    mp_int   t;


    /* if the shift count is <= 0 then we do no work */
    if (b <= 0) {
        res = mp_copy(a, c);
        if (d != NULL) {
            mp_zero(d);
        }
        return res;
    }

    if ((res = mp_init(&t)) != MP_OKAY) {
        return res;
    }

    /* get the remainder */
    if (d != NULL) {
        if ((res = mp_mod_2d(a, b, &t)) != MP_OKAY) {
            mp_clear(&t);
            return res;
        }
    }

    /* copy */
    if ((res = mp_copy(a, c)) != MP_OKAY) {
        mp_clear(&t);
        return res;
    }

    /* shift by as many digits in the bit count */
    if (b >= (int)DIGIT_BIT) {
        mp_rshd(c, b / DIGIT_BIT);
    }

    /* shift any bit count < DIGIT_BIT */
    D = (mp_digit)(b % DIGIT_BIT);
    if (D != 0) {
        mp_digit *tmpc, mask, shift;

        /* mask */
        mask = (((mp_digit)1) << D) - 1;

        /* shift for lsb */
        shift = DIGIT_BIT - D;

        /* alias */
        tmpc = c->dp + (c->used - 1);

        /* carry */
        r = 0;
        for (x = c->used - 1; x >= 0; x--) {
            /* get the lower  bits of this word in a temp */
            rr = *tmpc & mask;

            /* shift the current word and mix in the carry bits from the previous word */
            *tmpc = (*tmpc >> D) | (r << shift);
            --tmpc;

            /* set the carry to the carry bits of the current word found above */
            r = rr;
        }
    }
    mp_clamp(c);
    if (d != NULL) {
        mp_exch(&t, d);
    }
    mp_clear(&t);
    return MP_OKAY;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_DIV_3_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* divide by three (based on routine from MPI and the GMP manual) */
int
mp_div_3(mp_int *a, mp_int *c, mp_digit *d) {
    mp_int   q;
    mp_word  w, t;
    mp_digit b;
    int      res, ix;

    /* b = 2**DIGIT_BIT / 3 */
    b = (((mp_word)1) << ((mp_word)DIGIT_BIT)) / ((mp_word)3);

    if ((res = mp_init_size(&q, a->used)) != MP_OKAY) {
        return res;
    }

    q.used = a->used;
    q.sign = a->sign;
    w      = 0;
    for (ix = a->used - 1; ix >= 0; ix--) {
        w = (w << ((mp_word)DIGIT_BIT)) | ((mp_word)a->dp[ix]);

        if (w >= 3) {
            /* multiply w by [1/3] */
            t = (w * ((mp_word)b)) >> ((mp_word)DIGIT_BIT);

            /* now subtract 3 * [w/3] from w, to get the remainder */
            w -= t + t + t;

            /* fixup the remainder as required since
             * the optimization is not exact.
             */
            while (w >= 3) {
                t += 1;
                w -= 3;
            }
        } else {
            t = 0;
        }
        q.dp[ix] = (mp_digit)t;
    }

    /* [optional] store the remainder */
    if (d != NULL) {
        *d = (mp_digit)w;
    }

    /* [optional] store the quotient */
    if (c != NULL) {
        mp_clamp(&q);
        mp_exch(&q, c);
    }
    mp_clear(&q);

    return res;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_DIV_D_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

static int s_is_power_of_two(mp_digit b, int *p) {
    int x;

    /* fast return if no power of two */
    if ((b == 0) || ((b & (b - 1)) != 0)) {
        return 0;
    }

    for (x = 0; x < DIGIT_BIT; x++) {
        if (b == (((mp_digit)1) << x)) {
            *p = x;
            return 1;
        }
    }
    return 0;
}

/* single digit division (based on routine from MPI) */
int mp_div_d(mp_int *a, mp_digit b, mp_int *c, mp_digit *d) {
    mp_int   q;
    mp_word  w;
    mp_digit t;
    int      res, ix;

    /* cannot divide by zero */
    if (b == 0) {
        return MP_VAL;
    }

    /* quick outs */
    if ((b == 1) || (mp_iszero(a) == MP_YES)) {
        if (d != NULL) {
            *d = 0;
        }
        if (c != NULL) {
            return mp_copy(a, c);
        }
        return MP_OKAY;
    }

    /* power of two ? */
    if (s_is_power_of_two(b, &ix) == 1) {
        if (d != NULL) {
            *d = a->dp[0] & ((((mp_digit)1) << ix) - 1);
        }
        if (c != NULL) {
            return mp_div_2d(a, ix, c, NULL);
        }
        return MP_OKAY;
    }

 #ifdef BN_MP_DIV_3_C
    /* three? */
    if (b == 3) {
        return mp_div_3(a, c, d);
    }
 #endif

    /* no easy answer [c'est la vie].  Just division */
    if ((res = mp_init_size(&q, a->used)) != MP_OKAY) {
        return res;
    }

    q.used = a->used;
    q.sign = a->sign;
    w      = 0;
    for (ix = a->used - 1; ix >= 0; ix--) {
        w = (w << ((mp_word)DIGIT_BIT)) | ((mp_word)a->dp[ix]);

        if (w >= b) {
            t  = (mp_digit)(w / b);
            w -= ((mp_word)t) * ((mp_word)b);
        } else {
            t = 0;
        }
        q.dp[ix] = (mp_digit)t;
    }

    if (d != NULL) {
        *d = (mp_digit)w;
    }

    if (c != NULL) {
        mp_clamp(&q);
        mp_exch(&q, c);
    }
    mp_clear(&q);

    return res;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_DR_IS_MODULUS_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* determines if a number is a valid DR modulus */
int mp_dr_is_modulus(mp_int *a) {
    int ix;

    /* must be at least two digits */
    if (a->used < 2) {
        return 0;
    }

    /* must be of the form b**k - a [a <= b] so all
     * but the first digit must be equal to -1 (mod b).
     */
    for (ix = 1; ix < a->used; ix++) {
        if (a->dp[ix] != MP_MASK) {
            return 0;
        }
    }
    return 1;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_DR_REDUCE_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* reduce "x" in place modulo "n" using the Diminished Radix algorithm.
 *
 * Based on algorithm from the paper
 *
 * "Generating Efficient Primes for Discrete Log Cryptosystems"
 *                 Chae Hoon Lim, Pil Joong Lee,
 *          POSTECH Information Research Laboratories
 *
 * The modulus must be of a special format [see manual]
 *
 * Has been modified to use algorithm 7.10 from the LTM book instead
 *
 * Input x must be in the range 0 <= x <= (n-1)**2
 */
int
mp_dr_reduce(mp_int *x, mp_int *n, mp_digit k) {
    int      err, i, m;
    mp_word  r;
    mp_digit mu, *tmpx1, *tmpx2;

    /* m = digits in modulus */
    m = n->used;

    /* ensure that "x" has at least 2m digits */
    if (x->alloc < (m + m)) {
        if ((err = mp_grow(x, m + m)) != MP_OKAY) {
            return err;
        }
    }

/* top of loop, this is where the code resumes if
 * another reduction pass is required.
 */
top:
    /* aliases for digits */
    /* alias for lower half of x */
    tmpx1 = x->dp;

    /* alias for upper half of x, or x/B**m */
    tmpx2 = x->dp + m;

    /* set carry to zero */
    mu = 0;

    /* compute (x mod B**m) + k * [x/B**m] inline and inplace */
    for (i = 0; i < m; i++) {
        r        = (((mp_word) * tmpx2++) * (mp_word)k) + *tmpx1 + mu;
        *tmpx1++ = (mp_digit)(r & MP_MASK);
        mu       = (mp_digit)(r >> ((mp_word)DIGIT_BIT));
    }

    /* set final carry */
    *tmpx1++ = mu;

    /* zero words above m */
    for (i = m + 1; i < x->used; i++) {
        *tmpx1++ = 0;
    }

    /* clamp, sub and return */
    mp_clamp(x);

    /* if x >= n then subtract and reduce again
     * Each successive "recursion" makes the input smaller and smaller.
     */
    if (mp_cmp_mag(x, n) != MP_LT) {
        if ((err = s_mp_sub(x, n, x)) != MP_OKAY) {
            return err;
        }
        goto top;
    }
    return MP_OKAY;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_DR_SETUP_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* determines the setup value */
void mp_dr_setup(mp_int *a, mp_digit *d) {
    /* the casts are required if DIGIT_BIT is one less than
     * the number of bits in a mp_digit [e.g. DIGIT_BIT==31]
     */
    *d = (mp_digit)((((mp_word)1) << ((mp_word)DIGIT_BIT)) -
                    ((mp_word)a->dp[0]));
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_EXCH_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* swap the elements of two integers, for cases where you can't simply swap the
 * mp_int pointers around
 */
void
mp_exch(mp_int *a, mp_int *b) {
    mp_int t;

    t  = *a;
    *a = *b;
    *b = t;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_EXPORT_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* based on gmp's mpz_export.
 * see http://gmplib.org/manual/Integer-Import-and-Export.html
 */
int mp_export(void *rop, size_t *countp, int order, size_t size,
              int endian, size_t nails, mp_int *op) {
    int           result;
    size_t        odd_nails, nail_bytes, i, j, bits, count;
    unsigned char odd_nail_mask;

    mp_int t;

    if ((result = mp_init_copy(&t, op)) != MP_OKAY) {
        return result;
    }

    if (endian == 0) {
        union {
            unsigned int i;
            char         c[4];
        } lint;
        lint.i = 0x01020304;

        endian = (lint.c[0] == 4) ? -1 : 1;
    }

    odd_nails     = (nails % 8);
    odd_nail_mask = 0xff;
    for (i = 0; i < odd_nails; ++i) {
        odd_nail_mask ^= (1 << (7 - i));
    }
    nail_bytes = nails / 8;

    bits  = mp_count_bits(&t);
    count = (bits / ((size * 8) - nails)) + (((bits % ((size * 8) - nails)) != 0) ? 1 : 0);

    for (i = 0; i < count; ++i) {
        for (j = 0; j < size; ++j) {
            unsigned char *byte = (
                (unsigned char *)rop +
                (((order == -1) ? i : ((count - 1) - i)) * size) +
                ((endian == -1) ? j : ((size - 1) - j))
                );

            if (j >= (size - nail_bytes)) {
                *byte = 0;
                continue;
            }

            *byte = (unsigned char)((j == ((size - nail_bytes) - 1)) ? (t.dp[0] & odd_nail_mask) : (t.dp[0] & 0xFF));

            if ((result = mp_div_2d(&t, ((j == ((size - nail_bytes) - 1)) ? (8 - odd_nails) : 8), &t, NULL)) != MP_OKAY) {
                mp_clear(&t);
                return result;
            }
        }
    }

    mp_clear(&t);

    if (countp != NULL) {
        *countp = count;
    }

    return MP_OKAY;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_EXPT_D_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* wrapper function for mp_expt_d_ex() */
int mp_expt_d(mp_int *a, mp_digit b, mp_int *c) {
    return mp_expt_d_ex(a, b, c, 0);
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_EXPT_D_EX_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* calculate c = a**b  using a square-multiply algorithm */
int mp_expt_d_ex(mp_int *a, mp_digit b, mp_int *c, int fast) {
    int          res;
    unsigned int x;

    mp_int g;

    if ((res = mp_init_copy(&g, a)) != MP_OKAY) {
        return res;
    }

    /* set initial result */
    mp_set(c, 1);

    if (fast != 0) {
        while (b > 0) {
            /* if the bit is set multiply */
            if ((b & 1) != 0) {
                if ((res = mp_mul(c, &g, c)) != MP_OKAY) {
                    mp_clear(&g);
                    return res;
                }
            }

            /* square */
            if (b > 1) {
                if ((res = mp_sqr(&g, &g)) != MP_OKAY) {
                    mp_clear(&g);
                    return res;
                }
            }

            /* shift to next bit */
            b >>= 1;
        }
    } else {
        for (x = 0; x < DIGIT_BIT; x++) {
            /* square */
            if ((res = mp_sqr(c, c)) != MP_OKAY) {
                mp_clear(&g);
                return res;
            }

            /* if the bit is set multiply */
            if ((b & (mp_digit)(((mp_digit)1) << (DIGIT_BIT - 1))) != 0) {
                if ((res = mp_mul(c, &g, c)) != MP_OKAY) {
                    mp_clear(&g);
                    return res;
                }
            }

            /* shift to next bit */
            b <<= 1;
        }
    } /* if ... else */

    mp_clear(&g);
    return MP_OKAY;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_EXPTMOD_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */


/* this is a shell function that calls either the normal or Montgomery
 * exptmod functions.  Originally the call to the montgomery code was
 * embedded in the normal function but that wasted alot of stack space
 * for nothing (since 99% of the time the Montgomery code would be called)
 */
int mp_exptmod(mp_int *G, mp_int *X, mp_int *P, mp_int *Y) {
    int dr;

    /* modulus P must be positive */
    if (P->sign == MP_NEG) {
        return MP_VAL;
    }

    /* if exponent X is negative we have to recurse */
    if (X->sign == MP_NEG) {
 #ifdef BN_MP_INVMOD_C
        mp_int tmpG, tmpX;
        int    err;

        /* first compute 1/G mod P */
        if ((err = mp_init(&tmpG)) != MP_OKAY) {
            return err;
        }
        if ((err = mp_invmod(G, P, &tmpG)) != MP_OKAY) {
            mp_clear(&tmpG);
            return err;
        }

        /* now get |X| */
        if ((err = mp_init(&tmpX)) != MP_OKAY) {
            mp_clear(&tmpG);
            return err;
        }
        if ((err = mp_abs(X, &tmpX)) != MP_OKAY) {
            mp_clear_multi(&tmpG, &tmpX, NULL);
            return err;
        }

        /* and now compute (1/G)**|X| instead of G**X [X < 0] */
        err = mp_exptmod(&tmpG, &tmpX, P, Y);
        mp_clear_multi(&tmpG, &tmpX, NULL);
        return err;
 #else
        /* no invmod */
        return MP_VAL;
 #endif
    }

/* modified diminished radix reduction */
 #if defined(BN_MP_REDUCE_IS_2K_L_C) && defined(BN_MP_REDUCE_2K_L_C) && defined(BN_S_MP_EXPTMOD_C)
    if (mp_reduce_is_2k_l(P) == MP_YES) {
        return s_mp_exptmod(G, X, P, Y, 1);
    }
 #endif

 #ifdef BN_MP_DR_IS_MODULUS_C
    /* is it a DR modulus? */
    dr = mp_dr_is_modulus(P);
 #else
    /* default to no */
    dr = 0;
 #endif

 #ifdef BN_MP_REDUCE_IS_2K_C
    /* if not, is it a unrestricted DR modulus? */
    if (dr == 0) {
        dr = mp_reduce_is_2k(P) << 1;
    }
 #endif

    /* if the modulus is odd or dr != 0 use the montgomery method */
 #ifdef BN_MP_EXPTMOD_FAST_C
    if ((mp_isodd(P) == MP_YES) || (dr != 0)) {
        return mp_exptmod_fast(G, X, P, Y, dr);
    } else {
 #endif
 #ifdef BN_S_MP_EXPTMOD_C
    /* otherwise use the generic Barrett reduction technique */
    return s_mp_exptmod(G, X, P, Y, 0);
 #else
    /* no exptmod for evens */
    return MP_VAL;
 #endif
 #ifdef BN_MP_EXPTMOD_FAST_C
}
 #endif
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_EXPTMOD_FAST_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* computes Y == G**X mod P, HAC pp.616, Algorithm 14.85
 *
 * Uses a left-to-right k-ary sliding window to compute the modular exponentiation.
 * The value of k changes based on the size of the exponent.
 *
 * Uses Montgomery or Diminished Radix reduction [whichever appropriate]
 */

 #ifdef MP_LOW_MEM
  #define TAB_SIZE    32
 #else
  #define TAB_SIZE    256
 #endif

int mp_exptmod_fast(mp_int *G, mp_int *X, mp_int *P, mp_int *Y, int redmode) {
    mp_int   M[TAB_SIZE], res;
    mp_digit buf, mp;
    int      err, bitbuf, bitcpy, bitcnt, mode, digidx, x, y, winsize;

    /* use a pointer to the reduction algorithm.  This allows us to use
     * one of many reduction algorithms without modding the guts of
     * the code with if statements everywhere.
     */
    int (*redux)(mp_int *, mp_int *, mp_digit);

    /* find window size */
    x = mp_count_bits(X);
    if (x <= 7) {
        winsize = 2;
    } else if (x <= 36) {
        winsize = 3;
    } else if (x <= 140) {
        winsize = 4;
    } else if (x <= 450) {
        winsize = 5;
    } else if (x <= 1303) {
        winsize = 6;
    } else if (x <= 3529) {
        winsize = 7;
    } else {
        winsize = 8;
    }

 #ifdef MP_LOW_MEM
    if (winsize > 5) {
        winsize = 5;
    }
 #endif

    /* init M array */
    /* init first cell */
    if ((err = mp_init(&M[1])) != MP_OKAY) {
        return err;
    }

    /* now init the second half of the array */
    for (x = 1 << (winsize - 1); x < (1 << winsize); x++) {
        if ((err = mp_init(&M[x])) != MP_OKAY) {
            for (y = 1 << (winsize - 1); y < x; y++) {
                mp_clear(&M[y]);
            }
            mp_clear(&M[1]);
            return err;
        }
    }

    /* determine and setup reduction code */
    if (redmode == 0) {
 #ifdef BN_MP_MONTGOMERY_SETUP_C
        /* now setup montgomery  */
        if ((err = mp_montgomery_setup(P, &mp)) != MP_OKAY) {
            goto LBL_M;
        }
 #else
        err = MP_VAL;
        goto LBL_M;
 #endif

        /* automatically pick the comba one if available (saves quite a few calls/ifs) */
 #ifdef BN_FAST_MP_MONTGOMERY_REDUCE_C
        if ((((P->used * 2) + 1) < MP_WARRAY) &&
            (P->used < (1 << ((CHAR_BIT * sizeof(mp_word)) - (2 * DIGIT_BIT))))) {
            redux = fast_mp_montgomery_reduce;
        } else
 #endif
        {
 #ifdef BN_MP_MONTGOMERY_REDUCE_C
            /* use slower baseline Montgomery method */
            redux = mp_montgomery_reduce;
 #else
            err = MP_VAL;
            goto LBL_M;
 #endif
        }
    } else if (redmode == 1) {
 #if defined(BN_MP_DR_SETUP_C) && defined(BN_MP_DR_REDUCE_C)
        /* setup DR reduction for moduli of the form B**k - b */
        mp_dr_setup(P, &mp);
        redux = mp_dr_reduce;
 #else
        err = MP_VAL;
        goto LBL_M;
 #endif
    } else {
 #if defined(BN_MP_REDUCE_2K_SETUP_C) && defined(BN_MP_REDUCE_2K_C)
        /* setup DR reduction for moduli of the form 2**k - b */
        if ((err = mp_reduce_2k_setup(P, &mp)) != MP_OKAY) {
            goto LBL_M;
        }
        redux = mp_reduce_2k;
 #else
        err = MP_VAL;
        goto LBL_M;
 #endif
    }

    /* setup result */
    if ((err = mp_init(&res)) != MP_OKAY) {
        goto LBL_M;
    }

    /* create M table
     *

     *
     * The first half of the table is not computed though accept for M[0] and M[1]
     */

    if (redmode == 0) {
 #ifdef BN_MP_MONTGOMERY_CALC_NORMALIZATION_C
        /* now we need R mod m */
        if ((err = mp_montgomery_calc_normalization(&res, P)) != MP_OKAY) {
            goto LBL_RES;
        }
 #else
        err = MP_VAL;
        goto LBL_RES;
 #endif

        /* now set M[1] to G * R mod m */
        if ((err = mp_mulmod(G, &res, P, &M[1])) != MP_OKAY) {
            goto LBL_RES;
        }
    } else {
        mp_set(&res, 1);
        if ((err = mp_mod(G, P, &M[1])) != MP_OKAY) {
            goto LBL_RES;
        }
    }

    /* compute the value at M[1<<(winsize-1)] by squaring M[1] (winsize-1) times */
    if ((err = mp_copy(&M[1], &M[1 << (winsize - 1)])) != MP_OKAY) {
        goto LBL_RES;
    }

    for (x = 0; x < (winsize - 1); x++) {
        if ((err = mp_sqr(&M[1 << (winsize - 1)], &M[1 << (winsize - 1)])) != MP_OKAY) {
            goto LBL_RES;
        }
        if ((err = redux(&M[1 << (winsize - 1)], P, mp)) != MP_OKAY) {
            goto LBL_RES;
        }
    }

    /* create upper table */
    for (x = (1 << (winsize - 1)) + 1; x < (1 << winsize); x++) {
        if ((err = mp_mul(&M[x - 1], &M[1], &M[x])) != MP_OKAY) {
            goto LBL_RES;
        }
        if ((err = redux(&M[x], P, mp)) != MP_OKAY) {
            goto LBL_RES;
        }
    }

    /* set initial mode and bit cnt */
    mode   = 0;
    bitcnt = 1;
    buf    = 0;
    digidx = X->used - 1;
    bitcpy = 0;
    bitbuf = 0;

    for ( ; ; ) {
        /* grab next digit as required */
        if (--bitcnt == 0) {
            /* if digidx == -1 we are out of digits so break */
            if (digidx == -1) {
                break;
            }
            /* read next digit and reset bitcnt */
            buf    = X->dp[digidx--];
            bitcnt = (int)DIGIT_BIT;
        }

        /* grab the next msb from the exponent */
        y     = (mp_digit)(buf >> (DIGIT_BIT - 1)) & 1;
        buf <<= (mp_digit)1;

        /* if the bit is zero and mode == 0 then we ignore it
         * These represent the leading zero bits before the first 1 bit
         * in the exponent.  Technically this opt is not required but it
         * does lower the # of trivial squaring/reductions used
         */
        if ((mode == 0) && (y == 0)) {
            continue;
        }

        /* if the bit is zero and mode == 1 then we square */
        if ((mode == 1) && (y == 0)) {
            if ((err = mp_sqr(&res, &res)) != MP_OKAY) {
                goto LBL_RES;
            }
            if ((err = redux(&res, P, mp)) != MP_OKAY) {
                goto LBL_RES;
            }
            continue;
        }

        /* else we add it to the window */
        bitbuf |= (y << (winsize - ++bitcpy));
        mode    = 2;

        if (bitcpy == winsize) {
            /* ok window is filled so square as required and multiply  */
            /* square first */
            for (x = 0; x < winsize; x++) {
                if ((err = mp_sqr(&res, &res)) != MP_OKAY) {
                    goto LBL_RES;
                }
                if ((err = redux(&res, P, mp)) != MP_OKAY) {
                    goto LBL_RES;
                }
            }

            /* then multiply */
            if ((err = mp_mul(&res, &M[bitbuf], &res)) != MP_OKAY) {
                goto LBL_RES;
            }
            if ((err = redux(&res, P, mp)) != MP_OKAY) {
                goto LBL_RES;
            }

            /* empty window and reset */
            bitcpy = 0;
            bitbuf = 0;
            mode   = 1;
        }
    }

    /* if bits remain then square/multiply */
    if ((mode == 2) && (bitcpy > 0)) {
        /* square then multiply if the bit is set */
        for (x = 0; x < bitcpy; x++) {
            if ((err = mp_sqr(&res, &res)) != MP_OKAY) {
                goto LBL_RES;
            }
            if ((err = redux(&res, P, mp)) != MP_OKAY) {
                goto LBL_RES;
            }

            /* get next bit of the window */
            bitbuf <<= 1;
            if ((bitbuf & (1 << winsize)) != 0) {
                /* then multiply */
                if ((err = mp_mul(&res, &M[1], &res)) != MP_OKAY) {
                    goto LBL_RES;
                }
                if ((err = redux(&res, P, mp)) != MP_OKAY) {
                    goto LBL_RES;
                }
            }
        }
    }

    if (redmode == 0) {
        /* fixup result if Montgomery reduction is used
         * recall that any value in a Montgomery system is
         * actually multiplied by R mod n.  So we have
         * to reduce one more time to cancel out the factor
         * of R.
         */
        if ((err = redux(&res, P, mp)) != MP_OKAY) {
            goto LBL_RES;
        }
    }

    /* swap res with Y */
    mp_exch(&res, Y);
    err = MP_OKAY;
LBL_RES: mp_clear(&res);
LBL_M:
    mp_clear(&M[1]);
    for (x = 1 << (winsize - 1); x < (1 << winsize); x++) {
        mp_clear(&M[x]);
    }
    return err;
}
#endif


/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_EXTEUCLID_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* Extended euclidean algorithm of (a, b) produces
   a*u1 + b*u2 = u3
 */
int mp_exteuclid(mp_int *a, mp_int *b, mp_int *U1, mp_int *U2, mp_int *U3) {
    mp_int u1, u2, u3, v1, v2, v3, t1, t2, t3, q, tmp;
    int    err;

    if ((err = mp_init_multi(&u1, &u2, &u3, &v1, &v2, &v3, &t1, &t2, &t3, &q, &tmp, NULL)) != MP_OKAY) {
        return err;
    }

    /* initialize, (u1,u2,u3) = (1,0,a) */
    mp_set(&u1, 1);
    if ((err = mp_copy(a, &u3)) != MP_OKAY) {
        goto _ERR;
    }

    /* initialize, (v1,v2,v3) = (0,1,b) */
    mp_set(&v2, 1);
    if ((err = mp_copy(b, &v3)) != MP_OKAY) {
        goto _ERR;
    }

    /* loop while v3 != 0 */
    while (mp_iszero(&v3) == MP_NO) {
        /* q = u3/v3 */
        if ((err = mp_div(&u3, &v3, &q, NULL)) != MP_OKAY) {
            goto _ERR;
        }

        /* (t1,t2,t3) = (u1,u2,u3) - (v1,v2,v3)q */
        if ((err = mp_mul(&v1, &q, &tmp)) != MP_OKAY) {
            goto _ERR;
        }
        if ((err = mp_sub(&u1, &tmp, &t1)) != MP_OKAY) {
            goto _ERR;
        }
        if ((err = mp_mul(&v2, &q, &tmp)) != MP_OKAY) {
            goto _ERR;
        }
        if ((err = mp_sub(&u2, &tmp, &t2)) != MP_OKAY) {
            goto _ERR;
        }
        if ((err = mp_mul(&v3, &q, &tmp)) != MP_OKAY) {
            goto _ERR;
        }
        if ((err = mp_sub(&u3, &tmp, &t3)) != MP_OKAY) {
            goto _ERR;
        }

        /* (u1,u2,u3) = (v1,v2,v3) */
        if ((err = mp_copy(&v1, &u1)) != MP_OKAY) {
            goto _ERR;
        }
        if ((err = mp_copy(&v2, &u2)) != MP_OKAY) {
            goto _ERR;
        }
        if ((err = mp_copy(&v3, &u3)) != MP_OKAY) {
            goto _ERR;
        }

        /* (v1,v2,v3) = (t1,t2,t3) */
        if ((err = mp_copy(&t1, &v1)) != MP_OKAY) {
            goto _ERR;
        }
        if ((err = mp_copy(&t2, &v2)) != MP_OKAY) {
            goto _ERR;
        }
        if ((err = mp_copy(&t3, &v3)) != MP_OKAY) {
            goto _ERR;
        }
    }

    /* make sure U3 >= 0 */
    if (u3.sign == MP_NEG) {
        if ((err = mp_neg(&u1, &u1)) != MP_OKAY) {
            goto _ERR;
        }
        if ((err = mp_neg(&u2, &u2)) != MP_OKAY) {
            goto _ERR;
        }
        if ((err = mp_neg(&u3, &u3)) != MP_OKAY) {
            goto _ERR;
        }
    }

    /* copy result out */
    if (U1 != NULL) {
        mp_exch(U1, &u1);
    }
    if (U2 != NULL) {
        mp_exch(U2, &u2);
    }
    if (U3 != NULL) {
        mp_exch(U3, &u3);
    }

    err = MP_OKAY;
_ERR: mp_clear_multi(&u1, &u2, &u3, &v1, &v2, &v3, &t1, &t2, &t3, &q, &tmp, NULL);
    return err;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_FREAD_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* read a bigint from a file stream in ASCII */
int mp_fread(mp_int *a, int radix, FILE *stream) {
    int err, ch, neg, y;

    /* clear a */
    mp_zero(a);

    /* if first digit is - then set negative */
    ch = fgetc(stream);
    if (ch == '-') {
        neg = MP_NEG;
        ch  = fgetc(stream);
    } else {
        neg = MP_ZPOS;
    }

    for ( ; ; ) {
        /* find y in the radix map */
        for (y = 0; y < radix; y++) {
            if (mp_s_rmap[y] == ch) {
                break;
            }
        }
        if (y == radix) {
            break;
        }

        /* shift up and add */
        if ((err = mp_mul_d(a, radix, a)) != MP_OKAY) {
            return err;
        }
        if ((err = mp_add_d(a, y, a)) != MP_OKAY) {
            return err;
        }

        ch = fgetc(stream);
    }
    if (mp_cmp_d(a, 0) != MP_EQ) {
        a->sign = neg;
    }

    return MP_OKAY;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_FWRITE_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

int mp_fwrite(mp_int *a, int radix, FILE *stream) {
    char *buf;
    int  err, len, x;

    if ((err = mp_radix_size(a, radix, &len)) != MP_OKAY) {
        return err;
    }

    buf = OPT_CAST(char) XMALLOC(len);
    if (buf == NULL) {
        return MP_MEM;
    }

    if ((err = mp_toradix(a, buf, radix)) != MP_OKAY) {
        XFREE(buf);
        return err;
    }

    for (x = 0; x < len; x++) {
        if (fputc(buf[x], stream) == EOF) {
            XFREE(buf);
            return MP_VAL;
        }
    }

    XFREE(buf);
    return MP_OKAY;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_GCD_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* Greatest Common Divisor using the binary method */
int mp_gcd(mp_int *a, mp_int *b, mp_int *c) {
    mp_int u, v;
    int    k, u_lsb, v_lsb, res;

    /* either zero than gcd is the largest */
    if (mp_iszero(a) == MP_YES) {
        return mp_abs(b, c);
    }
    if (mp_iszero(b) == MP_YES) {
        return mp_abs(a, c);
    }

    /* get copies of a and b we can modify */
    if ((res = mp_init_copy(&u, a)) != MP_OKAY) {
        return res;
    }

    if ((res = mp_init_copy(&v, b)) != MP_OKAY) {
        goto LBL_U;
    }

    /* must be positive for the remainder of the algorithm */
    u.sign = v.sign = MP_ZPOS;

    /* B1.  Find the common power of two for u and v */
    u_lsb = mp_cnt_lsb(&u);
    v_lsb = mp_cnt_lsb(&v);
    k     = MIN(u_lsb, v_lsb);

    if (k > 0) {
        /* divide the power of two out */
        if ((res = mp_div_2d(&u, k, &u, NULL)) != MP_OKAY) {
            goto LBL_V;
        }

        if ((res = mp_div_2d(&v, k, &v, NULL)) != MP_OKAY) {
            goto LBL_V;
        }
    }

    /* divide any remaining factors of two out */
    if (u_lsb != k) {
        if ((res = mp_div_2d(&u, u_lsb - k, &u, NULL)) != MP_OKAY) {
            goto LBL_V;
        }
    }

    if (v_lsb != k) {
        if ((res = mp_div_2d(&v, v_lsb - k, &v, NULL)) != MP_OKAY) {
            goto LBL_V;
        }
    }

    while (mp_iszero(&v) == MP_NO) {
        /* make sure v is the largest */
        if (mp_cmp_mag(&u, &v) == MP_GT) {
            /* swap u and v to make sure v is >= u */
            mp_exch(&u, &v);
        }

        /* subtract smallest from largest */
        if ((res = s_mp_sub(&v, &u, &v)) != MP_OKAY) {
            goto LBL_V;
        }

        /* Divide out all factors of two */
        if ((res = mp_div_2d(&v, mp_cnt_lsb(&v), &v, NULL)) != MP_OKAY) {
            goto LBL_V;
        }
    }

    /* multiply by 2**k which we divided out at the beginning */
    if ((res = mp_mul_2d(&u, k, c)) != MP_OKAY) {
        goto LBL_V;
    }
    c->sign = MP_ZPOS;
    res     = MP_OKAY;
LBL_V: mp_clear(&u);
LBL_U: mp_clear(&v);
    return res;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_GET_INT_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* get the lower 32-bits of an mp_int */
unsigned long mp_get_int(mp_int *a) {
    int        i;
    mp_min_u32 res;

    if (a->used == 0) {
        return 0;
    }

    /* get number of digits of the lsb we have to read */
    i = MIN(a->used, (int)(((sizeof(unsigned long) * CHAR_BIT) + DIGIT_BIT - 1) / DIGIT_BIT)) - 1;

    /* get most significant digit of result */
    res = DIGIT(a, i);

    while (--i >= 0) {
        res = (res << DIGIT_BIT) | DIGIT(a, i);
    }

    /* force result to 32-bits always so it is consistent on non 32-bit platforms */
    return res & 0xFFFFFFFFUL;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_GET_LONG_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* get the lower unsigned long of an mp_int, platform dependent */
unsigned long mp_get_long(mp_int *a) {
    int           i;
    unsigned long res;

    if (a->used == 0) {
        return 0;
    }

    /* get number of digits of the lsb we have to read */
    i = MIN(a->used, (int)(((sizeof(unsigned long) * CHAR_BIT) + DIGIT_BIT - 1) / DIGIT_BIT)) - 1;

    /* get most significant digit of result */
    res = DIGIT(a, i);

 #if (ULONG_MAX != 0xffffffffuL) || (DIGIT_BIT < 32)
    while (--i >= 0) {
        res = (res << DIGIT_BIT) | DIGIT(a, i);
    }
 #endif
    return res;
}
#endif



#ifdef BN_MP_GET_LONG_LONG_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* get the lower unsigned long long of an mp_int, platform dependent */
unsigned long long mp_get_long_long(mp_int *a) {
    int i;
    unsigned long long res;

    if (a->used == 0) {
        return 0;
    }

    /* get number of digits of the lsb we have to read */
    i = MIN(a->used, (int)(((sizeof(unsigned long long) * CHAR_BIT) + DIGIT_BIT - 1) / DIGIT_BIT)) - 1;

    /* get most significant digit of result */
    res = DIGIT(a, i);

 #if DIGIT_BIT < 64
    while (--i >= 0) {
        res = (res << DIGIT_BIT) | DIGIT(a, i);
    }
 #endif
    return res;
}
#endif



#ifdef BN_MP_GROW_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* grow as required */
int mp_grow(mp_int *a, int size) {
    int      i;
    mp_digit *tmp;

    /* if the alloc size is smaller alloc more ram */
    if (a->alloc < size) {
        /* ensure there are always at least MP_PREC digits extra on top */
        size += (MP_PREC * 2) - (size % MP_PREC);

        /* reallocate the array a->dp
         *
         * We store the return in a temporary variable
         * in case the operation failed we don't want
         * to overwrite the dp member of a.
         */
        tmp = OPT_CAST(mp_digit) XREALLOC(a->dp, sizeof(mp_digit) * size);
        if (tmp == NULL) {
            /* reallocation failed but "a" is still valid [can be freed] */
            return MP_MEM;
        }

        /* reallocation succeeded so set a->dp */
        a->dp = tmp;

        /* zero excess digits */
        i        = a->alloc;
        a->alloc = size;
        for ( ; i < a->alloc; i++) {
            a->dp[i] = 0;
        }
    }
    return MP_OKAY;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_IMPORT_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* based on gmp's mpz_import.
 * see http://gmplib.org/manual/Integer-Import-and-Export.html
 */
int mp_import(mp_int *rop, size_t count, int order, size_t size,
              int endian, size_t nails, const void *op) {
    int           result;
    size_t        odd_nails, nail_bytes, i, j;
    unsigned char odd_nail_mask;

    mp_zero(rop);

    if (endian == 0) {
        union {
            unsigned int i;
            char         c[4];
        } lint;
        lint.i = 0x01020304;

        endian = (lint.c[0] == 4) ? -1 : 1;
    }

    odd_nails     = (nails % 8);
    odd_nail_mask = 0xff;
    for (i = 0; i < odd_nails; ++i) {
        odd_nail_mask ^= (1 << (7 - i));
    }
    nail_bytes = nails / 8;

    for (i = 0; i < count; ++i) {
        for (j = 0; j < (size - nail_bytes); ++j) {
            unsigned char byte = *(
                (unsigned char *)op +
                (((order == 1) ? i : ((count - 1) - i)) * size) +
                ((endian == 1) ? (j + nail_bytes) : (((size - 1) - j) - nail_bytes))
                );

            if (
                (result = mp_mul_2d(rop, ((j == 0) ? (8 - odd_nails) : 8), rop)) != MP_OKAY) {
                return result;
            }

            rop->dp[0] |= (j == 0) ? (byte & odd_nail_mask) : byte;
            rop->used  += 1;
        }
    }

    mp_clamp(rop);

    return MP_OKAY;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_INIT_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* init a new mp_int */
int mp_init(mp_int *a) {
    int i;

    /* allocate memory required and clear it */
    a->dp = OPT_CAST(mp_digit) XMALLOC(sizeof(mp_digit) * MP_PREC);
    if (a->dp == NULL) {
        return MP_MEM;
    }

    /* set the digits to zero */
    for (i = 0; i < MP_PREC; i++) {
        a->dp[i] = 0;
    }

    /* set the used to zero, allocated digits to the default precision
     * and sign to positive */
    a->used  = 0;
    a->alloc = MP_PREC;
    a->sign  = MP_ZPOS;

    return MP_OKAY;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_INIT_COPY_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* creates "a" then copies b into it */
int mp_init_copy(mp_int *a, mp_int *b) {
    int res;

    if ((res = mp_init_size(a, b->used)) != MP_OKAY) {
        return res;
    }
    return mp_copy(b, a);
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_INIT_MULTI_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */
#include <stdarg.h>

int mp_init_multi(mp_int *mp, ...) {
    mp_err  res      = MP_OKAY; /* Assume ok until proven otherwise */
    int     n        = 0;       /* Number of ok inits */
    mp_int  *cur_arg = mp;
    va_list args;

    va_start(args, mp);        /* init args to next argument from caller */
    while (cur_arg != NULL) {
        if (mp_init(cur_arg) != MP_OKAY) {
            /* Oops - error! Back-track and mp_clear what we already
               succeeded in init-ing, then return error.
             */
            va_list clean_args;

            /* end the current list */
            va_end(args);

            /* now start cleaning up */
            cur_arg = mp;
            va_start(clean_args, mp);
            while (n-- != 0) {
                mp_clear(cur_arg);
                cur_arg = va_arg(clean_args, mp_int *);
            }
            va_end(clean_args);
            res = MP_MEM;
            break;
        }
        n++;
        cur_arg = va_arg(args, mp_int *);
    }
    va_end(args);
    return res;                /* Assumed ok, if error flagged above. */
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_INIT_SET_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* initialize and set a digit */
int mp_init_set(mp_int *a, mp_digit b) {
    int err;

    if ((err = mp_init(a)) != MP_OKAY) {
        return err;
    }
    mp_set(a, b);
    return err;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_INIT_SET_INT_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* initialize and set a digit */
int mp_init_set_int(mp_int *a, unsigned long b) {
    int err;

    if ((err = mp_init(a)) != MP_OKAY) {
        return err;
    }
    return mp_set_int(a, b);
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_INIT_SIZE_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* init an mp_init for a given size */
int mp_init_size(mp_int *a, int size) {
    int x;

    /* pad size so there are always extra digits */
    size += (MP_PREC * 2) - (size % MP_PREC);

    /* alloc mem */
    a->dp = OPT_CAST(mp_digit) XMALLOC(sizeof(mp_digit) * size);
    if (a->dp == NULL) {
        return MP_MEM;
    }

    /* set the members */
    a->used  = 0;
    a->alloc = size;
    a->sign  = MP_ZPOS;

    /* zero the digits */
    for (x = 0; x < size; x++) {
        a->dp[x] = 0;
    }

    return MP_OKAY;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_INVMOD_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* hac 14.61, pp608 */
int mp_invmod(mp_int *a, mp_int *b, mp_int *c) {
    /* b cannot be negative */
    if ((b->sign == MP_NEG) || (mp_iszero(b) == MP_YES)) {
        return MP_VAL;
    }

 #ifdef BN_FAST_MP_INVMOD_C
    /* if the modulus is odd we can use a faster routine instead */
    if (mp_isodd(b) == MP_YES) {
        return fast_mp_invmod(a, b, c);
    }
 #endif

 #ifdef BN_MP_INVMOD_SLOW_C
    return mp_invmod_slow(a, b, c);
 #else
    return MP_VAL;
 #endif
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_INVMOD_SLOW_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* hac 14.61, pp608 */
int mp_invmod_slow(mp_int *a, mp_int *b, mp_int *c) {
    mp_int x, y, u, v, A, B, C, D;
    int    res;

    /* b cannot be negative */
    if ((b->sign == MP_NEG) || (mp_iszero(b) == MP_YES)) {
        return MP_VAL;
    }

    /* init temps */
    if ((res = mp_init_multi(&x, &y, &u, &v,
                             &A, &B, &C, &D, NULL)) != MP_OKAY) {
        return res;
    }

    /* x = a, y = b */
    if ((res = mp_mod(a, b, &x)) != MP_OKAY) {
        goto LBL_ERR;
    }
    if ((res = mp_copy(b, &y)) != MP_OKAY) {
        goto LBL_ERR;
    }

    /* 2. [modified] if x,y are both even then return an error! */
    if ((mp_iseven(&x) == MP_YES) && (mp_iseven(&y) == MP_YES)) {
        res = MP_VAL;
        goto LBL_ERR;
    }

    /* 3. u=x, v=y, A=1, B=0, C=0,D=1 */
    if ((res = mp_copy(&x, &u)) != MP_OKAY) {
        goto LBL_ERR;
    }
    if ((res = mp_copy(&y, &v)) != MP_OKAY) {
        goto LBL_ERR;
    }
    mp_set(&A, 1);
    mp_set(&D, 1);

top:
    /* 4.  while u is even do */
    while (mp_iseven(&u) == MP_YES) {
        /* 4.1 u = u/2 */
        if ((res = mp_div_2(&u, &u)) != MP_OKAY) {
            goto LBL_ERR;
        }
        /* 4.2 if A or B is odd then */
        if ((mp_isodd(&A) == MP_YES) || (mp_isodd(&B) == MP_YES)) {
            /* A = (A+y)/2, B = (B-x)/2 */
            if ((res = mp_add(&A, &y, &A)) != MP_OKAY) {
                goto LBL_ERR;
            }
            if ((res = mp_sub(&B, &x, &B)) != MP_OKAY) {
                goto LBL_ERR;
            }
        }
        /* A = A/2, B = B/2 */
        if ((res = mp_div_2(&A, &A)) != MP_OKAY) {
            goto LBL_ERR;
        }
        if ((res = mp_div_2(&B, &B)) != MP_OKAY) {
            goto LBL_ERR;
        }
    }

    /* 5.  while v is even do */
    while (mp_iseven(&v) == MP_YES) {
        /* 5.1 v = v/2 */
        if ((res = mp_div_2(&v, &v)) != MP_OKAY) {
            goto LBL_ERR;
        }
        /* 5.2 if C or D is odd then */
        if ((mp_isodd(&C) == MP_YES) || (mp_isodd(&D) == MP_YES)) {
            /* C = (C+y)/2, D = (D-x)/2 */
            if ((res = mp_add(&C, &y, &C)) != MP_OKAY) {
                goto LBL_ERR;
            }
            if ((res = mp_sub(&D, &x, &D)) != MP_OKAY) {
                goto LBL_ERR;
            }
        }
        /* C = C/2, D = D/2 */
        if ((res = mp_div_2(&C, &C)) != MP_OKAY) {
            goto LBL_ERR;
        }
        if ((res = mp_div_2(&D, &D)) != MP_OKAY) {
            goto LBL_ERR;
        }
    }

    /* 6.  if u >= v then */
    if (mp_cmp(&u, &v) != MP_LT) {
        /* u = u - v, A = A - C, B = B - D */
        if ((res = mp_sub(&u, &v, &u)) != MP_OKAY) {
            goto LBL_ERR;
        }

        if ((res = mp_sub(&A, &C, &A)) != MP_OKAY) {
            goto LBL_ERR;
        }

        if ((res = mp_sub(&B, &D, &B)) != MP_OKAY) {
            goto LBL_ERR;
        }
    } else {
        /* v - v - u, C = C - A, D = D - B */
        if ((res = mp_sub(&v, &u, &v)) != MP_OKAY) {
            goto LBL_ERR;
        }

        if ((res = mp_sub(&C, &A, &C)) != MP_OKAY) {
            goto LBL_ERR;
        }

        if ((res = mp_sub(&D, &B, &D)) != MP_OKAY) {
            goto LBL_ERR;
        }
    }

    /* if not zero goto step 4 */
    if (mp_iszero(&u) == MP_NO)
        goto top;

    /* now a = C, b = D, gcd == g*v */

    /* if v != 1 then there is no inverse */
    if (mp_cmp_d(&v, 1) != MP_EQ) {
        res = MP_VAL;
        goto LBL_ERR;
    }

    /* if its too low */
    while (mp_cmp_d(&C, 0) == MP_LT) {
        if ((res = mp_add(&C, b, &C)) != MP_OKAY) {
            goto LBL_ERR;
        }
    }

    /* too big */
    while (mp_cmp_mag(&C, b) != MP_LT) {
        if ((res = mp_sub(&C, b, &C)) != MP_OKAY) {
            goto LBL_ERR;
        }
    }

    /* C is now the inverse */
    mp_exch(&C, c);
    res = MP_OKAY;
LBL_ERR: mp_clear_multi(&x, &y, &u, &v, &A, &B, &C, &D, NULL);
    return res;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_IS_SQUARE_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* Check if remainders are possible squares - fast exclude non-squares */
static const char rem_128[128] = {
    0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1,
    0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1,
    1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1,
    1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1,
    0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1,
    1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1,
    1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1,
    1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1
};

static const char rem_105[105] = {
    0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1,
    0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1,
    0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1,
    1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1,
    0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1,
    1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1,
    1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1
};

/* Store non-zero to ret if arg is square, and zero if not */
int mp_is_square(mp_int *arg, int *ret) {
    int           res;
    mp_digit      c;
    mp_int        t;
    unsigned long r;

    /* Default to Non-square :) */
    *ret = MP_NO;

    if (arg->sign == MP_NEG) {
        return MP_VAL;
    }

    /* digits used?  (TSD) */
    if (arg->used == 0) {
        return MP_OKAY;
    }

    /* First check mod 128 (suppose that DIGIT_BIT is at least 7) */
    if (rem_128[127 & DIGIT(arg, 0)] == 1) {
        return MP_OKAY;
    }

    /* Next check mod 105 (3*5*7) */
    if ((res = mp_mod_d(arg, 105, &c)) != MP_OKAY) {
        return res;
    }
    if (rem_105[c] == 1) {
        return MP_OKAY;
    }


    if ((res = mp_init_set_int(&t, 11L * 13L * 17L * 19L * 23L * 29L * 31L)) != MP_OKAY) {
        return res;
    }
    if ((res = mp_mod(arg, &t, &t)) != MP_OKAY) {
        goto ERR;
    }
    r = mp_get_int(&t);

    /* Check for other prime modules, note it's not an ERROR but we must
     * free "t" so the easiest way is to goto ERR.  We know that res
     * is already equal to MP_OKAY from the mp_mod call
     */
    if (((1L << (r % 11)) & 0x5C4L) != 0L) goto ERR;
    if (((1L << (r % 13)) & 0x9E4L) != 0L) goto ERR;
    if (((1L << (r % 17)) & 0x5CE8L) != 0L) goto ERR;
    if (((1L << (r % 19)) & 0x4F50CL) != 0L) goto ERR;
    if (((1L << (r % 23)) & 0x7ACCA0L) != 0L) goto ERR;
    if (((1L << (r % 29)) & 0xC2EDD0CL) != 0L) goto ERR;
    if (((1L << (r % 31)) & 0x6DE2B848L) != 0L) goto ERR;

    /* Final check - is sqr(sqrt(arg)) == arg ? */
    if ((res = mp_sqrt(arg, &t)) != MP_OKAY) {
        goto ERR;
    }
    if ((res = mp_sqr(&t, &t)) != MP_OKAY) {
        goto ERR;
    }

    *ret = (mp_cmp_mag(&t, arg) == MP_EQ) ? MP_YES : MP_NO;
ERR: mp_clear(&t);
    return res;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_JACOBI_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* computes the jacobi c = (a | n) (or Legendre if n is prime)
 * HAC pp. 73 Algorithm 2.149
 * HAC is wrong here, as the special case of (0 | 1) is not
 * handled correctly.
 */
int mp_jacobi(mp_int *a, mp_int *n, int *c) {
    mp_int   a1, p1;
    int      k, s, r, res;
    mp_digit residue;

    /* if n <= 0 return MP_VAL */
    if (mp_cmp_d(n, 0) != MP_GT) {
        return MP_VAL;
    }

    /* step 1. handle case of a == 0 */
    if (mp_iszero(a) == MP_YES) {
        /* special case of a == 0 and n == 1 */
        if (mp_cmp_d(n, 1) == MP_EQ) {
            *c = 1;
        } else {
            *c = 0;
        }
        return MP_OKAY;
    }

    /* step 2.  if a == 1, return 1 */
    if (mp_cmp_d(a, 1) == MP_EQ) {
        *c = 1;
        return MP_OKAY;
    }

    /* default */
    s = 0;

    /* step 3.  write a = a1 * 2**k  */
    if ((res = mp_init_copy(&a1, a)) != MP_OKAY) {
        return res;
    }

    if ((res = mp_init(&p1)) != MP_OKAY) {
        goto LBL_A1;
    }

    /* divide out larger power of two */
    k = mp_cnt_lsb(&a1);
    if ((res = mp_div_2d(&a1, k, &a1, NULL)) != MP_OKAY) {
        goto LBL_P1;
    }

    /* step 4.  if e is even set s=1 */
    if ((k & 1) == 0) {
        s = 1;
    } else {
        /* else set s=1 if p = 1/7 (mod 8) or s=-1 if p = 3/5 (mod 8) */
        residue = n->dp[0] & 7;

        if ((residue == 1) || (residue == 7)) {
            s = 1;
        } else if ((residue == 3) || (residue == 5)) {
            s = -1;
        }
    }

    /* step 5.  if p == 3 (mod 4) *and* a1 == 3 (mod 4) then s = -s */
    if (((n->dp[0] & 3) == 3) && ((a1.dp[0] & 3) == 3)) {
        s = -s;
    }

    /* if a1 == 1 we're done */
    if (mp_cmp_d(&a1, 1) == MP_EQ) {
        *c = s;
    } else {
        /* n1 = n mod a1 */
        if ((res = mp_mod(n, &a1, &p1)) != MP_OKAY) {
            goto LBL_P1;
        }
        if ((res = mp_jacobi(&p1, &a1, &r)) != MP_OKAY) {
            goto LBL_P1;
        }
        *c = s * r;
    }

    /* done */
    res = MP_OKAY;
LBL_P1: mp_clear(&p1);
LBL_A1: mp_clear(&a1);
    return res;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_KARATSUBA_MUL_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* c = |a| * |b| using Karatsuba Multiplication using
 * three half size multiplications
 *
 * Let B represent the radix [e.g. 2**DIGIT_BIT] and
 * let n represent half of the number of digits in
 * the min(a,b)
 *
 * a = a1 * B**n + a0
 * b = b1 * B**n + b0
 *
 * Then, a * b =>
   a1b1 * B**2n + ((a1 + a0)(b1 + b0) - (a0b0 + a1b1)) * B + a0b0
 *
 * Note that a1b1 and a0b0 are used twice and only need to be
 * computed once.  So in total three half size (half # of
 * digit) multiplications are performed, a0b0, a1b1 and
 * (a1+b1)(a0+b0)
 *
 * Note that a multiplication of half the digits requires
 * 1/4th the number of single precision multiplications so in
 * total after one call 25% of the single precision multiplications
 * are saved.  Note also that the call to mp_mul can end up back
 * in this function if the a0, a1, b0, or b1 are above the threshold.
 * This is known as divide-and-conquer and leads to the famous
 * O(N**lg(3)) or O(N**1.584) work which is asymptopically lower than
 * the standard O(N**2) that the baseline/comba methods use.
 * Generally though the overhead of this method doesn't pay off
 * until a certain size (N ~ 80) is reached.
 */
int mp_karatsuba_mul(mp_int *a, mp_int *b, mp_int *c) {
    mp_int x0, x1, y0, y1, t1, x0y0, x1y1;
    int    B, err;

    /* default the return code to an error */
    err = MP_MEM;

    /* min # of digits */
    B = MIN(a->used, b->used);

    /* now divide in two */
    B = B >> 1;

    /* init copy all the temps */
    if (mp_init_size(&x0, B) != MP_OKAY)
        goto ERR;
    if (mp_init_size(&x1, a->used - B) != MP_OKAY)
        goto X0;
    if (mp_init_size(&y0, B) != MP_OKAY)
        goto X1;
    if (mp_init_size(&y1, b->used - B) != MP_OKAY)
        goto Y0;

    /* init temps */
    if (mp_init_size(&t1, B * 2) != MP_OKAY)
        goto Y1;
    if (mp_init_size(&x0y0, B * 2) != MP_OKAY)
        goto T1;
    if (mp_init_size(&x1y1, B * 2) != MP_OKAY)
        goto X0Y0;

    /* now shift the digits */
    x0.used = y0.used = B;
    x1.used = a->used - B;
    y1.used = b->used - B;

    {
        int      x;
        mp_digit *tmpa, *tmpb, *tmpx, *tmpy;

        /* we copy the digits directly instead of using higher level functions
         * since we also need to shift the digits
         */
        tmpa = a->dp;
        tmpb = b->dp;

        tmpx = x0.dp;
        tmpy = y0.dp;
        for (x = 0; x < B; x++) {
            *tmpx++ = *tmpa++;
            *tmpy++ = *tmpb++;
        }

        tmpx = x1.dp;
        for (x = B; x < a->used; x++) {
            *tmpx++ = *tmpa++;
        }

        tmpy = y1.dp;
        for (x = B; x < b->used; x++) {
            *tmpy++ = *tmpb++;
        }
    }

    /* only need to clamp the lower words since by definition the
     * upper words x1/y1 must have a known number of digits
     */
    mp_clamp(&x0);
    mp_clamp(&y0);

    /* now calc the products x0y0 and x1y1 */
    /* after this x0 is no longer required, free temp [x0==t2]! */
    if (mp_mul(&x0, &y0, &x0y0) != MP_OKAY)
        goto X1Y1;      /* x0y0 = x0*y0 */
    if (mp_mul(&x1, &y1, &x1y1) != MP_OKAY)
        goto X1Y1;      /* x1y1 = x1*y1 */

    /* now calc x1+x0 and y1+y0 */
    if (s_mp_add(&x1, &x0, &t1) != MP_OKAY)
        goto X1Y1;      /* t1 = x1 - x0 */
    if (s_mp_add(&y1, &y0, &x0) != MP_OKAY)
        goto X1Y1;      /* t2 = y1 - y0 */
    if (mp_mul(&t1, &x0, &t1) != MP_OKAY)
        goto X1Y1;      /* t1 = (x1 + x0) * (y1 + y0) */

    /* add x0y0 */
    if (mp_add(&x0y0, &x1y1, &x0) != MP_OKAY)
        goto X1Y1;      /* t2 = x0y0 + x1y1 */
    if (s_mp_sub(&t1, &x0, &t1) != MP_OKAY)
        goto X1Y1;      /* t1 = (x1+x0)*(y1+y0) - (x1y1 + x0y0) */

    /* shift by B */
    if (mp_lshd(&t1, B) != MP_OKAY)
        goto X1Y1;      /* t1 = (x0y0 + x1y1 - (x1-x0)*(y1-y0))<<B */
    if (mp_lshd(&x1y1, B * 2) != MP_OKAY)
        goto X1Y1;      /* x1y1 = x1y1 << 2*B */

    if (mp_add(&x0y0, &t1, &t1) != MP_OKAY)
        goto X1Y1;      /* t1 = x0y0 + t1 */
    if (mp_add(&t1, &x1y1, c) != MP_OKAY)
        goto X1Y1;      /* t1 = x0y0 + t1 + x1y1 */

    /* Algorithm succeeded set the return code to MP_OKAY */
    err = MP_OKAY;

X1Y1: mp_clear(&x1y1);
X0Y0: mp_clear(&x0y0);
T1: mp_clear(&t1);
Y1: mp_clear(&y1);
Y0: mp_clear(&y0);
X1: mp_clear(&x1);
X0: mp_clear(&x0);
ERR:
    return err;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_KARATSUBA_SQR_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* Karatsuba squaring, computes b = a*a using three
 * half size squarings
 *
 * See comments of karatsuba_mul for details.  It
 * is essentially the same algorithm but merely
 * tuned to perform recursive squarings.
 */
int mp_karatsuba_sqr(mp_int *a, mp_int *b) {
    mp_int x0, x1, t1, t2, x0x0, x1x1;
    int    B, err;

    err = MP_MEM;

    /* min # of digits */
    B = a->used;

    /* now divide in two */
    B = B >> 1;

    /* init copy all the temps */
    if (mp_init_size(&x0, B) != MP_OKAY)
        goto ERR;
    if (mp_init_size(&x1, a->used - B) != MP_OKAY)
        goto X0;

    /* init temps */
    if (mp_init_size(&t1, a->used * 2) != MP_OKAY)
        goto X1;
    if (mp_init_size(&t2, a->used * 2) != MP_OKAY)
        goto T1;
    if (mp_init_size(&x0x0, B * 2) != MP_OKAY)
        goto T2;
    if (mp_init_size(&x1x1, (a->used - B) * 2) != MP_OKAY)
        goto X0X0;

    {
        int      x;
        mp_digit *dst, *src;

        src = a->dp;

        /* now shift the digits */
        dst = x0.dp;
        for (x = 0; x < B; x++) {
            *dst++ = *src++;
        }

        dst = x1.dp;
        for (x = B; x < a->used; x++) {
            *dst++ = *src++;
        }
    }

    x0.used = B;
    x1.used = a->used - B;

    mp_clamp(&x0);

    /* now calc the products x0*x0 and x1*x1 */
    if (mp_sqr(&x0, &x0x0) != MP_OKAY)
        goto X1X1;       /* x0x0 = x0*x0 */
    if (mp_sqr(&x1, &x1x1) != MP_OKAY)
        goto X1X1;       /* x1x1 = x1*x1 */

    /* now calc (x1+x0)**2 */
    if (s_mp_add(&x1, &x0, &t1) != MP_OKAY)
        goto X1X1;       /* t1 = x1 - x0 */
    if (mp_sqr(&t1, &t1) != MP_OKAY)
        goto X1X1;       /* t1 = (x1 - x0) * (x1 - x0) */

    /* add x0y0 */
    if (s_mp_add(&x0x0, &x1x1, &t2) != MP_OKAY)
        goto X1X1;       /* t2 = x0x0 + x1x1 */
    if (s_mp_sub(&t1, &t2, &t1) != MP_OKAY)
        goto X1X1;       /* t1 = (x1+x0)**2 - (x0x0 + x1x1) */

    /* shift by B */
    if (mp_lshd(&t1, B) != MP_OKAY)
        goto X1X1;       /* t1 = (x0x0 + x1x1 - (x1-x0)*(x1-x0))<<B */
    if (mp_lshd(&x1x1, B * 2) != MP_OKAY)
        goto X1X1;       /* x1x1 = x1x1 << 2*B */

    if (mp_add(&x0x0, &t1, &t1) != MP_OKAY)
        goto X1X1;       /* t1 = x0x0 + t1 */
    if (mp_add(&t1, &x1x1, b) != MP_OKAY)
        goto X1X1;       /* t1 = x0x0 + t1 + x1x1 */

    err = MP_OKAY;

X1X1: mp_clear(&x1x1);
X0X0: mp_clear(&x0x0);
T2: mp_clear(&t2);
T1: mp_clear(&t1);
X1: mp_clear(&x1);
X0: mp_clear(&x0);
ERR:
    return err;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_LCM_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* computes least common multiple as |a*b|/(a, b) */
int mp_lcm(mp_int *a, mp_int *b, mp_int *c) {
    int    res;
    mp_int t1, t2;


    if ((res = mp_init_multi(&t1, &t2, NULL)) != MP_OKAY) {
        return res;
    }

    /* t1 = get the GCD of the two inputs */
    if ((res = mp_gcd(a, b, &t1)) != MP_OKAY) {
        goto LBL_T;
    }

    /* divide the smallest by the GCD */
    if (mp_cmp_mag(a, b) == MP_LT) {
        /* store quotient in t2 such that t2 * b is the LCM */
        if ((res = mp_div(a, &t1, &t2, NULL)) != MP_OKAY) {
            goto LBL_T;
        }
        res = mp_mul(b, &t2, c);
    } else {
        /* store quotient in t2 such that t2 * a is the LCM */
        if ((res = mp_div(b, &t1, &t2, NULL)) != MP_OKAY) {
            goto LBL_T;
        }
        res = mp_mul(a, &t2, c);
    }

    /* fix the sign to positive */
    c->sign = MP_ZPOS;

LBL_T:
    mp_clear_multi(&t1, &t2, NULL);
    return res;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_LSHD_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* shift left a certain amount of digits */
int mp_lshd(mp_int *a, int b) {
    int x, res;

    /* if its less than zero return */
    if (b <= 0) {
        return MP_OKAY;
    }

    /* grow to fit the new digits */
    if (a->alloc < (a->used + b)) {
        if ((res = mp_grow(a, a->used + b)) != MP_OKAY) {
            return res;
        }
    }

    {
        mp_digit *top, *bottom;

        /* increment the used by the shift amount then copy upwards */
        a->used += b;

        /* top */
        top = a->dp + a->used - 1;

        /* base */
        bottom = (a->dp + a->used - 1) - b;

        /* much like mp_rshd this is implemented using a sliding window
         * except the window goes the otherway around.  Copying from
         * the bottom to the top.  see bn_mp_rshd.c for more info.
         */
        for (x = a->used - 1; x >= b; x--) {
            *top-- = *bottom--;
        }

        /* zero the lower digits */
        top = a->dp;
        for (x = 0; x < b; x++) {
            *top++ = 0;
        }
    }
    return MP_OKAY;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_MOD_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* c = a mod b, 0 <= c < b if b > 0, b < c <= 0 if b < 0 */
int
mp_mod(mp_int *a, mp_int *b, mp_int *c) {
    mp_int t;
    int    res;

    if ((res = mp_init(&t)) != MP_OKAY) {
        return res;
    }

    if ((res = mp_div(a, b, NULL, &t)) != MP_OKAY) {
        mp_clear(&t);
        return res;
    }

    if ((mp_iszero(&t) != MP_NO) || (t.sign == b->sign)) {
        res = MP_OKAY;
        mp_exch(&t, c);
    } else {
        res = mp_add(b, &t, c);
    }

    mp_clear(&t);
    return res;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_MOD_2D_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* calc a value mod 2**b */
int
mp_mod_2d(mp_int *a, int b, mp_int *c) {
    int x, res;

    /* if b is <= 0 then zero the int */
    if (b <= 0) {
        mp_zero(c);
        return MP_OKAY;
    }

    /* if the modulus is larger than the value than return */
    if (b >= (int)(a->used * DIGIT_BIT)) {
        res = mp_copy(a, c);
        return res;
    }

    /* copy */
    if ((res = mp_copy(a, c)) != MP_OKAY) {
        return res;
    }

    /* zero digits above the last digit of the modulus */
    for (x = (b / DIGIT_BIT) + (((b % DIGIT_BIT) == 0) ? 0 : 1); x < c->used; x++) {
        c->dp[x] = 0;
    }
    /* clear the digit that is not completely outside/inside the modulus */
    c->dp[b / DIGIT_BIT] &=
        (mp_digit)((((mp_digit)1) << (((mp_digit)b) % DIGIT_BIT)) - ((mp_digit)1));
    mp_clamp(c);
    return MP_OKAY;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_MOD_D_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

int
mp_mod_d(mp_int *a, mp_digit b, mp_digit *c) {
    return mp_div_d(a, b, NULL, c);
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_MONTGOMERY_CALC_NORMALIZATION_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/*
 * shifts with subtractions when the result is greater than b.
 *
 * The method is slightly modified to shift B unconditionally upto just under
 * the leading bit of b.  This saves alot of multiple precision shifting.
 */
int mp_montgomery_calc_normalization(mp_int *a, mp_int *b) {
    int x, bits, res;

    /* how many bits of last digit does b use */
    bits = mp_count_bits(b) % DIGIT_BIT;

    if (b->used > 1) {
        if ((res = mp_2expt(a, ((b->used - 1) * DIGIT_BIT) + bits - 1)) != MP_OKAY) {
            return res;
        }
    } else {
        mp_set(a, 1);
        bits = 1;
    }


    /* now compute C = A * B mod b */
    for (x = bits - 1; x < (int)DIGIT_BIT; x++) {
        if ((res = mp_mul_2(a, a)) != MP_OKAY) {
            return res;
        }
        if (mp_cmp_mag(a, b) != MP_LT) {
            if ((res = s_mp_sub(a, b, a)) != MP_OKAY) {
                return res;
            }
        }
    }

    return MP_OKAY;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_MONTGOMERY_REDUCE_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* computes xR**-1 == x (mod N) via Montgomery Reduction */
int
mp_montgomery_reduce(mp_int *x, mp_int *n, mp_digit rho) {
    int      ix, res, digs;
    mp_digit mu;

    /* can the fast reduction [comba] method be used?
     *
     * Note that unlike in mul you're safely allowed *less*
     * than the available columns [255 per default] since carries
     * are fixed up in the inner loop.
     */
    digs = (n->used * 2) + 1;
    if ((digs < MP_WARRAY) &&
        (n->used <
         (1 << ((CHAR_BIT * sizeof(mp_word)) - (2 * DIGIT_BIT))))) {
        return fast_mp_montgomery_reduce(x, n, rho);
    }

    /* grow the input as required */
    if (x->alloc < digs) {
        if ((res = mp_grow(x, digs)) != MP_OKAY) {
            return res;
        }
    }
    x->used = digs;

    for (ix = 0; ix < n->used; ix++) {
        /* mu = ai * rho mod b
         *
         * The value of rho must be precalculated via
         * montgomery_setup() such that
         * it equals -1/n0 mod b this allows the
         * following inner loop to reduce the
         * input one digit at a time
         */
        mu = (mp_digit)(((mp_word)x->dp[ix] * (mp_word)rho) & MP_MASK);

        /* a = a + mu * m * b**i */
        {
            int      iy;
            mp_digit *tmpn, *tmpx, u;
            mp_word  r;

            /* alias for digits of the modulus */
            tmpn = n->dp;

            /* alias for the digits of x [the input] */
            tmpx = x->dp + ix;

            /* set the carry to zero */
            u = 0;

            /* Multiply and add in place */
            for (iy = 0; iy < n->used; iy++) {
                /* compute product and sum */
                r = ((mp_word)mu * (mp_word) * tmpn++) +
                    (mp_word)u + (mp_word) * tmpx;

                /* get carry */
                u = (mp_digit)(r >> ((mp_word)DIGIT_BIT));

                /* fix digit */
                *tmpx++ = (mp_digit)(r & ((mp_word)MP_MASK));
            }
            /* At this point the ix'th digit of x should be zero */


            /* propagate carries upwards as required*/
            while (u != 0) {
                *tmpx   += u;
                u        = *tmpx >> DIGIT_BIT;
                *tmpx++ &= MP_MASK;
            }
        }
    }

    /* at this point the n.used'th least
     * significant digits of x are all zero
     * which means we can shift x to the
     * right by n.used digits and the
     * residue is unchanged.
     */

    /* x = x/b**n.used */
    mp_clamp(x);
    mp_rshd(x, n->used);

    /* if x >= n then x = x - n */
    if (mp_cmp_mag(x, n) != MP_LT) {
        return s_mp_sub(x, n, x);
    }

    return MP_OKAY;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_MONTGOMERY_SETUP_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* setups the montgomery reduction stuff */
int
mp_montgomery_setup(mp_int *n, mp_digit *rho) {
    mp_digit x, b;

/* fast inversion mod 2**k
 *
 * Based on the fact that
 *
 * XA = 1 (mod 2**n)  =>  (X(2-XA)) A = 1 (mod 2**2n)
 *                    =>  2*X*A - X*X*A*A = 1
 *                    =>  2*(1) - (1)     = 1
 */
    b = n->dp[0];

    if ((b & 1) == 0) {
        return MP_VAL;
    }

    x  = (((b + 2) & 4) << 1) + b; /* here x*a==1 mod 2**4 */
    x *= 2 - (b * x);              /* here x*a==1 mod 2**8 */
 #if !defined(MP_8BIT)
    x *= 2 - (b * x);              /* here x*a==1 mod 2**16 */
 #endif
 #if defined(MP_64BIT) || !(defined(MP_8BIT) || defined(MP_16BIT))
    x *= 2 - (b * x);           /* here x*a==1 mod 2**32 */
 #endif
 #ifdef MP_64BIT
    x *= 2 - (b * x);           /* here x*a==1 mod 2**64 */
 #endif

    /* rho = -1/m mod b */
    *rho = (mp_digit)(((mp_word)1 << ((mp_word)DIGIT_BIT)) - x) & MP_MASK;

    return MP_OKAY;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_MUL_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* high level multiplication (handles sign) */
int mp_mul(mp_int *a, mp_int *b, mp_int *c) {
    int res, neg;

    neg = (a->sign == b->sign) ? MP_ZPOS : MP_NEG;

    /* use Toom-Cook? */
 #ifdef BN_MP_TOOM_MUL_C
    if (MIN(a->used, b->used) >= TOOM_MUL_CUTOFF) {
        res = mp_toom_mul(a, b, c);
    } else
 #endif
 #ifdef BN_MP_KARATSUBA_MUL_C
    /* use Karatsuba? */
    if (MIN(a->used, b->used) >= KARATSUBA_MUL_CUTOFF) {
        res = mp_karatsuba_mul(a, b, c);
    } else
 #endif
    {
        /* can we use the fast multiplier?
         *
         * The fast multiplier can be used if the output will
         * have less than MP_WARRAY digits and the number of
         * digits won't affect carry propagation
         */
        int digs = a->used + b->used + 1;

 #ifdef BN_FAST_S_MP_MUL_DIGS_C
        if ((digs < MP_WARRAY) &&
            (MIN(a->used, b->used) <=
             (1 << ((CHAR_BIT * sizeof(mp_word)) - (2 * DIGIT_BIT))))) {
            res = fast_s_mp_mul_digs(a, b, c, digs);
        } else
 #endif
        {
 #ifdef BN_S_MP_MUL_DIGS_C
            res = s_mp_mul(a, b, c); /* uses s_mp_mul_digs */
 #else
            res = MP_VAL;
 #endif
        }
    }
    c->sign = (c->used > 0) ? neg : MP_ZPOS;
    return res;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_MUL_2_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* b = a*2 */
int mp_mul_2(mp_int *a, mp_int *b) {
    int x, res, oldused;

    /* grow to accomodate result */
    if (b->alloc < (a->used + 1)) {
        if ((res = mp_grow(b, a->used + 1)) != MP_OKAY) {
            return res;
        }
    }

    oldused = b->used;
    b->used = a->used;

    {
        mp_digit r, rr, *tmpa, *tmpb;

        /* alias for source */
        tmpa = a->dp;

        /* alias for dest */
        tmpb = b->dp;

        /* carry */
        r = 0;
        for (x = 0; x < a->used; x++) {
            /* get what will be the *next* carry bit from the
             * MSB of the current digit
             */
            rr = *tmpa >> ((mp_digit)(DIGIT_BIT - 1));

            /* now shift up this digit, add in the carry [from the previous] */
            *tmpb++ = ((*tmpa++ << ((mp_digit)1)) | r) & MP_MASK;

            /* copy the carry that would be from the source
             * digit into the next iteration
             */
            r = rr;
        }

        /* new leading digit? */
        if (r != 0) {
            /* add a MSB which is always 1 at this point */
            *tmpb = 1;
            ++(b->used);
        }

        /* now zero any excess digits on the destination
         * that we didn't write to
         */
        tmpb = b->dp + b->used;
        for (x = b->used; x < oldused; x++) {
            *tmpb++ = 0;
        }
    }
    b->sign = a->sign;
    return MP_OKAY;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_MUL_2D_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* shift left by a certain bit count */
int mp_mul_2d(mp_int *a, int b, mp_int *c) {
    mp_digit d;
    int      res;

    /* copy */
    if (a != c) {
        if ((res = mp_copy(a, c)) != MP_OKAY) {
            return res;
        }
    }

    if (c->alloc < (int)(c->used + (b / DIGIT_BIT) + 1)) {
        if ((res = mp_grow(c, c->used + (b / DIGIT_BIT) + 1)) != MP_OKAY) {
            return res;
        }
    }

    /* shift by as many digits in the bit count */
    if (b >= (int)DIGIT_BIT) {
        if ((res = mp_lshd(c, b / DIGIT_BIT)) != MP_OKAY) {
            return res;
        }
    }

    /* shift any bit count < DIGIT_BIT */
    d = (mp_digit)(b % DIGIT_BIT);
    if (d != 0) {
        mp_digit *tmpc, shift, mask, r, rr;
        int      x;

        /* bitmask for carries */
        mask = (((mp_digit)1) << d) - 1;

        /* shift for msbs */
        shift = DIGIT_BIT - d;

        /* alias */
        tmpc = c->dp;

        /* carry */
        r = 0;
        for (x = 0; x < c->used; x++) {
            /* get the higher bits of the current word */
            rr = (*tmpc >> shift) & mask;

            /* shift the current word and OR in the carry */
            *tmpc = ((*tmpc << d) | r) & MP_MASK;
            ++tmpc;

            /* set the carry to the carry bits of the current word */
            r = rr;
        }

        /* set final carry */
        if (r != 0) {
            c->dp[(c->used)++] = r;
        }
    }
    mp_clamp(c);
    return MP_OKAY;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_MUL_D_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* multiply by a digit */
int
mp_mul_d(mp_int *a, mp_digit b, mp_int *c) {
    mp_digit u, *tmpa, *tmpc;
    mp_word  r;
    int      ix, res, olduse;

    /* make sure c is big enough to hold a*b */
    if (c->alloc < (a->used + 1)) {
        if ((res = mp_grow(c, a->used + 1)) != MP_OKAY) {
            return res;
        }
    }

    /* get the original destinations used count */
    olduse = c->used;

    /* set the sign */
    c->sign = a->sign;

    /* alias for a->dp [source] */
    tmpa = a->dp;

    /* alias for c->dp [dest] */
    tmpc = c->dp;

    /* zero carry */
    u = 0;

    /* compute columns */
    for (ix = 0; ix < a->used; ix++) {
        /* compute product and carry sum for this term */
        r = (mp_word)u + ((mp_word) * tmpa++ *(mp_word)b);

        /* mask off higher bits to get a single digit */
        *tmpc++ = (mp_digit)(r & ((mp_word)MP_MASK));

        /* send carry into next iteration */
        u = (mp_digit)(r >> ((mp_word)DIGIT_BIT));
    }

    /* store final carry [if any] and increment ix offset  */
    *tmpc++ = u;
    ++ix;

    /* now zero digits above the top */
    while (ix++ < olduse) {
        *tmpc++ = 0;
    }

    /* set used count */
    c->used = a->used + 1;
    mp_clamp(c);

    return MP_OKAY;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_MULMOD_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* d = a * b (mod c) */
int mp_mulmod(mp_int *a, mp_int *b, mp_int *c, mp_int *d) {
    int    res;
    mp_int t;

    if ((res = mp_init(&t)) != MP_OKAY) {
        return res;
    }

    if ((res = mp_mul(a, b, &t)) != MP_OKAY) {
        mp_clear(&t);
        return res;
    }
    res = mp_mod(&t, c, d);
    mp_clear(&t);
    return res;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_N_ROOT_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* wrapper function for mp_n_root_ex()
 * computes c = (a)**(1/b) such that (c)**b <= a and (c+1)**b > a
 */
int mp_n_root(mp_int *a, mp_digit b, mp_int *c) {
    return mp_n_root_ex(a, b, c, 0);
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_N_ROOT_EX_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* find the n'th root of an integer
 *
 * Result found such that (c)**b <= a and (c+1)**b > a
 *
 * This algorithm uses Newton's approximation
 * x[i+1] = x[i] - f(x[i])/f'(x[i])
 * which will find the root in log(N) time where
 * each step involves a fair bit.  This is not meant to
 * find huge roots [square and cube, etc].
 */
int mp_n_root_ex(mp_int *a, mp_digit b, mp_int *c, int fast) {
    mp_int t1, t2, t3;
    int    res, neg;

    /* input must be positive if b is even */
    if (((b & 1) == 0) && (a->sign == MP_NEG)) {
        return MP_VAL;
    }

    if ((res = mp_init(&t1)) != MP_OKAY) {
        return res;
    }

    if ((res = mp_init(&t2)) != MP_OKAY) {
        goto LBL_T1;
    }

    if ((res = mp_init(&t3)) != MP_OKAY) {
        goto LBL_T2;
    }

    /* if a is negative fudge the sign but keep track */
    neg     = a->sign;
    a->sign = MP_ZPOS;

    /* t2 = 2 */
    mp_set(&t2, 2);

    do {
        /* t1 = t2 */
        if ((res = mp_copy(&t2, &t1)) != MP_OKAY) {
            goto LBL_T3;
        }

        /* t2 = t1 - ((t1**b - a) / (b * t1**(b-1))) */

        /* t3 = t1**(b-1) */
        if ((res = mp_expt_d_ex(&t1, b - 1, &t3, fast)) != MP_OKAY) {
            goto LBL_T3;
        }

        /* numerator */
        /* t2 = t1**b */
        if ((res = mp_mul(&t3, &t1, &t2)) != MP_OKAY) {
            goto LBL_T3;
        }

        /* t2 = t1**b - a */
        if ((res = mp_sub(&t2, a, &t2)) != MP_OKAY) {
            goto LBL_T3;
        }

        /* denominator */
        /* t3 = t1**(b-1) * b  */
        if ((res = mp_mul_d(&t3, b, &t3)) != MP_OKAY) {
            goto LBL_T3;
        }

        /* t3 = (t1**b - a)/(b * t1**(b-1)) */
        if ((res = mp_div(&t2, &t3, &t3, NULL)) != MP_OKAY) {
            goto LBL_T3;
        }

        if ((res = mp_sub(&t1, &t3, &t2)) != MP_OKAY) {
            goto LBL_T3;
        }
    }  while (mp_cmp(&t1, &t2) != MP_EQ);

    /* result can be off by a few so check */
    for ( ; ; ) {
        if ((res = mp_expt_d_ex(&t1, b, &t2, fast)) != MP_OKAY) {
            goto LBL_T3;
        }

        if (mp_cmp(&t2, a) == MP_GT) {
            if ((res = mp_sub_d(&t1, 1, &t1)) != MP_OKAY) {
                goto LBL_T3;
            }
        } else {
            break;
        }
    }

    /* reset the sign of a first */
    a->sign = neg;

    /* set the result */
    mp_exch(&t1, c);

    /* set the sign of the result */
    c->sign = neg;

    res = MP_OKAY;

LBL_T3: mp_clear(&t3);
LBL_T2: mp_clear(&t2);
LBL_T1: mp_clear(&t1);
    return res;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_NEG_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* b = -a */
int mp_neg(mp_int *a, mp_int *b) {
    int res;

    if (a != b) {
        if ((res = mp_copy(a, b)) != MP_OKAY) {
            return res;
        }
    }

    if (mp_iszero(b) != MP_YES) {
        b->sign = (a->sign == MP_ZPOS) ? MP_NEG : MP_ZPOS;
    } else {
        b->sign = MP_ZPOS;
    }

    return MP_OKAY;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_OR_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* OR two ints together */
int mp_or(mp_int *a, mp_int *b, mp_int *c) {
    int    res, ix, px;
    mp_int t, *x;

    if (a->used > b->used) {
        if ((res = mp_init_copy(&t, a)) != MP_OKAY) {
            return res;
        }
        px = b->used;
        x  = b;
    } else {
        if ((res = mp_init_copy(&t, b)) != MP_OKAY) {
            return res;
        }
        px = a->used;
        x  = a;
    }

    for (ix = 0; ix < px; ix++) {
        t.dp[ix] |= x->dp[ix];
    }
    mp_clamp(&t);
    mp_exch(c, &t);
    mp_clear(&t);
    return MP_OKAY;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_PRIME_FERMAT_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* performs one Fermat test.
 *
 * If "a" were prime then b**a == b (mod a) since the order of
 * the multiplicative sub-group would be phi(a) = a-1.  That means
 * it would be the same as b**(a mod (a-1)) == b**1 == b (mod a).
 *
 * Sets result to 1 if the congruence holds, or zero otherwise.
 */
int mp_prime_fermat(mp_int *a, mp_int *b, int *result) {
    mp_int t;
    int    err;

    /* default to composite  */
    *result = MP_NO;

    /* ensure b > 1 */
    if (mp_cmp_d(b, 1) != MP_GT) {
        return MP_VAL;
    }

    /* init t */
    if ((err = mp_init(&t)) != MP_OKAY) {
        return err;
    }

    /* compute t = b**a mod a */
    if ((err = mp_exptmod(b, a, a, &t)) != MP_OKAY) {
        goto LBL_T;
    }

    /* is it equal to b? */
    if (mp_cmp(&t, b) == MP_EQ) {
        *result = MP_YES;
    }

    err = MP_OKAY;
LBL_T: mp_clear(&t);
    return err;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_PRIME_IS_DIVISIBLE_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* determines if an integers is divisible by one
 * of the first PRIME_SIZE primes or not
 *
 * sets result to 0 if not, 1 if yes
 */
int mp_prime_is_divisible(mp_int *a, int *result) {
    int      err, ix;
    mp_digit res;

    /* default to not */
    *result = MP_NO;

    for (ix = 0; ix < PRIME_SIZE; ix++) {
        /* what is a mod LBL_prime_tab[ix] */
        if ((err = mp_mod_d(a, ltm_prime_tab[ix], &res)) != MP_OKAY) {
            return err;
        }

        /* is the residue zero? */
        if (res == 0) {
            *result = MP_YES;
            return MP_OKAY;
        }
    }

    return MP_OKAY;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_PRIME_IS_PRIME_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* performs a variable number of rounds of Miller-Rabin
 *
 * Probability of error after t rounds is no more than

 *
 * Sets result to 1 if probably prime, 0 otherwise
 */
int mp_prime_is_prime(mp_int *a, int t, int *result) {
    mp_int b;
    int    ix, err, res;

    /* default to no */
    *result = MP_NO;

    /* valid value of t? */
    if ((t <= 0) || (t > PRIME_SIZE)) {
        return MP_VAL;
    }

    /* is the input equal to one of the primes in the table? */
    for (ix = 0; ix < PRIME_SIZE; ix++) {
        if (mp_cmp_d(a, ltm_prime_tab[ix]) == MP_EQ) {
            *result = 1;
            return MP_OKAY;
        }
    }

    /* first perform trial division */
    if ((err = mp_prime_is_divisible(a, &res)) != MP_OKAY) {
        return err;
    }

    /* return if it was trivially divisible */
    if (res == MP_YES) {
        return MP_OKAY;
    }

    /* now perform the miller-rabin rounds */
    if ((err = mp_init(&b)) != MP_OKAY) {
        return err;
    }

    for (ix = 0; ix < t; ix++) {
        /* set the prime */
        mp_set(&b, ltm_prime_tab[ix]);

        if ((err = mp_prime_miller_rabin(a, &b, &res)) != MP_OKAY) {
            goto LBL_B;
        }

        if (res == MP_NO) {
            goto LBL_B;
        }
    }

    /* passed the test */
    *result = MP_YES;
LBL_B: mp_clear(&b);
    return err;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_PRIME_MILLER_RABIN_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* Miller-Rabin test of "a" to the base of "b" as described in
 * HAC pp. 139 Algorithm 4.24
 *
 * Sets result to 0 if definitely composite or 1 if probably prime.
 * Randomly the chance of error is no more than 1/4 and often
 * very much lower.
 */
int mp_prime_miller_rabin(mp_int *a, mp_int *b, int *result) {
    mp_int n1, y, r;
    int    s, j, err;

    /* default */
    *result = MP_NO;

    /* ensure b > 1 */
    if (mp_cmp_d(b, 1) != MP_GT) {
        return MP_VAL;
    }

    /* get n1 = a - 1 */
    if ((err = mp_init_copy(&n1, a)) != MP_OKAY) {
        return err;
    }
    if ((err = mp_sub_d(&n1, 1, &n1)) != MP_OKAY) {
        goto LBL_N1;
    }

    /* set 2**s * r = n1 */
    if ((err = mp_init_copy(&r, &n1)) != MP_OKAY) {
        goto LBL_N1;
    }

    /* count the number of least significant bits
     * which are zero
     */
    s = mp_cnt_lsb(&r);

    /* now divide n - 1 by 2**s */
    if ((err = mp_div_2d(&r, s, &r, NULL)) != MP_OKAY) {
        goto LBL_R;
    }

    /* compute y = b**r mod a */
    if ((err = mp_init(&y)) != MP_OKAY) {
        goto LBL_R;
    }
    if ((err = mp_exptmod(b, &r, a, &y)) != MP_OKAY) {
        goto LBL_Y;
    }

    /* if y != 1 and y != n1 do */
    if ((mp_cmp_d(&y, 1) != MP_EQ) && (mp_cmp(&y, &n1) != MP_EQ)) {
        j = 1;
        /* while j <= s-1 and y != n1 */
        while ((j <= (s - 1)) && (mp_cmp(&y, &n1) != MP_EQ)) {
            if ((err = mp_sqrmod(&y, a, &y)) != MP_OKAY) {
                goto LBL_Y;
            }

            /* if y == 1 then composite */
            if (mp_cmp_d(&y, 1) == MP_EQ) {
                goto LBL_Y;
            }

            ++j;
        }

        /* if y != n1 then composite */
        if (mp_cmp(&y, &n1) != MP_EQ) {
            goto LBL_Y;
        }
    }

    /* probably prime now */
    *result = MP_YES;
LBL_Y: mp_clear(&y);
LBL_R: mp_clear(&r);
LBL_N1: mp_clear(&n1);
    return err;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_PRIME_NEXT_PRIME_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* finds the next prime after the number "a" using "t" trials
 * of Miller-Rabin.
 *
 * bbs_style = 1 means the prime must be congruent to 3 mod 4
 */
int mp_prime_next_prime(mp_int *a, int t, int bbs_style) {
    int      err, res = MP_NO, x, y;
    mp_digit res_tab[PRIME_SIZE], step, kstep;
    mp_int   b;

    /* ensure t is valid */
    if ((t <= 0) || (t > PRIME_SIZE)) {
        return MP_VAL;
    }

    /* force positive */
    a->sign = MP_ZPOS;

    /* simple algo if a is less than the largest prime in the table */
    if (mp_cmp_d(a, ltm_prime_tab[PRIME_SIZE - 1]) == MP_LT) {
        /* find which prime it is bigger than */
        for (x = PRIME_SIZE - 2; x >= 0; x--) {
            if (mp_cmp_d(a, ltm_prime_tab[x]) != MP_LT) {
                if (bbs_style == 1) {
                    /* ok we found a prime smaller or
                     * equal [so the next is larger]
                     *
                     * however, the prime must be
                     * congruent to 3 mod 4
                     */
                    if ((ltm_prime_tab[x + 1] & 3) != 3) {
                        /* scan upwards for a prime congruent to 3 mod 4 */
                        for (y = x + 1; y < PRIME_SIZE; y++) {
                            if ((ltm_prime_tab[y] & 3) == 3) {
                                mp_set(a, ltm_prime_tab[y]);
                                return MP_OKAY;
                            }
                        }
                    }
                } else {
                    mp_set(a, ltm_prime_tab[x + 1]);
                    return MP_OKAY;
                }
            }
        }
        /* at this point a maybe 1 */
        if (mp_cmp_d(a, 1) == MP_EQ) {
            mp_set(a, 2);
            return MP_OKAY;
        }
        /* fall through to the sieve */
    }

    /* generate a prime congruent to 3 mod 4 or 1/3 mod 4? */
    if (bbs_style == 1) {
        kstep = 4;
    } else {
        kstep = 2;
    }

    /* at this point we will use a combination of a sieve and Miller-Rabin */

    if (bbs_style == 1) {
        /* if a mod 4 != 3 subtract the correct value to make it so */
        if ((a->dp[0] & 3) != 3) {
            if ((err = mp_sub_d(a, (a->dp[0] & 3) + 1, a)) != MP_OKAY) {
                return err;
            }
        }
    } else {
        if (mp_iseven(a) == MP_YES) {
            /* force odd */
            if ((err = mp_sub_d(a, 1, a)) != MP_OKAY) {
                return err;
            }
        }
    }

    /* generate the restable */
    for (x = 1; x < PRIME_SIZE; x++) {
        if ((err = mp_mod_d(a, ltm_prime_tab[x], res_tab + x)) != MP_OKAY) {
            return err;
        }
    }

    /* init temp used for Miller-Rabin Testing */
    if ((err = mp_init(&b)) != MP_OKAY) {
        return err;
    }

    for ( ; ; ) {
        /* skip to the next non-trivially divisible candidate */
        step = 0;
        do {
            /* y == 1 if any residue was zero [e.g. cannot be prime] */
            y = 0;

            /* increase step to next candidate */
            step += kstep;

            /* compute the new residue without using division */
            for (x = 1; x < PRIME_SIZE; x++) {
                /* add the step to each residue */
                res_tab[x] += kstep;

                /* subtract the modulus [instead of using division] */
                if (res_tab[x] >= ltm_prime_tab[x]) {
                    res_tab[x] -= ltm_prime_tab[x];
                }

                /* set flag if zero */
                if (res_tab[x] == 0) {
                    y = 1;
                }
            }
        } while ((y == 1) && (step < ((((mp_digit)1) << DIGIT_BIT) - kstep)));

        /* add the step */
        if ((err = mp_add_d(a, step, a)) != MP_OKAY) {
            goto LBL_ERR;
        }

        /* if didn't pass sieve and step == MAX then skip test */
        if ((y == 1) && (step >= ((((mp_digit)1) << DIGIT_BIT) - kstep))) {
            continue;
        }

        /* is this prime? */
        for (x = 0; x < t; x++) {
            mp_set(&b, ltm_prime_tab[x]);
            if ((err = mp_prime_miller_rabin(a, &b, &res)) != MP_OKAY) {
                goto LBL_ERR;
            }
            if (res == MP_NO) {
                break;
            }
        }

        if (res == MP_YES) {
            break;
        }
    }

    err = MP_OKAY;
LBL_ERR:
    mp_clear(&b);
    return err;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_PRIME_RABIN_MILLER_TRIALS_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */


static const struct {
    int k, t;
} sizes[] = {
    {  128, 28 },
    {  256, 16 },
    {  384, 10 },
    {  512,  7 },
    {  640,  6 },
    {  768,  5 },
    {  896,  4 },
    { 1024,  4 }
};

/* returns # of RM trials required for a given bit size */
int mp_prime_rabin_miller_trials(int size) {
    int x;

    for (x = 0; x < (int)(sizeof(sizes) / (sizeof(sizes[0]))); x++) {
        if (sizes[x].k == size) {
            return sizes[x].t;
        } else if (sizes[x].k > size) {
            return (x == 0) ? sizes[0].t : sizes[x - 1].t;
        }
    }
    return sizes[x - 1].t + 1;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_PRIME_RANDOM_EX_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* makes a truly random prime of a given size (bits),
 *
 * Flags are as follows:
 *
 *   LTM_PRIME_BBS      - make prime congruent to 3 mod 4
 *   LTM_PRIME_SAFE     - make sure (p-1)/2 is prime as well (implies LTM_PRIME_BBS)
 *   LTM_PRIME_2MSB_ON  - make the 2nd highest bit one
 *
 * You have to supply a callback which fills in a buffer with random bytes.  "dat" is a parameter you can
 * have passed to the callback (e.g. a state or something).  This function doesn't use "dat" itself
 * so it can be NULL
 *
 */

/* This is possibly the mother of all prime generation functions, muahahahahaha! */
int mp_prime_random_ex(mp_int *a, int t, int size, int flags, ltm_prime_callback cb, void *dat) {
    unsigned char *tmp, maskAND, maskOR_msb, maskOR_lsb;
    int           res, err, bsize, maskOR_msb_offset;

    /* sanity check the input */
    if ((size <= 1) || (t <= 0)) {
        return MP_VAL;
    }

    /* LTM_PRIME_SAFE implies LTM_PRIME_BBS */
    if ((flags & LTM_PRIME_SAFE) != 0) {
        flags |= LTM_PRIME_BBS;
    }

    /* calc the byte size */
    bsize = (size >> 3) + ((size & 7) ? 1 : 0);

    /* we need a buffer of bsize bytes */
    tmp = OPT_CAST(unsigned char) XMALLOC(bsize);
    if (tmp == NULL) {
        return MP_MEM;
    }

    /* calc the maskAND value for the MSbyte*/
    maskAND = ((size & 7) == 0) ? 0xFF : (0xFF >> (8 - (size & 7)));

    /* calc the maskOR_msb */
    maskOR_msb        = 0;
    maskOR_msb_offset = ((size & 7) == 1) ? 1 : 0;
    if ((flags & LTM_PRIME_2MSB_ON) != 0) {
        maskOR_msb |= 0x80 >> ((9 - size) & 7);
    }

    /* get the maskOR_lsb */
    maskOR_lsb = 1;
    if ((flags & LTM_PRIME_BBS) != 0) {
        maskOR_lsb |= 3;
    }

    do {
        /* read the bytes */
        if (cb(tmp, bsize, dat) != bsize) {
            err = MP_VAL;
            goto error;
        }

        /* work over the MSbyte */
        tmp[0] &= maskAND;
        tmp[0] |= 1 << ((size - 1) & 7);

        /* mix in the maskORs */
        tmp[maskOR_msb_offset] |= maskOR_msb;
        tmp[bsize - 1]         |= maskOR_lsb;

        /* read it in */
        if ((err = mp_read_unsigned_bin(a, tmp, bsize)) != MP_OKAY) {
            goto error;
        }

        /* is it prime? */
        if ((err = mp_prime_is_prime(a, t, &res)) != MP_OKAY) {
            goto error;
        }
        if (res == MP_NO) {
            continue;
        }

        if ((flags & LTM_PRIME_SAFE) != 0) {
            /* see if (a-1)/2 is prime */
            if ((err = mp_sub_d(a, 1, a)) != MP_OKAY) {
                goto error;
            }
            if ((err = mp_div_2(a, a)) != MP_OKAY) {
                goto error;
            }

            /* is it prime? */
            if ((err = mp_prime_is_prime(a, t, &res)) != MP_OKAY) {
                goto error;
            }
        }
    } while (res == MP_NO);

    if ((flags & LTM_PRIME_SAFE) != 0) {
        /* restore a to the original value */
        if ((err = mp_mul_2(a, a)) != MP_OKAY) {
            goto error;
        }
        if ((err = mp_add_d(a, 1, a)) != MP_OKAY) {
            goto error;
        }
    }

    err = MP_OKAY;
error:
    XFREE(tmp);
    return err;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_RADIX_SIZE_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* returns size of ASCII reprensentation */
int mp_radix_size(mp_int *a, int radix, int *size) {
    int      res, digs;
    mp_int   t;
    mp_digit d;

    *size = 0;

    /* make sure the radix is in range */
    if ((radix < 2) || (radix > 64)) {
        return MP_VAL;
    }

    if (mp_iszero(a) == MP_YES) {
        *size = 2;
        return MP_OKAY;
    }

    /* special case for binary */
    if (radix == 2) {
        *size = mp_count_bits(a) + ((a->sign == MP_NEG) ? 1 : 0) + 1;
        return MP_OKAY;
    }

    /* digs is the digit count */
    digs = 0;

    /* if it's negative add one for the sign */
    if (a->sign == MP_NEG) {
        ++digs;
    }

    /* init a copy of the input */
    if ((res = mp_init_copy(&t, a)) != MP_OKAY) {
        return res;
    }

    /* force temp to positive */
    t.sign = MP_ZPOS;

    /* fetch out all of the digits */
    while (mp_iszero(&t) == MP_NO) {
        if ((res = mp_div_d(&t, (mp_digit)radix, &t, &d)) != MP_OKAY) {
            mp_clear(&t);
            return res;
        }
        ++digs;
    }
    mp_clear(&t);

    /* return digs + 1, the 1 is for the NULL byte that would be required. */
    *size = digs + 1;
    return MP_OKAY;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_RADIX_SMAP_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* chars used in radix conversions */
const char *mp_s_rmap = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+/";
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_RAND_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* makes a pseudo-random int of a given size */
int
mp_rand(mp_int *a, int digits) {
    int      res;
    mp_digit d;

    mp_zero(a);
    if (digits <= 0) {
        return MP_OKAY;
    }

    /* first place a random non-zero digit */
    do {
        d = ((mp_digit)abs(MP_GEN_RANDOM())) & MP_MASK;
    } while (d == 0);

    if ((res = mp_add_d(a, d, a)) != MP_OKAY) {
        return res;
    }

    while (--digits > 0) {
        if ((res = mp_lshd(a, 1)) != MP_OKAY) {
            return res;
        }

        if ((res = mp_add_d(a, ((mp_digit)abs(MP_GEN_RANDOM())), a)) != MP_OKAY) {
            return res;
        }
    }

    return MP_OKAY;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_READ_RADIX_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* read a string [ASCII] in a given radix */
int mp_read_radix(mp_int *a, const char *str, int radix) {
    int  y, res, neg;
    char ch;

    /* zero the digit bignum */
    mp_zero(a);

    /* make sure the radix is ok */
    if ((radix < 2) || (radix > 64)) {
        return MP_VAL;
    }

    /* if the leading digit is a
     * minus set the sign to negative.
     */
    if (*str == '-') {
        ++str;
        neg = MP_NEG;
    } else {
        neg = MP_ZPOS;
    }

    /* set the integer to the default of zero */
    mp_zero(a);

    /* process each digit of the string */
    while (*str != '\0') {
        /* if the radix <= 36 the conversion is case insensitive
         * this allows numbers like 1AB and 1ab to represent the same  value
         * [e.g. in hex]
         */
        ch = (radix <= 36) ? (char)toupper((int)*str) : *str;
        for (y = 0; y < 64; y++) {
            if (ch == mp_s_rmap[y]) {
                break;
            }
        }

        /* if the char was found in the map
         * and is less than the given radix add it
         * to the number, otherwise exit the loop.
         */
        if (y < radix) {
            if ((res = mp_mul_d(a, (mp_digit)radix, a)) != MP_OKAY) {
                return res;
            }
            if ((res = mp_add_d(a, (mp_digit)y, a)) != MP_OKAY) {
                return res;
            }
        } else {
            break;
        }
        ++str;
    }

    /* set the sign only if a != 0 */
    if (mp_iszero(a) != MP_YES) {
        a->sign = neg;
    }
    return MP_OKAY;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_READ_SIGNED_BIN_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* read signed bin, big endian, first byte is 0==positive or 1==negative */
int mp_read_signed_bin(mp_int *a, const unsigned char *b, int c) {
    int res;

    /* read magnitude */
    if ((res = mp_read_unsigned_bin(a, b + 1, c - 1)) != MP_OKAY) {
        return res;
    }

    /* first byte is 0 for positive, non-zero for negative */
    if (b[0] == 0) {
        a->sign = MP_ZPOS;
    } else {
        a->sign = MP_NEG;
    }

    return MP_OKAY;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_READ_UNSIGNED_BIN_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* reads a unsigned char array, assumes the msb is stored first [big endian] */
int mp_read_unsigned_bin(mp_int *a, const unsigned char *b, int c) {
    int res;

    /* make sure there are at least two digits */
    if (a->alloc < 2) {
        if ((res = mp_grow(a, 2)) != MP_OKAY) {
            return res;
        }
    }

    /* zero the int */
    mp_zero(a);

    /* read the bytes in */
    while (c-- > 0) {
        if ((res = mp_mul_2d(a, 8, a)) != MP_OKAY) {
            return res;
        }

 #ifndef MP_8BIT
        a->dp[0] |= *b++;
        a->used  += 1;
 #else
        a->dp[0]  = (*b & MP_MASK);
        a->dp[1] |= ((*b++ >> 7U) & 1);
        a->used  += 2;
 #endif
    }
    mp_clamp(a);
    return MP_OKAY;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_REDUCE_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* reduces x mod m, assumes 0 < x < m**2, mu is
 * precomputed via mp_reduce_setup.
 * From HAC pp.604 Algorithm 14.42
 */
int mp_reduce(mp_int *x, mp_int *m, mp_int *mu) {
    mp_int q;
    int    res, um = m->used;

    /* q = x */
    if ((res = mp_init_copy(&q, x)) != MP_OKAY) {
        return res;
    }

    /* q1 = x / b**(k-1)  */
    mp_rshd(&q, um - 1);

    /* according to HAC this optimization is ok */
    if (((mp_digit)um) > (((mp_digit)1) << (DIGIT_BIT - 1))) {
        if ((res = mp_mul(&q, mu, &q)) != MP_OKAY) {
            goto CLEANUP;
        }
    } else {
 #ifdef BN_S_MP_MUL_HIGH_DIGS_C
        if ((res = s_mp_mul_high_digs(&q, mu, &q, um)) != MP_OKAY) {
            goto CLEANUP;
        }
 #elif defined(BN_FAST_S_MP_MUL_HIGH_DIGS_C)
        if ((res = fast_s_mp_mul_high_digs(&q, mu, &q, um)) != MP_OKAY) {
            goto CLEANUP;
        }
 #else
        {
            res = MP_VAL;
            goto CLEANUP;
        }
 #endif
    }

    /* q3 = q2 / b**(k+1) */
    mp_rshd(&q, um + 1);

    /* x = x mod b**(k+1), quick (no division) */
    if ((res = mp_mod_2d(x, DIGIT_BIT * (um + 1), x)) != MP_OKAY) {
        goto CLEANUP;
    }

    /* q = q * m mod b**(k+1), quick (no division) */
    if ((res = s_mp_mul_digs(&q, m, &q, um + 1)) != MP_OKAY) {
        goto CLEANUP;
    }

    /* x = x - q */
    if ((res = mp_sub(x, &q, x)) != MP_OKAY) {
        goto CLEANUP;
    }

    /* If x < 0, add b**(k+1) to it */
    if (mp_cmp_d(x, 0) == MP_LT) {
        mp_set(&q, 1);
        if ((res = mp_lshd(&q, um + 1)) != MP_OKAY)
            goto CLEANUP;
        if ((res = mp_add(x, &q, x)) != MP_OKAY)
            goto CLEANUP;
    }

    /* Back off if it's too big */
    while (mp_cmp(x, m) != MP_LT) {
        if ((res = s_mp_sub(x, m, x)) != MP_OKAY) {
            goto CLEANUP;
        }
    }

CLEANUP:
    mp_clear(&q);

    return res;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_REDUCE_2K_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* reduces a modulo n where n is of the form 2**p - d */
int mp_reduce_2k(mp_int *a, mp_int *n, mp_digit d) {
    mp_int q;
    int    p, res;

    if ((res = mp_init(&q)) != MP_OKAY) {
        return res;
    }

    p = mp_count_bits(n);
top:
    /* q = a/2**p, a = a mod 2**p */
    if ((res = mp_div_2d(a, p, &q, a)) != MP_OKAY) {
        goto ERR;
    }

    if (d != 1) {
        /* q = q * d */
        if ((res = mp_mul_d(&q, d, &q)) != MP_OKAY) {
            goto ERR;
        }
    }

    /* a = a + q */
    if ((res = s_mp_add(a, &q, a)) != MP_OKAY) {
        goto ERR;
    }

    if (mp_cmp_mag(a, n) != MP_LT) {
        if ((res = s_mp_sub(a, n, a)) != MP_OKAY) {
            goto ERR;
        }
        goto top;
    }

ERR:
    mp_clear(&q);
    return res;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_REDUCE_2K_L_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* reduces a modulo n where n is of the form 2**p - d
   This differs from reduce_2k since "d" can be larger
   than a single digit.
 */
int mp_reduce_2k_l(mp_int *a, mp_int *n, mp_int *d) {
    mp_int q;
    int    p, res;

    if ((res = mp_init(&q)) != MP_OKAY) {
        return res;
    }

    p = mp_count_bits(n);
top:
    /* q = a/2**p, a = a mod 2**p */
    if ((res = mp_div_2d(a, p, &q, a)) != MP_OKAY) {
        goto ERR;
    }

    /* q = q * d */
    if ((res = mp_mul(&q, d, &q)) != MP_OKAY) {
        goto ERR;
    }

    /* a = a + q */
    if ((res = s_mp_add(a, &q, a)) != MP_OKAY) {
        goto ERR;
    }

    if (mp_cmp_mag(a, n) != MP_LT) {
        if ((res = s_mp_sub(a, n, a)) != MP_OKAY) {
            goto ERR;
        }
        goto top;
    }

ERR:
    mp_clear(&q);
    return res;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_REDUCE_2K_SETUP_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* determines the setup value */
int mp_reduce_2k_setup(mp_int *a, mp_digit *d) {
    int    res, p;
    mp_int tmp;

    if ((res = mp_init(&tmp)) != MP_OKAY) {
        return res;
    }

    p = mp_count_bits(a);
    if ((res = mp_2expt(&tmp, p)) != MP_OKAY) {
        mp_clear(&tmp);
        return res;
    }

    if ((res = s_mp_sub(&tmp, a, &tmp)) != MP_OKAY) {
        mp_clear(&tmp);
        return res;
    }

    *d = tmp.dp[0];
    mp_clear(&tmp);
    return MP_OKAY;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_REDUCE_2K_SETUP_L_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* determines the setup value */
int mp_reduce_2k_setup_l(mp_int *a, mp_int *d) {
    int    res;
    mp_int tmp;

    if ((res = mp_init(&tmp)) != MP_OKAY) {
        return res;
    }

    if ((res = mp_2expt(&tmp, mp_count_bits(a))) != MP_OKAY) {
        goto ERR;
    }

    if ((res = s_mp_sub(&tmp, a, d)) != MP_OKAY) {
        goto ERR;
    }

ERR:
    mp_clear(&tmp);
    return res;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_REDUCE_IS_2K_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* determines if mp_reduce_2k can be used */
int mp_reduce_is_2k(mp_int *a) {
    int      ix, iy, iw;
    mp_digit iz;

    if (a->used == 0) {
        return MP_NO;
    } else if (a->used == 1) {
        return MP_YES;
    } else if (a->used > 1) {
        iy = mp_count_bits(a);
        iz = 1;
        iw = 1;

        /* Test every bit from the second digit up, must be 1 */
        for (ix = DIGIT_BIT; ix < iy; ix++) {
            if ((a->dp[iw] & iz) == 0) {
                return MP_NO;
            }
            iz <<= 1;
            if (iz > (mp_digit)MP_MASK) {
                ++iw;
                iz = 1;
            }
        }
    }
    return MP_YES;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_REDUCE_IS_2K_L_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* determines if reduce_2k_l can be used */
int mp_reduce_is_2k_l(mp_int *a) {
    int ix, iy;

    if (a->used == 0) {
        return MP_NO;
    } else if (a->used == 1) {
        return MP_YES;
    } else if (a->used > 1) {
        /* if more than half of the digits are -1 we're sold */
        for (iy = ix = 0; ix < a->used; ix++) {
            if (a->dp[ix] == MP_MASK) {
                ++iy;
            }
        }
        return (iy >= (a->used / 2)) ? MP_YES : MP_NO;
    }
    return MP_NO;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_REDUCE_SETUP_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* pre-calculate the value required for Barrett reduction
 * For a given modulus "b" it calulates the value required in "a"
 */
int mp_reduce_setup(mp_int *a, mp_int *b) {
    int res;

    if ((res = mp_2expt(a, b->used * 2 * DIGIT_BIT)) != MP_OKAY) {
        return res;
    }
    return mp_div(a, b, a, NULL);
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_RSHD_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* shift right a certain amount of digits */
void mp_rshd(mp_int *a, int b) {
    int x;

    /* if b <= 0 then ignore it */
    if (b <= 0) {
        return;
    }

    /* if b > used then simply zero it and return */
    if (a->used <= b) {
        mp_zero(a);
        return;
    }

    {
        mp_digit *bottom, *top;

        /* shift the digits down */

        /* bottom */
        bottom = a->dp;

        /* top [offset into digits] */
        top = a->dp + b;

        /* this is implemented as a sliding window where
         * the window is b-digits long and digits from
         * the top of the window are copied to the bottom
         *
         * e.g.

           b-2 | b-1 | b0 | b1 | b2 | ... | bb |   ---->
                     /\                   |      ---->
         **\-------------------/      ---->
         */
        for (x = 0; x < (a->used - b); x++) {
            *bottom++ = *top++;
        }

        /* zero the top digits */
        for ( ; x < a->used; x++) {
            *bottom++ = 0;
        }
    }

    /* remove excess digits */
    a->used -= b;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_SET_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* set to a digit */
void mp_set(mp_int *a, mp_digit b) {
    mp_zero(a);
    a->dp[0] = b & MP_MASK;
    a->used  = (a->dp[0] != 0) ? 1 : 0;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_SET_INT_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* set a 32-bit const */
int mp_set_int(mp_int *a, unsigned long b) {
    int x, res;

    mp_zero(a);

    /* set four bits at a time */
    for (x = 0; x < 8; x++) {
        /* shift the number up four bits */
        if ((res = mp_mul_2d(a, 4, a)) != MP_OKAY) {
            return res;
        }

        /* OR in the top four bits of the source */
        a->dp[0] |= (b >> 28) & 15;

        /* shift the source up to the next four bits */
        b <<= 4;

        /* ensure that digits are not clamped off */
        a->used += 1;
    }
    mp_clamp(a);
    return MP_OKAY;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_SET_LONG_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* set a platform dependent unsigned long int */
MP_SET_XLONG(mp_set_long, unsigned long)
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_SET_LONG_LONG_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* set a platform dependent unsigned long long int */
MP_SET_XLONG(mp_set_long_long, unsigned long long)
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_SHRINK_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* shrink a bignum */
int mp_shrink(mp_int *a) {
    mp_digit *tmp;
    int      used = 1;

    if (a->used > 0) {
        used = a->used;
    }

    if (a->alloc != used) {
        if ((tmp = OPT_CAST(mp_digit) XREALLOC(a->dp, sizeof(mp_digit) * used)) == NULL) {
            return MP_MEM;
        }
        a->dp    = tmp;
        a->alloc = used;
    }
    return MP_OKAY;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_SIGNED_BIN_SIZE_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* get the size for an signed equivalent */
int mp_signed_bin_size(mp_int *a) {
    return 1 + mp_unsigned_bin_size(a);
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_SQR_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* computes b = a*a */
int
mp_sqr(mp_int *a, mp_int *b) {
    int res;

 #ifdef BN_MP_TOOM_SQR_C
    /* use Toom-Cook? */
    if (a->used >= TOOM_SQR_CUTOFF) {
        res = mp_toom_sqr(a, b);
        /* Karatsuba? */
    } else
 #endif
 #ifdef BN_MP_KARATSUBA_SQR_C
    if (a->used >= KARATSUBA_SQR_CUTOFF) {
        res = mp_karatsuba_sqr(a, b);
    } else
 #endif
    {
 #ifdef BN_FAST_S_MP_SQR_C
        /* can we use the fast comba multiplier? */
        if ((((a->used * 2) + 1) < MP_WARRAY) &&
            (a->used <
             (1 << (((sizeof(mp_word) * CHAR_BIT) - (2 * DIGIT_BIT)) - 1)))) {
            res = fast_s_mp_sqr(a, b);
        } else
 #endif
        {
 #ifdef BN_S_MP_SQR_C
            res = s_mp_sqr(a, b);
 #else
            res = MP_VAL;
 #endif
        }
    }
    b->sign = MP_ZPOS;
    return res;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_SQRMOD_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* c = a * a (mod b) */
int
mp_sqrmod(mp_int *a, mp_int *b, mp_int *c) {
    int    res;
    mp_int t;

    if ((res = mp_init(&t)) != MP_OKAY) {
        return res;
    }

    if ((res = mp_sqr(a, &t)) != MP_OKAY) {
        mp_clear(&t);
        return res;
    }
    res = mp_mod(&t, b, c);
    mp_clear(&t);
    return res;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_SQRT_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* this function is less generic than mp_n_root, simpler and faster */
int mp_sqrt(mp_int *arg, mp_int *ret) {
    int    res;
    mp_int t1, t2;

    /* must be positive */
    if (arg->sign == MP_NEG) {
        return MP_VAL;
    }

    /* easy out */
    if (mp_iszero(arg) == MP_YES) {
        mp_zero(ret);
        return MP_OKAY;
    }

    if ((res = mp_init_copy(&t1, arg)) != MP_OKAY) {
        return res;
    }

    if ((res = mp_init(&t2)) != MP_OKAY) {
        goto E2;
    }

    /* First approx. (not very bad for large arg) */
    mp_rshd(&t1, t1.used / 2);

    /* t1 > 0  */
    if ((res = mp_div(arg, &t1, &t2, NULL)) != MP_OKAY) {
        goto E1;
    }
    if ((res = mp_add(&t1, &t2, &t1)) != MP_OKAY) {
        goto E1;
    }
    if ((res = mp_div_2(&t1, &t1)) != MP_OKAY) {
        goto E1;
    }
    /* And now t1 > sqrt(arg) */
    do {
        if ((res = mp_div(arg, &t1, &t2, NULL)) != MP_OKAY) {
            goto E1;
        }
        if ((res = mp_add(&t1, &t2, &t1)) != MP_OKAY) {
            goto E1;
        }
        if ((res = mp_div_2(&t1, &t1)) != MP_OKAY) {
            goto E1;
        }
        /* t1 >= sqrt(arg) >= t2 at this point */
    } while (mp_cmp_mag(&t1, &t2) == MP_GT);

    mp_exch(&t1, ret);

E1: mp_clear(&t2);
E2: mp_clear(&t1);
    return res;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_SQRTMOD_PRIME_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 */

/* Tonelli-Shanks algorithm
 * https://en.wikipedia.org/wiki/Tonelli%E2%80%93Shanks_algorithm
 * https://gmplib.org/list-archives/gmp-discuss/2013-April/005300.html
 *
 */

int mp_sqrtmod_prime(mp_int *n, mp_int *prime, mp_int *ret) {
    int      res, legendre;
    mp_int   t1, C, Q, S, Z, M, T, R, two;
    mp_digit i;

    /* first handle the simple cases */
    if (mp_cmp_d(n, 0) == MP_EQ) {
        mp_zero(ret);
        return MP_OKAY;
    }
    if (mp_cmp_d(prime, 2) == MP_EQ) return MP_VAL;                            /* prime must be odd */
    if ((res = mp_jacobi(n, prime, &legendre)) != MP_OKAY) return res;
    if (legendre == -1) return MP_VAL;                                         /* quadratic non-residue mod prime */

    if ((res = mp_init_multi(&t1, &C, &Q, &S, &Z, &M, &T, &R, &two, NULL)) != MP_OKAY) {
        return res;
    }

    /* SPECIAL CASE: if prime mod 4 == 3
     * compute directly: res = n^(prime+1)/4 mod prime
     * Handbook of Applied Cryptography algorithm 3.36
     */
    if ((res = mp_mod_d(prime, 4, &i)) != MP_OKAY) goto cleanup;
    if (i == 3) {
        if ((res = mp_add_d(prime, 1, &t1)) != MP_OKAY) goto cleanup;
        if ((res = mp_div_2(&t1, &t1)) != MP_OKAY) goto cleanup;
        if ((res = mp_div_2(&t1, &t1)) != MP_OKAY) goto cleanup;
        if ((res = mp_exptmod(n, &t1, prime, ret)) != MP_OKAY) goto cleanup;
        res = MP_OKAY;
        goto cleanup;
    }

    /* NOW: Tonelli-Shanks algorithm */

    /* factor out powers of 2 from prime-1, defining Q and S as: prime-1 = Q*2^S */
    if ((res = mp_copy(prime, &Q)) != MP_OKAY) goto cleanup;
    if ((res = mp_sub_d(&Q, 1, &Q)) != MP_OKAY) goto cleanup;
    /* Q = prime - 1 */
    mp_zero(&S);
    /* S = 0 */
    while (mp_iseven(&Q) != MP_NO) {
        if ((res = mp_div_2(&Q, &Q)) != MP_OKAY) goto cleanup;
        /* Q = Q / 2 */
        if ((res = mp_add_d(&S, 1, &S)) != MP_OKAY) goto cleanup;
        /* S = S + 1 */
    }

    /* find a Z such that the Legendre symbol (Z|prime) == -1 */
    if ((res = mp_set_int(&Z, 2)) != MP_OKAY) goto cleanup;
    /* Z = 2 */
    while (1) {
        if ((res = mp_jacobi(&Z, prime, &legendre)) != MP_OKAY) goto cleanup;
        if (legendre == -1) break;
        if ((res = mp_add_d(&Z, 1, &Z)) != MP_OKAY) goto cleanup;
        /* Z = Z + 1 */
    }

    if ((res = mp_exptmod(&Z, &Q, prime, &C)) != MP_OKAY) goto cleanup;
    /* C = Z ^ Q mod prime */
    if ((res = mp_add_d(&Q, 1, &t1)) != MP_OKAY) goto cleanup;
    if ((res = mp_div_2(&t1, &t1)) != MP_OKAY) goto cleanup;
    /* t1 = (Q + 1) / 2 */
    if ((res = mp_exptmod(n, &t1, prime, &R)) != MP_OKAY) goto cleanup;
    /* R = n ^ ((Q + 1) / 2) mod prime */
    if ((res = mp_exptmod(n, &Q, prime, &T)) != MP_OKAY) goto cleanup;
    /* T = n ^ Q mod prime */
    if ((res = mp_copy(&S, &M)) != MP_OKAY) goto cleanup;
    /* M = S */
    if ((res = mp_set_int(&two, 2)) != MP_OKAY) goto cleanup;

    res = MP_VAL;
    while (1) {
        if ((res = mp_copy(&T, &t1)) != MP_OKAY) goto cleanup;
        i = 0;
        while (1) {
            if (mp_cmp_d(&t1, 1) == MP_EQ) break;
            if ((res = mp_exptmod(&t1, &two, prime, &t1)) != MP_OKAY) goto cleanup;
            i++;
        }
        if (i == 0) {
            if ((res = mp_copy(&R, ret)) != MP_OKAY) goto cleanup;
            res = MP_OKAY;
            goto cleanup;
        }
        if ((res = mp_sub_d(&M, i, &t1)) != MP_OKAY) goto cleanup;
        if ((res = mp_sub_d(&t1, 1, &t1)) != MP_OKAY) goto cleanup;
        if ((res = mp_exptmod(&two, &t1, prime, &t1)) != MP_OKAY) goto cleanup;
        /* t1 = 2 ^ (M - i - 1) */
        if ((res = mp_exptmod(&C, &t1, prime, &t1)) != MP_OKAY) goto cleanup;
        /* t1 = C ^ (2 ^ (M - i - 1)) mod prime */
        if ((res = mp_sqrmod(&t1, prime, &C)) != MP_OKAY) goto cleanup;
        /* C = (t1 * t1) mod prime */
        if ((res = mp_mulmod(&R, &t1, prime, &R)) != MP_OKAY) goto cleanup;
        /* R = (R * t1) mod prime */
        if ((res = mp_mulmod(&T, &C, prime, &T)) != MP_OKAY) goto cleanup;
        /* T = (T * C) mod prime */
        mp_set(&M, i);
        /* M = i */
    }

cleanup:
    mp_clear_multi(&t1, &C, &Q, &S, &Z, &M, &T, &R, &two, NULL);
    return res;
}
#endif



#ifdef BN_MP_SUB_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* high level subtraction (handles signs) */
int
mp_sub(mp_int *a, mp_int *b, mp_int *c) {
    int sa, sb, res;

    sa = a->sign;
    sb = b->sign;

    if (sa != sb) {
        /* subtract a negative from a positive, OR */
        /* subtract a positive from a negative. */
        /* In either case, ADD their magnitudes, */
        /* and use the sign of the first number. */
        c->sign = sa;
        res     = s_mp_add(a, b, c);
    } else {
        /* subtract a positive from a positive, OR */
        /* subtract a negative from a negative. */
        /* First, take the difference between their */
        /* magnitudes, then... */
        if (mp_cmp_mag(a, b) != MP_LT) {
            /* Copy the sign from the first */
            c->sign = sa;
            /* The first has a larger or equal magnitude */
            res = s_mp_sub(a, b, c);
        } else {
            /* The result has the *opposite* sign from */
            /* the first number. */
            c->sign = (sa == MP_ZPOS) ? MP_NEG : MP_ZPOS;
            /* The second has a larger magnitude */
            res = s_mp_sub(b, a, c);
        }
    }
    return res;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_SUB_D_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* single digit subtraction */
int
mp_sub_d(mp_int *a, mp_digit b, mp_int *c) {
    mp_digit *tmpa, *tmpc, mu;
    int      res, ix, oldused;

    /* grow c as required */
    if (c->alloc < (a->used + 1)) {
        if ((res = mp_grow(c, a->used + 1)) != MP_OKAY) {
            return res;
        }
    }

    /* if a is negative just do an unsigned
     * addition [with fudged signs]
     */
    if (a->sign == MP_NEG) {
        a->sign = MP_ZPOS;
        res     = mp_add_d(a, b, c);
        a->sign = c->sign = MP_NEG;

        /* clamp */
        mp_clamp(c);

        return res;
    }

    /* setup regs */
    oldused = c->used;
    tmpa    = a->dp;
    tmpc    = c->dp;

    /* if a <= b simply fix the single digit */
    if (((a->used == 1) && (a->dp[0] <= b)) || (a->used == 0)) {
        if (a->used == 1) {
            *tmpc++ = b - *tmpa;
        } else {
            *tmpc++ = b;
        }
        ix = 1;

        /* negative/1digit */
        c->sign = MP_NEG;
        c->used = 1;
    } else {
        /* positive/size */
        c->sign = MP_ZPOS;
        c->used = a->used;

        /* subtract first digit */
        *tmpc    = *tmpa++ - b;
        mu       = *tmpc >> ((sizeof(mp_digit) * CHAR_BIT) - 1);
        *tmpc++ &= MP_MASK;

        /* handle rest of the digits */
        for (ix = 1; ix < a->used; ix++) {
            *tmpc    = *tmpa++ - mu;
            mu       = *tmpc >> ((sizeof(mp_digit) * CHAR_BIT) - 1);
            *tmpc++ &= MP_MASK;
        }
    }

    /* zero excess digits */
    while (ix++ < oldused) {
        *tmpc++ = 0;
    }
    mp_clamp(c);
    return MP_OKAY;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_SUBMOD_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* d = a - b (mod c) */
int
mp_submod(mp_int *a, mp_int *b, mp_int *c, mp_int *d) {
    int    res;
    mp_int t;


    if ((res = mp_init(&t)) != MP_OKAY) {
        return res;
    }

    if ((res = mp_sub(a, b, &t)) != MP_OKAY) {
        mp_clear(&t);
        return res;
    }
    res = mp_mod(&t, c, d);
    mp_clear(&t);
    return res;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_TO_SIGNED_BIN_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* store in signed [big endian] format */
int mp_to_signed_bin(mp_int *a, unsigned char *b) {
    int res;

    if ((res = mp_to_unsigned_bin(a, b + 1)) != MP_OKAY) {
        return res;
    }
    b[0] = (a->sign == MP_ZPOS) ? (unsigned char)0 : (unsigned char)1;
    return MP_OKAY;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_TO_SIGNED_BIN_N_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* store in signed [big endian] format */
int mp_to_signed_bin_n(mp_int *a, unsigned char *b, unsigned long *outlen) {
    if (*outlen < (unsigned long)mp_signed_bin_size(a)) {
        return MP_VAL;
    }
    *outlen = mp_signed_bin_size(a);
    return mp_to_signed_bin(a, b);
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_TO_UNSIGNED_BIN_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* store in unsigned [big endian] format */
int mp_to_unsigned_bin(mp_int *a, unsigned char *b) {
    int    x, res;
    mp_int t;

    if ((res = mp_init_copy(&t, a)) != MP_OKAY) {
        return res;
    }

    x = 0;
    while (mp_iszero(&t) == MP_NO) {
 #ifndef MP_8BIT
        b[x++] = (unsigned char)(t.dp[0] & 255);
 #else
        b[x++] = (unsigned char)(t.dp[0] | ((t.dp[1] & 0x01) << 7));
 #endif
        if ((res = mp_div_2d(&t, 8, &t, NULL)) != MP_OKAY) {
            mp_clear(&t);
            return res;
        }
    }
    bn_reverse(b, x);
    mp_clear(&t);
    return MP_OKAY;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_TOOM_MUL_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* multiplication using the Toom-Cook 3-way algorithm
 *
 * Much more complicated than Karatsuba but has a lower
 * asymptotic running time of O(N**1.464).  This algorithm is
 * only particularly useful on VERY large inputs
 * (we're talking 1000s of digits here...).
 */
int mp_toom_mul(mp_int *a, mp_int *b, mp_int *c) {
    mp_int w0, w1, w2, w3, w4, tmp1, tmp2, a0, a1, a2, b0, b1, b2;
    int    res, B;

    /* init temps */
    if ((res = mp_init_multi(&w0, &w1, &w2, &w3, &w4,
                             &a0, &a1, &a2, &b0, &b1,
                             &b2, &tmp1, &tmp2, NULL)) != MP_OKAY) {
        return res;
    }

    /* B */
    B = MIN(a->used, b->used) / 3;

    /* a = a2 * B**2 + a1 * B + a0 */
    if ((res = mp_mod_2d(a, DIGIT_BIT * B, &a0)) != MP_OKAY) {
        goto ERR;
    }

    if ((res = mp_copy(a, &a1)) != MP_OKAY) {
        goto ERR;
    }
    mp_rshd(&a1, B);
    if ((res = mp_mod_2d(&a1, DIGIT_BIT * B, &a1)) != MP_OKAY) {
        goto ERR;
    }

    if ((res = mp_copy(a, &a2)) != MP_OKAY) {
        goto ERR;
    }
    mp_rshd(&a2, B * 2);

    /* b = b2 * B**2 + b1 * B + b0 */
    if ((res = mp_mod_2d(b, DIGIT_BIT * B, &b0)) != MP_OKAY) {
        goto ERR;
    }

    if ((res = mp_copy(b, &b1)) != MP_OKAY) {
        goto ERR;
    }
    mp_rshd(&b1, B);
    (void)mp_mod_2d(&b1, DIGIT_BIT * B, &b1);

    if ((res = mp_copy(b, &b2)) != MP_OKAY) {
        goto ERR;
    }
    mp_rshd(&b2, B * 2);

    /* w0 = a0*b0 */
    if ((res = mp_mul(&a0, &b0, &w0)) != MP_OKAY) {
        goto ERR;
    }

    /* w4 = a2 * b2 */
    if ((res = mp_mul(&a2, &b2, &w4)) != MP_OKAY) {
        goto ERR;
    }

    /* w1 = (a2 + 2(a1 + 2a0))(b2 + 2(b1 + 2b0)) */
    if ((res = mp_mul_2(&a0, &tmp1)) != MP_OKAY) {
        goto ERR;
    }
    if ((res = mp_add(&tmp1, &a1, &tmp1)) != MP_OKAY) {
        goto ERR;
    }
    if ((res = mp_mul_2(&tmp1, &tmp1)) != MP_OKAY) {
        goto ERR;
    }
    if ((res = mp_add(&tmp1, &a2, &tmp1)) != MP_OKAY) {
        goto ERR;
    }

    if ((res = mp_mul_2(&b0, &tmp2)) != MP_OKAY) {
        goto ERR;
    }
    if ((res = mp_add(&tmp2, &b1, &tmp2)) != MP_OKAY) {
        goto ERR;
    }
    if ((res = mp_mul_2(&tmp2, &tmp2)) != MP_OKAY) {
        goto ERR;
    }
    if ((res = mp_add(&tmp2, &b2, &tmp2)) != MP_OKAY) {
        goto ERR;
    }

    if ((res = mp_mul(&tmp1, &tmp2, &w1)) != MP_OKAY) {
        goto ERR;
    }

    /* w3 = (a0 + 2(a1 + 2a2))(b0 + 2(b1 + 2b2)) */
    if ((res = mp_mul_2(&a2, &tmp1)) != MP_OKAY) {
        goto ERR;
    }
    if ((res = mp_add(&tmp1, &a1, &tmp1)) != MP_OKAY) {
        goto ERR;
    }
    if ((res = mp_mul_2(&tmp1, &tmp1)) != MP_OKAY) {
        goto ERR;
    }
    if ((res = mp_add(&tmp1, &a0, &tmp1)) != MP_OKAY) {
        goto ERR;
    }

    if ((res = mp_mul_2(&b2, &tmp2)) != MP_OKAY) {
        goto ERR;
    }
    if ((res = mp_add(&tmp2, &b1, &tmp2)) != MP_OKAY) {
        goto ERR;
    }
    if ((res = mp_mul_2(&tmp2, &tmp2)) != MP_OKAY) {
        goto ERR;
    }
    if ((res = mp_add(&tmp2, &b0, &tmp2)) != MP_OKAY) {
        goto ERR;
    }

    if ((res = mp_mul(&tmp1, &tmp2, &w3)) != MP_OKAY) {
        goto ERR;
    }


    /* w2 = (a2 + a1 + a0)(b2 + b1 + b0) */
    if ((res = mp_add(&a2, &a1, &tmp1)) != MP_OKAY) {
        goto ERR;
    }
    if ((res = mp_add(&tmp1, &a0, &tmp1)) != MP_OKAY) {
        goto ERR;
    }
    if ((res = mp_add(&b2, &b1, &tmp2)) != MP_OKAY) {
        goto ERR;
    }
    if ((res = mp_add(&tmp2, &b0, &tmp2)) != MP_OKAY) {
        goto ERR;
    }
    if ((res = mp_mul(&tmp1, &tmp2, &w2)) != MP_OKAY) {
        goto ERR;
    }

    /* now solve the matrix

       0  0  0  0  1
       1  2  4  8  16
       1  1  1  1  1
       16 8  4  2  1
       1  0  0  0  0

       using 12 subtractions, 4 shifts,
              2 small divisions and 1 small multiplication
     */

    /* r1 - r4 */
    if ((res = mp_sub(&w1, &w4, &w1)) != MP_OKAY) {
        goto ERR;
    }
    /* r3 - r0 */
    if ((res = mp_sub(&w3, &w0, &w3)) != MP_OKAY) {
        goto ERR;
    }
    /* r1/2 */
    if ((res = mp_div_2(&w1, &w1)) != MP_OKAY) {
        goto ERR;
    }
    /* r3/2 */
    if ((res = mp_div_2(&w3, &w3)) != MP_OKAY) {
        goto ERR;
    }
    /* r2 - r0 - r4 */
    if ((res = mp_sub(&w2, &w0, &w2)) != MP_OKAY) {
        goto ERR;
    }
    if ((res = mp_sub(&w2, &w4, &w2)) != MP_OKAY) {
        goto ERR;
    }
    /* r1 - r2 */
    if ((res = mp_sub(&w1, &w2, &w1)) != MP_OKAY) {
        goto ERR;
    }
    /* r3 - r2 */
    if ((res = mp_sub(&w3, &w2, &w3)) != MP_OKAY) {
        goto ERR;
    }
    /* r1 - 8r0 */
    if ((res = mp_mul_2d(&w0, 3, &tmp1)) != MP_OKAY) {
        goto ERR;
    }
    if ((res = mp_sub(&w1, &tmp1, &w1)) != MP_OKAY) {
        goto ERR;
    }
    /* r3 - 8r4 */
    if ((res = mp_mul_2d(&w4, 3, &tmp1)) != MP_OKAY) {
        goto ERR;
    }
    if ((res = mp_sub(&w3, &tmp1, &w3)) != MP_OKAY) {
        goto ERR;
    }
    /* 3r2 - r1 - r3 */
    if ((res = mp_mul_d(&w2, 3, &w2)) != MP_OKAY) {
        goto ERR;
    }
    if ((res = mp_sub(&w2, &w1, &w2)) != MP_OKAY) {
        goto ERR;
    }
    if ((res = mp_sub(&w2, &w3, &w2)) != MP_OKAY) {
        goto ERR;
    }
    /* r1 - r2 */
    if ((res = mp_sub(&w1, &w2, &w1)) != MP_OKAY) {
        goto ERR;
    }
    /* r3 - r2 */
    if ((res = mp_sub(&w3, &w2, &w3)) != MP_OKAY) {
        goto ERR;
    }
    /* r1/3 */
    if ((res = mp_div_3(&w1, &w1, NULL)) != MP_OKAY) {
        goto ERR;
    }
    /* r3/3 */
    if ((res = mp_div_3(&w3, &w3, NULL)) != MP_OKAY) {
        goto ERR;
    }

    /* at this point shift W[n] by B*n */
    if ((res = mp_lshd(&w1, 1 * B)) != MP_OKAY) {
        goto ERR;
    }
    if ((res = mp_lshd(&w2, 2 * B)) != MP_OKAY) {
        goto ERR;
    }
    if ((res = mp_lshd(&w3, 3 * B)) != MP_OKAY) {
        goto ERR;
    }
    if ((res = mp_lshd(&w4, 4 * B)) != MP_OKAY) {
        goto ERR;
    }

    if ((res = mp_add(&w0, &w1, c)) != MP_OKAY) {
        goto ERR;
    }
    if ((res = mp_add(&w2, &w3, &tmp1)) != MP_OKAY) {
        goto ERR;
    }
    if ((res = mp_add(&w4, &tmp1, &tmp1)) != MP_OKAY) {
        goto ERR;
    }
    if ((res = mp_add(&tmp1, c, c)) != MP_OKAY) {
        goto ERR;
    }

ERR:
    mp_clear_multi(&w0, &w1, &w2, &w3, &w4,
                   &a0, &a1, &a2, &b0, &b1,
                   &b2, &tmp1, &tmp2, NULL);
    return res;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_TOOM_SQR_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* squaring using Toom-Cook 3-way algorithm */
int
mp_toom_sqr(mp_int *a, mp_int *b) {
    mp_int w0, w1, w2, w3, w4, tmp1, a0, a1, a2;
    int    res, B;

    /* init temps */
    if ((res = mp_init_multi(&w0, &w1, &w2, &w3, &w4, &a0, &a1, &a2, &tmp1, NULL)) != MP_OKAY) {
        return res;
    }

    /* B */
    B = a->used / 3;

    /* a = a2 * B**2 + a1 * B + a0 */
    if ((res = mp_mod_2d(a, DIGIT_BIT * B, &a0)) != MP_OKAY) {
        goto ERR;
    }

    if ((res = mp_copy(a, &a1)) != MP_OKAY) {
        goto ERR;
    }
    mp_rshd(&a1, B);
    if ((res = mp_mod_2d(&a1, DIGIT_BIT * B, &a1)) != MP_OKAY) {
        goto ERR;
    }

    if ((res = mp_copy(a, &a2)) != MP_OKAY) {
        goto ERR;
    }
    mp_rshd(&a2, B * 2);

    /* w0 = a0*a0 */
    if ((res = mp_sqr(&a0, &w0)) != MP_OKAY) {
        goto ERR;
    }

    /* w4 = a2 * a2 */
    if ((res = mp_sqr(&a2, &w4)) != MP_OKAY) {
        goto ERR;
    }

    /* w1 = (a2 + 2(a1 + 2a0))**2 */
    if ((res = mp_mul_2(&a0, &tmp1)) != MP_OKAY) {
        goto ERR;
    }
    if ((res = mp_add(&tmp1, &a1, &tmp1)) != MP_OKAY) {
        goto ERR;
    }
    if ((res = mp_mul_2(&tmp1, &tmp1)) != MP_OKAY) {
        goto ERR;
    }
    if ((res = mp_add(&tmp1, &a2, &tmp1)) != MP_OKAY) {
        goto ERR;
    }

    if ((res = mp_sqr(&tmp1, &w1)) != MP_OKAY) {
        goto ERR;
    }

    /* w3 = (a0 + 2(a1 + 2a2))**2 */
    if ((res = mp_mul_2(&a2, &tmp1)) != MP_OKAY) {
        goto ERR;
    }
    if ((res = mp_add(&tmp1, &a1, &tmp1)) != MP_OKAY) {
        goto ERR;
    }
    if ((res = mp_mul_2(&tmp1, &tmp1)) != MP_OKAY) {
        goto ERR;
    }
    if ((res = mp_add(&tmp1, &a0, &tmp1)) != MP_OKAY) {
        goto ERR;
    }

    if ((res = mp_sqr(&tmp1, &w3)) != MP_OKAY) {
        goto ERR;
    }


    /* w2 = (a2 + a1 + a0)**2 */
    if ((res = mp_add(&a2, &a1, &tmp1)) != MP_OKAY) {
        goto ERR;
    }
    if ((res = mp_add(&tmp1, &a0, &tmp1)) != MP_OKAY) {
        goto ERR;
    }
    if ((res = mp_sqr(&tmp1, &w2)) != MP_OKAY) {
        goto ERR;
    }

    /* now solve the matrix

       0  0  0  0  1
       1  2  4  8  16
       1  1  1  1  1
       16 8  4  2  1
       1  0  0  0  0

       using 12 subtractions, 4 shifts, 2 small divisions and 1 small multiplication.
     */

    /* r1 - r4 */
    if ((res = mp_sub(&w1, &w4, &w1)) != MP_OKAY) {
        goto ERR;
    }
    /* r3 - r0 */
    if ((res = mp_sub(&w3, &w0, &w3)) != MP_OKAY) {
        goto ERR;
    }
    /* r1/2 */
    if ((res = mp_div_2(&w1, &w1)) != MP_OKAY) {
        goto ERR;
    }
    /* r3/2 */
    if ((res = mp_div_2(&w3, &w3)) != MP_OKAY) {
        goto ERR;
    }
    /* r2 - r0 - r4 */
    if ((res = mp_sub(&w2, &w0, &w2)) != MP_OKAY) {
        goto ERR;
    }
    if ((res = mp_sub(&w2, &w4, &w2)) != MP_OKAY) {
        goto ERR;
    }
    /* r1 - r2 */
    if ((res = mp_sub(&w1, &w2, &w1)) != MP_OKAY) {
        goto ERR;
    }
    /* r3 - r2 */
    if ((res = mp_sub(&w3, &w2, &w3)) != MP_OKAY) {
        goto ERR;
    }
    /* r1 - 8r0 */
    if ((res = mp_mul_2d(&w0, 3, &tmp1)) != MP_OKAY) {
        goto ERR;
    }
    if ((res = mp_sub(&w1, &tmp1, &w1)) != MP_OKAY) {
        goto ERR;
    }
    /* r3 - 8r4 */
    if ((res = mp_mul_2d(&w4, 3, &tmp1)) != MP_OKAY) {
        goto ERR;
    }
    if ((res = mp_sub(&w3, &tmp1, &w3)) != MP_OKAY) {
        goto ERR;
    }
    /* 3r2 - r1 - r3 */
    if ((res = mp_mul_d(&w2, 3, &w2)) != MP_OKAY) {
        goto ERR;
    }
    if ((res = mp_sub(&w2, &w1, &w2)) != MP_OKAY) {
        goto ERR;
    }
    if ((res = mp_sub(&w2, &w3, &w2)) != MP_OKAY) {
        goto ERR;
    }
    /* r1 - r2 */
    if ((res = mp_sub(&w1, &w2, &w1)) != MP_OKAY) {
        goto ERR;
    }
    /* r3 - r2 */
    if ((res = mp_sub(&w3, &w2, &w3)) != MP_OKAY) {
        goto ERR;
    }
    /* r1/3 */
    if ((res = mp_div_3(&w1, &w1, NULL)) != MP_OKAY) {
        goto ERR;
    }
    /* r3/3 */
    if ((res = mp_div_3(&w3, &w3, NULL)) != MP_OKAY) {
        goto ERR;
    }

    /* at this point shift W[n] by B*n */
    if ((res = mp_lshd(&w1, 1 * B)) != MP_OKAY) {
        goto ERR;
    }
    if ((res = mp_lshd(&w2, 2 * B)) != MP_OKAY) {
        goto ERR;
    }
    if ((res = mp_lshd(&w3, 3 * B)) != MP_OKAY) {
        goto ERR;
    }
    if ((res = mp_lshd(&w4, 4 * B)) != MP_OKAY) {
        goto ERR;
    }

    if ((res = mp_add(&w0, &w1, b)) != MP_OKAY) {
        goto ERR;
    }
    if ((res = mp_add(&w2, &w3, &tmp1)) != MP_OKAY) {
        goto ERR;
    }
    if ((res = mp_add(&w4, &tmp1, &tmp1)) != MP_OKAY) {
        goto ERR;
    }
    if ((res = mp_add(&tmp1, b, b)) != MP_OKAY) {
        goto ERR;
    }

ERR:
    mp_clear_multi(&w0, &w1, &w2, &w3, &w4, &a0, &a1, &a2, &tmp1, NULL);
    return res;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_TORADIX_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* stores a bignum as a ASCII string in a given radix (2..64) */
int mp_toradix(mp_int *a, char *str, int radix) {
    int      res, digs;
    mp_int   t;
    mp_digit d;
    char     *_s = str;

    /* check range of the radix */
    if ((radix < 2) || (radix > 64)) {
        return MP_VAL;
    }

    /* quick out if its zero */
    if (mp_iszero(a) == MP_YES) {
        *str++ = '0';
        *str   = '\0';
        return MP_OKAY;
    }

    if ((res = mp_init_copy(&t, a)) != MP_OKAY) {
        return res;
    }

    /* if it is negative output a - */
    if (t.sign == MP_NEG) {
        ++_s;
        *str++ = '-';
        t.sign = MP_ZPOS;
    }

    digs = 0;
    while (mp_iszero(&t) == MP_NO) {
        if ((res = mp_div_d(&t, (mp_digit)radix, &t, &d)) != MP_OKAY) {
            mp_clear(&t);
            return res;
        }
        *str++ = mp_s_rmap[d];
        ++digs;
    }

    /* reverse the digits of the string.  In this case _s points
     * to the first digit [exluding the sign] of the number]
     */
    bn_reverse((unsigned char *)_s, digs);

    /* append a NULL so the string is properly terminated */
    *str = '\0';

    mp_clear(&t);
    return MP_OKAY;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_UNSIGNED_BIN_SIZE_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* get the size for an unsigned equivalent */
int mp_unsigned_bin_size(mp_int *a) {
    int size = mp_count_bits(a);

    return (size / 8) + (((size & 7) != 0) ? 1 : 0);
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_XOR_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* XOR two ints together */
int
mp_xor(mp_int *a, mp_int *b, mp_int *c) {
    int    res, ix, px;
    mp_int t, *x;

    if (a->used > b->used) {
        if ((res = mp_init_copy(&t, a)) != MP_OKAY) {
            return res;
        }
        px = b->used;
        x  = b;
    } else {
        if ((res = mp_init_copy(&t, b)) != MP_OKAY) {
            return res;
        }
        px = a->used;
        x  = a;
    }

    for (ix = 0; ix < px; ix++) {
        t.dp[ix] ^= x->dp[ix];
    }
    mp_clamp(&t);
    mp_exch(c, &t);
    mp_clear(&t);
    return MP_OKAY;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_MP_ZERO_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* set to zero */
void mp_zero(mp_int *a) {
    int      n;
    mp_digit *tmp;

    a->sign = MP_ZPOS;
    a->used = 0;

    tmp = a->dp;
    for (n = 0; n < a->alloc; n++) {
        *tmp++ = 0;
    }
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_PRIME_TAB_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */
const mp_digit ltm_prime_tab[] = {
    0x0002, 0x0003, 0x0005, 0x0007, 0x000B, 0x000D, 0x0011, 0x0013,
    0x0017, 0x001D, 0x001F, 0x0025, 0x0029, 0x002B, 0x002F, 0x0035,
    0x003B, 0x003D, 0x0043, 0x0047, 0x0049, 0x004F, 0x0053, 0x0059,
    0x0061, 0x0065, 0x0067, 0x006B, 0x006D, 0x0071, 0x007F,
 #ifndef MP_8BIT
    0x0083,
    0x0089, 0x008B, 0x0095, 0x0097, 0x009D, 0x00A3, 0x00A7, 0x00AD,
    0x00B3, 0x00B5, 0x00BF, 0x00C1, 0x00C5, 0x00C7, 0x00D3, 0x00DF,
    0x00E3, 0x00E5, 0x00E9, 0x00EF, 0x00F1, 0x00FB, 0x0101, 0x0107,
    0x010D, 0x010F, 0x0115, 0x0119, 0x011B, 0x0125, 0x0133, 0x0137,

    0x0139, 0x013D, 0x014B, 0x0151, 0x015B, 0x015D, 0x0161, 0x0167,
    0x016F, 0x0175, 0x017B, 0x017F, 0x0185, 0x018D, 0x0191, 0x0199,
    0x01A3, 0x01A5, 0x01AF, 0x01B1, 0x01B7, 0x01BB, 0x01C1, 0x01C9,
    0x01CD, 0x01CF, 0x01D3, 0x01DF, 0x01E7, 0x01EB, 0x01F3, 0x01F7,
    0x01FD, 0x0209, 0x020B, 0x021D, 0x0223, 0x022D, 0x0233, 0x0239,
    0x023B, 0x0241, 0x024B, 0x0251, 0x0257, 0x0259, 0x025F, 0x0265,
    0x0269, 0x026B, 0x0277, 0x0281, 0x0283, 0x0287, 0x028D, 0x0293,
    0x0295, 0x02A1, 0x02A5, 0x02AB, 0x02B3, 0x02BD, 0x02C5, 0x02CF,

    0x02D7, 0x02DD, 0x02E3, 0x02E7, 0x02EF, 0x02F5, 0x02F9, 0x0301,
    0x0305, 0x0313, 0x031D, 0x0329, 0x032B, 0x0335, 0x0337, 0x033B,
    0x033D, 0x0347, 0x0355, 0x0359, 0x035B, 0x035F, 0x036D, 0x0371,
    0x0373, 0x0377, 0x038B, 0x038F, 0x0397, 0x03A1, 0x03A9, 0x03AD,
    0x03B3, 0x03B9, 0x03C7, 0x03CB, 0x03D1, 0x03D7, 0x03DF, 0x03E5,
    0x03F1, 0x03F5, 0x03FB, 0x03FD, 0x0407, 0x0409, 0x040F, 0x0419,
    0x041B, 0x0425, 0x0427, 0x042D, 0x043F, 0x0443, 0x0445, 0x0449,
    0x044F, 0x0455, 0x045D, 0x0463, 0x0469, 0x047F, 0x0481, 0x048B,

    0x0493, 0x049D, 0x04A3, 0x04A9, 0x04B1, 0x04BD, 0x04C1, 0x04C7,
    0x04CD, 0x04CF, 0x04D5, 0x04E1, 0x04EB, 0x04FD, 0x04FF, 0x0503,
    0x0509, 0x050B, 0x0511, 0x0515, 0x0517, 0x051B, 0x0527, 0x0529,
    0x052F, 0x0551, 0x0557, 0x055D, 0x0565, 0x0577, 0x0581, 0x058F,
    0x0593, 0x0595, 0x0599, 0x059F, 0x05A7, 0x05AB, 0x05AD, 0x05B3,
    0x05BF, 0x05C9, 0x05CB, 0x05CF, 0x05D1, 0x05D5, 0x05DB, 0x05E7,
    0x05F3, 0x05FB, 0x0607, 0x060D, 0x0611, 0x0617, 0x061F, 0x0623,
    0x062B, 0x062F, 0x063D, 0x0641, 0x0647, 0x0649, 0x064D, 0x0653
 #endif
};
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_REVERSE_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* reverse an array, used for radix code */
void
bn_reverse(unsigned char *s, int len) {
    int           ix, iy;
    unsigned char t;

    ix = 0;
    iy = len - 1;
    while (ix < iy) {
        t     = s[ix];
        s[ix] = s[iy];
        s[iy] = t;
        ++ix;
        --iy;
    }
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_S_MP_ADD_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* low level addition, based on HAC pp.594, Algorithm 14.7 */
int
s_mp_add(mp_int *a, mp_int *b, mp_int *c) {
    mp_int *x;
    int    olduse, res, min, max;

    /* find sizes, we let |a| <= |b| which means we have to sort
     * them.  "x" will point to the input with the most digits
     */
    if (a->used > b->used) {
        min = b->used;
        max = a->used;
        x   = a;
    } else {
        min = a->used;
        max = b->used;
        x   = b;
    }

    /* init result */
    if (c->alloc < (max + 1)) {
        if ((res = mp_grow(c, max + 1)) != MP_OKAY) {
            return res;
        }
    }

    /* get old used digit count and set new one */
    olduse  = c->used;
    c->used = max + 1;

    {
        mp_digit u, *tmpa, *tmpb, *tmpc;
        int      i;

        /* alias for digit pointers */

        /* first input */
        tmpa = a->dp;

        /* second input */
        tmpb = b->dp;

        /* destination */
        tmpc = c->dp;

        /* zero the carry */
        u = 0;
        for (i = 0; i < min; i++) {
            /* Compute the sum at one digit, T[i] = A[i] + B[i] + U */
            *tmpc = *tmpa++ + *tmpb++ + u;

            /* U = carry bit of T[i] */
            u = *tmpc >> ((mp_digit)DIGIT_BIT);

            /* take away carry bit from T[i] */
            *tmpc++ &= MP_MASK;
        }

        /* now copy higher words if any, that is in A+B
         * if A or B has more digits add those in
         */
        if (min != max) {
            for ( ; i < max; i++) {
                /* T[i] = X[i] + U */
                *tmpc = x->dp[i] + u;

                /* U = carry bit of T[i] */
                u = *tmpc >> ((mp_digit)DIGIT_BIT);

                /* take away carry bit from T[i] */
                *tmpc++ &= MP_MASK;
            }
        }

        /* add carry */
        *tmpc++ = u;

        /* clear digits above oldused */
        for (i = c->used; i < olduse; i++) {
            *tmpc++ = 0;
        }
    }

    mp_clamp(c);
    return MP_OKAY;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_S_MP_EXPTMOD_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */
 
int s_mp_exptmod(mp_int *G, mp_int *X, mp_int *P, mp_int *Y, int redmode) {
    mp_int   M[TAB_SIZE], res, mu;
    mp_digit buf;
    int      err, bitbuf, bitcpy, bitcnt, mode, digidx, x, y, winsize;

    int (*redux)(mp_int *, mp_int *, mp_int *);

    /* find window size */
    x = mp_count_bits(X);
    if (x <= 7) {
        winsize = 2;
    } else if (x <= 36) {
        winsize = 3;
    } else if (x <= 140) {
        winsize = 4;
    } else if (x <= 450) {
        winsize = 5;
    } else if (x <= 1303) {
        winsize = 6;
    } else if (x <= 3529) {
        winsize = 7;
    } else {
        winsize = 8;
    }

 #ifdef MP_LOW_MEM
    if (winsize > 5) {
        winsize = 5;
    }
 #endif

    /* init M array */
    /* init first cell */
    if ((err = mp_init(&M[1])) != MP_OKAY) {
        return err;
    }

    /* now init the second half of the array */
    for (x = 1 << (winsize - 1); x < (1 << winsize); x++) {
        if ((err = mp_init(&M[x])) != MP_OKAY) {
            for (y = 1 << (winsize - 1); y < x; y++) {
                mp_clear(&M[y]);
            }
            mp_clear(&M[1]);
            return err;
        }
    }

    /* create mu, used for Barrett reduction */
    if ((err = mp_init(&mu)) != MP_OKAY) {
        goto LBL_M;
    }

    if (redmode == 0) {
        if ((err = mp_reduce_setup(&mu, P)) != MP_OKAY) {
            goto LBL_MU;
        }
        redux = mp_reduce;
    } else {
        if ((err = mp_reduce_2k_setup_l(P, &mu)) != MP_OKAY) {
            goto LBL_MU;
        }
        redux = mp_reduce_2k_l;
    }

    /* create M table
     *
     * The M table contains powers of the base,
     * e.g. M[x] = G**x mod P
     *
     * The first half of the table is not
     * computed though accept for M[0] and M[1]
     */
    if ((err = mp_mod(G, P, &M[1])) != MP_OKAY) {
        goto LBL_MU;
    }

    /* compute the value at M[1<<(winsize-1)] by squaring
     * M[1] (winsize-1) times
     */
    if ((err = mp_copy(&M[1], &M[1 << (winsize - 1)])) != MP_OKAY) {
        goto LBL_MU;
    }

    for (x = 0; x < (winsize - 1); x++) {
        /* square it */
        if ((err = mp_sqr(&M[1 << (winsize - 1)],
                          &M[1 << (winsize - 1)])) != MP_OKAY) {
            goto LBL_MU;
        }

        /* reduce modulo P */
        if ((err = redux(&M[1 << (winsize - 1)], P, &mu)) != MP_OKAY) {
            goto LBL_MU;
        }
    }

    /* create upper table, that is M[x] = M[x-1] * M[1] (mod P)
     * for x = (2**(winsize - 1) + 1) to (2**winsize - 1)
     */
    for (x = (1 << (winsize - 1)) + 1; x < (1 << winsize); x++) {
        if ((err = mp_mul(&M[x - 1], &M[1], &M[x])) != MP_OKAY) {
            goto LBL_MU;
        }
        if ((err = redux(&M[x], P, &mu)) != MP_OKAY) {
            goto LBL_MU;
        }
    }

    /* setup result */
    if ((err = mp_init(&res)) != MP_OKAY) {
        goto LBL_MU;
    }
    mp_set(&res, 1);

    /* set initial mode and bit cnt */
    mode   = 0;
    bitcnt = 1;
    buf    = 0;
    digidx = X->used - 1;
    bitcpy = 0;
    bitbuf = 0;

    for ( ; ; ) {
        /* grab next digit as required */
        if (--bitcnt == 0) {
            /* if digidx == -1 we are out of digits */
            if (digidx == -1) {
                break;
            }
            /* read next digit and reset the bitcnt */
            buf    = X->dp[digidx--];
            bitcnt = (int)DIGIT_BIT;
        }

        /* grab the next msb from the exponent */
        y     = (buf >> (mp_digit)(DIGIT_BIT - 1)) & 1;
        buf <<= (mp_digit)1;

        /* if the bit is zero and mode == 0 then we ignore it
         * These represent the leading zero bits before the first 1 bit
         * in the exponent.  Technically this opt is not required but it
         * does lower the # of trivial squaring/reductions used
         */
        if ((mode == 0) && (y == 0)) {
            continue;
        }

        /* if the bit is zero and mode == 1 then we square */
        if ((mode == 1) && (y == 0)) {
            if ((err = mp_sqr(&res, &res)) != MP_OKAY) {
                goto LBL_RES;
            }
            if ((err = redux(&res, P, &mu)) != MP_OKAY) {
                goto LBL_RES;
            }
            continue;
        }

        /* else we add it to the window */
        bitbuf |= (y << (winsize - ++bitcpy));
        mode    = 2;

        if (bitcpy == winsize) {
            /* ok window is filled so square as required and multiply  */
            /* square first */
            for (x = 0; x < winsize; x++) {
                if ((err = mp_sqr(&res, &res)) != MP_OKAY) {
                    goto LBL_RES;
                }
                if ((err = redux(&res, P, &mu)) != MP_OKAY) {
                    goto LBL_RES;
                }
            }

            /* then multiply */
            if ((err = mp_mul(&res, &M[bitbuf], &res)) != MP_OKAY) {
                goto LBL_RES;
            }
            if ((err = redux(&res, P, &mu)) != MP_OKAY) {
                goto LBL_RES;
            }

            /* empty window and reset */
            bitcpy = 0;
            bitbuf = 0;
            mode   = 1;
        }
    }

    /* if bits remain then square/multiply */
    if ((mode == 2) && (bitcpy > 0)) {
        /* square then multiply if the bit is set */
        for (x = 0; x < bitcpy; x++) {
            if ((err = mp_sqr(&res, &res)) != MP_OKAY) {
                goto LBL_RES;
            }
            if ((err = redux(&res, P, &mu)) != MP_OKAY) {
                goto LBL_RES;
            }

            bitbuf <<= 1;
            if ((bitbuf & (1 << winsize)) != 0) {
                /* then multiply */
                if ((err = mp_mul(&res, &M[1], &res)) != MP_OKAY) {
                    goto LBL_RES;
                }
                if ((err = redux(&res, P, &mu)) != MP_OKAY) {
                    goto LBL_RES;
                }
            }
        }
    }

    mp_exch(&res, Y);
    err = MP_OKAY;
LBL_RES: mp_clear(&res);
LBL_MU: mp_clear(&mu);
LBL_M:
    mp_clear(&M[1]);
    for (x = 1 << (winsize - 1); x < (1 << winsize); x++) {
        mp_clear(&M[x]);
    }
    return err;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_S_MP_MUL_DIGS_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* multiplies |a| * |b| and only computes upto digs digits of result
 * HAC pp. 595, Algorithm 14.12  Modified so you can control how
 * many digits of output are created.
 */
int s_mp_mul_digs(mp_int *a, mp_int *b, mp_int *c, int digs) {
    mp_int   t;
    int      res, pa, pb, ix, iy;
    mp_digit u;
    mp_word  r;
    mp_digit tmpx, *tmpt, *tmpy;

    /* can we use the fast multiplier? */
    if (((digs) < MP_WARRAY) &&
        (MIN(a->used, b->used) <
         (1 << ((CHAR_BIT * sizeof(mp_word)) - (2 * DIGIT_BIT))))) {
        return fast_s_mp_mul_digs(a, b, c, digs);
    }

    if ((res = mp_init_size(&t, digs)) != MP_OKAY) {
        return res;
    }
    t.used = digs;

    /* compute the digits of the product directly */
    pa = a->used;
    for (ix = 0; ix < pa; ix++) {
        /* set the carry to zero */
        u = 0;

        /* limit ourselves to making digs digits of output */
        pb = MIN(b->used, digs - ix);

        /* setup some aliases */
        /* copy of the digit from a used within the nested loop */
        tmpx = a->dp[ix];

        /* an alias for the destination shifted ix places */
        tmpt = t.dp + ix;

        /* an alias for the digits of b */
        tmpy = b->dp;

        /* compute the columns of the output and propagate the carry */
        for (iy = 0; iy < pb; iy++) {
            /* compute the column as a mp_word */
            r = (mp_word) * tmpt +
                ((mp_word)tmpx * (mp_word) * tmpy++) +
                (mp_word)u;

            /* the new column is the lower part of the result */
            *tmpt++ = (mp_digit)(r & ((mp_word)MP_MASK));

            /* get the carry word from the result */
            u = (mp_digit)(r >> ((mp_word)DIGIT_BIT));
        }
        /* set carry if it is placed below digs */
        if ((ix + iy) < digs) {
            *tmpt = u;
        }
    }

    mp_clamp(&t);
    mp_exch(&t, c);

    mp_clear(&t);
    return MP_OKAY;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_S_MP_MUL_HIGH_DIGS_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* multiplies |a| * |b| and does not compute the lower digs digits
 * [meant to get the higher part of the product]
 */
int
s_mp_mul_high_digs(mp_int *a, mp_int *b, mp_int *c, int digs) {
    mp_int   t;
    int      res, pa, pb, ix, iy;
    mp_digit u;
    mp_word  r;
    mp_digit tmpx, *tmpt, *tmpy;

    /* can we use the fast multiplier? */
 #ifdef BN_FAST_S_MP_MUL_HIGH_DIGS_C
    if (((a->used + b->used + 1) < MP_WARRAY) &&
        (MIN(a->used, b->used) < (1 << ((CHAR_BIT * sizeof(mp_word)) - (2 * DIGIT_BIT))))) {
        return fast_s_mp_mul_high_digs(a, b, c, digs);
    }
 #endif

    if ((res = mp_init_size(&t, a->used + b->used + 1)) != MP_OKAY) {
        return res;
    }
    t.used = a->used + b->used + 1;

    pa = a->used;
    pb = b->used;
    for (ix = 0; ix < pa; ix++) {
        /* clear the carry */
        u = 0;

        /* left hand side of A[ix] * B[iy] */
        tmpx = a->dp[ix];

        /* alias to the address of where the digits will be stored */
        tmpt = &(t.dp[digs]);

        /* alias for where to read the right hand side from */
        tmpy = b->dp + (digs - ix);

        for (iy = digs - ix; iy < pb; iy++) {
            /* calculate the double precision result */
            r = (mp_word) * tmpt +
                ((mp_word)tmpx * (mp_word) * tmpy++) +
                (mp_word)u;

            /* get the lower part */
            *tmpt++ = (mp_digit)(r & ((mp_word)MP_MASK));

            /* carry the carry */
            u = (mp_digit)(r >> ((mp_word)DIGIT_BIT));
        }
        *tmpt = u;
    }
    mp_clamp(&t);
    mp_exch(&t, c);
    mp_clear(&t);
    return MP_OKAY;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_S_MP_SQR_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* low level squaring, b = a*a, HAC pp.596-597, Algorithm 14.16 */
int s_mp_sqr(mp_int *a, mp_int *b) {
    mp_int   t;
    int      res, ix, iy, pa;
    mp_word  r;
    mp_digit u, tmpx, *tmpt;

    pa = a->used;
    if ((res = mp_init_size(&t, (2 * pa) + 1)) != MP_OKAY) {
        return res;
    }

    /* default used is maximum possible size */
    t.used = (2 * pa) + 1;

    for (ix = 0; ix < pa; ix++) {
        /* first calculate the digit at 2*ix */
        /* calculate double precision result */
        r = (mp_word)t.dp[2 * ix] +
            ((mp_word)a->dp[ix] * (mp_word)a->dp[ix]);

        /* store lower part in result */
        t.dp[ix + ix] = (mp_digit)(r & ((mp_word)MP_MASK));

        /* get the carry */
        u = (mp_digit)(r >> ((mp_word)DIGIT_BIT));

        /* left hand side of A[ix] * A[iy] */
        tmpx = a->dp[ix];

        /* alias for where to store the results */
        tmpt = t.dp + ((2 * ix) + 1);

        for (iy = ix + 1; iy < pa; iy++) {
            /* first calculate the product */
            r = ((mp_word)tmpx) * ((mp_word)a->dp[iy]);

            /* now calculate the double precision result, note we use
             * addition instead of *2 since it's easier to optimize
             */
            r = ((mp_word) * tmpt) + r + r + ((mp_word)u);

            /* store lower part */
            *tmpt++ = (mp_digit)(r & ((mp_word)MP_MASK));

            /* get carry */
            u = (mp_digit)(r >> ((mp_word)DIGIT_BIT));
        }
        /* propagate upwards */
        while (u != ((mp_digit)0)) {
            r       = ((mp_word) * tmpt) + ((mp_word)u);
            *tmpt++ = (mp_digit)(r & ((mp_word)MP_MASK));
            u       = (mp_digit)(r >> ((mp_word)DIGIT_BIT));
        }
    }

    mp_clamp(&t);
    mp_exch(&t, b);
    mp_clear(&t);
    return MP_OKAY;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BN_S_MP_SUB_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* low level subtraction (assumes |a| > |b|), HAC pp.595 Algorithm 14.9 */
int
s_mp_sub(mp_int *a, mp_int *b, mp_int *c) {
    int olduse, res, min, max;

    /* find sizes */
    min = b->used;
    max = a->used;

    /* init result */
    if (c->alloc < max) {
        if ((res = mp_grow(c, max)) != MP_OKAY) {
            return res;
        }
    }
    olduse  = c->used;
    c->used = max;

    {
        mp_digit u, *tmpa, *tmpb, *tmpc;
        int      i;

        /* alias for digit pointers */
        tmpa = a->dp;
        tmpb = b->dp;
        tmpc = c->dp;

        /* set carry to zero */
        u = 0;
        for (i = 0; i < min; i++) {
            /* T[i] = A[i] - B[i] - U */
            *tmpc = (*tmpa++ - *tmpb++) - u;

            /* U = carry bit of T[i]
             * Note this saves performing an AND operation since
             * if a carry does occur it will propagate all the way to the
             * MSB.  As a result a single shift is enough to get the carry
             */
            u = *tmpc >> ((mp_digit)((CHAR_BIT * sizeof(mp_digit)) - 1));

            /* Clear carry from T[i] */
            *tmpc++ &= MP_MASK;
        }

        /* now copy higher words if any, e.g. if A has more digits than B  */
        for ( ; i < max; i++) {
            /* T[i] = A[i] - U */
            *tmpc = *tmpa++ - u;

            /* U = carry bit of T[i] */
            u = *tmpc >> ((mp_digit)((CHAR_BIT * sizeof(mp_digit)) - 1));

            /* Clear carry from T[i] */
            *tmpc++ &= MP_MASK;
        }

        /* clear digits above used (since we may not have grown result above) */
        for (i = c->used; i < olduse; i++) {
            *tmpc++ = 0;
        }
    }

    mp_clamp(c);
    return MP_OKAY;
}
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */



#ifdef BNCORE_C

/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org
 */

/* Known optimal configurations

   CPU                    /Compiler     /MUL CUTOFF/SQR CUTOFF
   -------------------------------------------------------------
   Intel P4 Northwood     /GCC v3.4.1   /        88/       128/LTM 0.32 ;-)
   AMD Athlon64           /GCC v3.4.4   /        80/       120/LTM 0.35

 */

int KARATSUBA_MUL_CUTOFF = 80,          /* Min. number of digits before Karatsuba multiplication is used. */
    KARATSUBA_SQR_CUTOFF = 120,         /* Min. number of digits before Karatsuba squaring is used. */

    TOOM_MUL_CUTOFF = 350,              /* no optimal values of these are known yet so set em high */
    TOOM_SQR_CUTOFF = 400;
#endif

/* $Source$ */
/* $Revision$ */
/* $Date$ */


/* LibTomCrypt, modular cryptographic library -- Tom St Denis
 *
 * LibTomCrypt is a library that provides various cryptographic
 * algorithms in a highly modular and flexible manner.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tomstdenis@gmail.com, http://libtom.org
 */

/**
   @file crypt.c
   Build strings, Tom St Denis
 */

const char *crypt_build_settings =
    "LibTomCrypt ""1.17"" (Tom St Denis, tomstdenis@gmail.com)\n"
                          "LibTomCrypt is public domain software.\n"
                          "Built on " __DATE__ " at " __TIME__ "\n\n\n"
                                                               "Endianess: "
#if defined(ENDIAN_NEUTRAL)
    "neutral\n"
#elif defined(ENDIAN_LITTLE)
    "little"
 #if defined(ENDIAN_32BITWORD)
    " (32-bit words)\n"
 #else
    " (64-bit words)\n"
 #endif
#elif defined(ENDIAN_BIG)
    "big"
 #if defined(ENDIAN_32BITWORD)
    " (32-bit words)\n"
 #else
    " (64-bit words)\n"
 #endif
#endif
    "Clean stack: "
#if defined(LTC_CLEAN_STACK)
    "enabled\n"
#else
    "disabled\n"
#endif
    "Ciphers built-in:\n"
#if defined(LTC_BLOWFISH)
    "   Blowfish\n"
#endif
#if defined(LTC_RC2)
    "   LTC_RC2\n"
#endif
#if defined(LTC_RC5)
    "   LTC_RC5\n"
#endif
#if defined(LTC_RC6)
    "   LTC_RC6\n"
#endif
#if defined(LTC_SAFERP)
    "   Safer+\n"
#endif
#if defined(LTC_SAFER)
    "   Safer\n"
#endif
#if defined(LTC_RIJNDAEL)
    "   Rijndael\n"
#endif
#if defined(LTC_XTEA)
    "   LTC_XTEA\n"
#endif
#if defined(LTC_TWOFISH)
    "   Twofish "
 #if defined(LTC_TWOFISH_SMALL) && defined(LTC_TWOFISH_TABLES) && defined(LTC_TWOFISH_ALL_TABLES)
    "(small, tables, all_tables)\n"
 #elif defined(LTC_TWOFISH_SMALL) && defined(LTC_TWOFISH_TABLES)
    "(small, tables)\n"
 #elif defined(LTC_TWOFISH_SMALL) && defined(LTC_TWOFISH_ALL_TABLES)
    "(small, all_tables)\n"
 #elif defined(LTC_TWOFISH_TABLES) && defined(LTC_TWOFISH_ALL_TABLES)
    "(tables, all_tables)\n"
 #elif defined(LTC_TWOFISH_SMALL)
    "(small)\n"
 #elif defined(LTC_TWOFISH_TABLES)
    "(tables)\n"
 #elif defined(LTC_TWOFISH_ALL_TABLES)
    "(all_tables)\n"
 #else
    "\n"
 #endif
#endif
#if defined(LTC_DES)
    "   LTC_DES\n"
#endif
#if defined(LTC_CAST5)
    "   LTC_CAST5\n"
#endif
#if defined(LTC_NOEKEON)
    "   Noekeon\n"
#endif
#if defined(LTC_SKIPJACK)
    "   Skipjack\n"
#endif
#if defined(LTC_KHAZAD)
    "   Khazad\n"
#endif
#if defined(LTC_ANUBIS)
    "   Anubis "
#endif
#if defined(LTC_ANUBIS_TWEAK)
    " (tweaked)"
#endif
    "\n"
#if defined(LTC_KSEED)
    "   LTC_KSEED\n"
#endif
#if defined(LTC_KASUMI)
    "   KASUMI\n"
#endif

    "\nHashes built-in:\n"
#if defined(LTC_SHA512)
    "   LTC_SHA-512\n"
#endif
#if defined(LTC_SHA384)
    "   LTC_SHA-384\n"
#endif
#if defined(LTC_SHA256)
    "   LTC_SHA-256\n"
#endif
#if defined(LTC_SHA224)
    "   LTC_SHA-224\n"
#endif
#if defined(LTC_TIGER)
    "   LTC_TIGER\n"
#endif
#if defined(LTC_SHA1)
    "   LTC_SHA1\n"
#endif
#if defined(LTC_MD5)
    "   LTC_MD5\n"
#endif
#if defined(LTC_MD4)
    "   LTC_MD4\n"
#endif
#if defined(LTC_MD2)
    "   LTC_MD2\n"
#endif
#if defined(LTC_RIPEMD128)
    "   LTC_RIPEMD128\n"
#endif
#if defined(LTC_RIPEMD160)
    "   LTC_RIPEMD160\n"
#endif
#if defined(LTC_RIPEMD256)
    "   LTC_RIPEMD256\n"
#endif
#if defined(LTC_RIPEMD320)
    "   LTC_RIPEMD320\n"
#endif
#if defined(LTC_WHIRLPOOL)
    "   LTC_WHIRLPOOL\n"
#endif
#if defined(LTC_CHC_HASH)
    "   LTC_CHC_HASH \n"
#endif

    "\nBlock Chaining Modes:\n"
#if defined(LTC_CFB_MODE)
    "   CFB\n"
#endif
#if defined(LTC_OFB_MODE)
    "   OFB\n"
#endif
#if defined(LTC_ECB_MODE)
    "   ECB\n"
#endif
#if defined(LTC_CBC_MODE)
    "   CBC\n"
#endif
#if defined(LTC_CTR_MODE)
    "   CTR "
#endif
#if defined(LTC_CTR_OLD)
    " (CTR_OLD) "
#endif
    "\n"
#if defined(LRW_MODE)
    "   LRW_MODE"
 #if defined(LRW_TABLES)
    " (LRW_TABLES) "
 #endif
    "\n"
#endif
#if defined(LTC_F8_MODE)
    "   F8 MODE\n"
#endif
#if defined(LTC_XTS_MODE)
    "   LTC_XTS_MODE\n"
#endif

    "\nMACs:\n"
#if defined(LTC_HMAC)
    "   LTC_HMAC\n"
#endif
#if defined(LTC_OMAC)
    "   LTC_OMAC\n"
#endif
#if defined(LTC_PMAC)
    "   PMAC\n"
#endif
#if defined(LTC_PELICAN)
    "   LTC_PELICAN\n"
#endif
#if defined(LTC_XCBC)
    "   XCBC-MAC\n"
#endif
#if defined(LTC_F9_MODE)
    "   F9-MAC\n"
#endif

    "\nENC + AUTH modes:\n"
#if defined(LTC_EAX_MODE)
    "   LTC_EAX_MODE\n"
#endif
#if defined(LTC_OCB_MODE)
    "   LTC_OCB_MODE\n"
#endif
#if defined(LTC_CCM_MODE)
    "   LTC_CCM_MODE\n"
#endif
#if defined(LTC_GCM_MODE)
    "   LTC_GCM_MODE "
#endif
#if defined(LTC_GCM_TABLES)
    " (LTC_GCM_TABLES) "
#endif
    "\n"

    "\nPRNG:\n"
#if defined(LTC_YARROW)
    "   Yarrow\n"
#endif
#if defined(LTC_SPRNG)
    "   LTC_SPRNG\n"
#endif
#if defined(LTC_RC4)
    "   LTC_RC4\n"
#endif
#if defined(LTC_FORTUNA)
    "   Fortuna\n"
#endif
#if defined(LTC_SOBER128)
    "   LTC_SOBER128\n"
#endif

    "\nPK Algs:\n"
#if defined(LTC_MRSA)
    "   RSA \n"
#endif
#if defined(LTC_MECC)
    "   ECC\n"
#endif
#if defined(LTC_MDSA)
    "   DSA\n"
#endif
#if defined(MKAT)
    "   Katja\n"
#endif

    "\nCompiler:\n"
#if defined(WIN32)
    "   WIN32 platform detected.\n"
#endif
#if defined(__CYGWIN__)
    "   CYGWIN Detected.\n"
#endif
#if defined(__DJGPP__)
    "   DJGPP Detected.\n"
#endif
#if defined(_MSC_VER)
    "   MSVC compiler detected.\n"
#endif
#if defined(__GNUC__)
    "   GCC compiler detected.\n"
#endif
#if defined(INTEL_CC)
    "   Intel C Compiler detected.\n"
#endif
#if defined(__x86_64__)
    "   x86-64 detected.\n"
#endif
#if defined(LTC_PPC32)
    "   LTC_PPC32 defined \n"
#endif

    "\nVarious others: "
#if defined(LTC_BASE64)
    " LTC_BASE64 "
#endif
#if defined(MPI)
    " MPI "
#endif
#if defined(TRY_UNRANDOM_FIRST)
    " TRY_UNRANDOM_FIRST "
#endif
#if defined(LTC_TEST)
    " LTC_TEST "
#endif
#if defined(LTC_PKCS_1)
    " LTC_PKCS#1 "
#endif
#if defined(LTC_PKCS_5)
    " LTC_PKCS#5 "
#endif
#if defined(LTC_SMALL_CODE)
    " LTC_SMALL_CODE "
#endif
#if defined(LTC_NO_FILE)
    " LTC_NO_FILE "
#endif
#if defined(LTC_DER)
    " LTC_DER "
#endif
#if defined(LTC_FAST)
    " LTC_FAST "
#endif
#if defined(LTC_NO_FAST)
    " LTC_NO_FAST "
#endif
#if defined(LTC_NO_BSWAP)
    " LTC_NO_BSWAP "
#endif
#if defined(LTC_NO_ASM)
    " LTC_NO_ASM "
#endif
#if defined(LTC_NO_TEST)
    " LTC_NO_TEST "
#endif
#if defined(LTC_NO_TABLES)
    " LTC_NO_TABLES "
#endif
#if defined(LTC_PTHREAD)
    " LTC_PTHREAD "
#endif
#if defined(LTM_LTC_DESC)
    " LTM_DESC "
#endif
#if defined(TFM_LTC_DESC)
    " TFM_DESC "
#endif
#if defined(LTC_MECC_ACCEL)
    " LTC_MECC_ACCEL "
#endif
#if defined(GMP_LTC_DESC)
    " GMP_DESC "
#endif
#if defined(LTC_EASY)
    " (easy) "
#endif
#if defined(LTC_MECC_FP)
    " LTC_MECC_FP "
#endif
#if defined(LTC_ECC_SHAMIR)
    " LTC_ECC_SHAMIR "
#endif
    "\n"
    "\n\n\n"
;


/* $Source: /cvs/libtom/libtomcrypt/src/misc/crypt/crypt.c,v $ */
/* $Revision: 1.36 $ */
/* $Date: 2007/05/12 14:46:12 $ */


/* LibTomCrypt, modular cryptographic library -- Tom St Denis
 *
 * LibTomCrypt is a library that provides various cryptographic
 * algorithms in a highly modular and flexible manner.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tomstdenis@gmail.com, http://libtom.org
 */
#include <signal.h>

/**
   @file crypt_argchk.c
   Perform argument checking, Tom St Denis
 */

#if (ARGTYPE == 0)
void crypt_argchk(char *v, char *s, int d) {
    fprintf(stderr, "LTC_ARGCHK '%s' failure on line %d of file %s\n",
            v, d, s);
    (void)raise(SIGABRT);
}
#endif


#define USE_LTM
#define LTM_DESC
#define LTC_SHA1
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <limits.h>

/* use configuration data */
#ifndef TOMCRYPT_CUSTOM_H_
#define TOMCRYPT_CUSTOM_H_

/* macros for various libc functions you can change for embedded targets */
#ifndef XMALLOC
 #ifdef malloc
  #define LTC_NO_PROTOTYPES
 #endif
 #define XMALLOC    malloc
#endif
#ifndef XREALLOC
 #ifdef realloc
  #define LTC_NO_PROTOTYPES
 #endif
 #define XREALLOC    realloc
#endif
#ifndef XCALLOC
 #ifdef calloc
  #define LTC_NO_PROTOTYPES
 #endif
 #define XCALLOC    calloc
#endif
#ifndef XFREE
 #ifdef free
  #define LTC_NO_PROTOTYPES
 #endif
 #define XFREE    free
#endif

#ifndef XMEMSET
 #ifdef memset
  #define LTC_NO_PROTOTYPES
 #endif
 #define XMEMSET    memset
#endif
#ifndef XMEMCPY
 #ifdef memcpy
  #define LTC_NO_PROTOTYPES
 #endif
 #define XMEMCPY    memcpy
#endif
#ifndef XMEMCMP
 #ifdef memcmp
  #define LTC_NO_PROTOTYPES
 #endif
 #define XMEMCMP    memcmp
#endif
#ifndef XSTRCMP
 #ifdef strcmp
  #define LTC_NO_PROTOTYPES
 #endif
 #define XSTRCMP    strcmp
#endif

#ifndef XCLOCK
 #define XCLOCK             clock
#endif
#ifndef XCLOCKS_PER_SEC
 #define XCLOCKS_PER_SEC    CLOCKS_PER_SEC
#endif

#ifndef XQSORT
 #ifdef qsort
  #define LTC_NO_PROTOTYPES
 #endif
 #define XQSORT    qsort
#endif

/* Easy button? */
#ifdef LTC_EASY
 #define LTC_NO_CIPHERS
 #define LTC_RIJNDAEL
 #define LTC_BLOWFISH
 #define LTC_DES
 #define LTC_CAST5

 #define LTC_NO_MODES
 #define LTC_ECB_MODE
 #define LTC_CBC_MODE
 #define LTC_CTR_MODE

 #define LTC_NO_HASHES
 #define LTC_SHA1
 #define LTC_SHA512
 #define LTC_SHA384
 #define LTC_SHA256
 #define LTC_SHA224

 #define LTC_NO_MACS
 #define LTC_HMAC
 #define LTC_OMAC
 #define LTC_CCM_MODE

 #define LTC_NO_PRNGS
 #define LTC_SPRNG
 #define LTC_YARROW
 #define LTC_DEVRANDOM
 #define TRY_URANDOM_FIRST

 #define LTC_NO_PK
 #define LTC_MRSA
 #define LTC_MECC
#endif

/* Use small code where possible */
/* #define LTC_SMALL_CODE */

/* Enable self-test test vector checking */
#ifndef LTC_NO_TEST
 #define LTC_TEST
#endif

/* clean the stack of functions which put private information on stack */
/* #define LTC_CLEAN_STACK */

/* disable all file related functions */
/* #define LTC_NO_FILE */

/* disable all forms of ASM */
/* #define LTC_NO_ASM */

/* disable FAST mode */
/* #define LTC_NO_FAST */

/* disable BSWAP on x86 */
/* #define LTC_NO_BSWAP */

/* ---> Symmetric Block Ciphers <--- */
#ifndef LTC_NO_CIPHERS

 #define LTC_BLOWFISH
 #define LTC_RC2
 #define LTC_RC5
 #define LTC_RC6
 #define LTC_SAFERP
 #define LTC_RIJNDAEL
 #define LTC_XTEA

/* _TABLES tells it to use tables during setup, _SMALL means to use the smaller scheduled key format
 * (saves 4KB of ram), _ALL_TABLES enables all tables during setup */
 #define LTC_TWOFISH
 #ifndef LTC_NO_TABLES
  #define LTC_TWOFISH_TABLES
/* #define LTC_TWOFISH_ALL_TABLES */
 #else
  #define LTC_TWOFISH_SMALL
 #endif
/* #define LTC_TWOFISH_SMALL */
/* LTC_DES includes EDE triple-LTC_DES */
 #define LTC_DES
 #define LTC_CAST5
 #define LTC_NOEKEON
 #define LTC_SKIPJACK
 #define LTC_SAFER
 #define LTC_KHAZAD
 #define LTC_ANUBIS
 #define LTC_ANUBIS_TWEAK
 #define LTC_KSEED
 #define LTC_KASUMI
#endif /* LTC_NO_CIPHERS */


/* ---> Block Cipher Modes of Operation <--- */
#ifndef LTC_NO_MODES

 #define LTC_CFB_MODE
 #define LTC_OFB_MODE
 #define LTC_ECB_MODE
 #define LTC_CBC_MODE
 #define LTC_CTR_MODE

/* F8 chaining mode */
 #define LTC_F8_MODE

/* LRW mode */
 #define LTC_LRW_MODE
 #ifndef LTC_NO_TABLES

/* like GCM mode this will enable 16 8x128 tables [64KB] that make
 * seeking very fast.
 */
  #define LRW_TABLES
 #endif

/* XTS mode */
 #define LTC_XTS_MODE
#endif /* LTC_NO_MODES */

/* ---> One-Way Hash Functions <--- */
#ifndef LTC_NO_HASHES

 //#define LTC_CHC_HASH
 //#define LTC_WHIRLPOOL
 //#define LTC_SHA512
 //#define LTC_SHA384
 #define LTC_SHA256
// #define LTC_SHA224
 //#define LTC_TIGER
 //#define LTC_SHA1
 //#define LTC_MD5
 //#define LTC_MD4
 //#define LTC_MD2
 //#define LTC_RIPEMD128
 //#define LTC_RIPEMD160
 //#define LTC_RIPEMD256
 //#define LTC_RIPEMD320
#endif /* LTC_NO_HASHES */

/* ---> MAC functions <--- */
#ifndef LTC_NO_MACS

 #define LTC_HMAC
 #define LTC_OMAC
 #define LTC_PMAC
 #define LTC_XCBC
 #define LTC_F9_MODE
 #define LTC_PELICAN

 #if defined(LTC_PELICAN) && !defined(LTC_RIJNDAEL)
  #error Pelican-MAC requires LTC_RIJNDAEL
 #endif

/* ---> Encrypt + Authenticate Modes <--- */

 #define LTC_EAX_MODE
 #if defined(LTC_EAX_MODE) && !(defined(LTC_CTR_MODE) && defined(LTC_OMAC))
  #error LTC_EAX_MODE requires CTR and LTC_OMAC mode
 #endif

 #define LTC_OCB_MODE
 #define LTC_CCM_MODE
 #define LTC_GCM_MODE

/* Use 64KiB tables */
 #ifndef LTC_NO_TABLES
  #define LTC_GCM_TABLES
 #endif

/* USE SSE2? requires GCC works on x86_32 and x86_64*/
 #ifdef LTC_GCM_TABLES
/* #define LTC_GCM_TABLES_SSE2 */
 #endif
#endif /* LTC_NO_MACS */

/* Various tidbits of modern neatoness */
#define LTC_BASE64

/* --> Pseudo Random Number Generators <--- */
#ifndef LTC_NO_PRNGS

/* Yarrow */
 #define LTC_YARROW
/* which descriptor of AES to use?  */
/* 0 = rijndael_enc 1 = aes_enc, 2 = rijndael [full], 3 = aes [full] */
 #define LTC_YARROW_AES    0

 #if defined(LTC_YARROW) && !defined(LTC_CTR_MODE)
  #error LTC_YARROW requires LTC_CTR_MODE chaining mode to be defined!
 #endif

/* a PRNG that simply reads from an available system source */
 #define LTC_SPRNG

/* The LTC_RC4 stream cipher */
 #define LTC_RC4

/* Fortuna PRNG */
 #define LTC_FORTUNA
/* reseed every N calls to the read function */
 #define LTC_FORTUNA_WD       10
/* number of pools (4..32) can save a bit of ram by lowering the count */
 #define LTC_FORTUNA_POOLS    32

/* Greg's LTC_SOBER128 PRNG ;-0 */
 #define LTC_SOBER128

/* the *nix style /dev/random device */
 #define LTC_DEVRANDOM
/* try /dev/urandom before trying /dev/random */
 #define TRY_URANDOM_FIRST
#endif /* LTC_NO_PRNGS */

/* ---> math provider? <--- */
#ifndef LTC_NO_MATH

/* LibTomMath */
/* #define LTM_LTC_DESC */

/* TomsFastMath */
/* #define TFM_LTC_DESC */
#endif /* LTC_NO_MATH */

/* ---> Public Key Crypto <--- */
#ifndef LTC_NO_PK

/* Include RSA support */
 #define LTC_MRSA

/* Include Katja (a Rabin variant like RSA) */
/* #define MKAT */

/* Digital Signature Algorithm */
 #define LTC_MDSA

/* ECC */
 #define LTC_MECC

/* use Shamir's trick for point mul (speeds up signature verification) */
 #define LTC_ECC_SHAMIR

 #if defined(TFM_LTC_DESC) && defined(LTC_MECC)
  #define LTC_MECC_ACCEL
 #endif

/* do we want fixed point ECC */
/* #define LTC_MECC_FP */

/* Timing Resistant? */
/* #define LTC_ECC_TIMING_RESISTANT */
#endif /* LTC_NO_PK */

/* LTC_PKCS #1 (RSA) and #5 (Password Handling) stuff */
#ifndef LTC_NO_PKCS

 #define LTC_PKCS_1
 #define LTC_PKCS_5

/* Include ASN.1 DER (required by DSA/RSA) */
 #define LTC_DER
#endif /* LTC_NO_PKCS */

/* cleanup */

#ifdef LTC_MECC
/* Supported ECC Key Sizes */
 #ifndef LTC_NO_CURVES
  #define ECC112
  #define ECC128
  #define ECC160
  #define ECC192
  #define ECC224
  #define ECC256
  #define ECC384
  #define ECC521
 #endif
#endif

#if defined(LTC_MECC) || defined(LTC_MRSA) || defined(LTC_MDSA) || defined(MKATJA)
/* Include the MPI functionality?  (required by the PK algorithms) */
 #define MPI
#endif

#ifdef LTC_MRSA
 #define LTC_PKCS_1
#endif

#if defined(LTC_DER) && !defined(MPI)
 #error ASN.1 DER requires MPI functionality
#endif

#if (defined(LTC_MDSA) || defined(LTC_MRSA) || defined(LTC_MECC) || defined(MKATJA)) && !defined(LTC_DER)
 #error PK requires ASN.1 DER functionality, make sure LTC_DER is enabled
#endif

/* THREAD management */
#ifdef LTC_PTHREAD

 #include <pthread.h>

 #define LTC_MUTEX_GLOBAL(x)    pthread_mutex_t x = PTHREAD_MUTEX_INITIALIZER;
 #define LTC_MUTEX_PROTO(x)     extern pthread_mutex_t x;
 #define LTC_MUTEX_TYPE(x)      pthread_mutex_t x;
 #define LTC_MUTEX_INIT(x)      pthread_mutex_init(x, NULL);
 #define LTC_MUTEX_LOCK(x)      pthread_mutex_lock(x);
 #define LTC_MUTEX_UNLOCK(x)    pthread_mutex_unlock(x);

#else

/* default no functions */
 #define LTC_MUTEX_GLOBAL(x)
 #define LTC_MUTEX_PROTO(x)
 #define LTC_MUTEX_TYPE(x)
 #define LTC_MUTEX_INIT(x)
 #define LTC_MUTEX_LOCK(x)
 #define LTC_MUTEX_UNLOCK(x)
#endif

/* Debuggers */

/* define this if you use Valgrind, note: it CHANGES the way SOBER-128 and LTC_RC4 work (see the code) */
/* #define LTC_VALGRIND */
#endif



/* $Source: /cvs/libtom/libtomcrypt/src/headers/tomcrypt_custom.h,v $ */
/* $Revision: 1.73 $ */
/* $Date: 2007/05/12 14:37:41 $ */ 

#ifdef __cplusplus
extern "C" {
#endif

/* version */
#define CRYPT           0x0117
#define SCRYPT          "1.17"

/* max size of either a cipher/hash block or symmetric key [largest of the two] */
#define MAXBLOCKSIZE    128

/* descriptor table size */

/* error codes [will be expanded in future releases] */
enum {
    CRYPT_OK=0,               /* Result OK */
    CRYPT_ERROR,              /* Generic Error */
    CRYPT_NOP,                /* Not a failure but no operation was performed */

    CRYPT_INVALID_KEYSIZE,    /* Invalid key size given */
    CRYPT_INVALID_ROUNDS,     /* Invalid number of rounds */
    CRYPT_FAIL_TESTVECTOR,    /* Algorithm failed test vectors */

    CRYPT_BUFFER_OVERFLOW,    /* Not enough space for output */
    CRYPT_INVALID_PACKET,     /* Invalid input packet given */

    CRYPT_INVALID_PRNGSIZE,   /* Invalid number of bits for a PRNG */
    CRYPT_ERROR_READPRNG,     /* Could not read enough from PRNG */

    CRYPT_INVALID_CIPHER,     /* Invalid cipher specified */
    CRYPT_INVALID_HASH,       /* Invalid hash specified */
    CRYPT_INVALID_PRNG,       /* Invalid PRNG specified */

    CRYPT_MEM,                /* Out of memory */

    CRYPT_PK_TYPE_MISMATCH,   /* Not equivalent types of PK keys */
    CRYPT_PK_NOT_PRIVATE,     /* Requires a private PK key */

    CRYPT_INVALID_ARG,        /* Generic invalid argument */
    CRYPT_FILE_NOTFOUND,      /* File Not Found */

    CRYPT_PK_INVALID_TYPE,    /* Invalid type of PK key */
    CRYPT_PK_INVALID_SYSTEM,  /* Invalid PK system specified */
    CRYPT_PK_DUP,             /* Duplicate key already in key ring */
    CRYPT_PK_NOT_FOUND,       /* Key not found in keyring */
    CRYPT_PK_INVALID_SIZE,    /* Invalid size input for PK parameters */

    CRYPT_INVALID_PRIME_SIZE, /* Invalid size of prime requested */
    CRYPT_PK_INVALID_PADDING  /* Invalid padding on input */
};

/* This is the build config file.
 *
 * With this you can setup what to inlcude/exclude automatically during any build.  Just comment
 * out the line that #define's the word for the thing you want to remove.  phew!
 */

#ifndef TOMCRYPT_CFG_H
#define TOMCRYPT_CFG_H

#if defined(_WIN32) || defined(_MSC_VER)
 #define LTC_CALL    __cdecl
#else
 #ifndef LTC_CALL
  #define LTC_CALL
 #endif
#endif

#ifndef LTC_EXPORT
 #define LTC_EXPORT
#endif

/* certain platforms use macros for these, making the prototypes broken */
#ifndef LTC_NO_PROTOTYPES

/* you can change how memory allocation works ... */
LTC_EXPORT void *LTC_CALL XMALLOC(size_t n);
LTC_EXPORT void *LTC_CALL XREALLOC(void *p, size_t n);
LTC_EXPORT void *LTC_CALL XCALLOC(size_t n, size_t s);
LTC_EXPORT void LTC_CALL XFREE(void *p);

LTC_EXPORT void LTC_CALL XQSORT(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));


/* change the clock function too */
LTC_EXPORT clock_t LTC_CALL XCLOCK(void);

/* various other functions */
LTC_EXPORT void *LTC_CALL XMEMCPY(void *dest, const void *src, size_t n);
LTC_EXPORT int LTC_CALL XMEMCMP(const void *s1, const void *s2, size_t n);
LTC_EXPORT void *LTC_CALL XMEMSET(void *s, int c, size_t n);

LTC_EXPORT int LTC_CALL XSTRCMP(const char *s1, const char *s2);
#endif

/* type of argument checking, 0=default, 1=fatal and 2=error+continue, 3=nothing */
#ifndef ARGTYPE
 #define ARGTYPE    0
#endif

/* Controls endianess and size of registers.  Leave uncommented to get platform neutral [slower] code
 *
 * Note: in order to use the optimized macros your platform must support unaligned 32 and 64 bit read/writes.
 * The x86 platforms allow this but some others [ARM for instance] do not.  On those platforms you **MUST**
 * use the portable [slower] macros.
 */

/* detect x86-32 machines somewhat */
#if !defined(__STRICT_ANSI__) && (defined(INTEL_CC) || (defined(_MSC_VER) && defined(WIN32)) || (defined(__GNUC__) && (defined(__DJGPP__) || defined(__CYGWIN__) || defined(__MINGW32__) || defined(__i386__))))
 #define ENDIAN_LITTLE
 #define ENDIAN_32BITWORD
 #define LTC_FAST
 #define LTC_FAST_TYPE    unsigned long
#endif

/* detects MIPS R5900 processors (PS2) */
#if (defined(__R5900) || defined(R5900) || defined(__R5900__)) && (defined(_mips) || defined(__mips__) || defined(mips))
 #define ENDIAN_LITTLE
 #define ENDIAN_64BITWORD
#endif

/* detect amd64 */
#if !defined(__STRICT_ANSI__) && defined(__x86_64__)
 #define ENDIAN_LITTLE
 #define ENDIAN_64BITWORD
 #define LTC_FAST
 #define LTC_FAST_TYPE    unsigned long
#endif

/* detect PPC32 */
#if !defined(__STRICT_ANSI__) && defined(LTC_PPC32)
 #define ENDIAN_BIG
 #define ENDIAN_32BITWORD
 #define LTC_FAST
 #define LTC_FAST_TYPE    unsigned long
#endif

/* detect sparc and sparc64 */
#if defined(__sparc__)
 #define ENDIAN_BIG
 #if defined(__arch64__)
  #define ENDIAN_64BITWORD
 #else
  #define ENDIAN_32BITWORD
 #endif
#endif


#ifdef LTC_NO_FAST
 #ifdef LTC_FAST
  #undef LTC_FAST
 #endif
#endif

/* No asm is a quick way to disable anything "not portable" */
#ifdef LTC_NO_ASM
 #undef ENDIAN_LITTLE
 #undef ENDIAN_BIG
 #undef ENDIAN_32BITWORD
 #undef ENDIAN_64BITWORD
 #undef LTC_FAST
 #undef LTC_FAST_TYPE
 #define LTC_NO_ROLC
 #define LTC_NO_BSWAP
#endif

/* #define ENDIAN_LITTLE */
/* #define ENDIAN_BIG */

/* #define ENDIAN_32BITWORD */
/* #define ENDIAN_64BITWORD */

#if (defined(ENDIAN_BIG) || defined(ENDIAN_LITTLE)) && !(defined(ENDIAN_32BITWORD) || defined(ENDIAN_64BITWORD))
 #error You must specify a word size as well as endianess in tomcrypt_cfg.h
#endif

#if !(defined(ENDIAN_BIG) || defined(ENDIAN_LITTLE))
 #define ENDIAN_NEUTRAL
#endif
#endif


/* $Source: /cvs/libtom/libtomcrypt/src/headers/tomcrypt_cfg.h,v $ */
/* $Revision: 1.19 $ */
/* $Date: 2006/12/04 02:19:48 $ */ 

/* fix for MSVC ...evil! */
#ifdef _MSC_VER
 #define CONST64(n)    n ## ui64
typedef unsigned __int64     ulong64;
#else
 #define CONST64(n)    n ## ULL
typedef unsigned long long   ulong64;
#endif

/* this is the "32-bit at least" data type
 * Re-define it to suit your platform but it must be at least 32-bits
 */
#if defined(__x86_64__) || (defined(__sparc__) && defined(__arch64__))
typedef unsigned             ulong32;
#else
typedef unsigned long        ulong32;
#endif

/* ---- HELPER MACROS ---- */
#ifdef ENDIAN_NEUTRAL

 #define STORE32L(x, y)                                                                         \
    { (y)[3] = (unsigned char)(((x) >> 24) & 255); (y)[2] = (unsigned char)(((x) >> 16) & 255); \
      (y)[1] = (unsigned char)(((x) >> 8) & 255); (y)[0] = (unsigned char)((x) & 255); }

 #define LOAD32L(x, y)                            \
    { x = ((unsigned long)((y)[3] & 255) << 24) | \
          ((unsigned long)((y)[2] & 255) << 16) | \
          ((unsigned long)((y)[1] & 255) << 8) |  \
          ((unsigned long)((y)[0] & 255)); }

 #define STORE64L(x, y)                                                                         \
    { (y)[7] = (unsigned char)(((x) >> 56) & 255); (y)[6] = (unsigned char)(((x) >> 48) & 255); \
      (y)[5] = (unsigned char)(((x) >> 40) & 255); (y)[4] = (unsigned char)(((x) >> 32) & 255); \
      (y)[3] = (unsigned char)(((x) >> 24) & 255); (y)[2] = (unsigned char)(((x) >> 16) & 255); \
      (y)[1] = (unsigned char)(((x) >> 8) & 255); (y)[0] = (unsigned char)((x) & 255); }

 #define LOAD64L(x, y)                                                            \
    { x = (((ulong64)((y)[7] & 255)) << 56) | (((ulong64)((y)[6] & 255)) << 48) | \
          (((ulong64)((y)[5] & 255)) << 40) | (((ulong64)((y)[4] & 255)) << 32) | \
          (((ulong64)((y)[3] & 255)) << 24) | (((ulong64)((y)[2] & 255)) << 16) | \
          (((ulong64)((y)[1] & 255)) << 8) | (((ulong64)((y)[0] & 255))); }

 #define STORE32H(x, y)                                                                         \
    { (y)[0] = (unsigned char)(((x) >> 24) & 255); (y)[1] = (unsigned char)(((x) >> 16) & 255); \
      (y)[2] = (unsigned char)(((x) >> 8) & 255); (y)[3] = (unsigned char)((x) & 255); }

 #define LOAD32H(x, y)                            \
    { x = ((unsigned long)((y)[0] & 255) << 24) | \
          ((unsigned long)((y)[1] & 255) << 16) | \
          ((unsigned long)((y)[2] & 255) << 8) |  \
          ((unsigned long)((y)[3] & 255)); }

 #define STORE64H(x, y)                                                                         \
    { (y)[0] = (unsigned char)(((x) >> 56) & 255); (y)[1] = (unsigned char)(((x) >> 48) & 255); \
      (y)[2] = (unsigned char)(((x) >> 40) & 255); (y)[3] = (unsigned char)(((x) >> 32) & 255); \
      (y)[4] = (unsigned char)(((x) >> 24) & 255); (y)[5] = (unsigned char)(((x) >> 16) & 255); \
      (y)[6] = (unsigned char)(((x) >> 8) & 255); (y)[7] = (unsigned char)((x) & 255); }

 #define LOAD64H(x, y)                                                            \
    { x = (((ulong64)((y)[0] & 255)) << 56) | (((ulong64)((y)[1] & 255)) << 48) | \
          (((ulong64)((y)[2] & 255)) << 40) | (((ulong64)((y)[3] & 255)) << 32) | \
          (((ulong64)((y)[4] & 255)) << 24) | (((ulong64)((y)[5] & 255)) << 16) | \
          (((ulong64)((y)[6] & 255)) << 8) | (((ulong64)((y)[7] & 255))); }
#endif /* ENDIAN_NEUTRAL */

#ifdef ENDIAN_LITTLE

 #if !defined(LTC_NO_BSWAP) && (defined(INTEL_CC) || (defined(__GNUC__) && (defined(__DJGPP__) || defined(__CYGWIN__) || defined(__MINGW32__) || defined(__i386__) || defined(__x86_64__))))

  #define STORE32H(x, y)     \
    asm __volatile__ (       \
        "bswapl %0     \n\t" \
        "movl   %0,(%1)\n\t" \
        "bswapl %0     \n\t" \
           ::"r" (x), "r" (y));

  #define LOAD32H(x, y)    \
    asm __volatile__ (     \
        "movl (%1),%0\n\t" \
        "bswapl %0\n\t"    \
        : "=r" (x) : "r" (y));

 #else

  #define STORE32H(x, y)                                                                        \
    { (y)[0] = (unsigned char)(((x) >> 24) & 255); (y)[1] = (unsigned char)(((x) >> 16) & 255); \
      (y)[2] = (unsigned char)(((x) >> 8) & 255); (y)[3] = (unsigned char)((x) & 255); }

  #define LOAD32H(x, y)                           \
    { x = ((unsigned long)((y)[0] & 255) << 24) | \
          ((unsigned long)((y)[1] & 255) << 16) | \
          ((unsigned long)((y)[2] & 255) << 8) |  \
          ((unsigned long)((y)[3] & 255)); }
 #endif


/* x86_64 processor */
 #if !defined(LTC_NO_BSWAP) && (defined(__GNUC__) && defined(__x86_64__))

  #define STORE64H(x, y)     \
    asm __volatile__ (       \
        "bswapq %0     \n\t" \
        "movq   %0,(%1)\n\t" \
        "bswapq %0     \n\t" \
           ::"r" (x), "r" (y));

  #define LOAD64H(x, y)    \
    asm __volatile__ (     \
        "movq (%1),%0\n\t" \
        "bswapq %0\n\t"    \
        : "=r" (x) : "r" (y));

 #else

  #define STORE64H(x, y)                                                                        \
    { (y)[0] = (unsigned char)(((x) >> 56) & 255); (y)[1] = (unsigned char)(((x) >> 48) & 255); \
      (y)[2] = (unsigned char)(((x) >> 40) & 255); (y)[3] = (unsigned char)(((x) >> 32) & 255); \
      (y)[4] = (unsigned char)(((x) >> 24) & 255); (y)[5] = (unsigned char)(((x) >> 16) & 255); \
      (y)[6] = (unsigned char)(((x) >> 8) & 255); (y)[7] = (unsigned char)((x) & 255); }

  #define LOAD64H(x, y)                                                           \
    { x = (((ulong64)((y)[0] & 255)) << 56) | (((ulong64)((y)[1] & 255)) << 48) | \
          (((ulong64)((y)[2] & 255)) << 40) | (((ulong64)((y)[3] & 255)) << 32) | \
          (((ulong64)((y)[4] & 255)) << 24) | (((ulong64)((y)[5] & 255)) << 16) | \
          (((ulong64)((y)[6] & 255)) << 8) | (((ulong64)((y)[7] & 255))); }
 #endif

 #ifdef ENDIAN_32BITWORD

  #define STORE32L(x, y) \
    { ulong32 __t = (x); XMEMCPY(y, &__t, 4); }

  #define LOAD32L(x, y) \
    XMEMCPY(&(x), y, 4);

  #define STORE64L(x, y)                                                                        \
    { (y)[7] = (unsigned char)(((x) >> 56) & 255); (y)[6] = (unsigned char)(((x) >> 48) & 255); \
      (y)[5] = (unsigned char)(((x) >> 40) & 255); (y)[4] = (unsigned char)(((x) >> 32) & 255); \
      (y)[3] = (unsigned char)(((x) >> 24) & 255); (y)[2] = (unsigned char)(((x) >> 16) & 255); \
      (y)[1] = (unsigned char)(((x) >> 8) & 255); (y)[0] = (unsigned char)((x) & 255); }

  #define LOAD64L(x, y)                                                           \
    { x = (((ulong64)((y)[7] & 255)) << 56) | (((ulong64)((y)[6] & 255)) << 48) | \
          (((ulong64)((y)[5] & 255)) << 40) | (((ulong64)((y)[4] & 255)) << 32) | \
          (((ulong64)((y)[3] & 255)) << 24) | (((ulong64)((y)[2] & 255)) << 16) | \
          (((ulong64)((y)[1] & 255)) << 8) | (((ulong64)((y)[0] & 255))); }

 #else /* 64-bit words then  */

  #define STORE32L(x, y) \
    { ulong32 __t = (x); XMEMCPY(y, &__t, 4); }

  #define LOAD32L(x, y) \
    { XMEMCPY(&(x), y, 4); x &= 0xFFFFFFFF; }

  #define STORE64L(x, y) \
    { ulong64 __t = (x); XMEMCPY(y, &__t, 8); }

  #define LOAD64L(x, y) \
    { XMEMCPY(&(x), y, 8); }
 #endif /* ENDIAN_64BITWORD */
#endif  /* ENDIAN_LITTLE */

#ifdef ENDIAN_BIG
 #define STORE32L(x, y)                                                                         \
    { (y)[3] = (unsigned char)(((x) >> 24) & 255); (y)[2] = (unsigned char)(((x) >> 16) & 255); \
      (y)[1] = (unsigned char)(((x) >> 8) & 255); (y)[0] = (unsigned char)((x) & 255); }

 #define LOAD32L(x, y)                            \
    { x = ((unsigned long)((y)[3] & 255) << 24) | \
          ((unsigned long)((y)[2] & 255) << 16) | \
          ((unsigned long)((y)[1] & 255) << 8) |  \
          ((unsigned long)((y)[0] & 255)); }

 #define STORE64L(x, y)                                                                         \
    { (y)[7] = (unsigned char)(((x) >> 56) & 255); (y)[6] = (unsigned char)(((x) >> 48) & 255); \
      (y)[5] = (unsigned char)(((x) >> 40) & 255); (y)[4] = (unsigned char)(((x) >> 32) & 255); \
      (y)[3] = (unsigned char)(((x) >> 24) & 255); (y)[2] = (unsigned char)(((x) >> 16) & 255); \
      (y)[1] = (unsigned char)(((x) >> 8) & 255); (y)[0] = (unsigned char)((x) & 255); }

 #define LOAD64L(x, y)                                                            \
    { x = (((ulong64)((y)[7] & 255)) << 56) | (((ulong64)((y)[6] & 255)) << 48) | \
          (((ulong64)((y)[5] & 255)) << 40) | (((ulong64)((y)[4] & 255)) << 32) | \
          (((ulong64)((y)[3] & 255)) << 24) | (((ulong64)((y)[2] & 255)) << 16) | \
          (((ulong64)((y)[1] & 255)) << 8) | (((ulong64)((y)[0] & 255))); }

 #ifdef ENDIAN_32BITWORD

  #define STORE32H(x, y) \
    { ulong32 __t = (x); XMEMCPY(y, &__t, 4); }

  #define LOAD32H(x, y) \
    XMEMCPY(&(x), y, 4);

  #define STORE64H(x, y)                                                                        \
    { (y)[0] = (unsigned char)(((x) >> 56) & 255); (y)[1] = (unsigned char)(((x) >> 48) & 255); \
      (y)[2] = (unsigned char)(((x) >> 40) & 255); (y)[3] = (unsigned char)(((x) >> 32) & 255); \
      (y)[4] = (unsigned char)(((x) >> 24) & 255); (y)[5] = (unsigned char)(((x) >> 16) & 255); \
      (y)[6] = (unsigned char)(((x) >> 8) & 255);  (y)[7] = (unsigned char)((x) & 255); }

  #define LOAD64H(x, y)                                                           \
    { x = (((ulong64)((y)[0] & 255)) << 56) | (((ulong64)((y)[1] & 255)) << 48) | \
          (((ulong64)((y)[2] & 255)) << 40) | (((ulong64)((y)[3] & 255)) << 32) | \
          (((ulong64)((y)[4] & 255)) << 24) | (((ulong64)((y)[5] & 255)) << 16) | \
          (((ulong64)((y)[6] & 255)) << 8) | (((ulong64)((y)[7] & 255))); }

 #else /* 64-bit words then  */

  #define STORE32H(x, y) \
    { ulong32 __t = (x); XMEMCPY(y, &__t, 4); }

  #define LOAD32H(x, y) \
    { XMEMCPY(&(x), y, 4); x &= 0xFFFFFFFF; }

  #define STORE64H(x, y) \
    { ulong64 __t = (x); XMEMCPY(y, &__t, 8); }

  #define LOAD64H(x, y) \
    { XMEMCPY(&(x), y, 8); }
 #endif /* ENDIAN_64BITWORD */
#endif  /* ENDIAN_BIG */

#define BSWAP(x)                                               \
    (((x >> 24) & 0x000000FFUL) | ((x << 24) & 0xFF000000UL) | \
     ((x >> 8) & 0x0000FF00UL) | ((x << 8) & 0x00FF0000UL))


/* 32-bit Rotates */
#if defined(_MSC_VER)

/* instrinsic rotate */
 #include <stdlib.h>
 #pragma intrinsic(_lrotr,_lrotl)
 #define ROR(x, n)     _lrotr(x, n)
 #define ROL(x, n)     _lrotl(x, n)
 #define RORc(x, n)    _lrotr(x, n)
 #define ROLc(x, n)    _lrotl(x, n)

#elif !defined(__STRICT_ANSI__) && defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__)) && !defined(INTEL_CC) && !defined(LTC_NO_ASM)

static inline unsigned ROL(unsigned word, int i) {
    asm ("roll %%cl,%0"
         : "=r" (word)
         : "0" (word), "c" (i));
    return word;
}

static inline unsigned ROR(unsigned word, int i) {
    asm ("rorl %%cl,%0"
         : "=r" (word)
         : "0" (word), "c" (i));
    return word;
}

 #ifndef LTC_NO_ROLC

static inline unsigned ROLc(unsigned word, const int i) {
    asm ("roll %2,%0"
         : "=r" (word)
         : "0" (word), "I" (i));
    return word;
}

static inline unsigned RORc(unsigned word, const int i) {
    asm ("rorl %2,%0"
         : "=r" (word)
         : "0" (word), "I" (i));
    return word;
}

 #else

  #define ROLc    ROL
  #define RORc    ROR
 #endif

#elif !defined(__STRICT_ANSI__) && defined(LTC_PPC32)

static inline unsigned ROL(unsigned word, int i) {
    asm ("rotlw %0,%0,%2"
         : "=r" (word)
         : "0" (word), "r" (i));
    return word;
}

static inline unsigned ROR(unsigned word, int i) {
    asm ("rotlw %0,%0,%2"
         : "=r" (word)
         : "0" (word), "r" (32 - i));
    return word;
}

 #ifndef LTC_NO_ROLC

static inline unsigned ROLc(unsigned word, const int i) {
    asm ("rotlwi %0,%0,%2"
         : "=r" (word)
         : "0" (word), "I" (i));
    return word;
}

static inline unsigned RORc(unsigned word, const int i) {
    asm ("rotrwi %0,%0,%2"
         : "=r" (word)
         : "0" (word), "I" (i));
    return word;
}

 #else

  #define ROLc    ROL
  #define RORc    ROR
 #endif


#else

/* rotates the hard way */
 #define ROL(x, y)     ((((unsigned long)(x) << (unsigned long)((y) & 31)) | (((unsigned long)(x) & 0xFFFFFFFFUL) >> (unsigned long)(32 - ((y) & 31)))) & 0xFFFFFFFFUL)
 #define ROR(x, y)     (((((unsigned long)(x) & 0xFFFFFFFFUL) >> (unsigned long)((y) & 31)) | ((unsigned long)(x) << (unsigned long)(32 - ((y) & 31)))) & 0xFFFFFFFFUL)
 #define ROLc(x, y)    ((((unsigned long)(x) << (unsigned long)((y) & 31)) | (((unsigned long)(x) & 0xFFFFFFFFUL) >> (unsigned long)(32 - ((y) & 31)))) & 0xFFFFFFFFUL)
 #define RORc(x, y)    (((((unsigned long)(x) & 0xFFFFFFFFUL) >> (unsigned long)((y) & 31)) | ((unsigned long)(x) << (unsigned long)(32 - ((y) & 31)))) & 0xFFFFFFFFUL)
#endif


/* 64-bit Rotates */
#if !defined(__STRICT_ANSI__) && defined(__GNUC__) && defined(__x86_64__) && !defined(LTC_NO_ASM)

static inline unsigned long ROL64(unsigned long word, int i) {
    asm ("rolq %%cl,%0"
         : "=r" (word)
         : "0" (word), "c" (i));
    return word;
}

static inline unsigned long ROR64(unsigned long word, int i) {
    asm ("rorq %%cl,%0"
         : "=r" (word)
         : "0" (word), "c" (i));
    return word;
}

 #ifndef LTC_NO_ROLC

static inline unsigned long ROL64c(unsigned long word, const int i) {
    asm ("rolq %2,%0"
         : "=r" (word)
         : "0" (word), "J" (i));
    return word;
}

static inline unsigned long ROR64c(unsigned long word, const int i) {
    asm ("rorq %2,%0"
         : "=r" (word)
         : "0" (word), "J" (i));
    return word;
}

 #else /* LTC_NO_ROLC */

  #define ROL64c    ROL64
  #define ROR64c    ROR64
 #endif

#else /* Not x86_64  */

 #define ROL64(x, y)                 \
    ((((x) << ((ulong64)(y) & 63)) | \
      (((x) & CONST64(0xFFFFFFFFFFFFFFFF)) >> ((ulong64)64 - ((y) & 63)))) & CONST64(0xFFFFFFFFFFFFFFFF))

 #define ROR64(x, y)                                                          \
    (((((x) & CONST64(0xFFFFFFFFFFFFFFFF)) >> ((ulong64)(y) & CONST64(63))) | \
      ((x) << ((ulong64)(64 - ((y) & CONST64(63)))))) & CONST64(0xFFFFFFFFFFFFFFFF))

 #define ROL64c(x, y)                \
    ((((x) << ((ulong64)(y) & 63)) | \
      (((x) & CONST64(0xFFFFFFFFFFFFFFFF)) >> ((ulong64)64 - ((y) & 63)))) & CONST64(0xFFFFFFFFFFFFFFFF))

 #define ROR64c(x, y)                                                         \
    (((((x) & CONST64(0xFFFFFFFFFFFFFFFF)) >> ((ulong64)(y) & CONST64(63))) | \
      ((x) << ((ulong64)(64 - ((y) & CONST64(63)))))) & CONST64(0xFFFFFFFFFFFFFFFF))
#endif

#ifndef MAX
 #define MAX(x, y)    (((x) > (y)) ? (x) : (y))
#endif

#ifndef MIN
 #define MIN(x, y)    (((x) < (y)) ? (x) : (y))
#endif

/* extract a byte portably */
#ifdef _MSC_VER
 #define byte(x, n)    ((unsigned char)((x) >> (8 * (n))))
#else
 #define byte(x, n)    (((x) >> (8 * (n))) & 255)
#endif

/* $Source: /cvs/libtom/libtomcrypt/src/headers/tomcrypt_macros.h,v $ */
/* $Revision: 1.15 $ */
/* $Date: 2006/11/29 23:43:57 $ */ 

/* ---- SYMMETRIC KEY STUFF -----
 *
 * We put each of the ciphers scheduled keys in their own structs then we put all of
 * the key formats in one union.  This makes the function prototypes easier to use.
 */
#ifdef LTC_BLOWFISH
struct blowfish_key {
    ulong32 S[4][256];
    ulong32 K[18];
};
#endif

#ifdef LTC_RC5
struct rc5_key {
    int     rounds;
    ulong32 K[50];
};
#endif

#ifdef LTC_RC6
struct rc6_key {
    ulong32 K[44];
};
#endif

#ifdef LTC_SAFERP
struct saferp_key {
    unsigned char K[33][16];
    long          rounds;
};
#endif

#ifdef LTC_RIJNDAEL
struct rijndael_key {
    ulong32 eK[60], dK[60];
    int     Nr;
};
#endif

#ifdef LTC_KSEED
struct kseed_key {
    ulong32 K[32], dK[32];
};
#endif

#ifdef LTC_KASUMI
struct kasumi_key {
    ulong32 KLi1[8], KLi2[8],
            KOi1[8], KOi2[8], KOi3[8],
            KIi1[8], KIi2[8], KIi3[8];
};
#endif

#ifdef LTC_XTEA
struct xtea_key {
    unsigned long A[32], B[32];
};
#endif

#ifdef LTC_TWOFISH
 #ifndef LTC_TWOFISH_SMALL
struct twofish_key {
    ulong32 S[4][256], K[40];
};
 #else
struct twofish_key {
    ulong32       K[40];
    unsigned char S[32], start;
};
 #endif
#endif

#ifdef LTC_SAFER
 #define LTC_SAFER_K64_DEFAULT_NOF_ROUNDS      6
 #define LTC_SAFER_K128_DEFAULT_NOF_ROUNDS     10
 #define LTC_SAFER_SK64_DEFAULT_NOF_ROUNDS     8
 #define LTC_SAFER_SK128_DEFAULT_NOF_ROUNDS    10
 #define LTC_SAFER_MAX_NOF_ROUNDS              13
 #define LTC_SAFER_BLOCK_LEN                   8
 #define LTC_SAFER_KEY_LEN                     (1 + LTC_SAFER_BLOCK_LEN * (1 + 2 * LTC_SAFER_MAX_NOF_ROUNDS))
typedef unsigned char   safer_block_t[LTC_SAFER_BLOCK_LEN];
typedef unsigned char   safer_key_t[LTC_SAFER_KEY_LEN];
struct safer_key {
    safer_key_t key;
};
#endif

#ifdef LTC_RC2
struct rc2_key {
    unsigned xkey[64];
};
#endif

#ifdef LTC_DES
struct des_key {
    ulong32 ek[32], dk[32];
};

struct des3_key {
    ulong32 ek[3][32], dk[3][32];
};
#endif

#ifdef LTC_CAST5
struct cast5_key {
    ulong32 K[32], keylen;
};
#endif

#ifdef LTC_NOEKEON
struct noekeon_key {
    ulong32 K[4], dK[4];
};
#endif

#ifdef LTC_SKIPJACK
struct skipjack_key {
    unsigned char key[10];
};
#endif

#ifdef LTC_KHAZAD
struct khazad_key {
    ulong64 roundKeyEnc[8 + 1];
    ulong64 roundKeyDec[8 + 1];
};
#endif

#ifdef LTC_ANUBIS
struct anubis_key {
    int     keyBits;
    int     R;
    ulong32 roundKeyEnc[18 + 1][4];
    ulong32 roundKeyDec[18 + 1][4];
};
#endif

#ifdef LTC_MULTI2
struct multi2_key {
    int     N;
    ulong32 uk[8];
};
#endif

typedef union Symmetric_key {
#ifdef LTC_DES
    struct des_key      des;
    struct des3_key     des3;
#endif
#ifdef LTC_RC2
    struct rc2_key      rc2;
#endif
#ifdef LTC_SAFER
    struct safer_key    safer;
#endif
#ifdef LTC_TWOFISH
    struct twofish_key  twofish;
#endif
#ifdef LTC_BLOWFISH
    struct blowfish_key blowfish;
#endif
#ifdef LTC_RC5
    struct rc5_key      rc5;
#endif
#ifdef LTC_RC6
    struct rc6_key      rc6;
#endif
#ifdef LTC_SAFERP
    struct saferp_key   saferp;
#endif
#ifdef LTC_RIJNDAEL
    struct rijndael_key rijndael;
#endif
#ifdef LTC_XTEA
    struct xtea_key     xtea;
#endif
#ifdef LTC_CAST5
    struct cast5_key    cast5;
#endif
#ifdef LTC_NOEKEON
    struct noekeon_key  noekeon;
#endif
#ifdef LTC_SKIPJACK
    struct skipjack_key skipjack;
#endif
#ifdef LTC_KHAZAD
    struct khazad_key   khazad;
#endif
#ifdef LTC_ANUBIS
    struct anubis_key   anubis;
#endif
#ifdef LTC_KSEED
    struct kseed_key    kseed;
#endif
#ifdef LTC_KASUMI
    struct kasumi_key   kasumi;
#endif
#ifdef LTC_MULTI2
    struct multi2_key   multi2;
#endif
    void                *data;
} symmetric_key;

#ifdef LTC_ECB_MODE
/** A block cipher ECB structure */
typedef struct {
    /** The index of the cipher chosen */
    int           cipher,
    /** The block size of the given cipher */
                  blocklen;
    /** The scheduled key */
    symmetric_key key;
} symmetric_ECB;
#endif

#ifdef LTC_CFB_MODE
/** A block cipher CFB structure */
typedef struct {
    /** The index of the cipher chosen */
    int           cipher,
    /** The block size of the given cipher */
                  blocklen,
    /** The padding offset */
                  padlen;
    /** The current IV */
    unsigned char IV[MAXBLOCKSIZE],
    /** The pad used to encrypt/decrypt */
                  pad[MAXBLOCKSIZE];
    /** The scheduled key */
    symmetric_key key;
} symmetric_CFB;
#endif

#ifdef LTC_OFB_MODE
/** A block cipher OFB structure */
typedef struct {
    /** The index of the cipher chosen */
    int           cipher,
    /** The block size of the given cipher */
                  blocklen,
    /** The padding offset */
                  padlen;
    /** The current IV */
    unsigned char IV[MAXBLOCKSIZE];
    /** The scheduled key */
    symmetric_key key;
} symmetric_OFB;
#endif

#ifdef LTC_CBC_MODE
/** A block cipher CBC structure */
typedef struct {
    /** The index of the cipher chosen */
    int           cipher,
    /** The block size of the given cipher */
                  blocklen;
    /** The current IV */
    unsigned char IV[MAXBLOCKSIZE];
    /** The scheduled key */
    symmetric_key key;
} symmetric_CBC;
#endif


#ifdef LTC_CTR_MODE
/** A block cipher CTR structure */
typedef struct {
    /** The index of the cipher chosen */
    int           cipher,
    /** The block size of the given cipher */
                  blocklen,
    /** The padding offset */
                  padlen,
    /** The mode (endianess) of the CTR, 0==little, 1==big */
                  mode,
    /** counter width */
                  ctrlen;

    /** The counter */
    unsigned char ctr[MAXBLOCKSIZE],
    /** The pad used to encrypt/decrypt */
                  pad[MAXBLOCKSIZE];
    /** The scheduled key */
    symmetric_key key;
} symmetric_CTR;
#endif


#ifdef LTC_LRW_MODE
/** A LRW structure */
typedef struct {
    /** The index of the cipher chosen (must be a 128-bit block cipher) */
    int           cipher;

    /** The current IV */
    unsigned char IV[16],

    /** the tweak key */
                  tweak[16],

    /** The current pad, it's the product of the first 15 bytes against the tweak key */
                  pad[16];

    /** The scheduled symmetric key */
    symmetric_key key;

 #ifdef LRW_TABLES
    /** The pre-computed multiplication table */
    unsigned char PC[16][256][16];
 #endif
} symmetric_LRW;
#endif

#ifdef LTC_F8_MODE
/** A block cipher F8 structure */
typedef struct {
    /** The index of the cipher chosen */
    int           cipher,
    /** The block size of the given cipher */
                  blocklen,
    /** The padding offset */
                  padlen;
    /** The current IV */
    unsigned char IV[MAXBLOCKSIZE],
                  MIV[MAXBLOCKSIZE];
    /** Current block count */
    ulong32       blockcnt;
    /** The scheduled key */
    symmetric_key key;
} symmetric_F8;
#endif


/** cipher descriptor table, last entry has "name == NULL" to mark the end of table */
extern struct ltc_cipher_descriptor {
    /** name of cipher */
    char          *name;
    /** internal ID */
    unsigned char ID;
    /** min keysize (octets) */
    int           min_key_length,
    /** max keysize (octets) */
                  max_key_length,
    /** block size (octets) */
                  block_length,
    /** default number of rounds */
                  default_rounds;

    /** Setup the cipher
       @param key         The input symmetric key
       @param keylen      The length of the input key (octets)
       @param num_rounds  The requested number of rounds (0==default)
       @param skey        [out] The destination of the scheduled key
       @return CRYPT_OK if successful
     */
    int           (*setup)(const unsigned char *key, int keylen, int num_rounds, symmetric_key *skey);

    /** Encrypt a block
       @param pt      The plaintext
       @param ct      [out] The ciphertext
       @param skey    The scheduled key
       @return CRYPT_OK if successful
     */
    int           (*ecb_encrypt)(const unsigned char *pt, unsigned char *ct, symmetric_key *skey);

    /** Decrypt a block
       @param ct      The ciphertext
       @param pt      [out] The plaintext
       @param skey    The scheduled key
       @return CRYPT_OK if successful
     */
    int           (*ecb_decrypt)(const unsigned char *ct, unsigned char *pt, symmetric_key *skey);

    /** Test the block cipher
        @return CRYPT_OK if successful, CRYPT_NOP if self-testing has been disabled
     */
    int           (*test)(void);

    /** Terminate the context
       @param skey    The scheduled key
     */
    void          (*done)(symmetric_key *skey);

    /** Determine a key size
        @param keysize    [in/out] The size of the key desired and the suggested size
        @return CRYPT_OK if successful
     */
    int           (*keysize)(int *keysize);

/** Accelerators **/

    /** Accelerated ECB encryption
        @param pt      Plaintext
        @param ct      Ciphertext
        @param blocks  The number of complete blocks to process
        @param skey    The scheduled key context
        @return CRYPT_OK if successful
     */
    int           (*accel_ecb_encrypt)(const unsigned char *pt, unsigned char *ct, unsigned long blocks, symmetric_key *skey);

    /** Accelerated ECB decryption
        @param pt      Plaintext
        @param ct      Ciphertext
        @param blocks  The number of complete blocks to process
        @param skey    The scheduled key context
        @return CRYPT_OK if successful
     */
    int           (*accel_ecb_decrypt)(const unsigned char *ct, unsigned char *pt, unsigned long blocks, symmetric_key *skey);

    /** Accelerated CBC encryption
        @param pt      Plaintext
        @param ct      Ciphertext
        @param blocks  The number of complete blocks to process
        @param IV      The initial value (input/output)
        @param skey    The scheduled key context
        @return CRYPT_OK if successful
     */
    int           (*accel_cbc_encrypt)(const unsigned char *pt, unsigned char *ct, unsigned long blocks, unsigned char *IV, symmetric_key *skey);

    /** Accelerated CBC decryption
        @param pt      Plaintext
        @param ct      Ciphertext
        @param blocks  The number of complete blocks to process
        @param IV      The initial value (input/output)
        @param skey    The scheduled key context
        @return CRYPT_OK if successful
     */
    int           (*accel_cbc_decrypt)(const unsigned char *ct, unsigned char *pt, unsigned long blocks, unsigned char *IV, symmetric_key *skey);

    /** Accelerated CTR encryption
        @param pt      Plaintext
        @param ct      Ciphertext
        @param blocks  The number of complete blocks to process
        @param IV      The initial value (input/output)
        @param mode    little or big endian counter (mode=0 or mode=1)
        @param skey    The scheduled key context
        @return CRYPT_OK if successful
     */
    int           (*accel_ctr_encrypt)(const unsigned char *pt, unsigned char *ct, unsigned long blocks, unsigned char *IV, int mode, symmetric_key *skey);

    /** Accelerated LRW
        @param pt      Plaintext
        @param ct      Ciphertext
        @param blocks  The number of complete blocks to process
        @param IV      The initial value (input/output)
        @param tweak   The LRW tweak
        @param skey    The scheduled key context
        @return CRYPT_OK if successful
     */
    int           (*accel_lrw_encrypt)(const unsigned char *pt, unsigned char *ct, unsigned long blocks, unsigned char *IV, const unsigned char *tweak, symmetric_key *skey);

    /** Accelerated LRW
        @param ct      Ciphertext
        @param pt      Plaintext
        @param blocks  The number of complete blocks to process
        @param IV      The initial value (input/output)
        @param tweak   The LRW tweak
        @param skey    The scheduled key context
        @return CRYPT_OK if successful
     */
    int           (*accel_lrw_decrypt)(const unsigned char *ct, unsigned char *pt, unsigned long blocks, unsigned char *IV, const unsigned char *tweak, symmetric_key *skey);

    /** Accelerated CCM packet (one-shot)
        @param key        The secret key to use
        @param keylen     The length of the secret key (octets)
        @param uskey      A previously scheduled key [optional can be NULL]
        @param nonce      The session nonce [use once]
        @param noncelen   The length of the nonce
        @param header     The header for the session
        @param headerlen  The length of the header (octets)
        @param pt         [out] The plaintext
        @param ptlen      The length of the plaintext (octets)
        @param ct         [out] The ciphertext
        @param tag        [out] The destination tag
        @param taglen     [in/out] The max size and resulting size of the authentication tag
        @param direction  Encrypt or Decrypt direction (0 or 1)
        @return CRYPT_OK if successful
     */
    int           (*accel_ccm_memory)(
        const unsigned char *key, unsigned long keylen,
        symmetric_key *uskey,
        const unsigned char *nonce, unsigned long noncelen,
        const unsigned char *header, unsigned long headerlen,
        unsigned char *pt, unsigned long ptlen,
        unsigned char *ct,
        unsigned char *tag, unsigned long *taglen,
        int direction);

    /** Accelerated GCM packet (one shot)
        @param key        The secret key
        @param keylen     The length of the secret key
        @param IV         The initial vector
        @param IVlen      The length of the initial vector
        @param adata      The additional authentication data (header)
        @param adatalen   The length of the adata
        @param pt         The plaintext
        @param ptlen      The length of the plaintext (ciphertext length is the same)
        @param ct         The ciphertext
        @param tag        [out] The MAC tag
        @param taglen     [in/out] The MAC tag length
        @param direction  Encrypt or Decrypt mode (GCM_ENCRYPT or GCM_DECRYPT)
        @return CRYPT_OK on success
     */
    int           (*accel_gcm_memory)(
        const unsigned char *key, unsigned long keylen,
        const unsigned char *IV, unsigned long IVlen,
        const unsigned char *adata, unsigned long adatalen,
        unsigned char *pt, unsigned long ptlen,
        unsigned char *ct,
        unsigned char *tag, unsigned long *taglen,
        int direction);

    /** Accelerated one shot LTC_OMAC
        @param key            The secret key
        @param keylen         The key length (octets)
        @param in             The message
        @param inlen          Length of message (octets)
        @param out            [out] Destination for tag
        @param outlen         [in/out] Initial and final size of out
        @return CRYPT_OK on success
     */
    int           (*omac_memory)(
        const unsigned char *key, unsigned long keylen,
        const unsigned char *in, unsigned long inlen,
        unsigned char *out, unsigned long *outlen);

    /** Accelerated one shot XCBC
        @param key            The secret key
        @param keylen         The key length (octets)
        @param in             The message
        @param inlen          Length of message (octets)
        @param out            [out] Destination for tag
        @param outlen         [in/out] Initial and final size of out
        @return CRYPT_OK on success
     */
    int           (*xcbc_memory)(
        const unsigned char *key, unsigned long keylen,
        const unsigned char *in, unsigned long inlen,
        unsigned char *out, unsigned long *outlen);

    /** Accelerated one shot F9
        @param key            The secret key
        @param keylen         The key length (octets)
        @param in             The message
        @param inlen          Length of message (octets)
        @param out            [out] Destination for tag
        @param outlen         [in/out] Initial and final size of out
        @return CRYPT_OK on success
        @remark Requires manual padding
     */
    int           (*f9_memory)(
        const unsigned char *key, unsigned long keylen,
        const unsigned char *in, unsigned long inlen,
        unsigned char *out, unsigned long *outlen);
} cipher_descriptor[];

#ifdef LTC_BLOWFISH
int blowfish_setup(const unsigned char *key, int keylen, int num_rounds, symmetric_key *skey);
int blowfish_ecb_encrypt(const unsigned char *pt, unsigned char *ct, symmetric_key *skey);
int blowfish_ecb_decrypt(const unsigned char *ct, unsigned char *pt, symmetric_key *skey);
int blowfish_test(void);
void blowfish_done(symmetric_key *skey);
int blowfish_keysize(int *keysize);

extern const struct ltc_cipher_descriptor blowfish_desc;
#endif

#ifdef LTC_RC5
int rc5_setup(const unsigned char *key, int keylen, int num_rounds, symmetric_key *skey);
int rc5_ecb_encrypt(const unsigned char *pt, unsigned char *ct, symmetric_key *skey);
int rc5_ecb_decrypt(const unsigned char *ct, unsigned char *pt, symmetric_key *skey);
int rc5_test(void);
void rc5_done(symmetric_key *skey);
int rc5_keysize(int *keysize);

extern const struct ltc_cipher_descriptor rc5_desc;
#endif

#ifdef LTC_RC6
int rc6_setup(const unsigned char *key, int keylen, int num_rounds, symmetric_key *skey);
int rc6_ecb_encrypt(const unsigned char *pt, unsigned char *ct, symmetric_key *skey);
int rc6_ecb_decrypt(const unsigned char *ct, unsigned char *pt, symmetric_key *skey);
int rc6_test(void);
void rc6_done(symmetric_key *skey);
int rc6_keysize(int *keysize);

extern const struct ltc_cipher_descriptor rc6_desc;
#endif

#ifdef LTC_RC2
int rc2_setup(const unsigned char *key, int keylen, int num_rounds, symmetric_key *skey);
int rc2_ecb_encrypt(const unsigned char *pt, unsigned char *ct, symmetric_key *skey);
int rc2_ecb_decrypt(const unsigned char *ct, unsigned char *pt, symmetric_key *skey);
int rc2_test(void);
void rc2_done(symmetric_key *skey);
int rc2_keysize(int *keysize);

extern const struct ltc_cipher_descriptor rc2_desc;
#endif

#ifdef LTC_SAFERP
int saferp_setup(const unsigned char *key, int keylen, int num_rounds, symmetric_key *skey);
int saferp_ecb_encrypt(const unsigned char *pt, unsigned char *ct, symmetric_key *skey);
int saferp_ecb_decrypt(const unsigned char *ct, unsigned char *pt, symmetric_key *skey);
int saferp_test(void);
void saferp_done(symmetric_key *skey);
int saferp_keysize(int *keysize);

extern const struct ltc_cipher_descriptor saferp_desc;
#endif

#ifdef LTC_SAFER
int safer_k64_setup(const unsigned char *key, int keylen, int num_rounds, symmetric_key *skey);
int safer_sk64_setup(const unsigned char *key, int keylen, int num_rounds, symmetric_key *skey);
int safer_k128_setup(const unsigned char *key, int keylen, int num_rounds, symmetric_key *skey);
int safer_sk128_setup(const unsigned char *key, int keylen, int num_rounds, symmetric_key *skey);
int safer_ecb_encrypt(const unsigned char *pt, unsigned char *ct, symmetric_key *key);
int safer_ecb_decrypt(const unsigned char *ct, unsigned char *pt, symmetric_key *key);
int safer_k64_test(void);
int safer_sk64_test(void);
int safer_sk128_test(void);
void safer_done(symmetric_key *skey);
int safer_64_keysize(int *keysize);
int safer_128_keysize(int *keysize);

extern const struct ltc_cipher_descriptor safer_k64_desc, safer_k128_desc, safer_sk64_desc, safer_sk128_desc;
#endif

#ifdef LTC_RIJNDAEL

/* make aes an alias */
 #define aes_setup              rijndael_setup
 #define aes_ecb_encrypt        rijndael_ecb_encrypt
 #define aes_ecb_decrypt        rijndael_ecb_decrypt
 #define aes_test               rijndael_test
 #define aes_done               rijndael_done
 #define aes_keysize            rijndael_keysize

 #define aes_enc_setup          rijndael_enc_setup
 #define aes_enc_ecb_encrypt    rijndael_enc_ecb_encrypt
 #define aes_enc_keysize        rijndael_enc_keysize

int rijndael_setup(const unsigned char *key, int keylen, int num_rounds, symmetric_key *skey);
int rijndael_ecb_encrypt(const unsigned char *pt, unsigned char *ct, symmetric_key *skey);
int rijndael_ecb_decrypt(const unsigned char *ct, unsigned char *pt, symmetric_key *skey);
int rijndael_test(void);
void rijndael_done(symmetric_key *skey);
int rijndael_keysize(int *keysize);
int rijndael_enc_setup(const unsigned char *key, int keylen, int num_rounds, symmetric_key *skey);
int rijndael_enc_ecb_encrypt(const unsigned char *pt, unsigned char *ct, symmetric_key *skey);
void rijndael_enc_done(symmetric_key *skey);
int rijndael_enc_keysize(int *keysize);

extern const struct ltc_cipher_descriptor rijndael_desc, aes_desc;
extern const struct ltc_cipher_descriptor rijndael_enc_desc, aes_enc_desc;
#endif

#ifdef LTC_XTEA
int xtea_setup(const unsigned char *key, int keylen, int num_rounds, symmetric_key *skey);
int xtea_ecb_encrypt(const unsigned char *pt, unsigned char *ct, symmetric_key *skey);
int xtea_ecb_decrypt(const unsigned char *ct, unsigned char *pt, symmetric_key *skey);
int xtea_test(void);
void xtea_done(symmetric_key *skey);
int xtea_keysize(int *keysize);

extern const struct ltc_cipher_descriptor xtea_desc;
#endif

#ifdef LTC_TWOFISH
int twofish_setup(const unsigned char *key, int keylen, int num_rounds, symmetric_key *skey);
int twofish_ecb_encrypt(const unsigned char *pt, unsigned char *ct, symmetric_key *skey);
int twofish_ecb_decrypt(const unsigned char *ct, unsigned char *pt, symmetric_key *skey);
int twofish_test(void);
void twofish_done(symmetric_key *skey);
int twofish_keysize(int *keysize);

extern const struct ltc_cipher_descriptor twofish_desc;
#endif

#ifdef LTC_DES
int des_setup(const unsigned char *key, int keylen, int num_rounds, symmetric_key *skey);
int des_ecb_encrypt(const unsigned char *pt, unsigned char *ct, symmetric_key *skey);
int des_ecb_decrypt(const unsigned char *ct, unsigned char *pt, symmetric_key *skey);
int des_test(void);
void des_done(symmetric_key *skey);
int des_keysize(int *keysize);
int des3_setup(const unsigned char *key, int keylen, int num_rounds, symmetric_key *skey);
int des3_ecb_encrypt(const unsigned char *pt, unsigned char *ct, symmetric_key *skey);
int des3_ecb_decrypt(const unsigned char *ct, unsigned char *pt, symmetric_key *skey);
int des3_test(void);
void des3_done(symmetric_key *skey);
int des3_keysize(int *keysize);

extern const struct ltc_cipher_descriptor des_desc, des3_desc;
#endif

#ifdef LTC_CAST5
int cast5_setup(const unsigned char *key, int keylen, int num_rounds, symmetric_key *skey);
int cast5_ecb_encrypt(const unsigned char *pt, unsigned char *ct, symmetric_key *skey);
int cast5_ecb_decrypt(const unsigned char *ct, unsigned char *pt, symmetric_key *skey);
int cast5_test(void);
void cast5_done(symmetric_key *skey);
int cast5_keysize(int *keysize);

extern const struct ltc_cipher_descriptor cast5_desc;
#endif

#ifdef LTC_NOEKEON
int noekeon_setup(const unsigned char *key, int keylen, int num_rounds, symmetric_key *skey);
int noekeon_ecb_encrypt(const unsigned char *pt, unsigned char *ct, symmetric_key *skey);
int noekeon_ecb_decrypt(const unsigned char *ct, unsigned char *pt, symmetric_key *skey);
int noekeon_test(void);
void noekeon_done(symmetric_key *skey);
int noekeon_keysize(int *keysize);

extern const struct ltc_cipher_descriptor noekeon_desc;
#endif

#ifdef LTC_SKIPJACK
int skipjack_setup(const unsigned char *key, int keylen, int num_rounds, symmetric_key *skey);
int skipjack_ecb_encrypt(const unsigned char *pt, unsigned char *ct, symmetric_key *skey);
int skipjack_ecb_decrypt(const unsigned char *ct, unsigned char *pt, symmetric_key *skey);
int skipjack_test(void);
void skipjack_done(symmetric_key *skey);
int skipjack_keysize(int *keysize);

extern const struct ltc_cipher_descriptor skipjack_desc;
#endif

#ifdef LTC_KHAZAD
int khazad_setup(const unsigned char *key, int keylen, int num_rounds, symmetric_key *skey);
int khazad_ecb_encrypt(const unsigned char *pt, unsigned char *ct, symmetric_key *skey);
int khazad_ecb_decrypt(const unsigned char *ct, unsigned char *pt, symmetric_key *skey);
int khazad_test(void);
void khazad_done(symmetric_key *skey);
int khazad_keysize(int *keysize);

extern const struct ltc_cipher_descriptor khazad_desc;
#endif

#ifdef LTC_ANUBIS
int anubis_setup(const unsigned char *key, int keylen, int num_rounds, symmetric_key *skey);
int anubis_ecb_encrypt(const unsigned char *pt, unsigned char *ct, symmetric_key *skey);
int anubis_ecb_decrypt(const unsigned char *ct, unsigned char *pt, symmetric_key *skey);
int anubis_test(void);
void anubis_done(symmetric_key *skey);
int anubis_keysize(int *keysize);

extern const struct ltc_cipher_descriptor anubis_desc;
#endif

#ifdef LTC_KSEED
int kseed_setup(const unsigned char *key, int keylen, int num_rounds, symmetric_key *skey);
int kseed_ecb_encrypt(const unsigned char *pt, unsigned char *ct, symmetric_key *skey);
int kseed_ecb_decrypt(const unsigned char *ct, unsigned char *pt, symmetric_key *skey);
int kseed_test(void);
void kseed_done(symmetric_key *skey);
int kseed_keysize(int *keysize);

extern const struct ltc_cipher_descriptor kseed_desc;
#endif

#ifdef LTC_KASUMI
int kasumi_setup(const unsigned char *key, int keylen, int num_rounds, symmetric_key *skey);
int kasumi_ecb_encrypt(const unsigned char *pt, unsigned char *ct, symmetric_key *skey);
int kasumi_ecb_decrypt(const unsigned char *ct, unsigned char *pt, symmetric_key *skey);
int kasumi_test(void);
void kasumi_done(symmetric_key *skey);
int kasumi_keysize(int *keysize);

extern const struct ltc_cipher_descriptor kasumi_desc;
#endif


#ifdef LTC_MULTI2
int multi2_setup(const unsigned char *key, int keylen, int num_rounds, symmetric_key *skey);
int multi2_ecb_encrypt(const unsigned char *pt, unsigned char *ct, symmetric_key *skey);
int multi2_ecb_decrypt(const unsigned char *ct, unsigned char *pt, symmetric_key *skey);
int multi2_test(void);
void multi2_done(symmetric_key *skey);
int multi2_keysize(int *keysize);

extern const struct ltc_cipher_descriptor multi2_desc;
#endif

#ifdef LTC_ECB_MODE
int ecb_start(int cipher, const unsigned char *key,
              int keylen, int num_rounds, symmetric_ECB *ecb);
int ecb_encrypt(const unsigned char *pt, unsigned char *ct, unsigned long len, symmetric_ECB *ecb);
int ecb_decrypt(const unsigned char *ct, unsigned char *pt, unsigned long len, symmetric_ECB *ecb);
int ecb_done(symmetric_ECB *ecb);
#endif

#ifdef LTC_CFB_MODE
int cfb_start(int cipher, const unsigned char *IV, const unsigned char *key,
              int keylen, int num_rounds, symmetric_CFB *cfb);
int cfb_encrypt(const unsigned char *pt, unsigned char *ct, unsigned long len, symmetric_CFB *cfb);
int cfb_decrypt(const unsigned char *ct, unsigned char *pt, unsigned long len, symmetric_CFB *cfb);
int cfb_getiv(unsigned char *IV, unsigned long *len, symmetric_CFB *cfb);
int cfb_setiv(const unsigned char *IV, unsigned long len, symmetric_CFB *cfb);
int cfb_done(symmetric_CFB *cfb);
#endif

#ifdef LTC_OFB_MODE
int ofb_start(int cipher, const unsigned char *IV, const unsigned char *key,
              int keylen, int num_rounds, symmetric_OFB *ofb);
int ofb_encrypt(const unsigned char *pt, unsigned char *ct, unsigned long len, symmetric_OFB *ofb);
int ofb_decrypt(const unsigned char *ct, unsigned char *pt, unsigned long len, symmetric_OFB *ofb);
int ofb_getiv(unsigned char *IV, unsigned long *len, symmetric_OFB *ofb);
int ofb_setiv(const unsigned char *IV, unsigned long len, symmetric_OFB *ofb);
int ofb_done(symmetric_OFB *ofb);
#endif

#ifdef LTC_CBC_MODE
int cbc_start(int cipher, const unsigned char *IV, const unsigned char *key,
              int keylen, int num_rounds, symmetric_CBC *cbc);
int cbc_encrypt(const unsigned char *pt, unsigned char *ct, unsigned long len, symmetric_CBC *cbc);
int cbc_decrypt(const unsigned char *ct, unsigned char *pt, unsigned long len, symmetric_CBC *cbc);
int cbc_getiv(unsigned char *IV, unsigned long *len, symmetric_CBC *cbc);
int cbc_setiv(const unsigned char *IV, unsigned long len, symmetric_CBC *cbc);
int cbc_done(symmetric_CBC *cbc);
#endif

#ifdef LTC_CTR_MODE

 #define CTR_COUNTER_LITTLE_ENDIAN    0x0000
 #define CTR_COUNTER_BIG_ENDIAN       0x1000
 #define LTC_CTR_RFC3686              0x2000

int ctr_start(int cipher,
              const unsigned char *IV,
              const unsigned char *key, int keylen,
              int num_rounds, int ctr_mode,
              symmetric_CTR *ctr);
int ctr_encrypt(const unsigned char *pt, unsigned char *ct, unsigned long len, symmetric_CTR *ctr);
int ctr_decrypt(const unsigned char *ct, unsigned char *pt, unsigned long len, symmetric_CTR *ctr);
int ctr_getiv(unsigned char *IV, unsigned long *len, symmetric_CTR *ctr);
int ctr_setiv(const unsigned char *IV, unsigned long len, symmetric_CTR *ctr);
int ctr_done(symmetric_CTR *ctr);
int ctr_test(void);
#endif

#ifdef LTC_LRW_MODE

 #define LRW_ENCRYPT    0
 #define LRW_DECRYPT    1

int lrw_start(int cipher,
              const unsigned char *IV,
              const unsigned char *key, int keylen,
              const unsigned char *tweak,
              int num_rounds,
              symmetric_LRW *lrw);
int lrw_encrypt(const unsigned char *pt, unsigned char *ct, unsigned long len, symmetric_LRW *lrw);
int lrw_decrypt(const unsigned char *ct, unsigned char *pt, unsigned long len, symmetric_LRW *lrw);
int lrw_getiv(unsigned char *IV, unsigned long *len, symmetric_LRW *lrw);
int lrw_setiv(const unsigned char *IV, unsigned long len, symmetric_LRW *lrw);
int lrw_done(symmetric_LRW *lrw);
int lrw_test(void);

/* don't call */
int lrw_process(const unsigned char *pt, unsigned char *ct, unsigned long len, int mode, symmetric_LRW *lrw);
#endif

#ifdef LTC_F8_MODE
int f8_start(int cipher, const unsigned char *IV,
             const unsigned char *key, int keylen,
             const unsigned char *salt_key, int skeylen,
             int num_rounds, symmetric_F8 *f8);
int f8_encrypt(const unsigned char *pt, unsigned char *ct, unsigned long len, symmetric_F8 *f8);
int f8_decrypt(const unsigned char *ct, unsigned char *pt, unsigned long len, symmetric_F8 *f8);
int f8_getiv(unsigned char *IV, unsigned long *len, symmetric_F8 *f8);
int f8_setiv(const unsigned char *IV, unsigned long len, symmetric_F8 *f8);
int f8_done(symmetric_F8 *f8);
int f8_test_mode(void);
#endif

#ifdef LTC_XTS_MODE
typedef struct {
    symmetric_key key1, key2;
    int           cipher;
} symmetric_xts;

int xts_start(int                 cipher,
              const unsigned char *key1,
              const unsigned char *key2,
              unsigned long       keylen,
              int                 num_rounds,
              symmetric_xts       *xts);

int xts_encrypt(
    const unsigned char *pt, unsigned long ptlen,
    unsigned char *ct,
    const unsigned char *tweak,
    symmetric_xts *xts);
int xts_decrypt(
    const unsigned char *ct, unsigned long ptlen,
    unsigned char *pt,
    const unsigned char *tweak,
    symmetric_xts *xts);

void xts_done(symmetric_xts *xts);
int  xts_test(void);
void xts_mult_x(unsigned char *I);
#endif

int find_cipher(const char *name);
int find_cipher_any(const char *name, int blocklen, int keylen);
int find_cipher_id(unsigned char ID);
int register_cipher(const struct ltc_cipher_descriptor *cipher);
int unregister_cipher(const struct ltc_cipher_descriptor *cipher);
int cipher_is_valid(int idx);

LTC_MUTEX_PROTO(ltc_cipher_mutex)

/* $Source: /cvs/libtom/libtomcrypt/src/headers/tomcrypt_cipher.h,v $ */
/* $Revision: 1.54 $ */
/* $Date: 2007/05/12 14:37:41 $ */ 

#define LTC_SHA1
/* ---- HASH FUNCTIONS ---- */
#ifdef LTC_SHA512
struct sha512_state {
    ulong64       length, state[8];
    unsigned long curlen;
    unsigned char buf[128];
};
#endif

#ifdef LTC_SHA256
struct sha256_state {
    ulong64       length;
    ulong32       state[8], curlen;
    unsigned char buf[64];
};
#endif

#ifdef LTC_SHA1
struct sha1_state {
    ulong64       length;
    ulong32       state[5], curlen;
    unsigned char buf[64];
};
#endif

#ifdef LTC_MD5
struct md5_state {
    ulong64       length;
    ulong32       state[4], curlen;
    unsigned char buf[64];
};
#endif

#ifdef LTC_MD4
struct md4_state {
    ulong64       length;
    ulong32       state[4], curlen;
    unsigned char buf[64];
};
#endif

#ifdef LTC_TIGER
struct tiger_state {
    ulong64       state[3], length;
    unsigned long curlen;
    unsigned char buf[64];
};
#endif

#ifdef LTC_MD2
struct md2_state {
    unsigned char chksum[16], X[48], buf[16];
    unsigned long curlen;
};
#endif

#ifdef LTC_RIPEMD128
struct rmd128_state {
    ulong64       length;
    unsigned char buf[64];
    ulong32       curlen, state[4];
};
#endif

#ifdef LTC_RIPEMD160
struct rmd160_state {
    ulong64       length;
    unsigned char buf[64];
    ulong32       curlen, state[5];
};
#endif

#ifdef LTC_RIPEMD256
struct rmd256_state {
    ulong64       length;
    unsigned char buf[64];
    ulong32       curlen, state[8];
};
#endif

#ifdef LTC_RIPEMD320
struct rmd320_state {
    ulong64       length;
    unsigned char buf[64];
    ulong32       curlen, state[10];
};
#endif

#ifdef LTC_WHIRLPOOL
struct whirlpool_state {
    ulong64       length, state[8];
    unsigned char buf[64];
    ulong32       curlen;
};
#endif

#ifdef LTC_CHC_HASH
struct chc_state {
    ulong64       length;
    unsigned char state[MAXBLOCKSIZE], buf[MAXBLOCKSIZE];
    ulong32       curlen;
};
#endif

typedef union Hash_state {
    char                   dummy[1];
#ifdef LTC_CHC_HASH
    struct chc_state       chc;
#endif
#ifdef LTC_WHIRLPOOL
    struct whirlpool_state whirlpool;
#endif
#ifdef LTC_SHA512
    struct sha512_state    sha512;
#endif
#ifdef LTC_SHA256
    struct sha256_state    sha256;
#endif
#ifdef LTC_SHA1
    struct sha1_state      sha1;
#endif
#ifdef LTC_MD5
    struct md5_state       md5;
#endif
#ifdef LTC_MD4
    struct md4_state       md4;
#endif
#ifdef LTC_MD2
    struct md2_state       md2;
#endif
#ifdef LTC_TIGER
    struct tiger_state     tiger;
#endif
#ifdef LTC_RIPEMD128
    struct rmd128_state    rmd128;
#endif
#ifdef LTC_RIPEMD160
    struct rmd160_state    rmd160;
#endif
#ifdef LTC_RIPEMD256
    struct rmd256_state    rmd256;
#endif
#ifdef LTC_RIPEMD320
    struct rmd320_state    rmd320;
#endif
    void                   *data;
} hash_state;

/** hash descriptor */
extern struct ltc_hash_descriptor {
    /** name of hash */
    char          *name;
    /** internal ID */
    unsigned char ID;
    /** Size of digest in octets */
    unsigned long hashsize;
    /** Input block size in octets */
    unsigned long blocksize;
    /** ASN.1 OID */
    unsigned long OID[16];
    /** Length of DER encoding */
    unsigned long OIDlen;

    /** Init a hash state
       @param hash   The hash to initialize
       @return CRYPT_OK if successful
     */
    int           (*init)(hash_state *hash);

    /** Process a block of data
       @param hash   The hash state
       @param in     The data to hash
       @param inlen  The length of the data (octets)
       @return CRYPT_OK if successful
     */
    int           (*process)(hash_state *hash, const unsigned char *in, unsigned long inlen);

    /** Produce the digest and store it
       @param hash   The hash state
       @param out    [out] The destination of the digest
       @return CRYPT_OK if successful
     */
    int           (*done)(hash_state *hash, unsigned char *out);

    /** Self-test
       @return CRYPT_OK if successful, CRYPT_NOP if self-tests have been disabled
     */
    int           (*test)(void);

    /* accelerated hmac callback: if you need to-do multiple packets just use the generic hmac_memory and provide a hash callback */
    int           (*hmac_block)(const unsigned char *key, unsigned long keylen,
                                const unsigned char *in, unsigned long inlen,
                                unsigned char *out, unsigned long *outlen);
} hash_descriptor[];

#ifdef LTC_CHC_HASH
int chc_register(int cipher);
int chc_init(hash_state *md);
int chc_process(hash_state *md, const unsigned char *in, unsigned long inlen);
int chc_done(hash_state *md, unsigned char *hash);
int chc_test(void);

extern const struct ltc_hash_descriptor chc_desc;
#endif

#ifdef LTC_WHIRLPOOL
int whirlpool_init(hash_state *md);
int whirlpool_process(hash_state *md, const unsigned char *in, unsigned long inlen);
int whirlpool_done(hash_state *md, unsigned char *hash);
int whirlpool_test(void);

extern const struct ltc_hash_descriptor whirlpool_desc;
#endif

#ifdef LTC_SHA512
int sha512_init(hash_state *md);
int sha512_process(hash_state *md, const unsigned char *in, unsigned long inlen);
int sha512_done(hash_state *md, unsigned char *hash);
int sha512_test(void);

extern const struct ltc_hash_descriptor sha512_desc;
#endif

#ifdef LTC_SHA384
 #ifndef LTC_SHA512
  #error LTC_SHA512 is required for LTC_SHA384
 #endif
int sha384_init(hash_state *md);

 #define sha384_process    sha512_process
int sha384_done(hash_state *md, unsigned char *hash);
int sha384_test(void);

extern const struct ltc_hash_descriptor sha384_desc;
#endif

#ifdef LTC_SHA256
int sha256_init(hash_state *md);
int sha256_process(hash_state *md, const unsigned char *in, unsigned long inlen);
int sha256_done(hash_state *md, unsigned char *hash);
int sha256_test(void);

extern const struct ltc_hash_descriptor sha256_desc;

 #ifdef LTC_SHA224
  #ifndef LTC_SHA256
   #error LTC_SHA256 is required for LTC_SHA224
  #endif
int sha224_init(hash_state *md);

  #define sha224_process    sha256_process
int sha224_done(hash_state *md, unsigned char *hash);
int sha224_test(void);

extern const struct ltc_hash_descriptor sha224_desc;
 #endif
#endif

#ifdef LTC_SHA1
int sha1_init(hash_state *md);
int sha1_process(hash_state *md, const unsigned char *in, unsigned long inlen);
int sha1_done(hash_state *md, unsigned char *hash);
int sha1_test(void);

extern const struct ltc_hash_descriptor sha1_desc;
#endif

#ifdef LTC_MD5
int md5_init(hash_state *md);
int md5_process(hash_state *md, const unsigned char *in, unsigned long inlen);
int md5_done(hash_state *md, unsigned char *hash);
int md5_test(void);

extern const struct ltc_hash_descriptor md5_desc;
#endif

#ifdef LTC_MD4
int md4_init(hash_state *md);
int md4_process(hash_state *md, const unsigned char *in, unsigned long inlen);
int md4_done(hash_state *md, unsigned char *hash);
int md4_test(void);

extern const struct ltc_hash_descriptor md4_desc;
#endif

#ifdef LTC_MD2
int md2_init(hash_state *md);
int md2_process(hash_state *md, const unsigned char *in, unsigned long inlen);
int md2_done(hash_state *md, unsigned char *hash);
int md2_test(void);

extern const struct ltc_hash_descriptor md2_desc;
#endif

#ifdef LTC_TIGER
int tiger_init(hash_state *md);
int tiger_process(hash_state *md, const unsigned char *in, unsigned long inlen);
int tiger_done(hash_state *md, unsigned char *hash);
int tiger_test(void);

extern const struct ltc_hash_descriptor tiger_desc;
#endif

#ifdef LTC_RIPEMD128
int rmd128_init(hash_state *md);
int rmd128_process(hash_state *md, const unsigned char *in, unsigned long inlen);
int rmd128_done(hash_state *md, unsigned char *hash);
int rmd128_test(void);

extern const struct ltc_hash_descriptor rmd128_desc;
#endif

#ifdef LTC_RIPEMD160
int rmd160_init(hash_state *md);
int rmd160_process(hash_state *md, const unsigned char *in, unsigned long inlen);
int rmd160_done(hash_state *md, unsigned char *hash);
int rmd160_test(void);

extern const struct ltc_hash_descriptor rmd160_desc;
#endif

#ifdef LTC_RIPEMD256
int rmd256_init(hash_state *md);
int rmd256_process(hash_state *md, const unsigned char *in, unsigned long inlen);
int rmd256_done(hash_state *md, unsigned char *hash);
int rmd256_test(void);

extern const struct ltc_hash_descriptor rmd256_desc;
#endif

#ifdef LTC_RIPEMD320
int rmd320_init(hash_state *md);
int rmd320_process(hash_state *md, const unsigned char *in, unsigned long inlen);
int rmd320_done(hash_state *md, unsigned char *hash);
int rmd320_test(void);

extern const struct ltc_hash_descriptor rmd320_desc;
#endif


int find_hash(const char *name);
int find_hash_id(unsigned char ID);
int find_hash_oid(const unsigned long *ID, unsigned long IDlen);
int find_hash_any(const char *name, int digestlen);
int register_hash(const struct ltc_hash_descriptor *hash);
int unregister_hash(const struct ltc_hash_descriptor *hash);
int hash_is_valid(int idx);

LTC_MUTEX_PROTO(ltc_hash_mutex)

int hash_memory(int hash,
                const unsigned char *in, unsigned long inlen,
                unsigned char *out, unsigned long *outlen);
int hash_memory_multi(int hash, unsigned char *out, unsigned long *outlen,
                      const unsigned char *in, unsigned long inlen, ...);
int hash_filehandle(int hash, FILE *in, unsigned char *out, unsigned long *outlen);
int hash_file(int hash, const char *fname, unsigned char *out, unsigned long *outlen);

/* a simple macro for making hash "process" functions */
#define HASH_PROCESS(func_name, compress_name, state_var, block_size)               \
    int func_name(hash_state * md, const unsigned char *in, unsigned long inlen)    \
    {                                                                               \
        unsigned long n;                                                            \
        int           err;                                                          \
        LTC_ARGCHK(md != NULL);                                                     \
        LTC_ARGCHK(in != NULL);                                                     \
        if (md->state_var.curlen > sizeof(md->state_var.buf)) {                     \
            return CRYPT_INVALID_ARG;                                               \
        }                                                                           \
        while (inlen > 0) {                                                         \
            if (md->state_var.curlen == 0 && inlen >= block_size) {                 \
                if ((err = compress_name(md, (unsigned char *)in)) != CRYPT_OK) {   \
                    return err;                                                     \
                }                                                                   \
                md->state_var.length += block_size * 8;                             \
                in    += block_size;                                                \
                inlen -= block_size;                                                \
            } else {                                                                \
                n = MIN(inlen, (block_size - md->state_var.curlen));                \
                memcpy(md->state_var.buf + md->state_var.curlen, in, (size_t)n);    \
                md->state_var.curlen += n;                                          \
                in    += n;                                                         \
                inlen -= n;                                                         \
                if (md->state_var.curlen == block_size) {                           \
                    if ((err = compress_name(md, md->state_var.buf)) != CRYPT_OK) { \
                        return err;                                                 \
                    }                                                               \
                    md->state_var.length += 8 * block_size;                         \
                    md->state_var.curlen  = 0;                                      \
                }                                                                   \
            }                                                                       \
        }                                                                           \
        return CRYPT_OK;                                                            \
    }

/* $Source: /cvs/libtom/libtomcrypt/src/headers/tomcrypt_hash.h,v $ */
/* $Revision: 1.22 $ */
/* $Date: 2007/05/12 14:32:35 $ */ 

#ifdef LTC_HMAC
typedef struct Hmac_state {
    hash_state    md;
    int           hash;
    hash_state    hashstate;
    unsigned char *key;
} hmac_state;

int hmac_init(hmac_state *hmac, int hash, const unsigned char *key, unsigned long keylen);
int hmac_process(hmac_state *hmac, const unsigned char *in, unsigned long inlen);
int hmac_done(hmac_state *hmac, unsigned char *out, unsigned long *outlen);
int hmac_test(void);
int hmac_memory(int hash,
                const unsigned char *key, unsigned long keylen,
                const unsigned char *in, unsigned long inlen,
                unsigned char *out, unsigned long *outlen);
int hmac_memory_multi(int hash,
                      const unsigned char *key, unsigned long keylen,
                      unsigned char *out, unsigned long *outlen,
                      const unsigned char *in, unsigned long inlen, ...);
int hmac_file(int hash, const char *fname, const unsigned char *key,
              unsigned long keylen,
              unsigned char *dst, unsigned long *dstlen);
#endif

#ifdef LTC_OMAC

typedef struct {
    int           cipher_idx,
                  buflen,
                  blklen;
    unsigned char block[MAXBLOCKSIZE],
                  prev[MAXBLOCKSIZE],
                  Lu[2][MAXBLOCKSIZE];
    symmetric_key key;
} omac_state;

int omac_init(omac_state *omac, int cipher, const unsigned char *key, unsigned long keylen);
int omac_process(omac_state *omac, const unsigned char *in, unsigned long inlen);
int omac_done(omac_state *omac, unsigned char *out, unsigned long *outlen);
int omac_memory(int cipher,
                const unsigned char *key, unsigned long keylen,
                const unsigned char *in, unsigned long inlen,
                unsigned char *out, unsigned long *outlen);
int omac_memory_multi(int cipher,
                      const unsigned char *key, unsigned long keylen,
                      unsigned char *out, unsigned long *outlen,
                      const unsigned char *in, unsigned long inlen, ...);
int omac_file(int cipher,
              const unsigned char *key, unsigned long keylen,
              const char *filename,
              unsigned char *out, unsigned long *outlen);
int omac_test(void);
#endif /* LTC_OMAC */

#ifdef LTC_PMAC

typedef struct {
    unsigned char Ls[32][MAXBLOCKSIZE],       /* L shifted by i bits to the left */
                  Li[MAXBLOCKSIZE],           /* value of Li [current value, we calc from previous recall] */
                  Lr[MAXBLOCKSIZE],           /* L * x^-1 */
                  block[MAXBLOCKSIZE],        /* currently accumulated block */
                  checksum[MAXBLOCKSIZE];     /* current checksum */

    symmetric_key key;                        /* scheduled key for cipher */
    unsigned long block_index;                /* index # for current block */
    int           cipher_idx,                 /* cipher idx */
                  block_len,                  /* length of block */
                  buflen;                     /* number of bytes in the buffer */
} pmac_state;

int pmac_init(pmac_state *pmac, int cipher, const unsigned char *key, unsigned long keylen);
int pmac_process(pmac_state *pmac, const unsigned char *in, unsigned long inlen);
int pmac_done(pmac_state *pmac, unsigned char *out, unsigned long *outlen);

int pmac_memory(int cipher,
                const unsigned char *key, unsigned long keylen,
                const unsigned char *msg, unsigned long msglen,
                unsigned char *out, unsigned long *outlen);

int pmac_memory_multi(int cipher,
                      const unsigned char *key, unsigned long keylen,
                      unsigned char *out, unsigned long *outlen,
                      const unsigned char *in, unsigned long inlen, ...);

int pmac_file(int cipher,
              const unsigned char *key, unsigned long keylen,
              const char *filename,
              unsigned char *out, unsigned long *outlen);

int pmac_test(void);

/* internal functions */
int pmac_ntz(unsigned long x);
void pmac_shift_xor(pmac_state *pmac);
#endif /* PMAC */

#ifdef LTC_EAX_MODE

 #if !(defined(LTC_OMAC) && defined(LTC_CTR_MODE))
  #error LTC_EAX_MODE requires LTC_OMAC and CTR
 #endif

typedef struct {
    unsigned char N[MAXBLOCKSIZE];
    symmetric_CTR ctr;
    omac_state    headeromac, ctomac;
} eax_state;

int eax_init(eax_state *eax, int cipher, const unsigned char *key, unsigned long keylen,
             const unsigned char *nonce, unsigned long noncelen,
             const unsigned char *header, unsigned long headerlen);

int eax_encrypt(eax_state *eax, const unsigned char *pt, unsigned char *ct, unsigned long length);
int eax_decrypt(eax_state *eax, const unsigned char *ct, unsigned char *pt, unsigned long length);
int eax_addheader(eax_state *eax, const unsigned char *header, unsigned long length);
int eax_done(eax_state *eax, unsigned char *tag, unsigned long *taglen);

int eax_encrypt_authenticate_memory(int cipher,
                                    const unsigned char *key, unsigned long keylen,
                                    const unsigned char *nonce, unsigned long noncelen,
                                    const unsigned char *header, unsigned long headerlen,
                                    const unsigned char *pt, unsigned long ptlen,
                                    unsigned char *ct,
                                    unsigned char *tag, unsigned long *taglen);

int eax_decrypt_verify_memory(int cipher,
                              const unsigned char *key, unsigned long keylen,
                              const unsigned char *nonce, unsigned long noncelen,
                              const unsigned char *header, unsigned long headerlen,
                              const unsigned char *ct, unsigned long ctlen,
                              unsigned char *pt,
                              unsigned char *tag, unsigned long taglen,
                              int *stat);

int eax_test(void);
#endif /* EAX MODE */

#ifdef LTC_OCB_MODE
typedef struct {
    unsigned char L[MAXBLOCKSIZE],            /* L value */
                  Ls[32][MAXBLOCKSIZE],       /* L shifted by i bits to the left */
                  Li[MAXBLOCKSIZE],           /* value of Li [current value, we calc from previous recall] */
                  Lr[MAXBLOCKSIZE],           /* L * x^-1 */
                  R[MAXBLOCKSIZE],            /* R value */
                  checksum[MAXBLOCKSIZE];     /* current checksum */

    symmetric_key key;                        /* scheduled key for cipher */
    unsigned long block_index;                /* index # for current block */
    int           cipher,                     /* cipher idx */
                  block_len;                  /* length of block */
} ocb_state;

int ocb_init(ocb_state *ocb, int cipher,
             const unsigned char *key, unsigned long keylen, const unsigned char *nonce);

int ocb_encrypt(ocb_state *ocb, const unsigned char *pt, unsigned char *ct);
int ocb_decrypt(ocb_state *ocb, const unsigned char *ct, unsigned char *pt);

int ocb_done_encrypt(ocb_state *ocb,
                     const unsigned char *pt, unsigned long ptlen,
                     unsigned char *ct,
                     unsigned char *tag, unsigned long *taglen);

int ocb_done_decrypt(ocb_state *ocb,
                     const unsigned char *ct, unsigned long ctlen,
                     unsigned char *pt,
                     const unsigned char *tag, unsigned long taglen, int *stat);

int ocb_encrypt_authenticate_memory(int cipher,
                                    const unsigned char *key, unsigned long keylen,
                                    const unsigned char *nonce,
                                    const unsigned char *pt, unsigned long ptlen,
                                    unsigned char *ct,
                                    unsigned char *tag, unsigned long *taglen);

int ocb_decrypt_verify_memory(int cipher,
                              const unsigned char *key, unsigned long keylen,
                              const unsigned char *nonce,
                              const unsigned char *ct, unsigned long ctlen,
                              unsigned char *pt,
                              const unsigned char *tag, unsigned long taglen,
                              int *stat);

int ocb_test(void);

/* internal functions */
void ocb_shift_xor(ocb_state *ocb, unsigned char *Z);
int ocb_ntz(unsigned long x);
int s_ocb_done(ocb_state *ocb, const unsigned char *pt, unsigned long ptlen,
               unsigned char *ct, unsigned char *tag, unsigned long *taglen, int mode);
#endif /* LTC_OCB_MODE */

#ifdef LTC_CCM_MODE

 #define CCM_ENCRYPT    0
 #define CCM_DECRYPT    1

int ccm_memory(int cipher,
               const unsigned char *key, unsigned long keylen,
               symmetric_key *uskey,
               const unsigned char *nonce, unsigned long noncelen,
               const unsigned char *header, unsigned long headerlen,
               unsigned char *pt, unsigned long ptlen,
               unsigned char *ct,
               unsigned char *tag, unsigned long *taglen,
               int direction);

int ccm_test(void);
#endif /* LTC_CCM_MODE */

#if defined(LRW_MODE) || defined(LTC_GCM_MODE)
void gcm_gf_mult(const unsigned char *a, const unsigned char *b, unsigned char *c);
#endif


/* table shared between GCM and LRW */
#if defined(LTC_GCM_TABLES) || defined(LRW_TABLES) || ((defined(LTC_GCM_MODE) || defined(LTC_GCM_MODE)) && defined(LTC_FAST))
extern const unsigned char gcm_shift_table[];
#endif

#ifdef LTC_GCM_MODE

 #define GCM_ENCRYPT          0
 #define GCM_DECRYPT          1

 #define LTC_GCM_MODE_IV      0
 #define LTC_GCM_MODE_AAD     1
 #define LTC_GCM_MODE_TEXT    2

typedef struct {
    symmetric_key K;
    unsigned char H[16],             /* multiplier */
                  X[16],             /* accumulator */
                  Y[16],             /* counter */
                  Y_0[16],           /* initial counter */
                  buf[16];           /* buffer for stuff */

    int           cipher,            /* which cipher */
                  ivmode,            /* Which mode is the IV in? */
                  mode,              /* mode the GCM code is in */
                  buflen;            /* length of data in buf */

    ulong64       totlen,            /* 64-bit counter used for IV and AAD */
                  pttotlen;          /* 64-bit counter for the PT */

 #ifdef LTC_GCM_TABLES
    unsigned char PC[16][256][16]       /* 16 tables of 8x128 */
  #ifdef LTC_GCM_TABLES_SSE2
    __attribute__ ((aligned(16)))
  #endif
    ;
 #endif
} gcm_state;

void gcm_mult_h(gcm_state *gcm, unsigned char *I);

int gcm_init(gcm_state *gcm, int cipher,
             const unsigned char *key, int keylen);

int gcm_reset(gcm_state *gcm);

int gcm_add_iv(gcm_state *gcm,
               const unsigned char *IV, unsigned long IVlen);

int gcm_add_aad(gcm_state *gcm,
                const unsigned char *adata, unsigned long adatalen);

int gcm_process(gcm_state *gcm,
                unsigned char *pt, unsigned long ptlen,
                unsigned char *ct,
                int direction);

int gcm_done(gcm_state *gcm,
             unsigned char *tag, unsigned long *taglen);

int gcm_memory(int cipher,
               const unsigned char *key, unsigned long keylen,
               const unsigned char *IV, unsigned long IVlen,
               const unsigned char *adata, unsigned long adatalen,
               unsigned char *pt, unsigned long ptlen,
               unsigned char *ct,
               unsigned char *tag, unsigned long *taglen,
               int direction);
int gcm_test(void);
#endif /* LTC_GCM_MODE */

#ifdef LTC_PELICAN

typedef struct pelican_state {
    symmetric_key K;
    unsigned char state[16];
    int           buflen;
} pelican_state;

int pelican_init(pelican_state *pelmac, const unsigned char *key, unsigned long keylen);
int pelican_process(pelican_state *pelmac, const unsigned char *in, unsigned long inlen);
int pelican_done(pelican_state *pelmac, unsigned char *out);
int pelican_test(void);

int pelican_memory(const unsigned char *key, unsigned long keylen,
                   const unsigned char *in, unsigned long inlen,
                   unsigned char *out);
#endif

#ifdef LTC_XCBC

/* add this to "keylen" to xcbc_init to use a pure three-key XCBC MAC */
 #define LTC_XCBC_PURE    0x8000UL

typedef struct {
    unsigned char K[3][MAXBLOCKSIZE],
                  IV[MAXBLOCKSIZE];

    symmetric_key key;

    int           cipher,
                  buflen,
                  blocksize;
} xcbc_state;

int xcbc_init(xcbc_state *xcbc, int cipher, const unsigned char *key, unsigned long keylen);
int xcbc_process(xcbc_state *xcbc, const unsigned char *in, unsigned long inlen);
int xcbc_done(xcbc_state *xcbc, unsigned char *out, unsigned long *outlen);
int xcbc_memory(int cipher,
                const unsigned char *key, unsigned long keylen,
                const unsigned char *in, unsigned long inlen,
                unsigned char *out, unsigned long *outlen);
int xcbc_memory_multi(int cipher,
                      const unsigned char *key, unsigned long keylen,
                      unsigned char *out, unsigned long *outlen,
                      const unsigned char *in, unsigned long inlen, ...);
int xcbc_file(int cipher,
              const unsigned char *key, unsigned long keylen,
              const char *filename,
              unsigned char *out, unsigned long *outlen);
int xcbc_test(void);
#endif

#ifdef LTC_F9_MODE

typedef struct {
    unsigned char akey[MAXBLOCKSIZE],
                  ACC[MAXBLOCKSIZE],
                  IV[MAXBLOCKSIZE];

    symmetric_key key;

    int           cipher,
                  buflen,
                  keylen,
                  blocksize;
} f9_state;

int f9_init(f9_state *f9, int cipher, const unsigned char *key, unsigned long keylen);
int f9_process(f9_state *f9, const unsigned char *in, unsigned long inlen);
int f9_done(f9_state *f9, unsigned char *out, unsigned long *outlen);
int f9_memory(int cipher,
              const unsigned char *key, unsigned long keylen,
              const unsigned char *in, unsigned long inlen,
              unsigned char *out, unsigned long *outlen);
int f9_memory_multi(int cipher,
                    const unsigned char *key, unsigned long keylen,
                    unsigned char *out, unsigned long *outlen,
                    const unsigned char *in, unsigned long inlen, ...);
int f9_file(int cipher,
            const unsigned char *key, unsigned long keylen,
            const char *filename,
            unsigned char *out, unsigned long *outlen);
int f9_test(void);
#endif


/* $Source: /cvs/libtom/libtomcrypt/src/headers/tomcrypt_mac.h,v $ */
/* $Revision: 1.23 $ */
/* $Date: 2007/05/12 14:37:41 $ */ 

/* ---- PRNG Stuff ---- */
#ifdef LTC_YARROW
struct yarrow_prng {
    int           cipher, hash;
    unsigned char pool[MAXBLOCKSIZE];
    symmetric_CTR ctr;
    LTC_MUTEX_TYPE(prng_lock)
};
#endif

#ifdef LTC_RC4
struct rc4_prng {
    int           x, y;
    unsigned char buf[256];
};
#endif

#ifdef LTC_FORTUNA
struct fortuna_prng {
    hash_state    pool[LTC_FORTUNA_POOLS];  /* the  pools */

    symmetric_key skey;

    unsigned char K[32],      /* the current key */
                  IV[16];     /* IV for CTR mode */

    unsigned long pool_idx,   /* current pool we will add to */
                  pool0_len,  /* length of 0'th pool */
                  wd;

    ulong64       reset_cnt;  /* number of times we have reset */
    LTC_MUTEX_TYPE(prng_lock)
};
#endif

#ifdef LTC_SOBER128
struct sober128_prng {
    ulong32 R[17],               /* Working storage for the shift register */
            initR[17],           /* saved register contents */
            konst,               /* key dependent constant */
            sbuf;                /* partial word encryption buffer */

    int     nbuf,                /* number of part-word stream bits buffered */
            flag,                /* first add_entropy call or not? */
            set;                 /* did we call add_entropy to set key? */
};
#endif

typedef union Prng_state {
    char                 dummy[1];
#ifdef LTC_YARROW
    struct yarrow_prng   yarrow;
#endif
#ifdef LTC_RC4
    struct rc4_prng      rc4;
#endif
#ifdef LTC_FORTUNA
    struct fortuna_prng  fortuna;
#endif
#ifdef LTC_SOBER128
    struct sober128_prng sober128;
#endif
} prng_state;

/** PRNG descriptor */
extern struct ltc_prng_descriptor {
    /** Name of the PRNG */
    char          *name;
    /** size in bytes of exported state */
    int           export_size;

    /** Start a PRNG state
        @param prng   [out] The state to initialize
        @return CRYPT_OK if successful
     */
    int           (*start)(prng_state *prng);

    /** Add entropy to the PRNG
        @param in         The entropy
        @param inlen      Length of the entropy (octets)\
        @param prng       The PRNG state
        @return CRYPT_OK if successful
     */
    int           (*add_entropy)(const unsigned char *in, unsigned long inlen, prng_state *prng);

    /** Ready a PRNG state to read from
        @param prng       The PRNG state to ready
        @return CRYPT_OK if successful
     */
    int           (*ready)(prng_state *prng);

    /** Read from the PRNG
        @param out     [out] Where to store the data
        @param outlen  Length of data desired (octets)
        @param prng    The PRNG state to read from
        @return Number of octets read
     */
    unsigned long (*read)(unsigned char *out, unsigned long outlen, prng_state *prng);

    /** Terminate a PRNG state
        @param prng   The PRNG state to terminate
        @return CRYPT_OK if successful
     */
    int           (*done)(prng_state *prng);

    /** Export a PRNG state
        @param out     [out] The destination for the state
        @param outlen  [in/out] The max size and resulting size of the PRNG state
        @param prng    The PRNG to export
        @return CRYPT_OK if successful
     */
    int           (*pexport)(unsigned char *out, unsigned long *outlen, prng_state *prng);

    /** Import a PRNG state
        @param in      The data to import
        @param inlen   The length of the data to import (octets)
        @param prng    The PRNG to initialize/import
        @return CRYPT_OK if successful
     */
    int           (*pimport)(const unsigned char *in, unsigned long inlen, prng_state *prng);

    /** Self-test the PRNG
        @return CRYPT_OK if successful, CRYPT_NOP if self-testing has been disabled
     */
    int           (*test)(void);
} prng_descriptor[];

#ifdef LTC_YARROW
int yarrow_start(prng_state *prng);
int yarrow_add_entropy(const unsigned char *in, unsigned long inlen, prng_state *prng);
int yarrow_ready(prng_state *prng);
unsigned long yarrow_read(unsigned char *out, unsigned long outlen, prng_state *prng);
int yarrow_done(prng_state *prng);
int  yarrow_export(unsigned char *out, unsigned long *outlen, prng_state *prng);
int  yarrow_import(const unsigned char *in, unsigned long inlen, prng_state *prng);
int  yarrow_test(void);

extern const struct ltc_prng_descriptor yarrow_desc;
#endif

#ifdef LTC_FORTUNA
int fortuna_start(prng_state *prng);
int fortuna_add_entropy(const unsigned char *in, unsigned long inlen, prng_state *prng);
int fortuna_ready(prng_state *prng);
unsigned long fortuna_read(unsigned char *out, unsigned long outlen, prng_state *prng);
int fortuna_done(prng_state *prng);
int  fortuna_export(unsigned char *out, unsigned long *outlen, prng_state *prng);
int  fortuna_import(const unsigned char *in, unsigned long inlen, prng_state *prng);
int  fortuna_test(void);

extern const struct ltc_prng_descriptor fortuna_desc;
#endif

#ifdef LTC_RC4
int rc4_start(prng_state *prng);
int rc4_add_entropy(const unsigned char *in, unsigned long inlen, prng_state *prng);
int rc4_ready(prng_state *prng);
unsigned long rc4_read(unsigned char *out, unsigned long outlen, prng_state *prng);
int  rc4_done(prng_state *prng);
int  rc4_export(unsigned char *out, unsigned long *outlen, prng_state *prng);
int  rc4_import(const unsigned char *in, unsigned long inlen, prng_state *prng);
int  rc4_test(void);

extern const struct ltc_prng_descriptor rc4_desc;
#endif

#ifdef LTC_SPRNG
int sprng_start(prng_state *prng);
int sprng_add_entropy(const unsigned char *in, unsigned long inlen, prng_state *prng);
int sprng_ready(prng_state *prng);
unsigned long sprng_read(unsigned char *out, unsigned long outlen, prng_state *prng);
int sprng_done(prng_state *prng);
int  sprng_export(unsigned char *out, unsigned long *outlen, prng_state *prng);
int  sprng_import(const unsigned char *in, unsigned long inlen, prng_state *prng);
int  sprng_test(void);

extern const struct ltc_prng_descriptor sprng_desc;
#endif

#ifdef LTC_SOBER128
int sober128_start(prng_state *prng);
int sober128_add_entropy(const unsigned char *in, unsigned long inlen, prng_state *prng);
int sober128_ready(prng_state *prng);
unsigned long sober128_read(unsigned char *out, unsigned long outlen, prng_state *prng);
int sober128_done(prng_state *prng);
int  sober128_export(unsigned char *out, unsigned long *outlen, prng_state *prng);
int  sober128_import(const unsigned char *in, unsigned long inlen, prng_state *prng);
int  sober128_test(void);

extern const struct ltc_prng_descriptor sober128_desc;
#endif

int find_prng(const char *name);
int register_prng(const struct ltc_prng_descriptor *prng);
int unregister_prng(const struct ltc_prng_descriptor *prng);
int prng_is_valid(int idx);

LTC_MUTEX_PROTO(ltc_prng_mutex)

/* Slow RNG you **might** be able to use to seed a PRNG with.  Be careful as this
 * might not work on all platforms as planned
 */
unsigned long rng_get_bytes(unsigned char *out,
                            unsigned long outlen,
                            void (        *callback)(void));

int rng_make_prng(int bits, int wprng, prng_state *prng, void (*callback)(void));


/* $Source: /cvs/libtom/libtomcrypt/src/headers/tomcrypt_prng.h,v $ */
/* $Revision: 1.9 $ */
/* $Date: 2007/05/12 14:32:35 $ */ 

/* ---- NUMBER THEORY ---- */

enum {
    PK_PUBLIC =0,
    PK_PRIVATE=1
};

int rand_prime(void *N, long len, prng_state *prng, int wprng);

/* ---- RSA ---- */
#ifdef LTC_MRSA

/* Min and Max RSA key sizes (in bits) */
 #define MIN_RSA_SIZE    1024
 #define MAX_RSA_SIZE    4096

/** RSA LTC_PKCS style key */
typedef struct Rsa_key {
    /** Type of key, PK_PRIVATE or PK_PUBLIC */
    int  type;
    /** The public exponent */
    void *e;
    /** The private exponent */
    void *d;
    /** The modulus */
    void *N;
    /** The p factor of N */
    void *p;
    /** The q factor of N */
    void *q;
    /** The 1/q mod p CRT param */
    void *qP;
    /** The d mod (p - 1) CRT param */
    void *dP;
    /** The d mod (q - 1) CRT param */
    void *dQ;
} rsa_key;

int rsa_make_key(prng_state *prng, int wprng, int size, long e, rsa_key *key);

int rsa_exptmod(const unsigned char *in, unsigned long inlen,
                unsigned char *out, unsigned long *outlen, int which,
                rsa_key *key);

void rsa_free(rsa_key *key);

/* These use LTC_PKCS #1 v2.0 padding */
 #define rsa_encrypt_key(_in, _inlen, _out, _outlen, _lparam, _lparamlen, _prng, _prng_idx, _hash_idx, _key) \
    rsa_encrypt_key_ex(_in, _inlen, _out, _outlen, _lparam, _lparamlen, _prng, _prng_idx, _hash_idx, LTC_LTC_PKCS_1_OAEP, _key)

 #define rsa_decrypt_key(_in, _inlen, _out, _outlen, _lparam, _lparamlen, _hash_idx, _stat, _key) \
    rsa_decrypt_key_ex(_in, _inlen, _out, _outlen, _lparam, _lparamlen, _hash_idx, LTC_LTC_PKCS_1_OAEP, _stat, _key)

 #define rsa_sign_hash(_in, _inlen, _out, _outlen, _prng, _prng_idx, _hash_idx, _saltlen, _key) \
    rsa_sign_hash_ex(_in, _inlen, _out, _outlen, LTC_LTC_PKCS_1_PSS, _prng, _prng_idx, _hash_idx, _saltlen, _key)

 #define rsa_verify_hash(_sig, _siglen, _hash, _hashlen, _hash_idx, _saltlen, _stat, _key) \
    rsa_verify_hash_ex(_sig, _siglen, _hash, _hashlen, LTC_LTC_PKCS_1_PSS, _hash_idx, _saltlen, _stat, _key)

/* These can be switched between LTC_PKCS #1 v2.x and LTC_PKCS #1 v1.5 paddings */
int rsa_encrypt_key_ex(const unsigned char *in, unsigned long inlen,
                       unsigned char *out, unsigned long *outlen,
                       const unsigned char *lparam, unsigned long lparamlen,
                       prng_state *prng, int prng_idx, int hash_idx, int padding, rsa_key *key);

int rsa_decrypt_key_ex(const unsigned char *in, unsigned long inlen,
                       unsigned char *out, unsigned long *outlen,
                       const unsigned char *lparam, unsigned long lparamlen,
                       int hash_idx, int padding,
                       int *stat, rsa_key *key);

int rsa_sign_hash_ex(const unsigned char *in, unsigned long inlen,
                     unsigned char *out, unsigned long *outlen,
                     int padding,
                     prng_state *prng, int prng_idx,
                     int hash_idx, unsigned long saltlen,
                     rsa_key *key);

int rsa_verify_hash_ex(const unsigned char *sig, unsigned long siglen,
                       const unsigned char *hash, unsigned long hashlen,
                       int padding,
                       int hash_idx, unsigned long saltlen,
                       int *stat, rsa_key *key);

/* LTC_PKCS #1 import/export */
int rsa_export(unsigned char *out, unsigned long *outlen, int type, rsa_key *key);
int rsa_import(const unsigned char *in, unsigned long inlen, rsa_key *key);
#endif

/* ---- Katja ---- */
#ifdef MKAT

/* Min and Max KAT key sizes (in bits) */
 #define MIN_KAT_SIZE    1024
 #define MAX_KAT_SIZE    4096

/** Katja LTC_PKCS style key */
typedef struct KAT_key {
    /** Type of key, PK_PRIVATE or PK_PUBLIC */
    int  type;
    /** The private exponent */
    void *d;
    /** The modulus */
    void *N;
    /** The p factor of N */
    void *p;
    /** The q factor of N */
    void *q;
    /** The 1/q mod p CRT param */
    void *qP;
    /** The d mod (p - 1) CRT param */
    void *dP;
    /** The d mod (q - 1) CRT param */
    void *dQ;
    /** The pq param */
    void *pq;
} katja_key;

int katja_make_key(prng_state *prng, int wprng, int size, katja_key *key);

int katja_exptmod(const unsigned char *in, unsigned long inlen,
                  unsigned char *out, unsigned long *outlen, int which,
                  katja_key *key);

void katja_free(katja_key *key);

/* These use LTC_PKCS #1 v2.0 padding */
int katja_encrypt_key(const unsigned char *in, unsigned long inlen,
                      unsigned char *out, unsigned long *outlen,
                      const unsigned char *lparam, unsigned long lparamlen,
                      prng_state *prng, int prng_idx, int hash_idx, katja_key *key);

int katja_decrypt_key(const unsigned char *in, unsigned long inlen,
                      unsigned char *out, unsigned long *outlen,
                      const unsigned char *lparam, unsigned long lparamlen,
                      int hash_idx, int *stat,
                      katja_key *key);

/* LTC_PKCS #1 import/export */
int katja_export(unsigned char *out, unsigned long *outlen, int type, katja_key *key);
int katja_import(const unsigned char *in, unsigned long inlen, katja_key *key);
#endif

/* ---- ECC Routines ---- */
#ifdef LTC_MECC

/* size of our temp buffers for exported keys */
 #define ECC_BUF_SIZE    256

/* max private key size */
 #define ECC_MAXSIZE     66

/** Structure defines a NIST GF(p) curve */
typedef struct {
    /** The size of the curve in octets */
    int  size;

    /** name of curve */
    char *name;

    /** The prime that defines the field the curve is in (encoded in hex) */
    char *prime;

    /** The fields B param (hex) */
    char *B;

    /** The order of the curve (hex) */
    char *order;

    /** The x co-ordinate of the base point on the curve (hex) */
    char *Gx;

    /** The y co-ordinate of the base point on the curve (hex) */
    char *Gy;
} ltc_ecc_set_type;

/** A point on a ECC curve, stored in Jacbobian format such that (x,y,z) => (x/z^2, y/z^3, 1) when interpretted as affine */
typedef struct {
    /** The x co-ordinate */
    void *x;

    /** The y co-ordinate */
    void *y;

    /** The z co-ordinate */
    void *z;
} ecc_point;

/** An ECC key */
typedef struct {
    /** Type of key, PK_PRIVATE or PK_PUBLIC */
    int                    type;

    /** Index into the ltc_ecc_sets[] for the parameters of this curve; if -1, then this key is using user supplied curve in dp */
    int                    idx;

    /** pointer to domain parameters; either points to NIST curves (identified by idx >= 0) or user supplied curve */
    const ltc_ecc_set_type *dp;

    /** The public key */
    ecc_point              pubkey;

    /** The private key */
    void                   *k;
} ecc_key;

/** the ECC params provided */
extern const ltc_ecc_set_type ltc_ecc_sets[];

int  ecc_test(void);
void ecc_sizes(int *low, int *high);
int  ecc_get_size(ecc_key *key);

int  ecc_make_key(prng_state *prng, int wprng, int keysize, ecc_key *key);
int  ecc_make_key_ex(prng_state *prng, int wprng, ecc_key *key, const ltc_ecc_set_type *dp);
void ecc_free(ecc_key *key);

int  ecc_export(unsigned char *out, unsigned long *outlen, int type, ecc_key *key);
int  ecc_import(const unsigned char *in, unsigned long inlen, ecc_key *key);
int  ecc_import_ex(const unsigned char *in, unsigned long inlen, ecc_key *key, const ltc_ecc_set_type *dp);

int ecc_ansi_x963_export(ecc_key *key, unsigned char *out, unsigned long *outlen);
int ecc_ansi_x963_import(const unsigned char *in, unsigned long inlen, ecc_key *key);
int ecc_ansi_x963_import_ex(const unsigned char *in, unsigned long inlen, ecc_key *key, ltc_ecc_set_type *dp);

int  ecc_shared_secret(ecc_key *private_key, ecc_key *public_key,
                       unsigned char *out, unsigned long *outlen);

int  ecc_encrypt_key(const unsigned char *in, unsigned long inlen,
                     unsigned char *out, unsigned long *outlen,
                     prng_state *prng, int wprng, int hash,
                     ecc_key *key);

int  ecc_decrypt_key(const unsigned char *in, unsigned long inlen,
                     unsigned char *out, unsigned long *outlen,
                     ecc_key *key);

int  ecc_sign_hash(const unsigned char *in, unsigned long inlen,
                   unsigned char *out, unsigned long *outlen,
                   prng_state *prng, int wprng, ecc_key *key);

int  ecc_verify_hash(const unsigned char *sig, unsigned long siglen,
                     const unsigned char *hash, unsigned long hashlen,
                     int *stat, ecc_key *key);

/* low level functions */
ecc_point *ltc_ecc_new_point(void);
void       ltc_ecc_del_point(ecc_point *p);
int        ltc_ecc_is_valid_idx(int n);

/* point ops (mp == montgomery digit) */
 #if !defined(LTC_MECC_ACCEL) || defined(LTM_LTC_DESC) || defined(GMP_LTC_DESC)
/* R = 2P */
int ltc_ecc_projective_dbl_point(ecc_point *P, ecc_point *R, void *modulus, void *mp);

/* R = P + Q */
int ltc_ecc_projective_add_point(ecc_point *P, ecc_point *Q, ecc_point *R, void *modulus, void *mp);
 #endif

 #if defined(LTC_MECC_FP)
/* optimized point multiplication using fixed point cache (HAC algorithm 14.117) */
int ltc_ecc_fp_mulmod(void *k, ecc_point *G, ecc_point *R, void *modulus, int map);

/* functions for saving/loading/freeing/adding to fixed point cache */
int ltc_ecc_fp_save_state(unsigned char **out, unsigned long *outlen);
int ltc_ecc_fp_restore_state(unsigned char *in, unsigned long inlen);
void ltc_ecc_fp_free(void);
int ltc_ecc_fp_add_point(ecc_point *g, void *modulus, int lock);

/* lock/unlock all points currently in fixed point cache */
void ltc_ecc_fp_tablelock(int lock);
 #endif

/* R = kG */
int ltc_ecc_mulmod(void *k, ecc_point *G, ecc_point *R, void *modulus, int map);

 #ifdef LTC_ECC_SHAMIR
/* kA*A + kB*B = C */
int ltc_ecc_mul2add(ecc_point *A, void *kA,
                    ecc_point *B, void *kB,
                    ecc_point *C,
                    void *modulus);

  #ifdef LTC_MECC_FP
/* Shamir's trick with optimized point multiplication using fixed point cache */
int ltc_ecc_fp_mul2add(ecc_point *A, void *kA,
                       ecc_point *B, void *kB,
                       ecc_point *C, void *modulus);
  #endif
 #endif


/* map P to affine from projective */
int ltc_ecc_map(ecc_point *P, void *modulus, void *mp);
#endif

#ifdef LTC_MDSA

/* Max diff between group and modulus size in bytes */
 #define LTC_MDSA_DELTA        512

/* Max DSA group size in bytes (default allows 4k-bit groups) */
 #define LTC_MDSA_MAX_GROUP    512

/** DSA key structure */
typedef struct {
    /** The key type, PK_PRIVATE or PK_PUBLIC */
    int  type;

    /** The order of the sub-group used in octets */
    int  qord;

    /** The generator  */
    void *g;

    /** The prime used to generate the sub-group */
    void *q;

    /** The large prime that generats the field the contains the sub-group */
    void *p;

    /** The private key */
    void *x;

    /** The public key */
    void *y;
} dsa_key;

int dsa_make_key(prng_state *prng, int wprng, int group_size, int modulus_size, dsa_key *key);
void dsa_free(dsa_key *key);

int dsa_sign_hash_raw(const unsigned char *in, unsigned long inlen,
                      void *r, void *s,
                      prng_state *prng, int wprng, dsa_key *key);

int dsa_sign_hash(const unsigned char *in, unsigned long inlen,
                  unsigned char *out, unsigned long *outlen,
                  prng_state *prng, int wprng, dsa_key *key);

int dsa_verify_hash_raw(void *r, void *s,
                        const unsigned char *hash, unsigned long hashlen,
                        int *stat, dsa_key *key);

int dsa_verify_hash(const unsigned char *sig, unsigned long siglen,
                    const unsigned char *hash, unsigned long hashlen,
                    int *stat, dsa_key *key);

int dsa_encrypt_key(const unsigned char *in, unsigned long inlen,
                    unsigned char *out, unsigned long *outlen,
                    prng_state *prng, int wprng, int hash,
                    dsa_key *key);

int dsa_decrypt_key(const unsigned char *in, unsigned long inlen,
                    unsigned char *out, unsigned long *outlen,
                    dsa_key *key);

int dsa_import(const unsigned char *in, unsigned long inlen, dsa_key *key);
int dsa_export(unsigned char *out, unsigned long *outlen, int type, dsa_key *key);
int dsa_verify_key(dsa_key *key, int *stat);

int dsa_shared_secret(void *private_key, void *base,
                      dsa_key *public_key,
                      unsigned char *out, unsigned long *outlen);
#endif

#ifdef LTC_DER
/* DER handling */

enum {
    LTC_ASN1_EOL,
    LTC_ASN1_BOOLEAN,
    LTC_ASN1_INTEGER,
    LTC_ASN1_SHORT_INTEGER,
    LTC_ASN1_BIT_STRING,
    LTC_ASN1_OCTET_STRING,
    LTC_ASN1_NULL,
    LTC_ASN1_OBJECT_IDENTIFIER,
    LTC_ASN1_IA5_STRING,
    LTC_ASN1_PRINTABLE_STRING,
    LTC_ASN1_UTF8_STRING,
    LTC_ASN1_UTCTIME,
    LTC_ASN1_CHOICE,
    LTC_ASN1_SEQUENCE,
    LTC_ASN1_SET,
    LTC_ASN1_SETOF
};

/** A LTC ASN.1 list type */
typedef struct ltc_asn1_list_ {
    /** The LTC ASN.1 enumerated type identifier */
    int                   type;
    /** The data to encode or place for decoding */
    void                  *data;
    /** The size of the input or resulting output */
    unsigned long         size;
    /** The used flag, this is used by the CHOICE ASN.1 type to indicate which choice was made */
    int                   used;
    /** prev/next entry in the list */
    struct ltc_asn1_list_ *prev, *next, *child, *parent;
} ltc_asn1_list;

 #define LTC_SET_ASN1(list, index, Type, Data, Size)          \
    do {                                                      \
        int           LTC_MACRO_temp  = (index);              \
        ltc_asn1_list *LTC_MACRO_list = (list);               \
        LTC_MACRO_list[LTC_MACRO_temp].type = (Type);         \
        LTC_MACRO_list[LTC_MACRO_temp].data = (void *)(Data); \
        LTC_MACRO_list[LTC_MACRO_temp].size = (Size);         \
        LTC_MACRO_list[LTC_MACRO_temp].used = 0;              \
    } while (0);

/* SEQUENCE */
int der_encode_sequence_ex(ltc_asn1_list *list, unsigned long inlen,
                           unsigned char *out, unsigned long *outlen, int type_of);

 #define der_encode_sequence(list, inlen, out, outlen)    der_encode_sequence_ex(list, inlen, out, outlen, LTC_ASN1_SEQUENCE)

int der_decode_sequence_ex(const unsigned char *in, unsigned long inlen,
                           ltc_asn1_list *list, unsigned long outlen, int ordered);

 #define der_decode_sequence(in, inlen, list, outlen)    der_decode_sequence_ex(in, inlen, list, outlen, 1)

int der_length_sequence(ltc_asn1_list *list, unsigned long inlen,
                        unsigned long *outlen);

/* SET */
 #define der_decode_set(in, inlen, list, outlen)    der_decode_sequence_ex(in, inlen, list, outlen, 0)
 #define der_length_set    der_length_sequence
int der_encode_set(ltc_asn1_list *list, unsigned long inlen,
                   unsigned char *out, unsigned long *outlen);

int der_encode_setof(ltc_asn1_list *list, unsigned long inlen,
                     unsigned char *out, unsigned long *outlen);

/* VA list handy helpers with triplets of <type, size, data> */
int der_encode_sequence_multi(unsigned char *out, unsigned long *outlen, ...);
int der_decode_sequence_multi(const unsigned char *in, unsigned long inlen, ...);

/* FLEXI DECODER handle unknown list decoder */
int  der_decode_sequence_flexi(const unsigned char *in, unsigned long *inlen, ltc_asn1_list **out);
void der_free_sequence_flexi(ltc_asn1_list *list);
void der_sequence_free(ltc_asn1_list *in);

/* BOOLEAN */
int der_length_boolean(unsigned long *outlen);
int der_encode_boolean(int in,
                       unsigned char *out, unsigned long *outlen);
int der_decode_boolean(const unsigned char *in, unsigned long inlen,
                       int *out);

/* INTEGER */
int der_encode_integer(void *num, unsigned char *out, unsigned long *outlen);
int der_decode_integer(const unsigned char *in, unsigned long inlen, void *num);
int der_length_integer(void *num, unsigned long *len);

/* INTEGER -- handy for 0..2^32-1 values */
int der_decode_short_integer(const unsigned char *in, unsigned long inlen, unsigned long *num);
int der_encode_short_integer(unsigned long num, unsigned char *out, unsigned long *outlen);
int der_length_short_integer(unsigned long num, unsigned long *outlen);

/* BIT STRING */
int der_encode_bit_string(const unsigned char *in, unsigned long inlen,
                          unsigned char *out, unsigned long *outlen);
int der_decode_bit_string(const unsigned char *in, unsigned long inlen,
                          unsigned char *out, unsigned long *outlen);
int der_length_bit_string(unsigned long nbits, unsigned long *outlen);

/* OCTET STRING */
int der_encode_octet_string(const unsigned char *in, unsigned long inlen,
                            unsigned char *out, unsigned long *outlen);
int der_decode_octet_string(const unsigned char *in, unsigned long inlen,
                            unsigned char *out, unsigned long *outlen);
int der_length_octet_string(unsigned long noctets, unsigned long *outlen);

/* OBJECT IDENTIFIER */
int der_encode_object_identifier(unsigned long *words, unsigned long nwords,
                                 unsigned char *out, unsigned long *outlen);
int der_decode_object_identifier(const unsigned char *in, unsigned long inlen,
                                 unsigned long *words, unsigned long *outlen);
int der_length_object_identifier(unsigned long *words, unsigned long nwords, unsigned long *outlen);
unsigned long der_object_identifier_bits(unsigned long x);

/* IA5 STRING */
int der_encode_ia5_string(const unsigned char *in, unsigned long inlen,
                          unsigned char *out, unsigned long *outlen);
int der_decode_ia5_string(const unsigned char *in, unsigned long inlen,
                          unsigned char *out, unsigned long *outlen);
int der_length_ia5_string(const unsigned char *octets, unsigned long noctets, unsigned long *outlen);

int der_ia5_char_encode(int c);
int der_ia5_value_decode(int v);

/* Printable STRING */
int der_encode_printable_string(const unsigned char *in, unsigned long inlen,
                                unsigned char *out, unsigned long *outlen);
int der_decode_printable_string(const unsigned char *in, unsigned long inlen,
                                unsigned char *out, unsigned long *outlen);
int der_length_printable_string(const unsigned char *octets, unsigned long noctets, unsigned long *outlen);

int der_printable_char_encode(int c);
int der_printable_value_decode(int v);

/* UTF-8 */
 #if (defined(SIZE_MAX) || __STDC_VERSION__ >= 199901L || defined(WCHAR_MAX) || defined(_WCHAR_T) || defined(_WCHAR_T_DEFINED) || defined (__WCHAR_TYPE__)) && !defined(LTC_NO_WCHAR)
  #include <wchar.h>
 #else
typedef ulong32   wchar_t;
 #endif

int der_encode_utf8_string(const wchar_t *in, unsigned long inlen,
                           unsigned char *out, unsigned long *outlen);

int der_decode_utf8_string(const unsigned char *in, unsigned long inlen,
                           wchar_t *out, unsigned long *outlen);
unsigned long der_utf8_charsize(const wchar_t c);
int der_length_utf8_string(const wchar_t *in, unsigned long noctets, unsigned long *outlen);


/* CHOICE */
int der_decode_choice(const unsigned char *in, unsigned long *inlen,
                      ltc_asn1_list *list, unsigned long outlen);

/* UTCTime */
typedef struct {
    unsigned YY,      /* year */
             MM,      /* month */
             DD,      /* day */
             hh,      /* hour */
             mm,      /* minute */
             ss,      /* second */
             off_dir, /* timezone offset direction 0 == +, 1 == - */
             off_hh,  /* timezone offset hours */
             off_mm;  /* timezone offset minutes */
} ltc_utctime;

int der_encode_utctime(ltc_utctime *utctime,
                       unsigned char *out, unsigned long *outlen);

int der_decode_utctime(const unsigned char *in, unsigned long *inlen,
                       ltc_utctime *out);

int der_length_utctime(ltc_utctime *utctime, unsigned long *outlen);
#endif

/* $Source: /cvs/libtom/libtomcrypt/src/headers/tomcrypt_pk.h,v $ */
/* $Revision: 1.81 $ */
/* $Date: 2007/05/12 14:32:35 $ */ 

/** math functions **/
#define LTC_SOURCE
#define LTC_MP_LT     -1
#define LTC_MP_EQ     0
#define LTC_MP_GT     1

#define LTC_MP_NO     0
#define LTC_MP_YES    1

#ifndef LTC_MECC
typedef void   ecc_point;
#endif

#ifndef LTC_MRSA
typedef void   rsa_key;
#endif

/** math descriptor */
typedef struct {
    /** Name of the math provider */
    char *name;

    /** Bits per digit, amount of bits must fit in an unsigned long */
    int  bits_per_digit;

/* ---- init/deinit functions ---- */

    /** initialize a bignum
       @param   a     The number to initialize
       @return  CRYPT_OK on success
     */
    int (*init)(void **a);

    /** init copy
       @param  dst    The number to initialize and write to
       @param  src    The number to copy from
       @return CRYPT_OK on success
     */
    int (*init_copy)(void **dst, void *src);

    /** deinit
       @param   a    The number to free
       @return CRYPT_OK on success
     */
    void (*deinit)(void *a);

/* ---- data movement ---- */

    /** negate
       @param   src   The number to negate
       @param   dst   The destination
       @return CRYPT_OK on success
     */
    int (*neg)(void *src, void *dst);

    /** copy
       @param   src   The number to copy from
       @param   dst   The number to write to
       @return CRYPT_OK on success
     */
    int (*copy)(void *src, void *dst);

/* ---- trivial low level functions ---- */

    /** set small constant
       @param a    Number to write to
       @param n    Source upto bits_per_digit (actually meant for very small constants)
       @return CRYPT_OK on succcess
     */
    int (*set_int)(void *a, unsigned long n);

    /** get small constant
       @param a    Number to read, only fetches upto bits_per_digit from the number
       @return  The lower bits_per_digit of the integer (unsigned)
     */
    unsigned long (*get_int)(void *a);

    /** get digit n
       @param a  The number to read from
       @param n  The number of the digit to fetch
       @return  The bits_per_digit  sized n'th digit of a
     */
    unsigned long (*get_digit)(void *a, int n);

    /** Get the number of digits that represent the number
       @param a   The number to count
       @return The number of digits used to represent the number
     */
    int (*get_digit_count)(void *a);

    /** compare two integers
       @param a   The left side integer
       @param b   The right side integer
       @return LTC_MP_LT if a < b, LTC_MP_GT if a > b and LTC_MP_EQ otherwise.  (signed comparison)
     */
    int (*compare)(void *a, void *b);

    /** compare against int
       @param a   The left side integer
       @param b   The right side integer (upto bits_per_digit)
       @return LTC_MP_LT if a < b, LTC_MP_GT if a > b and LTC_MP_EQ otherwise.  (signed comparison)
     */
    int (*compare_d)(void *a, unsigned long n);

    /** Count the number of bits used to represent the integer
       @param a   The integer to count
       @return The number of bits required to represent the integer
     */
    int (*count_bits)(void *a);

    /** Count the number of LSB bits which are zero
       @param a   The integer to count
       @return The number of contiguous zero LSB bits
     */
    int (*count_lsb_bits)(void *a);

    /** Compute a power of two
       @param a  The integer to store the power in
       @param n  The power of two you want to store (a = 2^n)
       @return CRYPT_OK on success
     */
    int (*twoexpt)(void *a, int n);

/* ---- radix conversions ---- */

    /** read ascii string
       @param a     The integer to store into
       @param str   The string to read
       @param radix The radix the integer has been represented in (2-64)
       @return CRYPT_OK on success
     */
    int (*read_radix)(void *a, const char *str, int radix);

    /** write number to string
       @param a     The integer to store
       @param str   The destination for the string
       @param radix The radix the integer is to be represented in (2-64)
       @return CRYPT_OK on success
     */
    int (*write_radix)(void *a, char *str, int radix);

    /** get size as unsigned char string
       @param a     The integer to get the size (when stored in array of octets)
       @return The length of the integer
     */
    unsigned long (*unsigned_size)(void *a);

    /** store an integer as an array of octets
       @param src   The integer to store
       @param dst   The buffer to store the integer in
       @return CRYPT_OK on success
     */
    int (*unsigned_write)(void *src, unsigned char *dst);

    /** read an array of octets and store as integer
       @param dst   The integer to load
       @param src   The array of octets
       @param len   The number of octets
       @return CRYPT_OK on success
     */
    int (*unsigned_read)(void *dst, unsigned char *src, unsigned long len);

/* ---- basic math ---- */

    /** add two integers
       @param a   The first source integer
       @param b   The second source integer
       @param c   The destination of "a + b"
       @return CRYPT_OK on success
     */
    int (*add)(void *a, void *b, void *c);


    /** add two integers
       @param a   The first source integer
       @param b   The second source integer (single digit of upto bits_per_digit in length)
       @param c   The destination of "a + b"
       @return CRYPT_OK on success
     */
    int (*addi)(void *a, unsigned long b, void *c);

    /** subtract two integers
       @param a   The first source integer
       @param b   The second source integer
       @param c   The destination of "a - b"
       @return CRYPT_OK on success
     */
    int (*sub)(void *a, void *b, void *c);

    /** subtract two integers
       @param a   The first source integer
       @param b   The second source integer (single digit of upto bits_per_digit in length)
       @param c   The destination of "a - b"
       @return CRYPT_OK on success
     */
    int (*subi)(void *a, unsigned long b, void *c);

    /** multiply two integers
       @param a   The first source integer
       @param b   The second source integer (single digit of upto bits_per_digit in length)
       @param c   The destination of "a * b"
       @return CRYPT_OK on success
     */
    int (*mul)(void *a, void *b, void *c);

    /** multiply two integers
       @param a   The first source integer
       @param b   The second source integer (single digit of upto bits_per_digit in length)
       @param c   The destination of "a * b"
       @return CRYPT_OK on success
     */
    int (*muli)(void *a, unsigned long b, void *c);

    /** Square an integer
       @param a    The integer to square
       @param b    The destination
       @return CRYPT_OK on success
     */
    int (*sqr)(void *a, void *b);

    /** Divide an integer
       @param a    The dividend
       @param b    The divisor
       @param c    The quotient (can be NULL to signify don't care)
       @param d    The remainder (can be NULL to signify don't care)
       @return CRYPT_OK on success
     */
    int (*mpdiv)(void *a, void *b, void *c, void *d);

    /** divide by two
       @param  a   The integer to divide (shift right)
       @param  b   The destination
       @return CRYPT_OK on success
     */
    int (*div_2)(void *a, void *b);

    /** Get remainder (small value)
       @param  a    The integer to reduce
       @param  b    The modulus (upto bits_per_digit in length)
       @param  c    The destination for the residue
       @return CRYPT_OK on success
     */
    int (*modi)(void *a, unsigned long b, unsigned long *c);

    /** gcd
       @param  a     The first integer
       @param  b     The second integer
       @param  c     The destination for (a, b)
       @return CRYPT_OK on success
     */
    int (*gcd)(void *a, void *b, void *c);

    /** lcm
       @param  a     The first integer
       @param  b     The second integer
       @param  c     The destination for [a, b]
       @return CRYPT_OK on success
     */
    int (*lcm)(void *a, void *b, void *c);

    /** Modular multiplication
       @param  a     The first source
       @param  b     The second source
       @param  c     The modulus
       @param  d     The destination (a*b mod c)
       @return CRYPT_OK on success
     */
    int (*mulmod)(void *a, void *b, void *c, void *d);

    /** Modular squaring
       @param  a     The first source
       @param  b     The modulus
       @param  c     The destination (a*a mod b)
       @return CRYPT_OK on success
     */
    int (*sqrmod)(void *a, void *b, void *c);

    /** Modular inversion
       @param  a     The value to invert
       @param  b     The modulus
       @param  c     The destination (1/a mod b)
       @return CRYPT_OK on success
     */
    int (*invmod)(void *, void *, void *);

/* ---- reduction ---- */

    /** setup montgomery
        @param a  The modulus
        @param b  The destination for the reduction digit
        @return CRYPT_OK on success
     */
    int (*montgomery_setup)(void *a, void **b);

    /** get normalization value
        @param a   The destination for the normalization value
        @param b   The modulus
        @return  CRYPT_OK on success
     */
    int (*montgomery_normalization)(void *a, void *b);

    /** reduce a number
        @param a   The number [and dest] to reduce
        @param b   The modulus
        @param c   The value "b" from montgomery_setup()
        @return CRYPT_OK on success
     */
    int (*montgomery_reduce)(void *a, void *b, void *c);

    /** clean up  (frees memory)
        @param a   The value "b" from montgomery_setup()
        @return CRYPT_OK on success
     */
    void (*montgomery_deinit)(void *a);

/* ---- exponentiation ---- */

    /** Modular exponentiation
        @param a    The base integer
        @param b    The power (can be negative) integer
        @param c    The modulus integer
        @param d    The destination
        @return CRYPT_OK on success
     */
    int (*exptmod)(void *a, void *b, void *c, void *d);

    /** Primality testing
        @param a     The integer to test
        @param b     The destination of the result (FP_YES if prime)
        @return CRYPT_OK on success
     */
    int (*isprime)(void *a, int *b);

/* ----  (optional) ecc point math ---- */

    /** ECC GF(p) point multiplication (from the NIST curves)
        @param k   The integer to multiply the point by
        @param G   The point to multiply
        @param R   The destination for kG
        @param modulus  The modulus for the field
        @param map Boolean indicated whether to map back to affine or not (can be ignored if you work in affine only)
        @return CRYPT_OK on success
     */
    int (*ecc_ptmul)(void *k, ecc_point *G, ecc_point *R, void *modulus, int map);

    /** ECC GF(p) point addition
        @param P    The first point
        @param Q    The second point
        @param R    The destination of P + Q
        @param modulus  The modulus
        @param mp   The "b" value from montgomery_setup()
        @return CRYPT_OK on success
     */
    int (*ecc_ptadd)(ecc_point *P, ecc_point *Q, ecc_point *R, void *modulus, void *mp);

    /** ECC GF(p) point double
        @param P    The first point
        @param R    The destination of 2P
        @param modulus  The modulus
        @param mp   The "b" value from montgomery_setup()
        @return CRYPT_OK on success
     */
    int (*ecc_ptdbl)(ecc_point *P, ecc_point *R, void *modulus, void *mp);

    /** ECC mapping from projective to affine, currently uses (x,y,z) => (x/z^2, y/z^3, 1)
        @param P     The point to map
        @param modulus The modulus
        @param mp    The "b" value from montgomery_setup()
        @return CRYPT_OK on success
        @remark  The mapping can be different but keep in mind a ecc_point only has three
                 integers (x,y,z) so if you use a different mapping you have to make it fit.
     */
    int (*ecc_map)(ecc_point *P, void *modulus, void *mp);

    /** Computes kA*A + kB*B = C using Shamir's Trick
        @param A        First point to multiply
        @param kA       What to multiple A by
        @param B        Second point to multiply
        @param kB       What to multiple B by
        @param C        [out] Destination point (can overlap with A or B
        @param modulus  Modulus for curve
        @return CRYPT_OK on success
     */
    int (*ecc_mul2add)(ecc_point *A, void *kA,
                       ecc_point *B, void *kB,
                       ecc_point *C,
                       void *modulus);

/* ---- (optional) rsa optimized math (for internal CRT) ---- */

    /** RSA Key Generation
        @param prng     An active PRNG state
        @param wprng    The index of the PRNG desired
        @param size     The size of the modulus (key size) desired (octets)
        @param e        The "e" value (public key).  e==65537 is a good choice
        @param key      [out] Destination of a newly created private key pair
        @return CRYPT_OK if successful, upon error all allocated ram is freed
     */
    int (*rsa_keygen)(prng_state *prng, int wprng, int size, long e, rsa_key *key);


    /** RSA exponentiation
       @param in       The octet array representing the base
       @param inlen    The length of the input
       @param out      The destination (to be stored in an octet array format)
       @param outlen   The length of the output buffer and the resulting size (zero padded to the size of the modulus)
       @param which    PK_PUBLIC for public RSA and PK_PRIVATE for private RSA
       @param key      The RSA key to use
       @return CRYPT_OK on success
     */
    int (*rsa_me)(const unsigned char *in, unsigned long inlen,
                  unsigned char *out, unsigned long *outlen, int which,
                  rsa_key *key);
} ltc_math_descriptor;

extern ltc_math_descriptor ltc_mp;

int ltc_init_multi(void **a, ...);
void ltc_deinit_multi(void *a, ...);

#ifdef LTM_DESC
extern const ltc_math_descriptor ltm_desc;
#endif

#ifdef TFM_DESC
extern const ltc_math_descriptor tfm_desc;
#endif

#ifdef GMP_DESC
extern const ltc_math_descriptor gmp_desc;
#endif


/* $Source: /cvs/libtom/libtomcrypt/src/headers/tomcrypt_math.h,v $ */
/* $Revision: 1.44 $ */
/* $Date: 2007/05/12 14:32:35 $ */ 

/* ---- LTC_BASE64 Routines ---- */
#ifdef LTC_BASE64
int base64_encode(const unsigned char *in, unsigned long len,
                  unsigned char *out, unsigned long *outlen);

int base64_decode(const unsigned char *in, unsigned long len,
                  unsigned char *out, unsigned long *outlen);
#endif

/* ---- MEM routines ---- */
void zeromem(void *dst, size_t len);
void burn_stack(unsigned long len);

const char *error_to_string(int err);

extern const char *crypt_build_settings;

/* ---- HMM ---- */
int crypt_fsa(void *mp, ...);

/* $Source: /cvs/libtom/libtomcrypt/src/headers/tomcrypt_misc.h,v $ */
/* $Revision: 1.5 $ */
/* $Date: 2007/05/12 14:32:35 $ */ 

/* Defines the LTC_ARGCHK macro used within the library */
/* ARGTYPE is defined in mycrypt_cfg.h */
#if ARGTYPE == 0

 #include <signal.h>

/* this is the default LibTomCrypt macro  */
void crypt_argchk(char *v, char *s, int d);

 #define LTC_ARGCHK(x)      if (!(x)) { crypt_argchk(#x, __FILE__, __LINE__); }
 #define LTC_ARGCHKVD(x)    LTC_ARGCHK(x)

#elif ARGTYPE == 1

/* fatal type of error */
 #define LTC_ARGCHK(x)      assert((x))
 #define LTC_ARGCHKVD(x)    LTC_ARGCHK(x)

#elif ARGTYPE == 2

 #define LTC_ARGCHK(x)      if (!(x)) { fprintf(stderr, "\nwarning: ARGCHK failed at %s:%d\n", __FILE__, __LINE__); }
 #define LTC_ARGCHKVD(x)    LTC_ARGCHK(x)

#elif ARGTYPE == 3

 #define LTC_ARGCHK(x)
 #define LTC_ARGCHKVD(x)    LTC_ARGCHK(x)

#elif ARGTYPE == 4

 #define LTC_ARGCHK(x)      if (!(x)) return CRYPT_INVALID_ARG;
 #define LTC_ARGCHKVD(x)    if (!(x)) return;
#endif


/* $Source: /cvs/libtom/libtomcrypt/src/headers/tomcrypt_argchk.h,v $ */
/* $Revision: 1.5 $ */
/* $Date: 2006/08/27 20:50:21 $ */ 

/* LTC_PKCS Header Info */

/* ===> LTC_PKCS #1 -- RSA Cryptography <=== */





/* $Source: /cvs/libtom/libtomcrypt/src/pk/asn1/der/sequence/der_sequence_free.c,v $ */
/* $Revision: 1.4 $ */
/* $Date: 2006/12/28 01:27:24 $ */


/* LibTomCrypt, modular cryptographic library -- Tom St Denis
 *
 * LibTomCrypt is a library that provides various cryptographic
 * algorithms in a highly modular and flexible manner.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tomstdenis@gmail.com, http://libtom.org
 */

/* Implements ECC over Z/pZ for curve y^2 = x^3 - 3x + b
 *
 * All curves taken from NIST recommendation paper of July 1999
 * Available at http://csrc.nist.gov/cryptval/dss.htm
 */


/**
   @file ecc.c
   ECC Crypto, Tom St Denis
 */


/* $Source: /cvs/libtom/libtomcrypt/src/pk/ecc/ecc.c,v $ */
/* $Revision: 1.40 $ */
/* $Date: 2007/05/12 14:32:35 $ */


/* LibTomCrypt, modular cryptographic library -- Tom St Denis
 *
 * LibTomCrypt is a library that provides various cryptographic
 * algorithms in a highly modular and flexible manner.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tomstdenis@gmail.com, http://libtom.org
 */

/* Implements ECC over Z/pZ for curve y^2 = x^3 - 3x + b
 *
 * All curves taken from NIST recommendation paper of July 1999
 * Available at http://csrc.nist.gov/cryptval/dss.htm
 */


/**
   @file ecc_ansi_x963_export.c
   ECC Crypto, Tom St Denis
 */

#ifdef LTC_MECC

/** ECC X9.63 (Sec. 4.3.6) uncompressed export
   @param key     Key to export
   @param out     [out] destination of export
   @param outlen  [in/out]  Length of destination and final output size
   Return CRYPT_OK on success
 */
int ecc_ansi_x963_export(ecc_key *key, unsigned char *out, unsigned long *outlen) {
    unsigned char buf[ECC_BUF_SIZE];
    unsigned long numlen;

    LTC_ARGCHK(key != NULL);
    LTC_ARGCHK(out != NULL);
    LTC_ARGCHK(outlen != NULL);

    if (ltc_ecc_is_valid_idx(key->idx) == 0) {
        return CRYPT_INVALID_ARG;
    }
    numlen = key->dp->size;

    if (*outlen < (1 + 2 * numlen)) {
        *outlen = 1 + 2 * numlen;
        return CRYPT_BUFFER_OVERFLOW;
    }

    /* store byte 0x04 */
    out[0] = 0x04;

    /* pad and store x */
    zeromem(buf, sizeof(buf));
    mp_to_unsigned_bin(key->pubkey.x, buf + (numlen - mp_unsigned_bin_size(key->pubkey.x)));
    XMEMCPY(out + 1, buf, numlen);

    /* pad and store y */
    zeromem(buf, sizeof(buf));
    mp_to_unsigned_bin(key->pubkey.y, buf + (numlen - mp_unsigned_bin_size(key->pubkey.y)));
    XMEMCPY(out + 1 + numlen, buf, numlen);

    *outlen = 1 + 2 * numlen;
    return CRYPT_OK;
}
#endif

/* $Source: /cvs/libtom/libtomcrypt/src/pk/ecc/ecc_ansi_x963_export.c,v $ */
/* $Revision: 1.6 $ */
/* $Date: 2007/05/12 14:32:35 $ */


/* LibTomCrypt, modular cryptographic library -- Tom St Denis
 *
 * LibTomCrypt is a library that provides various cryptographic
 * algorithms in a highly modular and flexible manner.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tomstdenis@gmail.com, http://libtom.org
 */

/* Implements ECC over Z/pZ for curve y^2 = x^3 - 3x + b
 *
 * All curves taken from NIST recommendation paper of July 1999
 * Available at http://csrc.nist.gov/cryptval/dss.htm
 */


/**
   @file ecc_ansi_x963_import.c
   ECC Crypto, Tom St Denis
 */

#ifdef LTC_MECC

/** Import an ANSI X9.63 format public key
   @param in      The input data to read
   @param inlen   The length of the input data
   @param key     [out] destination to store imported key \
 */
int ecc_ansi_x963_import(const unsigned char *in, unsigned long inlen, ecc_key *key) {
    return ecc_ansi_x963_import_ex(in, inlen, key, NULL);
}

int ecc_ansi_x963_import_ex(const unsigned char *in, unsigned long inlen, ecc_key *key, ltc_ecc_set_type *dp) {
    int x, err;

    LTC_ARGCHK(in != NULL);
    LTC_ARGCHK(key != NULL);

    /* must be odd */
    if ((inlen & 1) == 0) {
        return CRYPT_INVALID_ARG;
    }

    /* init key */
    if (mp_init_multi(&key->pubkey.x, &key->pubkey.y, &key->pubkey.z, &key->k, NULL) != CRYPT_OK) {
        return CRYPT_MEM;
    }

    /* check for 4, 6 or 7 */
    if ((in[0] != 4) && (in[0] != 6) && (in[0] != 7)) {
        err = CRYPT_INVALID_PACKET;
        goto error;
    }

    /* read data */
    if ((err = mp_read_unsigned_bin(key->pubkey.x, (unsigned char *)in + 1, (inlen - 1) >> 1)) != CRYPT_OK) {
        goto error;
    }

    if ((err = mp_read_unsigned_bin(key->pubkey.y, (unsigned char *)in + 1 + ((inlen - 1) >> 1), (inlen - 1) >> 1)) != CRYPT_OK) {
        goto error;
    }
    if ((err = mp_set(key->pubkey.z, 1)) != CRYPT_OK) {
        goto error;
    }

    if (dp == NULL) {
        /* determine the idx */
        for (x = 0; ltc_ecc_sets[x].size != 0; x++) {
            if ((unsigned)ltc_ecc_sets[x].size >= ((inlen - 1) >> 1)) {
                break;
            }
        }
        if (ltc_ecc_sets[x].size == 0) {
            err = CRYPT_INVALID_PACKET;
            goto error;
        }
        /* set the idx */
        key->idx = x;
        key->dp  = &ltc_ecc_sets[x];
    } else {
        if (((inlen - 1) >> 1) != (unsigned long)dp->size) {
            err = CRYPT_INVALID_PACKET;
            goto error;
        }
        key->idx = -1;
        key->dp  = dp;
    }
    key->type = PK_PUBLIC;

    /* we're done */
    return CRYPT_OK;
error:
    mp_clear_multi(key->pubkey.x, key->pubkey.y, key->pubkey.z, key->k, NULL);
    return err;
}
#endif

/* $Source: /cvs/libtom/libtomcrypt/src/pk/ecc/ecc_ansi_x963_import.c,v $ */
/* $Revision: 1.11 $ */
/* $Date: 2007/05/12 14:32:35 $ */





/* $Source$ */
/* $Revision$ */
/* $Date$ */ 
