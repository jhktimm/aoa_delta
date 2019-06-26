/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * f_generate_online_UKF_residual_full.h
 *
 * Code generation for function 'f_generate_online_UKF_residual_full'
 *
 */

#ifndef F_GENERATE_ONLINE_UKF_RESIDUAL_FULL_H
#define F_GENERATE_ONLINE_UKF_RESIDUAL_FULL_H

/* Include files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "f_generate_and_eval_residual_types.h"

/* Function Declarations */
extern void c_f_generate_online_UKF_residua(const emxArray_real_T *Probe_Ampl,
  const emxArray_real_T *Probe_Phase, const emxArray_real_T *Forw_Ampl, const
  emxArray_real_T *Forw_Phase, const emxArray_real_T *Refl_Ampl, const
  emxArray_real_T *Refl_Probe, double FS, const creal_T cal_coeff[4], const
  double tau_m[4], const double K_m[4], const double X0[4], double QL_nom, const
  double MeasNoiseVar[4], const double ProcessVar[36], emxArray_real_T
  *res_full_mean, emxArray_real_T *res_full_Variance);

#endif

/* End of code generation (f_generate_online_UKF_residual_full.h) */
