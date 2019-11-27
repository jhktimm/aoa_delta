/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: f_compute_parity_Res2_full.h
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 17-Nov-2019 17:33:56
 */

#ifndef F_COMPUTE_PARITY_RES2_FULL_H
#define F_COMPUTE_PARITY_RES2_FULL_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "f_generate_and_eval_multi_residuals_types.h"

/* Function Declarations */
extern void f_compute_parity_Res2_full(const emxArray_creal_T *u_mC, const
  emxArray_creal_T *y_mC, const double tau_m[4], const double K_m[4], double QL,
  double fs, emxArray_real_T *r_2);

#endif

/*
 * File trailer for f_compute_parity_Res2_full.h
 *
 * [EOF]
 */
