/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: f_compute_ukf_residual_fixdw.h
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 11-Jun-2020 08:14:38
 */

#ifndef F_COMPUTE_UKF_RESIDUAL_FIXDW_H
#define F_COMPUTE_UKF_RESIDUAL_FIXDW_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "f_generate_and_eval_multi_residuals_dwfix_types.h"

/* Function Declarations */
extern void f_compute_ukf_residual_fixdw(const double MeasNoiseVar[4], const
  double ProcessVar[4], const emxArray_real_T *y_Meas, const emxArray_real_T
  *u_Meas, double fs, double QL, const emxArray_real_T *dw, emxArray_real_T
  *residual_mean, emxArray_real_T *residual_Variance, emxArray_real_T
  *residual_xi, emxArray_real_T *residual_Info);

#endif

/*
 * File trailer for f_compute_ukf_residual_fixdw.h
 *
 * [EOF]
 */
