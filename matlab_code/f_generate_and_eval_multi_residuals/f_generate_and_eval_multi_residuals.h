/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * f_generate_and_eval_multi_residuals.h
 *
 * Code generation for function 'f_generate_and_eval_multi_residuals'
 *
 */

#ifndef F_GENERATE_AND_EVAL_MULTI_RESIDUALS_H
#define F_GENERATE_AND_EVAL_MULTI_RESIDUALS_H

/* Include files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "f_generate_and_eval_multi_residuals_types.h"

/* Function Declarations */
extern void f_generate_and_eval_multi_residuals(const emxArray_real_T *PA,
  emxArray_real_T *PP, const emxArray_real_T *FA, const emxArray_real_T *FP,
  const emxArray_real_T *RA, const emxArray_real_T *RP, double FS, double F0,
  const creal_T cal_coeff[4], const double tau_m[4], const double K_m[4], const
  double X0[4], double QL_nom, const emxArray_real_T *dw_trace_nom, double DELAY,
  double FILLING, double FLATTOP, const double Sigma_nom_UKF[4], const double
  r_mean_nom_UKF[2], const double MeasNoiseVar[4], const double ProcessVar[36],
  double Sigma_nom_dw, const emxArray_real_T *r_PS1_nom, double Sigma_nom_PS1,
  emxArray_real_T *s_max_UKF, emxArray_real_T *s_max_dw, emxArray_real_T
  *s_max_PS1, emxArray_real_T *res_PS2, double *classis_UKF, double *classis_PS,
  double *classis_dw, double *strengthis_UKF, double *strengthis_PS, double
  *strengthis_dw, double *QL, double *dw_stat, double *SP_F, double *SP_P,
  double *PC, double *calib_check, double *dec_hq);

#endif

/* End of code generation (f_generate_and_eval_multi_residuals.h) */
