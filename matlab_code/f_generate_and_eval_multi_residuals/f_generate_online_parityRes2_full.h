/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: f_generate_online_parityRes2_full.h
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 17-Nov-2019 17:33:56
 */

#ifndef F_GENERATE_ONLINE_PARITYRES2_FULL_H
#define F_GENERATE_ONLINE_PARITYRES2_FULL_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "f_generate_and_eval_multi_residuals_types.h"

/* Function Declarations */
extern void c_f_generate_online_parityRes2_(const emxArray_real_T *Probe_Ampl,
  const emxArray_real_T *Probe_Phase, const emxArray_real_T *Forw_Ampl, const
  emxArray_real_T *Forw_Phase, const emxArray_real_T *Refl_Ampl, const
  emxArray_real_T *Refl_Probe, double FS, const creal_T cal_coeff[4], const
  double tau_m[4], const double K_m[4], double QL_nom, emxArray_real_T
  *residual2);

#endif

/*
 * File trailer for f_generate_online_parityRes2_full.h
 *
 * [EOF]
 */
