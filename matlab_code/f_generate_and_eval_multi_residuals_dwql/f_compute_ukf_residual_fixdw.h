/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * f_compute_ukf_residual_fixdw.h
 *
 * Code generation for function 'f_compute_ukf_residual_fixdw'
 *
 */

#ifndef F_COMPUTE_UKF_RESIDUAL_FIXDW_H
#define F_COMPUTE_UKF_RESIDUAL_FIXDW_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "f_generate_and_eval_multi_residuals_dwql_types.h"

/* Function Declarations */
extern void f_compute_ukf_residual_fixdw(const double MeasNoiseVar[4], const
  double ProcessVar[4], const emxArray_real_T *y_Meas, const emxArray_real_T
  *u_Meas, double fs, double QL, const emxArray_real_T *dw, emxArray_real_T
  *residual_mean, emxArray_real_T *residual_Variance, emxArray_real_T
  *residual_xi, emxArray_real_T *residual_Info);

#endif

/* End of code generation (f_compute_ukf_residual_fixdw.h) */
