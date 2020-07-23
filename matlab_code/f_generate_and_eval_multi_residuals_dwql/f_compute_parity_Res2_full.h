/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * f_compute_parity_Res2_full.h
 *
 * Code generation for function 'f_compute_parity_Res2_full'
 *
 */

#ifndef F_COMPUTE_PARITY_RES2_FULL_H
#define F_COMPUTE_PARITY_RES2_FULL_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "f_generate_and_eval_multi_residuals_dwql_types.h"

/* Function Declarations */
extern void f_compute_parity_Res2_full(const emxArray_creal_T *u_mC, const
  emxArray_creal_T *y_mC, const double tau_m[4], const double K_m[4], double QL,
  double fs, emxArray_real_T *r_2);

#endif

/* End of code generation (f_compute_parity_Res2_full.h) */
