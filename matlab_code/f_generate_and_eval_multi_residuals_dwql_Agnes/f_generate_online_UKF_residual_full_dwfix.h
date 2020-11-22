/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * f_generate_online_UKF_residual_full_dwfix.h
 *
 * Code generation for function 'f_generate_online_UKF_residual_full_dwfix'
 *
 */

#ifndef F_GENERATE_ONLINE_UKF_RESIDUAL_FULL_DWFIX_H
#define F_GENERATE_ONLINE_UKF_RESIDUAL_FULL_DWFIX_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "f_generate_and_eval_multi_residuals_dwql_types.h"

/* Function Declarations */
extern void d_f_generate_online_UKF_residua(const emxArray_real_T *Probe_Ampl,
  const emxArray_real_T *Probe_Phase, const emxArray_real_T *Forw_Ampl, const
  emxArray_real_T *Forw_Phase, const emxArray_real_T *Refl_Ampl, const
  emxArray_real_T *Refl_Probe, double FS, const creal_T cal_coeff[4], const
  emxArray_real_T *dwfix, double QL_nom, const double MeasNoiseVar[4], const
  double ProcessVar[4], emxArray_real_T *res_full_mean, emxArray_real_T
  *res_full_Variance);

#endif

/* End of code generation (f_generate_online_UKF_residual_full_dwfix.h) */
